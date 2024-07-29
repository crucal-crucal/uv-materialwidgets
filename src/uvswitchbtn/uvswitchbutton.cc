#include "uvswitchbutton.hpp"

#include <QDebug>
#include <QPainterPath>
#include <QTimer>

#include "uvswitchbutton_p.hpp"

/*!
 *  \CUVSwitchButtonPrivate
 *  \internal
 */
CUVSwitchButtonPrivate::CUVSwitchButtonPrivate(CUVSwitchButton* q): q_ptr(q) {
}

CUVSwitchButtonPrivate::~CUVSwitchButtonPrivate() = default;

void CUVSwitchButtonPrivate::init() {
	Q_Q(CUVSwitchButton);

	spaceSlider = 2;
	radius = 5;
	spaceText = 15;
	checked = false;
	showText = true;
	animation = true;

	bgColorOn = qRgb(82, 164, 255);
	bgColorOff = qRgb(170, 170, 170);

	sliderColorOn = Qt::white;
	sliderColorOff = Qt::white;

	textColorOn = qRgb(51, 145, 255);
	textColorOff = qRgb(91, 91, 91);

	textOn = QObject::tr("Open");
	textOff = QObject::tr("Close");
	fontSize = 10;
	fontBold = false;

	textPostion = CUVSwitchButton::TextPosition::Right;

	step = 0;
	startX = 0;
	endX = 0;

	timer = new QTimer(q);
	timer->setInterval(30);
	QObject::connect(timer, &QTimer::timeout, this, &CUVSwitchButtonPrivate::updateValue);

	const int width = textPostion == CUVSwitchButton::TextPosition::Center ? 50 : 110;
	q->resize(width, 25);
}

void CUVSwitchButtonPrivate::drawBackGround(QPainter* painter) const {
	Q_Q(const CUVSwitchButton);

	painter->save();
	painter->setPen(Qt::NoPen);

	QColor bgColor = checked ? bgColorOn : bgColorOff;
	if (q->isEnabled()) {
		bgColor.setAlpha(255);
	}
	painter->setBrush(bgColor);

	const QPainterPath path = getBackgroundPath(getBackgroundRect());
	painter->drawPath(path);

	painter->restore();
}

void CUVSwitchButtonPrivate::drawSlider(QPainter* painter) const {
	painter->save();
	painter->setPen(Qt::NoPen);

	const QColor color = checked ? sliderColorOn : sliderColorOff;

	painter->setBrush(QBrush(color));

	painter->drawEllipse(getSliderRect());

	painter->restore();
}

void CUVSwitchButtonPrivate::drawText(QPainter* painter) const {
	painter->save();
	painter->setPen(Qt::NoPen);

	// 设置文字大小
	QFont font = painter->font();
	font.setPointSize(fontSize);
	font.setBold(fontBold);
	painter->setFont(font);

	// 绘制文本
	if (showText) {
		painter->setPen(checked ? QPen(textColorOn) : QPen(textColorOff));
		painter->drawText(getTextRect(textPostion, checked), Qt::AlignCenter, checked ? textOn : textOff);
	}

	painter->restore();
}

int CUVSwitchButtonPrivate::getTextWidth() const {
	Q_Q(const CUVSwitchButton);

	if (showText) {
		return std::max(q->fontMetrics().boundingRect(textOn).width(), q->fontMetrics().boundingRect(textOff).width()) + spaceText;
	}
	return 0;
}

QRect CUVSwitchButtonPrivate::getBackgroundRect() const {
	Q_Q(const CUVSwitchButton);

	int x = 0, y = 0, w = q->width(), h = q->height();
	if (textPostion == CUVSwitchButton::TextPosition::Right) {
		w -= getTextWidth();
	} else if (textPostion == CUVSwitchButton::TextPosition::Left) {
		x += getTextWidth();
		w -= getTextWidth();
	}
	return { x, y, w, h };
}

QPainterPath CUVSwitchButtonPrivate::getBackgroundPath(const QRect& rect) const {
	Q_Q(const CUVSwitchButton);

	const int side = qMin(q->width(), q->height());
	const int rightRectX = (textPostion == CUVSwitchButton::TextPosition::Left) ? rect.width() - side + getTextWidth() : rect.width() - side;

	QPainterPath path1, path2, path3;
	// 左侧半圆
	path1.addEllipse(rect.x(), rect.y(), side, side);
	// 右侧半圆
	path2.addEllipse(rightRectX, rect.y(), side, side);
	// 中间的矩形
	path3.addRect(rect.x() + side / static_cast<qreal>(2), rect.y(), rect.width() - side, q->height());
	return { path1 + path2 + path3 };
}

