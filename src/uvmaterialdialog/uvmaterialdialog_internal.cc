#include "uvmaterialdialog_internal.hpp"

#include <QEvent>
#include <QPainter>
#include <QPixmap>
#include <QtWidgets/QStackedLayout>

#include "uvmaterialdialog.hpp"

/*!
 *  \class CUVMaterialDialogProxy
 *  \internal
 */
CUVMaterialDialogProxy::CUVMaterialDialogProxy(CUVMaterialDialogWindow* source, QStackedLayout* layout, CUVMaterialDialog* dialog, QWidget* parent)
: QWidget(parent), m_source(source), m_layout(layout), m_dialog(dialog), m_opacity(0), m_mode(Transparent) {
}

CUVMaterialDialogProxy::~CUVMaterialDialogProxy() = default;

void CUVMaterialDialogProxy::setOpacity(const qreal opacity) {
	m_opacity = opacity;
	m_mode = SemiTransparent;
	update();
	m_dialog->update();
}

void CUVMaterialDialogProxy::makeOpaque() {
	m_dialog->setAttribute(Qt::WA_TransparentForMouseEvents, false);
	m_layout->setCurrentIndex(0);
	m_opacity = 1.0;
	m_mode = Opaque;
	update();
}

void CUVMaterialDialogProxy::makeTransparent() {
	m_opacity = 0.0;
	m_mode = Transparent;
	update();
}

QSize CUVMaterialDialogProxy::sizeHint() const {
	return m_source->sizeHint();
}

bool CUVMaterialDialogProxy::event(QEvent* event) {
	if (const QEvent::Type type = event->type(); QEvent::Move == type || QEvent::Resize == type) {
		m_source->setGeometry(geometry());
	}
	return QWidget::event(event);
}

void CUVMaterialDialogProxy::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	QPainter painter(this);

	if (Transparent == m_mode) {
		return;
	} else if (Opaque != m_mode) {
		painter.setOpacity(m_opacity);
	}
	const QPixmap pm = m_source->grab(m_source->rect());
	painter.drawPixmap(0, 0, pm);
}

/*!
 *  \class CUVMaterialDialogWindow
 *  \internal
 */
CUVMaterialDialogWindow::CUVMaterialDialogWindow(CUVMaterialDialog* dialog, QWidget* parent)
: QWidget(parent), m_dialog(dialog) {
}

CUVMaterialDialogWindow::~CUVMaterialDialogWindow() = default;

void CUVMaterialDialogWindow::setOffset(const int offset) const {
	QMargins margins = m_dialog->layout()->contentsMargins();
	margins.setBottom(offset);
	m_dialog->layout()->setContentsMargins(margins);
}

int CUVMaterialDialogWindow::offset() const {
	return m_dialog->layout()->contentsMargins().bottom();
}

void CUVMaterialDialogWindow::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	QPainter painter(this);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::white);
	painter.setPen(Qt::NoPen);
	painter.setBrush(brush);
	painter.drawRect(rect());
}
