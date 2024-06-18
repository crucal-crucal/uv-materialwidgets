#include "uvmaterialtoggleswitch.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>

#include "uvmaterialtoggleswitch_p.hpp"

/*!
 *  \class CUVMaterialToggleSwitchPrivate
 *  \internal
 */
CUVMaterialToggleSwitchPrivate::CUVMaterialToggleSwitchPrivate(CUVMaterialToggleSwitch* q, QObject* parent): QObject(parent), q_ptr(q) {
}

CUVMaterialToggleSwitchPrivate::~CUVMaterialToggleSwitchPrivate() = default;

void CUVMaterialToggleSwitchPrivate::init() {
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

void CUVMaterialToggleSwitchPrivate::setcircleCenterX(const qreal centerX) {
	m_circleCenterX = centerX;
}

qreal CUVMaterialToggleSwitchPrivate::circleCenterX() const {
	return m_circleCenterX;
}

void CUVMaterialToggleSwitchPrivate::setcircleRadius(const qreal radius) {
	m_circleRadius = radius;
}

qreal CUVMaterialToggleSwitchPrivate::circleRadius() const {
	return m_circleRadius;
}

int CUVMaterialToggleSwitchPrivate::getTextWidth() const {
	Q_Q(const CUVMaterialToggleSwitch);

	if (showText) {
		return std::max(q->fontMetrics().boundingRect(onText).width(), q->fontMetrics().boundingRect(offText).width()) + spaceText;
	}
	return 0;
}

void CUVMaterialToggleSwitchPrivate::startPosAnimation(const qreal startX, const qreal endX, const bool isToggle) {
	Q_Q(CUVMaterialToggleSwitch);

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

void CUVMaterialToggleSwitchPrivate::startRadiusAnimation(const qreal startRadius, const qreal endRadius) {
	Q_Q(CUVMaterialToggleSwitch);

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

void CUVMaterialToggleSwitchPrivate::adjustCircleCenterX() {
	Q_Q(CUVMaterialToggleSwitch);

	if (m_circleCenterX > q->width() - getTextWidth() - q->height() / 2 - margin * 2) { // NOLINT
		m_circleCenterX = q->width() - getTextWidth() - q->height() / 2 - margin * 2;   // NOLINT
	}

	if (m_circleCenterX < q->height() / 2) { // NOLINT
		m_circleCenterX = q->height() / 2;   // NOLINT
	}
}

/*!
 *  \class CUVMaterialToggleSwitch
 */
CUVMaterialToggleSwitch::CUVMaterialToggleSwitch(QWidget* parent): QWidget(parent), d_ptr(new CUVMaterialToggleSwitchPrivate(this)) {
	d_func()->init();
	setMouseTracking(true);
	setFixedSize(88, 22);
}

CUVMaterialToggleSwitch::~CUVMaterialToggleSwitch() = default;

void CUVMaterialToggleSwitch::setChecked(const bool checked) {
	Q_D(CUVMaterialToggleSwitch);

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

bool CUVMaterialToggleSwitch::isChecked() const {
	Q_D(const CUVMaterialToggleSwitch);

	return d->isToggled;
}

void CUVMaterialToggleSwitch::setShowText(const bool showText) {
	Q_D(CUVMaterialToggleSwitch);

	if (d->showText != showText) {
		d->showText = showText;
		update();
	}
}

bool CUVMaterialToggleSwitch::showText() const {
	Q_D(const CUVMaterialToggleSwitch);

	return d->showText;
}

void CUVMaterialToggleSwitch::setOnText(const QString& text) {
	Q_D(CUVMaterialToggleSwitch);

	if (d->onText != text) {
		d->onText = text;
		update();
	}
}

QString CUVMaterialToggleSwitch::onText() const {
	Q_D(const CUVMaterialToggleSwitch);

	return d->onText;
}

void CUVMaterialToggleSwitch::setOffText(const QString& text) {
	Q_D(CUVMaterialToggleSwitch);

	if (d->offText != text) {
		d->offText = text;
		update();
	}
}

QString CUVMaterialToggleSwitch::offText() const {
	Q_D(const CUVMaterialToggleSwitch);

	return d->offText;
}

void CUVMaterialToggleSwitch::setTextBold(const bool bold) {
	Q_D(CUVMaterialToggleSwitch);

	if (d->fontBold != bold) {
		d->fontBold = bold;
		update();
	}
}

bool CUVMaterialToggleSwitch::textBold() const {
	Q_D(const CUVMaterialToggleSwitch);

	return d->fontBold;
}

void CUVMaterialToggleSwitch::setFontSize(const int size) {
	Q_D(CUVMaterialToggleSwitch);

	if (d->fontSize != size) {
		d->fontSize = size;
		update();
	}
}

int CUVMaterialToggleSwitch::fontSize() const {
	Q_D(const CUVMaterialToggleSwitch);

	return d->fontSize;
}

void CUVMaterialToggleSwitch::setOnTextColor(const QColor& color) {
	Q_D(CUVMaterialToggleSwitch);

	if (d->onTextColor != color) {
		d->onTextColor = color;
		update();
	}
}

QColor CUVMaterialToggleSwitch::onTextColor() const {
	Q_D(const CUVMaterialToggleSwitch);

	return d->onTextColor;
}

void CUVMaterialToggleSwitch::setOffTextColor(const QColor& color) {
	Q_D(CUVMaterialToggleSwitch);

	if (d->offTextColor != color) {
		d->offTextColor = color;
		update();
	}
}

QColor CUVMaterialToggleSwitch::offTextColor() const {
	Q_D(const CUVMaterialToggleSwitch);

	return d->offTextColor;
}

void CUVMaterialToggleSwitch::setOffCircleColor(const QColor& color) {
	Q_D(CUVMaterialToggleSwitch);

	if (d->circleOffColor != color) {
		d->circleOffColor = color;
		update();
	}
}

QColor CUVMaterialToggleSwitch::circleOffColor() const {
	Q_D(const CUVMaterialToggleSwitch);

	return d->circleOffColor;
}

void CUVMaterialToggleSwitch::setOnCircleColor(const QColor& color) {
	Q_D(CUVMaterialToggleSwitch);

	if (d->circleOnColor != color) {
		d->circleOnColor = color;
		update();
	}
}

QColor CUVMaterialToggleSwitch::circleOnColor() const {
	Q_D(const CUVMaterialToggleSwitch);

	return d->circleOnColor;
}

void CUVMaterialToggleSwitch::setOffBackgroundColor(const QColor& color) {
	Q_D(CUVMaterialToggleSwitch);

	if (d->backgroundOffColor != color) {
		d->backgroundOffColor = color;
		update();
	}
}

QColor CUVMaterialToggleSwitch::backgroundOffColor() const {
	Q_D(const CUVMaterialToggleSwitch);

	return d->backgroundOffColor;
}

void CUVMaterialToggleSwitch::setOnBackgroundColor(const QColor& color) {
	Q_D(CUVMaterialToggleSwitch);

	if (d->backgroundOnColor != color) {
		d->backgroundOnColor = color;
		update();
	}
}

QColor CUVMaterialToggleSwitch::backgroundOnColor() const {
	Q_D(const CUVMaterialToggleSwitch);

	return d->backgroundOnColor;
}

bool CUVMaterialToggleSwitch::event(QEvent* event) {
	Q_D(CUVMaterialToggleSwitch);

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

void CUVMaterialToggleSwitch::mousePressEvent(QMouseEvent* event) {
	Q_D(CUVMaterialToggleSwitch);

	d->adjustCircleCenterX();
	d->isLeftButtonPress = true;
	d->lastMouseX = event->pos().x();
	d->startRadiusAnimation(d->m_circleRadius, height() * 0.35);

	QWidget::mousePressEvent(event);
}

void CUVMaterialToggleSwitch::mouseReleaseEvent(QMouseEvent* event) {
	Q_D(CUVMaterialToggleSwitch);

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

void CUVMaterialToggleSwitch::mouseMoveEvent(QMouseEvent* event) {
	Q_D(CUVMaterialToggleSwitch);

	if (d->isLeftButtonPress) {
		d->isMousePressMove = true;
		const int moveX = event->pos().x() - d->lastMouseX;
		d->lastMouseX = event->pos().x();
		d->m_circleCenterX += moveX;
		d->adjustCircleCenterX();
	}

	QWidget::mouseMoveEvent(event);
}

void CUVMaterialToggleSwitch::paintEvent(QPaintEvent* event) {
	Q_D(CUVMaterialToggleSwitch);

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
