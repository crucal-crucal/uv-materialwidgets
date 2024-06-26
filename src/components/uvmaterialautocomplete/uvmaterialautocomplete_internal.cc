﻿#include "uvmaterialautocomplete_internal.hpp"

#include <QDebug>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QtWidgets/QGraphicsOpacityEffect>

/*!
 *  \class CUVMaterialAutoCompleteStateMachine
 */
CUVMaterialAutoCompleteStateMachine::CUVMaterialAutoCompleteStateMachine(QWidget* menu)
: QStateMachine(menu), m_menu(menu), m_closedState(new QState), m_openState(new QState), m_closingState(new QState) {
	Q_ASSERT(menu);

	addState(m_closedState);
	addState(m_openState);
	addState(m_closingState);
	setInitialState(m_closedState);

	auto transition = new QSignalTransition(this, &CUVMaterialAutoCompleteStateMachine::shouldOpen);
	transition->setTargetState(m_openState);
	m_closedState->addTransition(transition);

	transition = new QSignalTransition(this, &CUVMaterialAutoCompleteStateMachine::shouldClose);
	transition->setTargetState(m_closedState);
	m_openState->addTransition(transition);

	transition = new QSignalTransition(this, &CUVMaterialAutoCompleteStateMachine::shouldFade);
	transition->setTargetState(m_closingState);
	m_openState->addTransition(transition);

	m_closedState->assignProperty(menu, "visible", false);
	m_openState->assignProperty(menu, "visible", true);

	const auto effect = new QGraphicsOpacityEffect;
	menu->setGraphicsEffect(effect);

	m_openState->assignProperty(effect, "opacity", 1);
	m_closingState->assignProperty(effect, "opacity", 0);
	m_closedState->assignProperty(effect, "opacity", 0);

	const auto animation = new QPropertyAnimation(effect, "opacity", this);
	animation->setDuration(240);
	addDefaultAnimation(animation);

	transition = new QSignalTransition(animation, &QPropertyAnimation::finished);
	transition->setTargetState(m_closedState);
	m_closingState->addTransition(transition);
}

CUVMaterialAutoCompleteStateMachine::~CUVMaterialAutoCompleteStateMachine() = default;