QRect CUVSwitchButtonPrivate::getSliderRect() const {
	Q_Q(const CUVSwitchButton);

	int x = spaceSlider + startX;
	if (textPostion == CUVSwitchButton::TextPosition::Left) {
		x += getTextWidth();
	}
	return { x, spaceSlider, qMin(q->width(), q->height() - spaceSlider * 2), qMin(q->width(), q->height()) - spaceSlider * 2 };
}

QRect CUVSwitchButtonPrivate::getTextRect(const CUVSwitchButton::TextPosition& position, const bool isChecked) const {
	Q_Q(const CUVSwitchButton);

	const int sliderWidth = qMin(q->width(), q->height()) - spaceSlider * 2 - radius;
	int x = isChecked ? 0 : sliderWidth;
	int y = 0, w = q->width() - sliderWidth, h = q->height();
	if (position == CUVSwitchButton::TextPosition::Right) {
		x = q->width() - getTextWidth();
		w = getTextWidth();
	} else if (position == CUVSwitchButton::TextPosition::Left) {
		x = 0;
		w = getTextWidth();
	}
	return { x, y, w, h };
}

std::pair<int, int> CUVSwitchButtonPrivate::getEndXandStep(const CUVSwitchButton::TextPosition& position) const {
	Q_Q(const CUVSwitchButton);

	int endX{}, step{};
	if (position == CUVSwitchButton::TextPosition::Center) {
		step = q->width() / 10;
		endX = q->width() - q->height();
	} else {
		step = (q->width() - getTextWidth()) / 10;
		endX = q->width() - q->height() - getTextWidth();
	}
	return { endX, step };
}

void CUVSwitchButtonPrivate::updateValue() {
	Q_Q(CUVSwitchButton);

	if (checked) {
		if (startX < endX) {
			startX += step;
		} else {
			startX = endX;
			timer->stop();
		}
	} else {
		if (startX > endX) {
			startX -= step;
		} else {
			startX = endX;
			timer->stop();
		}
	}

	q->update();
}

/*!
 *  \CUVSwitchButton
 */
CUVSwitchButton::CUVSwitchButton(QWidget* parent): QWidget(parent), d_ptr(new CUVSwitchButtonPrivate(this)) {
	d_func()->init();
}

CUVSwitchButton::~CUVSwitchButton() = default;

void CUVSwitchButton::paintEvent(QPaintEvent* event) {
	Q_D(CUVSwitchButton);
	// 启用反锯齿
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

	// 绘制背景
	d->drawBackGround(&painter);

	// 绘制滑块
	d->drawSlider(&painter);

	// 绘制文本
	d->drawText(&painter);
}

void CUVSwitchButton::mousePressEvent(QMouseEvent* event) {
	Q_UNUSED(event)

	Q_D(CUVSwitchButton);

	d->checked = !d->checked;
	emit statusChanged(d->checked);

	auto [endX, step] = d->getEndXandStep(d->textPostion);
	d->step = step;
	// 计算滑块X轴终点坐标
	if (d->checked) {
		d->endX = endX;
	} else {
		d->endX = 0;
	}

	// 判断是否使用动画
	if (d->animation) {
		d->timer->start();
	} else {
		d->startX = d->endX;
		update();
	}
}

int CUVSwitchButton::spaceSlider() const {
	Q_D(const CUVSwitchButton);

	return d->spaceSlider;
}

int CUVSwitchButton::spaceText() const {
	Q_D(const CUVSwitchButton);

	return d->spaceText;
}

int CUVSwitchButton::radius() const {
	Q_D(const CUVSwitchButton);

	return d->radius;
}

bool CUVSwitchButton::showText() const {
	Q_D(const CUVSwitchButton);

	return d->showText;
}

bool CUVSwitchButton::showAnimation() const {
	Q_D(const CUVSwitchButton);

	return d->animation;
}

QColor CUVSwitchButton::bgColorOn() const {
	Q_D(const CUVSwitchButton);

	return d->bgColorOn;
}

QColor CUVSwitchButton::bgColorOff() const {
	Q_D(const CUVSwitchButton);

	return d->bgColorOff;
}

QColor CUVSwitchButton::sliderColorOn() const {
	Q_D(const CUVSwitchButton);

	return d->sliderColorOn;
}

QColor CUVSwitchButton::sliderColorOff() const {
	Q_D(const CUVSwitchButton);

	return d->sliderColorOff;
}

QColor CUVSwitchButton::textColorOn() const {
	Q_D(const CUVSwitchButton);

	return d->textColorOn;
}

QColor CUVSwitchButton::textColorOff() const {
	Q_D(const CUVSwitchButton);

	return d->textColorOff;
}

QString CUVSwitchButton::textOn() const {
	Q_D(const CUVSwitchButton);

	return d->textOn;
}

