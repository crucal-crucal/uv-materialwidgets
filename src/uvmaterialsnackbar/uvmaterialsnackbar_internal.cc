#include "uvmaterialsnackbar_internal.hpp"

#include <QDebug>
#include <QPropertyAnimation>

#include "uvmaterialsnackbar.hpp"
#include "uvmaterialshared/uvmaterialstatetransition.hpp"

CUVMaterialSnackbarStateMachine::CUVMaterialSnackbarStateMachine(CUVMaterialSnackbar* parent, const CUVMaterialSnackbar::SnackBarPosition& position)
: QStateMachine(parent), m_snackbar(parent), m_position(position) {
	m_timer.setSingleShot(true);

	m_hiddenState = new QState;
	m_visibleState = new QState;
	m_finalState = new QState;

	addState(m_hiddenState);
	addState(m_visibleState);
	addState(m_finalState);

	setInitialState(m_hiddenState);

	auto transition = new CUVMaterialStateTransition(SnackbarShowTransition);
	transition->setTargetState(m_visibleState);
	m_hiddenState->addTransition(transition);

	transition = new CUVMaterialStateTransition(SnackbarHideTransition);
	transition->setTargetState(m_visibleState);
	m_hiddenState->addTransition(transition);

	transition = new CUVMaterialStateTransition(SnackbarHideTransition);
	transition->setTargetState(m_finalState);
	m_visibleState->addTransition(transition);

	transition = new CUVMaterialStateTransition(SnackbarWaitTransition);
	transition->setTargetState(m_hiddenState);
	m_finalState->addTransition(transition);

	transition = new CUVMaterialStateTransition(SnackbarNextTransition);
	transition->setTargetState(m_visibleState);
	m_finalState->addTransition(transition);

	connect(m_visibleState, &QState::propertiesAssigned, this, &CUVMaterialSnackbarStateMachine::snackbarShown);
	connect(m_finalState, &QState::propertiesAssigned, m_snackbar, &CUVMaterialSnackbar::dequeue);

	const auto animation = new QPropertyAnimation(this, "offset", this);
	animation->setEasingCurve(QEasingCurve::OutCubic);
	animation->setDuration(300);
	addDefaultAnimation(animation);

	setStateProperty();

	connect(&m_timer, &QTimer::timeout, this, &CUVMaterialSnackbarStateMachine::progress);

	m_snackbar->installEventFilter(this);
}

CUVMaterialSnackbarStateMachine::~CUVMaterialSnackbarStateMachine() = default;

bool CUVMaterialSnackbarStateMachine::eventFilter(QObject* watched, QEvent* event) {
	if (QEvent::MouseButtonPress == event->type() && m_snackbar->clickToDismissMode()) {
		progress();
	}
	return QStateMachine::eventFilter(watched, event);
}

void CUVMaterialSnackbarStateMachine::setStateProperty() {
	if (m_position == CUVMaterialSnackbar::TOP) {
		m_hiddenState->assignProperty(this, "offset", 0);
		m_visibleState->assignProperty(this, "offset", 1);
		m_finalState->assignProperty(this, "offset", 0);
	} else if (m_position == CUVMaterialSnackbar::BOTTOM) {
		m_hiddenState->assignProperty(this, "offset", 1);
		m_visibleState->assignProperty(this, "offset", 0);
		m_finalState->assignProperty(this, "offset", 1);
	}
}

void CUVMaterialSnackbarStateMachine::setOffset(const qreal offset) {
	m_offset = offset;
	m_snackbar->update();
}

void CUVMaterialSnackbarStateMachine::setPosition(const CUVMaterialSnackbar::SnackBarPosition position) {
	m_position = position;
	this->setStateProperty();
}

void CUVMaterialSnackbarStateMachine::progress() {
	m_timer.stop();
	postEvent(new CUVMaterialStateTransitionEvent(SnackbarHideTransition));
	if (m_snackbar->clickToDismissMode()) {
		m_snackbar->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	}
}

void CUVMaterialSnackbarStateMachine::snackbarShown() {
	m_timer.start(m_snackbar->autoHideDuration());
	if (m_snackbar->clickToDismissMode()) {
		m_snackbar->setAttribute(Qt::WA_TransparentForMouseEvents, false);
	}
}
