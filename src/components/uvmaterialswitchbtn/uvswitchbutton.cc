#include "uvswitchbutton.hpp"

#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>

CUVSwitchButton::CUVSwitchButton(QWidget* parent) : QWidget(parent) {
	init();
}

void CUVSwitchButton::drawBackGround(QPainter* painter) const {
	painter->save();
	painter->setPen(Qt::NoPen);

	QColor bgColor = m_checked ? m_bgColorOn : m_bgColorOff;
	if (isEnabled()) {
		bgColor.setAlpha(255);
	}
	painter->setBrush(bgColor);

	const QPainterPath path = getBackgroundPath(getBackgroundRect());
	painter->drawPath(path);

	painter->restore();
}

void CUVSwitchButton::drawSlider(QPainter* painter) const {
	painter->save();
	painter->setPen(Qt::NoPen);

	const QColor color = m_checked ? m_sliderColorOn : m_sliderColorOff;

	painter->setBrush(QBrush(color));

	painter->drawEllipse(getSliderRect());

	painter->restore();
}

void CUVSwitchButton::drawText(QPainter* painter) const {
	painter->save();
	painter->setPen(Qt::NoPen);
	// 绘制文本
	if (m_showText) {
		painter->setPen(m_checked ? QPen(m_textColorOn) : QPen(m_textColorOff));
		painter->drawText(getTextRect(m_textPostion, m_checked), Qt::AlignCenter, m_checked ? m_textOn : m_textOff);
	}

	painter->restore();
}

int CUVSwitchButton::getTextWidth() const {
	if (m_showText) {
		return std::max(fontMetrics().boundingRect(m_textOn).width(), fontMetrics().boundingRect(m_textOff).width()) + m_spaceText;
	}
	return 0;
}

QRect CUVSwitchButton::getBackgroundRect() const {
	int x = 0, y = 0, w = width(), h = height();
	if (m_textPostion == TextPosition::Right) {
		w -= getTextWidth();
	} else if (m_textPostion == TextPosition::Left) {
		x += getTextWidth();
		w -= getTextWidth();
	}
	return { x, y, w, h };
}

QPainterPath CUVSwitchButton::getBackgroundPath(const QRect& rect) const {
	const int side = qMin(width(), height());
	const int rightRectX = (m_textPostion == TextPosition::Left) ? rect.width() - side + getTextWidth() : rect.width() - side;

	QPainterPath path1, path2, path3;
	// 左侧半圆
	path1.addEllipse(rect.x(), rect.y(), side, side);
	// 右侧半圆
	path2.addEllipse(rightRectX, rect.y(), side, side);
	// 中间的矩形
	path3.addRect(rect.x() + side / static_cast<qreal>(2), rect.y(), rect.width() - side, height());
	return { path1 + path2 + path3 };
}

QRect CUVSwitchButton::getSliderRect() const {
	int x = m_spaceSlider + m_startX;
	if (m_textPostion == TextPosition::Left) {
		x += getTextWidth();
	}
	return { x, m_spaceSlider, qMin(width(), height() - m_spaceSlider * 2), qMin(width(), height()) - m_spaceSlider * 2 };
}

QRect CUVSwitchButton::getTextRect(const TextPosition& position, const bool isChecked) const {
	const int sliderWidth = qMin(width(), height()) - m_spaceSlider * 2 - m_radius;
	int x = isChecked ? 0 : sliderWidth;
	int y = 0, w = width() - sliderWidth, h = height();
	if (position == TextPosition::Right) {
		x = width() - getTextWidth();
		w = getTextWidth();
	} else if (position == TextPosition::Left) {
		x = 0;
		w = getTextWidth();
	}
	return { x, y, w, h };
}

std::pair<int, int> CUVSwitchButton::getEndXandStep(const TextPosition& position) const {
	int endX{}, step{};
	if (position == TextPosition::Center) {
		step = width() / 10;
		endX = width() - height();
	} else {
		step = (width() - getTextWidth()) / 10;
		endX = width() - height() - getTextWidth();
	}
	return { endX, step };
}

void CUVSwitchButton::paintEvent(QPaintEvent* ev) {
	// 启用反锯齿
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

	// 绘制背景
	drawBackGround(&painter);

	// 绘制滑块
	drawSlider(&painter);

	// 绘制文本
	drawText(&painter);
}

void CUVSwitchButton::mousePressEvent(QMouseEvent* ev) {
	Q_UNUSED(ev)

	m_checked = !m_checked;
	emit statusChanged(m_checked);

	auto [endX, step] = getEndXandStep(m_textPostion);
	m_step = step;
	// 计算滑块X轴终点坐标
	if (m_checked) {
		m_endX = endX;
	} else {
		m_endX = 0;
	}

	// 判断是否使用动画
	if (m_animation) {
		m_timer->start();
	} else {
		m_startX = m_endX;
		update();
	}
}

void CUVSwitchButton::updateValue() {
	if (m_checked) {
		if (m_startX < m_endX) {
			m_startX += m_step;
		} else {
			m_startX = m_endX;
			m_timer->stop();
		}
	} else {
		if (m_startX > m_endX) {
			m_startX -= m_step;
		} else {
			m_startX = m_endX;
			m_timer->stop();
		}
	}

	update();
}