QString CUVSwitchButton::textOff() const {
	Q_D(const CUVSwitchButton);

	return d->textOff;
}

void CUVSwitchButton::setFontSize(const int fontsize) {
	Q_D(CUVSwitchButton);

	d->fontSize = fontsize;
}

int CUVSwitchButton::fontSize() const {
	Q_D(const CUVSwitchButton);

	return d->fontSize;
}

void CUVSwitchButton::setFontBold(const bool fontbold) {
	Q_D(CUVSwitchButton);

	d->fontBold = fontbold;
}

bool CUVSwitchButton::fontBold() const {
	Q_D(const CUVSwitchButton);

	return d->fontBold;
}

int CUVSwitchButton::step() const {
	Q_D(const CUVSwitchButton);

	return d->step;
}

int CUVSwitchButton::startX() const {
	Q_D(const CUVSwitchButton);

	return d->startX;
}

int CUVSwitchButton::endX() const {
	Q_D(const CUVSwitchButton);

	return d->endX;
}

void CUVSwitchButton::setSpaceSlider(const int spaceslider) {
	Q_D(CUVSwitchButton);

	if (d->spaceSlider != spaceslider) {
		d->spaceSlider = spaceslider;
		update();
	}
}

void CUVSwitchButton::setSpaceText(const int spacetext) {
	Q_D(CUVSwitchButton);

	if (d->spaceText != spacetext) {
		d->spaceText = spacetext;
		update();
	}
}

void CUVSwitchButton::setRadius(const int radius) {
	Q_D(CUVSwitchButton);

	if (d->radius != radius) {
		d->radius = radius;
		update();
	}
}

void CUVSwitchButton::setChecked(const bool checked) {
	Q_D(CUVSwitchButton);

	d->checked = checked;
	emit statusChanged(d->checked);

	auto [endX, step] = d->getEndXandStep(d->textPostion);
	d->step = step;
	// 计算滑块X轴终点坐标
	if (d->checked) {
		d->endX = endX;
		d->startX = d->endX;
	} else {
		d->endX = 0;
		d->startX = d->endX;
	}

	update();
}

void CUVSwitchButton::setShowText(const bool showtext) {
	Q_D(CUVSwitchButton);

	if (d->showText != showtext) {
		d->showText = showtext;
		update();
	}
}

void CUVSwitchButton::setShowAnimation(const bool showanimation) {
	Q_D(CUVSwitchButton);

	if (d->animation != showanimation) {
		d->animation = showanimation;
		update();
	}
}

void CUVSwitchButton::setBgColorOn(const QColor& color) {
	Q_D(CUVSwitchButton);

	if (d->bgColorOn != color) {
		d->bgColorOn = color;
		update();
	}
}

void CUVSwitchButton::setBgColorOff(const QColor& color) {
	Q_D(CUVSwitchButton);

	if (d->bgColorOff != color) {
		d->bgColorOff = color;
		update();
	}
}

void CUVSwitchButton::setSliderColorOn(const QColor& color) {
	Q_D(CUVSwitchButton);

	if (d->sliderColorOn != color) {
		d->sliderColorOn = color;
		update();
	}
}

void CUVSwitchButton::setSliderColorOff(const QColor& color) {
	Q_D(CUVSwitchButton);

	if (d->sliderColorOff != color) {
		d->sliderColorOff = color;
		update();
	}
}

void CUVSwitchButton::setTextColorOn(const QColor& color) {
	Q_D(CUVSwitchButton);

	if (d->textColorOn != color) {
		d->textColorOn = color;
		update();
	}
}

void CUVSwitchButton::setTextColorOff(const QColor& color) {
	Q_D(CUVSwitchButton);

	if (d->textColorOff != color) {
		d->textColorOff = color;
		update();
	}
}

void CUVSwitchButton::setTextOn(const QString& text) {
	Q_D(CUVSwitchButton);

	if (d->textOn != text) {
		d->textOn = text;
		update();
	}
}

void CUVSwitchButton::setTextOff(const QString& text) {
	Q_D(CUVSwitchButton);

	if (d->textOff != text) {
		d->textOff = text;
		update();
	}
}

void CUVSwitchButton::setTextPosition(const CUVSwitchButton::TextPosition& position) {
	Q_D(CUVSwitchButton);

	if (d->textPostion != position) {
		d->textPostion = position;
		update();
	}
}

bool CUVSwitchButton::isChecked() const {
	Q_D(const CUVSwitchButton);

	return d->checked;
}

CUVSwitchButton::TextPosition CUVSwitchButton::textPosition() const {
	Q_D(const CUVSwitchButton);

	return d->textPostion;
}
