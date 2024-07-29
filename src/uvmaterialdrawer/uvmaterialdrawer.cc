#include "uvmaterialdrawer.hpp"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLayout>
#include <QtWidgets/QVBoxLayout>

#include "uvmaterialdrawer_internal.hpp"
#include "uvmaterialdrawer_p.hpp"

/*!
 *  \class CUVMaterialDrawerPrivate
 *  \internal
 */
CUVMaterialDrawerPrivate::CUVMaterialDrawerPrivate(CUVMaterialDrawer* q): q_ptr(q) {
}

CUVMaterialDrawerPrivate::~CUVMaterialDrawerPrivate() = default;

void CUVMaterialDrawerPrivate::init() {
	Q_Q(CUVMaterialDrawer);

	widget = new CUVMaterialDrawerWidget;
	stateMachine = new CUVMaterialDrawerStateMachine(widget, q);
	window = new QWidget;
	width = 250;
	clickToClose = false;
	autoRaise = true;
	closed = true;
	overlay = false;

	const auto layout = new QVBoxLayout;
	layout->addWidget(window);

	widget->setLayout(layout);
	widget->setFixedWidth(width + 16);

	widget->setParent(q);

	stateMachine->start();
	QCoreApplication::processEvents();
}

/*!
 *  \class CUVMaterialDrawer
 */
CUVMaterialDrawer::CUVMaterialDrawer(QWidget* parent)
: CUVMaterialOverlayWidget(parent), d_ptr(new CUVMaterialDrawerPrivate(this)) {
	d_func()->init();
}

CUVMaterialDrawer::~CUVMaterialDrawer() = default;

void CUVMaterialDrawer::setDrawerWidth(const int width) {
	Q_D(CUVMaterialDrawer);

	d->width = width;
	d->stateMachine->updatePropertyAssignments();
	d->widget->setFixedWidth(width + 16);
}

int CUVMaterialDrawer::drawerWidth() const {
	Q_D(const CUVMaterialDrawer);

	return d->width;
}

void CUVMaterialDrawer::setDrawerLayout(QLayout* layout) {
	Q_D(CUVMaterialDrawer);

	d->window->setLayout(layout);
}

QLayout* CUVMaterialDrawer::drawerLayout() const {
	Q_D(const CUVMaterialDrawer);

	return d->window->layout();
}

void CUVMaterialDrawer::setClickOutsideToClose(const bool state) {
	Q_D(CUVMaterialDrawer);

	d->clickToClose = state;
}

bool CUVMaterialDrawer::clickOutsideToClose() const {
	Q_D(const CUVMaterialDrawer);

	return d->clickToClose;
}

void CUVMaterialDrawer::setAutoRaise(const bool state) {
	Q_D(CUVMaterialDrawer);

	d->autoRaise = state;
}

bool CUVMaterialDrawer::autoRaise() const {
	Q_D(const CUVMaterialDrawer);

	return d->autoRaise;
}

void CUVMaterialDrawer::setOverlayMode(const bool value) {
	Q_D(CUVMaterialDrawer);

	d->overlay = value;
	update();
}

bool CUVMaterialDrawer::overlayMode() const {
	Q_D(const CUVMaterialDrawer);

	return d->overlay;
}

void CUVMaterialDrawer::openDrawer() {
	Q_D(CUVMaterialDrawer);

	emit d->stateMachine->signalOpen();

	if (d->autoRaise) {
		raise();
	}
	setAttribute(Qt::WA_TransparentForMouseEvents, false);
	setAttribute(Qt::WA_NoSystemBackground, false);
}

void CUVMaterialDrawer::closeDrawer() {
	Q_D(CUVMaterialDrawer);

	emit d->stateMachine->signalClose();

	if (d->overlay) {
		setAttribute(Qt::WA_TransparentForMouseEvents);
		setAttribute(Qt::WA_NoSystemBackground);
	}
}

bool CUVMaterialDrawer::event(QEvent* event) {
	Q_D(CUVMaterialDrawer);

	switch (event->type()) {
		case QEvent::Move:
		case QEvent::Resize:
			if (!d->overlay) {
				setMask(QRegion(d->widget->rect()));
			}
			break;
		default:
			break;
	}
	return CUVMaterialOverlayWidget::event(event);
}

bool CUVMaterialDrawer::eventFilter(QObject* watched, QEvent* event) {
	Q_D(CUVMaterialDrawer);
	if (!event) {
		return false;
	}
	switch (event->type()) {
		case QEvent::MouseButtonPress: {
			if (const auto mouseEvent = dynamic_cast<QMouseEvent*>(event)) {
				if (const bool canClose = d->clickToClose || d->overlay; !d->widget->geometry().contains(mouseEvent->pos()) && canClose) {
					closeDrawer();
				}
			}
			break;
		}
		case QEvent::Move:
		case QEvent::Resize: {
			if (QLayout* lw = d->widget->layout(); lw && 16 != lw->contentsMargins().right()) {
				lw->setContentsMargins(0, 0, 16, 0);
			}
			break;
		}
		default:
			break;
	}
	return CUVMaterialOverlayWidget::eventFilter(watched, event);
}

void CUVMaterialDrawer::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	Q_D(CUVMaterialDrawer);

	if (!d->overlay || d->stateMachine->isInClosedState()) {
		return;
	}
	QPainter painter(this);
	painter.setOpacity(d->stateMachine->opacity());
	painter.fillRect(rect(), Qt::SolidPattern);
}
