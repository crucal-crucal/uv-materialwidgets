#include "uvmaterialdrawer_internal.hpp"

#include <QPainter>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QState>
#include <QtWidgets/QLayout>

#include "uvmaterialdrawer.hpp"

/*!
 *  \class CUVMaterialDrawerStateMachine
 *  \internal
 */
CUVMaterialDrawerStateMachine::CUVMaterialDrawerStateMachine(CUVMaterialDrawerWidget* drawer, CUVMaterialDrawer* parent)
: QStateMachine(parent), m_drawer(drawer), m_main(parent), m_openingState(new QState), m_openedState(new QState),
  m_closingState(new QState), m_closedState(new QState), m_opacity(0) {
	addState(m_openingState);
	addState(m_openedState);
	addState(m_closingState);
	addState(m_closedState);

	setInitialState(m_closedState);

	auto transition = new QSignalTransition(this, &CUVMaterialDrawerStateMachine::signalOpen);
	transition->setTargetState(m_openingState);
	m_closedState->addTransition(transition);

	auto animation = new QPropertyAnimation(drawer, "offset", this);
	animation->setDuration(220);
	animation->setEasingCurve(QEasingCurve::OutCirc);
	transition->addAnimation(animation);

	animation = new QPropertyAnimation(this, "opacity", this);
	animation->setDuration(220);
	transition->addAnimation(animation);

	transition = new QSignalTransition(animation, &QAbstractAnimation::finished);
	transition->setTargetState(m_openedState);
	m_openingState->addTransition(transition);

	transition = new QSignalTransition(this, &CUVMaterialDrawerStateMachine::signalClose);
	transition->setTargetState(m_closingState);
	m_openingState->addTransition(transition);

	animation = new QPropertyAnimation(this, "opacity", this);
	animation->setDuration(220);
	transition->addAnimation(animation);

	animation = new QPropertyAnimation(drawer, "offset", this);
	animation->setDuration(220);
	animation->setEasingCurve(QEasingCurve::InCirc);
	transition->addAnimation(animation);

	transition = new QSignalTransition(animation, &QAbstractAnimation::finished);
	transition->setTargetState(m_closedState);
	m_closingState->addTransition(transition);

	transition = new QSignalTransition(this, &CUVMaterialDrawerStateMachine::signalClose);
	transition->setTargetState(m_closingState);
	m_openedState->addTransition(transition);

	animation = new QPropertyAnimation(drawer, "offset", this);
	animation->setDuration(220);
	animation->setEasingCurve(QEasingCurve::InCirc);
	transition->addAnimation(animation);

	animation = new QPropertyAnimation(this, "opacity", this);
	animation->setDuration(220);
	transition->addAnimation(animation);

	transition = new QSignalTransition(animation, &QAbstractAnimation::finished);
	transition->setTargetState(m_closedState);
	m_closingState->addTransition(transition);

	updatePropertyAssignments();
}

CUVMaterialDrawerStateMachine::~CUVMaterialDrawerStateMachine() = default;

void CUVMaterialDrawerStateMachine::setOpacity(const qreal opacity) {
	m_opacity = opacity;
	m_main->update();
}

bool CUVMaterialDrawerStateMachine::isInClosedState() const {
	return m_closedState->active();
}

void CUVMaterialDrawerStateMachine::updatePropertyAssignments() {
	const qreal closedOffset = -(m_drawer->width() + 32);

	m_closingState->assignProperty(m_drawer, "offset", closedOffset);
	m_closedState->assignProperty(m_drawer, "offset", closedOffset);

	m_closingState->assignProperty(this, "opacity", 0);
	m_closedState->assignProperty(this, "opacity", 0);

	m_openingState->assignProperty(m_drawer, "offset", 0);
	m_openingState->assignProperty(this, "opacity", 0.4);
}

/*!
 *  \class CUVMaterialDrawerWidget
 *  \internal
 */
CUVMaterialDrawerWidget::CUVMaterialDrawerWidget(QWidget* parent)
: CUVMaterialOverlayWidget(parent), m_offset(0) {
}

CUVMaterialDrawerWidget::~CUVMaterialDrawerWidget() = default;

void CUVMaterialDrawerWidget::setOffset(const int offset) {
	m_offset = offset;

	if (const QWidget* widget = parentWidget()) {
		setGeometry(widget->rect().translated(offset, 0));
	}
	update();
}

void CUVMaterialDrawerWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	QPainter painter(this);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::white);
	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);

	painter.drawRect(rect().adjusted(0, 0, -16, 0));

	QLinearGradient gradient(QPointF(width() - 16, 0), QPointF(width(), 0));
	gradient.setColorAt(0, QColor(0, 0, 0, 80));
	gradient.setColorAt(0.5, QColor(0, 0, 0, 20));
	gradient.setColorAt(1, QColor(0, 0, 0, 0));
	painter.setBrush(QBrush(gradient));

	painter.drawRect(width() - 16, 0, 16, height());
}

QRect CUVMaterialDrawerWidget::overlayGeometry() const {
	return CUVMaterialOverlayWidget::overlayGeometry().translated(m_offset, 0);
}