void CUVSwitchButton::init() {
	m_spaceSlider = 2;
	m_radius = 5;
	m_spaceText = 15;
	m_checked = false;
	m_showText = true;
	m_animation = true;

	m_bgColorOn = qRgb(82, 164, 255);
	m_bgColorOff = qRgb(170, 170, 170);

	m_sliderColorOn = Qt::white;
	m_sliderColorOff = Qt::white;

	m_textColorOn = qRgb(51, 145, 255);
	m_textColorOff = qRgb(91, 91, 91);

	m_textOn = tr("Open");
	m_textOff = tr("Close");

	m_textPostion = TextPosition::Right;

	m_step = 0;
	m_startX = 0;
	m_endX = 0;

	m_timer = new QTimer(this);
	m_timer->setInterval(30);
	connect(m_timer, &QTimer::timeout, this, &CUVSwitchButton::updateValue);

	const int width = m_textPostion == TextPosition::Center ? 50 : 110;
	this->resize(width, 25);
}

int CUVSwitchButton::spaceSlider() const { return m_spaceSlider; }

int CUVSwitchButton::spaceText() const { return m_spaceText; }

int CUVSwitchButton::radius() const { return m_radius; }

bool CUVSwitchButton::checked() const { return m_checked; }

bool CUVSwitchButton::showText() const { return m_showText; }

bool CUVSwitchButton::showCircel() const { return m_showCircle; }

bool CUVSwitchButton::animation() const { return m_animation; }

QColor CUVSwitchButton::bgColorOn() const { return m_bgColorOn; }

QColor CUVSwitchButton::bgColorOff() const { return m_bgColorOff; }

QColor CUVSwitchButton::sliderColorOn() const { return m_sliderColorOn; }

QColor CUVSwitchButton::sliderColorOff() const { return m_sliderColorOff; }

QColor CUVSwitchButton::textColorOn() const { return m_textColorOn; }

QColor CUVSwitchButton::textColorOff() const { return m_textColorOff; }

QString CUVSwitchButton::textOn() const { return m_textOn; }

QString CUVSwitchButton::textOff() const { return m_textOff; }

int CUVSwitchButton::step() const { return m_step; }

int CUVSwitchButton::startX() const { return m_startX; }

int CUVSwitchButton::endX() const { return m_endX; }

void CUVSwitchButton::setSpaceSlider(const int space) {
	if (m_spaceSlider != space) {
		m_spaceSlider = space;
		update();
	}
}

void CUVSwitchButton::setSpaceText(const int space) {
	if (m_spaceText != space) {
		m_spaceText = space;
		update();
	}
}

void CUVSwitchButton::setRadius(const int radius) {
	if (m_radius != radius) {
		m_radius = radius;
		update();
	}
}

void CUVSwitchButton::setChecked(const bool checked) {
	m_checked = checked;
	emit statusChanged(m_checked);

	auto [endX, step] = getEndXandStep(m_textPostion);
	m_step = step;
	// 计算滑块X轴终点坐标
	if (m_checked) {
		m_endX = endX;
		m_startX = m_endX;
	} else {
		m_endX = 0;
		m_startX = m_endX;
	}

	update();
}

void CUVSwitchButton::setShowText(const bool show) {
	if (m_showText != show) {
		m_showText = show;
		update();
	}
}

void CUVSwitchButton::setShowCircle(const bool show) {
	if (m_showCircle != show) {
		m_showCircle = show;
		update();
	}
}

void CUVSwitchButton::setAnimation(const bool ok) {
	if (m_animation != ok) {
		m_animation = ok;
		update();
	}
}

void CUVSwitchButton::setBgColorOn(const QColor& color) {
	if (m_bgColorOn != color) {
		m_bgColorOn = color;
		update();
	}
}

void CUVSwitchButton::setBgColorOff(const QColor& color) {
	if (m_bgColorOff != color) {
		m_bgColorOff = color;
		update();
	}
}

void CUVSwitchButton::setSliderColorOn(const QColor& color) {
	if (m_sliderColorOn != color) {
		m_sliderColorOn = color;
		update();
	}
}

void CUVSwitchButton::setSliderColorOff(const QColor& color) {
	if (m_sliderColorOff != color) {
		m_sliderColorOff = color;
		update();
	}
}

void CUVSwitchButton::setTextColorOn(const QColor& color) {
	if (m_textColorOn != color) {
		m_textColorOn = color;
		update();
	}
}

void CUVSwitchButton::setTextColorOff(const QColor& color) {
	if (m_textColorOff != color) {
		m_textColorOff = color;
		update();
	}
}

void CUVSwitchButton::setTextOn(const QString& text) {
	if (m_textOn != text) {
		m_textOn = text;
		update();
	}
}

void CUVSwitchButton::setTextOff(const QString& text) {
	if (m_textOff != text) {
		m_textOff = text;
		update();
	}
}

void CUVSwitchButton::setTextShowInBtn(const bool show) {
	m_showInCenter = show;
}

void CUVSwitchButton::setTextPosition(const CUVSwitchButton::TextPosition& position) {
	if (m_textPostion != position) {
		m_textPostion = position;
		update();
	}
}

bool CUVSwitchButton::status() const { return m_checked; }

CUVSwitchButton::TextPosition CUVSwitchButton::textPosition() const { return m_textPostion; }
