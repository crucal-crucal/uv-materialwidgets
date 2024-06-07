﻿#include "uvmaterialtextfield_internal.hpp"

#include <QEventTransition>
#include <QPainter>
#include <QPropertyAnimation>

#include "uvmaterialtextfield.hpp"

/*!
 *  \class CUVMaterialTextFieldStateMachine
 *  \internal
 */
CUVMaterialTextFieldStateMachine::CUVMaterialTextFieldStateMachine(CUVMaterialTextField* parent)
: QStateMachine(parent), m_textField(parent), m_normalState(new QState), m_focusedState(new QState),
  m_label(nullptr), m_offsetAnimation(nullptr), m_colorAnimation(nullptr), m_progress(0.0) {
	Q_ASSERT(parent);

	addState(m_normalState);
	addState(m_focusedState);

	setInitialState(m_normalState);

	auto transition = new QEventTransition(parent, QEvent::FocusIn);
	transition->setTargetState(m_focusedState);
	m_normalState->addTransition(transition);

	auto animation = new QPropertyAnimation(this, "progress", this);
	animation->setEasingCurve(QEasingCurve::InCubic);
	animation->setDuration(310);
	transition->addAnimation(animation);

	transition = new QEventTransition(parent, QEvent::FocusOut);
	transition->setTargetState(m_normalState);
	m_focusedState->addTransition(transition);

	animation = new QPropertyAnimation(this, "progress", this);
	animation->setEasingCurve(QEasingCurve::OutCubic);
	animation->setDuration(310);
	transition->addAnimation(animation);

	m_normalState->assignProperty(this, "progress", 0);
	m_focusedState->assignProperty(this, "progress", 1);

	setupProperties();

	connect(m_textField, &CUVMaterialTextField::textChanged, this, &CUVMaterialTextFieldStateMachine::setupProperties);
}

CUVMaterialTextFieldStateMachine::~CUVMaterialTextFieldStateMachine() = default;

void CUVMaterialTextFieldStateMachine::setLabel(CUVMaterialTextFieldLabel* label) {
	if (m_offsetAnimation) {
		removeDefaultAnimation(m_offsetAnimation);
		delete m_offsetAnimation;
	}

	if (m_colorAnimation) {
		removeDefaultAnimation(m_colorAnimation);
		delete m_colorAnimation;
	}

	m_label.reset(label);

	if (m_label) {
		m_offsetAnimation = new QPropertyAnimation(m_label.get(), "offset", this);
		m_offsetAnimation->setDuration(210);
		m_offsetAnimation->setEasingCurve(QEasingCurve::OutCubic);
		addDefaultAnimation(m_offsetAnimation);

		m_colorAnimation = new QPropertyAnimation(m_label.get(), "color", this);
		m_colorAnimation->setDuration(210);
		addDefaultAnimation(m_colorAnimation);
	}

	setupProperties();
}

void CUVMaterialTextFieldStateMachine::setProgress(const qreal progress) {
	m_progress = progress;
	m_textField->update();
}

qreal CUVMaterialTextFieldStateMachine::progress() const {
	return m_progress;
}

void CUVMaterialTextFieldStateMachine::setupProperties(const QString& text) const {
	Q_UNUSED(text)
	if (m_label) {
		const int m = m_textField->textMargins().top();

		if (m_textField->text().isEmpty()) {
			m_normalState->assignProperty(m_label.get(), "offset", QPointF(0, 26));
		} else {
			m_normalState->assignProperty(m_label.get(), "offset", QPointF(0, 0 - m));
		}

		m_focusedState->assignProperty(m_label.get(), "offset", QPointF(0, 0 - m));
		m_focusedState->assignProperty(m_label.get(), "color", m_textField->inkColor());
		m_normalState->assignProperty(m_label.get(), "color", m_textField->labelColor());

		if (0 != m_label->offset().y() && !m_textField->text().isEmpty()) {
			m_label->setOffset(QPointF(0, 0 - m));
		} else if (!m_textField->hasFocus() && m_label->offset().y() <= 0 && m_textField->text().isEmpty()) {
			m_label->setOffset(QPointF(0, 26));
		}
	}

	m_textField->update();
}

/*!
 *  \class CUVMaterialTextFieldLabel
 *  \internal
 */
CUVMaterialTextFieldLabel::CUVMaterialTextFieldLabel(CUVMaterialTextField* parent)
: QWidget(parent), m_textField(parent), m_scale(1), m_posX(0), m_posY(26), m_color(parent->labelColor()) {
	Q_ASSERT(parent);

	QFont font("Roboto", static_cast<int>(parent->labelFontSize()), QFont::Medium);
	font.setLetterSpacing(QFont::PercentageSpacing, 102);
	setFont(font);
}

CUVMaterialTextFieldLabel::~CUVMaterialTextFieldLabel() = default;

/*!
 *  \reimp
 */
void CUVMaterialTextFieldLabel::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	if (!m_textField->hasLabel()) {
		return;
	}

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.scale(m_scale, m_scale);
	painter.setPen(m_color);
	painter.setOpacity(1);

	const QPointF pos(2 + m_posX, height() - 36 + m_posY);
	painter.drawText(static_cast<int>(pos.x()), static_cast<int>(pos.y()), m_textField->label());
}
