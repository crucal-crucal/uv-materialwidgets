#include "uvtoggleswitch.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>

#include "uvtoggleswitch_p.hpp"

/*!
 *  \class CUVToggleSwitchPrivate
 *  \internal
 */
CUVToggleSwitchPrivate::CUVToggleSwitchPrivate(CUVToggleSwitch* q, QObject* parent): QObject(parent), q_ptr(q) {
}

CUVToggleSwitchPrivate::~CUVToggleSwitchPrivate() = default;

void CUVToggleSwitchPrivate::init() {
	showText = true;
	spaceText = 15;
	fontSize = 10;
	fontBold = false;

	circleOffColor = qRgb(255, 255, 255);
	circleOnColor = qRgb(255, 255, 255);

	backgroundOffColor = qRgb(170, 170, 170);
	backgroundOnColor = qRgb(51, 145, 255);

	offText = tr("Off");
	onText = tr("On");

	offTextColor = qRgb(91, 91, 91);
	onTextColor = qRgb(51, 145, 255);
}

void CUVToggleSwitchPrivate::setcircleCenterX(const qreal centerX) {
	m_circleCenterX = centerX;
}

qreal CUVToggleSwitchPrivate::circleCenterX() const {
	return m_circleCenterX;
}

void CUVToggleSwitchPrivate::setcircleRadius(const qreal radius) {
	m_circleRadius = radius;
}

qreal CUVToggleSwitchPrivate::circleRadius() const {
	return m_circleRadius;
}

int CUVToggleSwitchPrivate::getTextWidth() const {
	Q_Q(const CUVToggleSwitch);

	if (showText) {
		return std::max(q->fontMetrics().boundingRect(onText).width(), q->fontMetrics().boundingRect(offText).width()) + spaceText;
	}
	return 0;
}

void CUVToggleSwitchPrivate::startPosAnimation(const qreal startX, const qreal endX, const bool isToggle) {
	Q_Q(CUVToggleSwitch);

	const auto posAnimation = new QPropertyAnimation(this, "circleCenterX");
	connect(posAnimation, &QPropertyAnimation::finished, this, [=]() {
		this->isAnimationFinished = true;
	});
	connect(posAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
		this->m_circleCenterX = value.toReal();
		q->update();
	});

	posAnimation->setStartValue(startX);
	posAnimation->setEndValue(endX);
	posAnimation->setEasingCurve(QEasingCurve::InOutSine);
	posAnimation->start(QAbstractAnimation::DeleteWhenStopped);
	isAnimationFinished = false;
	isToggled = isToggle;
	emit q->clicked(isToggled);
}

void CUVToggleSwitchPrivate::startRadiusAnimation(const qreal startRadius, const qreal endRadius) {
	Q_Q(CUVToggleSwitch);

	const auto radiusAnimation = new QPropertyAnimation(this, "circleRadius");
	connect(radiusAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
		this->m_circleRadius = value.toReal();
		q->update();
	});

	radiusAnimation->setEasingCurve(QEasingCurve::InOutSine);
	radiusAnimation->setStartValue(startRadius);
	radiusAnimation->setEndValue(endRadius);
	radiusAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void CUVToggleSwitchPrivate::adjustCircleCenterX() {
	Q_Q(CUVToggleSwitch);

	if (m_circleCenterX > q->width() - getTextWidth() - q->height() / 2 - margin * 2) { // NOLINT
		m_circleCenterX = q->width() - getTextWidth() - q->height() / 2 - margin * 2;   // NOLINT
	}

	if (m_circleCenterX < q->height() / 2) { // NOLINT
		m_circleCenterX = q->height() / 2;   // NOLINT
	}
}

/*!
 *  \class CUVToggleSwitch
 */
CUVToggleSwitch::CUVToggleSwitch(QWidget* parent): QWidget(parent), d_ptr(new CUVToggleSwitchPrivate(this)) {
	d_func()->init();
	setMouseTracking(true);
	setFixedSize(88, 22);
}

CUVToggleSwitch::~CUVToggleSwitch() = default;

void CUVToggleSwitch::setChecked(const bool checked) {
	Q_D(CUVToggleSwitch);

	if (d->isToggled == checked) {
		return;
	}

	const int adjustedWidth = width() - d->getTextWidth();
	if (d->isToggled) {
		d->startPosAnimation(adjustedWidth - static_cast<qreal>(height()) / 2 - d->margin * 2, static_cast<qreal>(height()) / 2, checked);
	} else {
		d->startPosAnimation(static_cast<qreal>(height()) / 2, adjustedWidth - static_cast<qreal>(height()) / 2 - d->margin * 2, checked);
	}
}

bool CUVToggleSwitch::isChecked() const {
	Q_D(const CUVToggleSwitch);

	return d->isToggled;
}

