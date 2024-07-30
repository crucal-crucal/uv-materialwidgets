#include "uvstackwidget.hpp"

#include <QPropertyAnimation>

#include "uvstackwidget_p.hpp"

/**
 * class CUVStackWidgetPrivate
 * @param q the pointer to the public class
 * @param parent the pointer to the parent class
 */
CUVStackWidgetPrivate::CUVStackWidgetPrivate(CUVStackWidget* q, QObject* parent): QObject(parent), q_ptr(q) {
	m_offset = 0;
	m_curIndex = 0;
	m_lastIndex = 0;
	m_duration = 500;
	m_moveDirection = CUVStackWidget::MoveDirection::Horizontal;
	m_pMoveAnimation = new QPropertyAnimation(q, "");
	m_pMoveAnimation->setDuration(m_duration);

	connect(m_pMoveAnimation, &QPropertyAnimation::valueChanged, this, &CUVStackWidgetPrivate::onValueChanged);
}

CUVStackWidgetPrivate::~CUVStackWidgetPrivate() = default;

void CUVStackWidgetPrivate::onValueChanged(const QVariant& value) {
	Q_Q(CUVStackWidget);

	m_offset = value.toInt();
	const bool isHorizontal = m_moveDirection == CUVStackWidget::MoveDirection::Horizontal;
	int ax = isHorizontal ? m_offset : 0;
	int ay = isHorizontal ? 0 : m_offset;
	m_WidgetList.at(m_curIndex)->move(ax, ay);
	if (m_curIndex != m_lastIndex) {
		if (isHorizontal) {
			ax = m_curIndex > m_lastIndex ? m_offset - q->width() : q->width() + m_offset;
			ay = 0;
		} else {
			ax = 0;
			ay = m_curIndex > m_lastIndex ? m_offset - q->height() : q->height() + m_offset;
		}
		m_WidgetList.at(m_lastIndex)->move(ax, ay);
	}
}

void CUVStackWidgetPrivate::moveAnimationStart() {
	Q_Q(CUVStackWidget);

	m_pMoveAnimation->stop();
	setWidgetsVisible();
	const int curOffset = m_moveDirection == CUVStackWidget::MoveDirection::Horizontal ? q->width() : q->height();
	int startOffset = m_offset;
	if (m_curIndex > m_lastIndex) {
		startOffset = startOffset == 0 ? curOffset : curOffset - qAbs(startOffset);
	} else {
		startOffset = startOffset == 0 ? -curOffset : -curOffset + qAbs(startOffset);
	}
	m_pMoveAnimation->setDuration(qAbs(startOffset) * m_duration / curOffset);
	m_pMoveAnimation->setStartValue(startOffset);
	m_pMoveAnimation->setEndValue(0);
	m_pMoveAnimation->start();
}

void CUVStackWidgetPrivate::setWidgetsVisible() const {
	for (int i = 0; i < m_WidgetList.size(); i++) {
		m_WidgetList.at(i)->setVisible(m_lastIndex == i || m_curIndex == i);
	}
}

/**
 * class CUVStackWidget
 * @param parent the parent widget
 */
CUVStackWidget::CUVStackWidget(QWidget* parent): QWidget(parent), d_ptr(new CUVStackWidgetPrivate(this, this)) {
}

CUVStackWidget::~CUVStackWidget() = default;

int CUVStackWidget::count() const {
	Q_D(const CUVStackWidget);

	return d->m_WidgetList.count();
}

int CUVStackWidget::currentIndex() const {
	Q_D(const CUVStackWidget);

	return d->m_curIndex;
}

int CUVStackWidget::indexOf(QWidget* widget) const {
	Q_D(const CUVStackWidget);

	return d->m_WidgetList.indexOf(widget);
}

QWidget* CUVStackWidget::currentWidget() const {
	Q_D(const CUVStackWidget);

	if (d->m_curIndex >= 0 && d->m_curIndex < d->m_WidgetList.size()) {
		return d->m_WidgetList.at(d->m_curIndex);
	}
	return nullptr;
}

QWidget* CUVStackWidget::widget(const int index) const {
	Q_D(const CUVStackWidget);
	if (index >= 0 && index < d->m_WidgetList.size()) {
		return d->m_WidgetList.at(index);
	}

	return nullptr;
}

int CUVStackWidget::addWidget(QWidget* widget) {
	Q_D(CUVStackWidget);

	if (const int index = this->indexOf(widget); index >= 0) {
		return index;
	}

	widget->setParent(this);
	d->m_WidgetList.append(widget);
	return d->m_WidgetList.size() - 1;
}

int CUVStackWidget::insertWidget(const int index, QWidget* widget) {
	Q_D(CUVStackWidget);

	if (const int curIndex = this->indexOf(widget); curIndex >= 0) {
		return curIndex;
	}

	widget->setParent(this);
	d->m_WidgetList.insert(index, widget);
	return index;
}

void CUVStackWidget::removeWidget(QWidget* widget) {
	Q_D(CUVStackWidget);

	if (const int index = this->indexOf(widget); index >= 0) {
		d->m_WidgetList.removeAll(widget);
		emit widgetRemoved(index);
	}
}

void CUVStackWidget::removeWidget(const int index) {
	Q_D(CUVStackWidget);
	if (index >= 0 && index < d->m_WidgetList.size()) {
		d->m_WidgetList.removeAt(index);
		emit widgetRemoved(index);
	}
}

void CUVStackWidget::setDuration(const int duration) {
	Q_D(CUVStackWidget);

	d->m_duration = duration;
}

void CUVStackWidget::setMoveDirection(const MoveDirection& move_direction) {
	Q_D(CUVStackWidget);

	d->m_moveDirection = move_direction;
}

void CUVStackWidget::setCurrentIndex(const int index) {
	Q_D(CUVStackWidget);

	if (index >= 0 && d->m_curIndex != index) {
		d->m_lastIndex = d->m_curIndex;
		d->m_curIndex = index;
		d->moveAnimationStart();
		emit currentChanged(index);
	}
}

void CUVStackWidget::setCurrentWidget(QWidget* widget) {
	Q_D(CUVStackWidget);

	if (const int index = this->indexOf(widget); index >= 0 && d->m_curIndex != index) {
		setCurrentIndex(index);
	}
}

void CUVStackWidget::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);

	Q_D(CUVStackWidget);

	for (const auto& widget: d->m_WidgetList) {
		widget->resize(this->width(), this->height());
	}

	if (d->m_pMoveAnimation->state() == QAbstractAnimation::Running) {
		d->moveAnimationStart();
	} else {
		d->setWidgetsVisible();
		d->onValueChanged(0);
	}
}
