#include "uvmaterialdialog.hpp"

#include <QPainter>
#include <QPropertyAnimation>
#include <QStateMachine>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QStackedLayout>

#include "uvmaterialdialog_internal.hpp"
#include "uvmaterialdialog_p.hpp"
#include "uvmaterialshared/uvmaterialstatetransition.hpp"

/*!
 *  \class CUVMaterialDialogPrivate
 *  \internal
 */
CUVMaterialDialogPrivate::CUVMaterialDialogPrivate(CUVMaterialDialog* q): q_ptr(q) {
}

CUVMaterialDialogPrivate::~CUVMaterialDialogPrivate() = default;

void CUVMaterialDialogPrivate::init() {
	Q_Q(CUVMaterialDialog);

	dialogWindow = new CUVMaterialDialogWindow(q);
	proxyStack = new QStackedLayout;
	stateMachine = new QStateMachine(q);
	proxy = new CUVMaterialDialogProxy(dialogWindow, proxyStack, q);

	const auto layout = new QVBoxLayout;
	q->setLayout(layout);

	const auto widget = new QWidget;
	widget->setLayout(proxyStack);
	widget->setMinimumWidth(400);

	const auto effect = new QGraphicsDropShadowEffect;
	effect->setColor(QColor(0, 0, 0, 200));
	effect->setBlurRadius(64);
	effect->setOffset(0, 13);
	widget->setGraphicsEffect(effect);

	layout->addWidget(widget);
	layout->setAlignment(widget, Qt::AlignCenter);

	proxyStack->addWidget(dialogWindow);
	proxyStack->addWidget(proxy);
	proxyStack->setCurrentIndex(1);

	q->setAttribute(Qt::WA_TransparentForMouseEvents);

	const auto hiddenState = new QState;
	const auto visibleState = new QState;

	stateMachine->addState(hiddenState);
	stateMachine->addState(visibleState);
	stateMachine->setInitialState(hiddenState);

	auto transition = new CUVMaterialStateTransition(DialogShowTransition);
	transition->setTargetState(visibleState);
	hiddenState->addTransition(transition);

	transition = new CUVMaterialStateTransition(DialogHideTransition);
	transition->setTargetState(hiddenState);
	visibleState->addTransition(transition);

	visibleState->assignProperty(proxy, "opacity", 1);
	visibleState->assignProperty(effect, "color", QColor(0, 0, 0, 200));
	visibleState->assignProperty(dialogWindow, "offset", 0);
	hiddenState->assignProperty(proxy, "opacity", 0);
	hiddenState->assignProperty(effect, "color", QColor(0, 0, 0, 0));
	hiddenState->assignProperty(dialogWindow, "offset", 200);

	auto animation = new QPropertyAnimation(proxy, "opacity", q);
	animation->setDuration(280);
	stateMachine->addDefaultAnimation(animation);

	animation = new QPropertyAnimation(effect, "color", q);
	animation->setDuration(280);
	stateMachine->addDefaultAnimation(animation);

	animation = new QPropertyAnimation(dialogWindow, "offset", q);
	animation->setDuration(280);
	animation->setEasingCurve(QEasingCurve::OutCirc);
	stateMachine->addDefaultAnimation(animation);

	QObject::connect(visibleState, &QState::propertiesAssigned, proxy, &CUVMaterialDialogProxy::makeOpaque);
	QObject::connect(hiddenState, &QState::propertiesAssigned, proxy, &CUVMaterialDialogProxy::makeTransparent);

	stateMachine->start();
	QCoreApplication::processEvents();
}

/*!
 *  \class CUVMaterialDialog
 */
CUVMaterialDialog::CUVMaterialDialog(QWidget* parent)
: CUVMaterialOverlayWidget(parent), d_ptr(new CUVMaterialDialogPrivate(this)) {
	d_func()->init();
}

CUVMaterialDialog::~CUVMaterialDialog() = default;

QLayout* CUVMaterialDialog::windowLayout() const {
	Q_D(const CUVMaterialDialog);

	return d->dialogWindow->layout();
}

void CUVMaterialDialog::setWindowLayout(QLayout* layout) {
	Q_D(CUVMaterialDialog);

	d->dialogWindow->setLayout(layout);
}

void CUVMaterialDialog::showDialog() {
	Q_D(CUVMaterialDialog);

	d->stateMachine->postEvent(new CUVMaterialStateTransitionEvent(DialogShowTransition));
	raise();
}

void CUVMaterialDialog::hideDialog() {
	Q_D(CUVMaterialDialog);

	d->stateMachine->postEvent(new CUVMaterialStateTransitionEvent(DialogHideTransition));
	setAttribute(Qt::WA_TransparentForMouseEvents);
	d->proxyStack->setCurrentIndex(1);
}

void CUVMaterialDialog::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	Q_D(CUVMaterialDialog);

	QPainter painter(this);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::black);
	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);
	painter.setOpacity(d->proxy->opacity() / 2.4);
	painter.drawRect(rect());
}