void CUVToggleSwitch::setShowText(const bool showText) {
	Q_D(CUVToggleSwitch);

	if (d->showText != showText) {
		d->showText = showText;
		update();
	}
}

bool CUVToggleSwitch::showText() const {
	Q_D(const CUVToggleSwitch);

	return d->showText;
}

void CUVToggleSwitch::setOnText(const QString& text) {
	Q_D(CUVToggleSwitch);

	if (d->onText != text) {
		d->onText = text;
		update();
	}
}

QString CUVToggleSwitch::onText() const {
	Q_D(const CUVToggleSwitch);

	return d->onText;
}

void CUVToggleSwitch::setOffText(const QString& text) {
	Q_D(CUVToggleSwitch);

	if (d->offText != text) {
		d->offText = text;
		update();
	}
}

QString CUVToggleSwitch::offText() const {
	Q_D(const CUVToggleSwitch);

	return d->offText;
}

void CUVToggleSwitch::setTextBold(const bool bold) {
	Q_D(CUVToggleSwitch);

	if (d->fontBold != bold) {
		d->fontBold = bold;
		update();
	}
}

bool CUVToggleSwitch::textBold() const {
	Q_D(const CUVToggleSwitch);

	return d->fontBold;
}

void CUVToggleSwitch::setFontSize(const int size) {
	Q_D(CUVToggleSwitch);

	if (d->fontSize != size) {
		d->fontSize = size;
		update();
	}
}

int CUVToggleSwitch::fontSize() const {
	Q_D(const CUVToggleSwitch);

	return d->fontSize;
}

void CUVToggleSwitch::setOnTextColor(const QColor& color) {
	Q_D(CUVToggleSwitch);

	if (d->onTextColor != color) {
		d->onTextColor = color;
		update();
	}
}

QColor CUVToggleSwitch::onTextColor() const {
	Q_D(const CUVToggleSwitch);

	return d->onTextColor;
}

void CUVToggleSwitch::setOffTextColor(const QColor& color) {
	Q_D(CUVToggleSwitch);

	if (d->offTextColor != color) {
		d->offTextColor = color;
		update();
	}
}

QColor CUVToggleSwitch::offTextColor() const {
	Q_D(const CUVToggleSwitch);

	return d->offTextColor;
}

void CUVToggleSwitch::setOffCircleColor(const QColor& color) {
	Q_D(CUVToggleSwitch);

	if (d->circleOffColor != color) {
		d->circleOffColor = color;
		update();
	}
}

QColor CUVToggleSwitch::circleOffColor() const {
	Q_D(const CUVToggleSwitch);

	return d->circleOffColor;
}

void CUVToggleSwitch::setOnCircleColor(const QColor& color) {
	Q_D(CUVToggleSwitch);

	if (d->circleOnColor != color) {
		d->circleOnColor = color;
		update();
	}
}

QColor CUVToggleSwitch::circleOnColor() const {
	Q_D(const CUVToggleSwitch);

	return d->circleOnColor;
}

void CUVToggleSwitch::setOffBackgroundColor(const QColor& color) {
	Q_D(CUVToggleSwitch);

	if (d->backgroundOffColor != color) {
		d->backgroundOffColor = color;
		update();
	}
}

QColor CUVToggleSwitch::backgroundOffColor() const {
	Q_D(const CUVToggleSwitch);

	return d->backgroundOffColor;
}

void CUVToggleSwitch::setOnBackgroundColor(const QColor& color) {
	Q_D(CUVToggleSwitch);

	if (d->backgroundOnColor != color) {
		d->backgroundOnColor = color;
		update();
	}
}

QColor CUVToggleSwitch::backgroundOnColor() const {
	Q_D(const CUVToggleSwitch);

	return d->backgroundOnColor;
}

bool CUVToggleSwitch::event(QEvent* event) {
	Q_D(CUVToggleSwitch);

	switch (event->type()) {
		case QEvent::Enter: {
			d->startRadiusAnimation(height() * 0.3, height() * 0.35);
			break;
		}
		case QEvent::Leave: {
			d->startRadiusAnimation(height() * 0.35, height() * 0.3);
			break;
		}
		case QEvent::MouseMove: {
			update();
			break;
		}
		default: break;
	}

	return QWidget::event(event);
}

void CUVToggleSwitch::mousePressEvent(QMouseEvent* event) {
	Q_D(CUVToggleSwitch);

	d->adjustCircleCenterX();
	d->isLeftButtonPress = true;
	d->lastMouseX = event->pos().x();
	d->startRadiusAnimation(d->m_circleRadius, height() * 0.35);

	QWidget::mousePressEvent(event);
}

