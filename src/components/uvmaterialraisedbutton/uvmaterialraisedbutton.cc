#include "uvmaterialraisedbutton.hpp"

#include <QEventTransition>
#include <QPropertyAnimation>
#include <QStateMachine>
#include <QtWidgets/QGraphicsDropShadowEffect>

#include "uvmaterialraisedbutton_p.hpp"

/*!
 *  \class CUVMaterialRaisedButtonPrivate
 *  \internal
 */
CUVMaterialRaisedButtonPrivate::CUVMaterialRaisedButtonPrivate(CUVMaterialRaisedButton* q)
: CUVMaterialFlatButtonPrivate(q) {
}

CUVMaterialRaisedButtonPrivate::~CUVMaterialRaisedButtonPrivate() = default;

void CUVMaterialRaisedButtonPrivate::init() {
	Q_Q(CUVMaterialRaisedButton);

	shadowStateMachine = new QStateMachine(q);
	normalState = new QState;
	pressedState = new QState;
	effect = new QGraphicsDropShadowEffect;

	effect->setBlurRadius(7);
	effect->setOffset(QPointF(0, 2));
	effect->setColor(QColor(0, 0, 0, 75));

	q->setBackgroundMode(Qt::OpaqueMode);
	q->setMinimumHeight(42);
	q->setGraphicsEffect(effect);
	q->setBaseOpacity(0.3);

	shadowStateMachine->addState(normalState);
	shadowStateMachine->addState(pressedState);

	normalState->assignProperty(effect, "offset", QPointF(0, 2));
	normalState->assignProperty(effect, "blurRadius", 7);

	pressedState->assignProperty(effect, "offset", QPointF(0, 5));
	pressedState->assignProperty(effect, "blurRadius", 29);

	QAbstractTransition* transition = new QEventTransition(q, QEvent::MouseButtonPress);
	transition->setTargetState(pressedState);
	normalState->addTransition(transition);

	transition = new QEventTransition(q, QEvent::MouseButtonDblClick);
	transition->setTargetState(pressedState);
	normalState->addTransition(transition);

	transition = new QEventTransition(q, QEvent::MouseButtonRelease);
	transition->setTargetState(normalState);
	pressedState->addTransition(transition);

	auto animation = new QPropertyAnimation(effect, "offset", q);
	animation->setDuration(100);
	shadowStateMachine->addDefaultAnimation(animation);

	animation = new QPropertyAnimation(effect, "blurRadius", q);
	animation->setDuration(100);
	shadowStateMachine->addDefaultAnimation(animation);

	shadowStateMachine->setInitialState(normalState);
	shadowStateMachine->start();
}

/*!
 *  \class CUVMaterialRaisedButton
 */
CUVMaterialRaisedButton::CUVMaterialRaisedButton(QWidget* parent)
: CUVMaterialFlatButton(*new CUVMaterialRaisedButtonPrivate(this), parent) {
	d_func()->init();
}

CUVMaterialRaisedButton::CUVMaterialRaisedButton(const QString& text, QWidget* parent)
: CUVMaterialFlatButton(*new CUVMaterialRaisedButtonPrivate(this), parent) {
	d_func()->init();

	setText(text);
}

CUVMaterialRaisedButton::~CUVMaterialRaisedButton() = default;

CUVMaterialRaisedButton::CUVMaterialRaisedButton(CUVMaterialRaisedButtonPrivate& d, QWidget* parent): CUVMaterialFlatButton(d, parent) {
	d_func()->init();
}

bool CUVMaterialRaisedButton::event(QEvent* event) {
	Q_D(CUVMaterialRaisedButton);

	if (QEvent::EnabledChange == event->type()) {
		if (isEnabled()) {
			d->shadowStateMachine->start();
			d->effect->setEnabled(true);
		} else {
			d->shadowStateMachine->stop();
			d->effect->setEnabled(false);
		}
	}
	return CUVMaterialFlatButton::event(event);
}