void CUVToggleSwitch::mouseReleaseEvent(QMouseEvent* event) {
	Q_D(CUVToggleSwitch);

	d->isLeftButtonPress = false;
	QWidget::mouseReleaseEvent(event);

	const int adjustedWidth = width() - d->getTextWidth();

	if (d->isMousePressMove) {
		d->isMousePressMove = false;
		if (d->m_circleCenterX > static_cast<qreal>(adjustedWidth) / 2) {
			d->startPosAnimation(d->m_circleCenterX, adjustedWidth - static_cast<qreal>(height()) / 2 - d->margin * 2, true);
		} else {
			d->startPosAnimation(d->m_circleCenterX, static_cast<qreal>(height()) / 2, false);
		}
	} else {
		if (d->isAnimationFinished) {
			if (d->isToggled) {
				d->startPosAnimation(adjustedWidth - static_cast<qreal>(height()) / 2 - d->margin * 2, static_cast<qreal>(height()) / 2, false);
			} else {
				d->startPosAnimation(static_cast<qreal>(height()) / 2, adjustedWidth - static_cast<qreal>(height()) / 2 - d->margin * 2, true);
			}
		}
	}

	d->startRadiusAnimation(height() * 0.35, height() * 0.35);
}

void CUVToggleSwitch::mouseMoveEvent(QMouseEvent* event) {
	Q_D(CUVToggleSwitch);

	if (d->isLeftButtonPress) {
		d->isMousePressMove = true;
		const int moveX = event->pos().x() - d->lastMouseX;
		d->lastMouseX = event->pos().x();
		d->m_circleCenterX += moveX;
		d->adjustCircleCenterX();
	}

	QWidget::mouseMoveEvent(event);
}

void CUVToggleSwitch::paintEvent(QPaintEvent* event) {
	Q_D(CUVToggleSwitch);

	QPainter painter(this);
	painter.save();
	painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);

	// 调整路径，减去文本宽度
	const int adjustedWidth = width() - d->getTextWidth();

	// 绘制背景
	painter.setPen(d->isToggled ? QPen(d->backgroundOnColor, 2) : QPen(d->backgroundOffColor, 2));
	// painter.setBrush(d->isToggled ? d->m_backgroundOnColor : (underMouse() ? d->m_backgroundOnColor : d->m_backgroundOffColor));
	painter.setBrush(d->isToggled ? d->backgroundOnColor : d->backgroundOffColor);
	QPainterPath path{};
	path.moveTo(adjustedWidth - height() - d->margin, height() - d->margin);
	path.arcTo(QRectF(QPointF(adjustedWidth - height() - d->margin, d->margin), QSize(height() - d->margin * 2, height() - d->margin * 2)), -90, 180);
	path.lineTo(static_cast<qreal>(height()) / 2 + d->margin, d->margin);
	path.arcTo(QRectF(QPointF(d->margin, d->margin), QSize(height() - d->margin * 2, height() - d->margin * 2)), 90, 180);
	path.lineTo(adjustedWidth - height() - d->margin, height() - d->margin);
	painter.drawPath(path);

	// 圆心绘制
	painter.setBrush(d->isToggled ? d->circleOnColor : d->circleOffColor);
	painter.setPen(Qt::NoPen);
	if (d->m_circleRadius == 0) {
		d->m_circleRadius = this->isEnabled() ? (underMouse() ? height() * 0.35 : height() * 0.3) : height() * 0.3;
	}

	if (d->isLeftButtonPress) {
		painter.drawEllipse(QPointF(d->m_circleCenterX, static_cast<qreal>(height()) / 2), d->m_circleRadius, d->m_circleRadius);
	} else {
		if (d->isAnimationFinished) {
			painter.drawEllipse(QPointF(d->isToggled ? adjustedWidth - height() / 2 - d->margin * 2 : height() / 2,
			                            static_cast<qreal>(height()) / 2), d->m_circleRadius, d->m_circleRadius);
		} else {
			painter.drawEllipse(QPointF(d->m_circleCenterX, static_cast<qreal>(height()) / 2), d->m_circleRadius, d->m_circleRadius);
		}
	}
	painter.restore();

	if (d->showText) {
		painter.setPen(d->isToggled ? d->onTextColor : d->offTextColor);
		QFont font = painter.font();
		font.setPointSize(d->fontSize);
		font.setBold(d->fontBold);
		painter.setFont(font);

		const QString text = d->isToggled ? d->onText : d->offText;
		const int textHeight = painter.fontMetrics().height();
		painter.drawText(QRect(width() + 5 - d->getTextWidth(), (height() - textHeight) / 2, d->getTextWidth(), textHeight), Qt::AlignLeft, text);
	}

	QWidget::paintEvent(event);
}
