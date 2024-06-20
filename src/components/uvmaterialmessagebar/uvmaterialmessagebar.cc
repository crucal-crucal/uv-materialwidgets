#include "uvmaterialmessagebar.hpp"

#include <QApplication>
#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QTimer>
#include <QVariant>

#include "uvmaterialmessagebar_p.hpp"
#include "uvmaterialawesomebutton/uvmaterialawesomebutton.hpp"

using namespace UVIconType;

/*!
 *  \class CUVMaterialMessageBarPrivate
 *  \internal
 */
QMap<UVMessageBarType::PositionPolicy, QList<CUVMaterialMessageBar*>*> CUVMaterialMessageBarPrivate::messageBarActiveMap;

CUVMaterialMessageBarPrivate::CUVMaterialMessageBarPrivate(CUVMaterialMessageBar* q, QObject* parent): QObject(parent), q_ptr(q) {
	this->setProperty("MessagebarCloseY", 0);
	this->setProperty("MessageBarFinishY", 0);
}

CUVMaterialMessageBarPrivate::~CUVMaterialMessageBarPrivate() = default;

void CUVMaterialMessageBarPrivate::init() {
	borderRadius = 6;
	title = "";
	text = "";
	leftPadding = 20;
	titleLeftSpacing = 30;
	textLeftSpacing = 15;
	closeButtonLeftRightMargin = 20;
	closeButtonWidth = 30;
	messageBarHorizontalMargin = 20;
	messageBarVerticalBottomMargin = 20;
	messageBarVerticalTopMargin = 50;
	messageBarSpacing = 15;
	shadowBorderWidth = 6;

	messageBarIndex = 0;
	isMessageBarStartAnimationFinished = false;
	isMessageBarEventAnimationInStartAnimation = false;
	isCloseAnimationStart = false;
	isNormalDisplay = false;
	isMessageBarEventAnimationStart = false;
}

void CUVMaterialMessageBarPrivate::messageBarStartAnimation(const int displayMsec) {
	Q_Q(CUVMaterialMessageBar);

	q->show();
	QFont font = q->font();
	font.setPixelSize(16);
	font.setWeight(QFont::Bold);
	q->setFont(font);
	const int titleWidth = q->fontMetrics().horizontalAdvance(this->title);
	font.setPixelSize(14);
	font.setWeight(QFont::Medium);
	q->setFont(font);
	const int textWidth = q->fontMetrics().horizontalAdvance(this->text);
	const int fixedWidth = this->closeButtonLeftRightMargin + this->leftPadding + this->titleLeftSpacing * 2 + this->closeButtonWidth
		+ titleWidth + textWidth + 2 * this->shadowBorderWidth;
	q->setFixedWidth(fixedWidth > 600 ? 600 : fixedWidth);
	updateActiveMap(true); // 计算坐标前增加
	int startX, startY, endX, endY;
	calculatePos(startX, startY, endX, endY);
	// 划入动画
	const auto barPosAnimation = new QPropertyAnimation(q, "pos");
	connect(barPosAnimation, &QPropertyAnimation::finished, q, [=]() {
		this->isNormalDisplay = true;
		this->isMessageBarStartAnimationFinished = true;
		if (this->isMessageBarEventAnimationInStartAnimation) {
			messageBarEventAnimation();
		}
		QTimer::singleShot(displayMsec, q, [=]() {
			this->isCloseAnimationStart = true;
			if (!this->isMessageBarEventAnimationStart) {
				messageBarFinishAnimation();
			}
		});
	});

	switch (this->policy) {
		case UVMessageBarType::Top:
		case UVMessageBarType::Bottom: {
			barPosAnimation->setDuration(250);
			break;
		}
		case UVMessageBarType::Left:
		case UVMessageBarType::Right:
		case UVMessageBarType::TopRight:
		case UVMessageBarType::TopLeft:
		case UVMessageBarType::BottomRight:
		case UVMessageBarType::BottomLeft: {
			barPosAnimation->setDuration(450);
			break;
		}
		default: break;
	}

	barPosAnimation->setStartValue(QPoint(startX, startY));
	barPosAnimation->setEndValue(QPoint(endX, endY));
	barPosAnimation->setEasingCurve(QEasingCurve::InOutSine);
	barPosAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void CUVMaterialMessageBarPrivate::messageBarFinishAnimation() {
	Q_Q(CUVMaterialMessageBar);

	const auto barFinishedOpacityAnimation = new QPropertyAnimation(q->graphicsEffect(), "opacity");
	connect(barFinishedOpacityAnimation, &QPropertyAnimation::finished, this, [=]() {
		q->deleteLater();
	});
	barFinishedOpacityAnimation->setDuration(300);
	barFinishedOpacityAnimation->setEasingCurve(QEasingCurve::InOutSine);
	barFinishedOpacityAnimation->setStartValue(1);
	barFinishedOpacityAnimation->setEndValue(0);
	barFinishedOpacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
	updateActiveMap(false);
	emit messageBarClosed(policy, messageBarIndex);
}

void CUVMaterialMessageBarPrivate::messageBarEventAnimation() {
	Q_Q(CUVMaterialMessageBar);

	this->isMessageBarEventAnimationStart = true;
	const auto closePosAnimation = new QPropertyAnimation(this, "MessagebarCloseY");
	connect(closePosAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
		q->move(q->pos().x(), value.toInt());
	});
	connect(closePosAnimation, &QPropertyAnimation::finished, this, [=]() {
		if (this->isCloseAnimationStart) {
			messageBarFinishAnimation();
		} else {
			this->isMessageBarEventAnimationStart = false;
		}
	});

	closePosAnimation->setEasingCurve(QEasingCurve::InOutSine);
	closePosAnimation->setDuration(200);
	closePosAnimation->setStartValue(q->pos().y());
	const int minimumHeightTotal = calculateMinimumHeightTotal(true);
	const int spacing = this->messageBarSpacing * (this->messageBarIndex - 1);
	const int parentHeight = q->parentWidget()->height();
	const int minimumHeight = q->minimumHeight();
	switch (this->policy) {
		case UVMessageBarType::Top: {
			closePosAnimation->setEndValue(minimumHeightTotal + spacing + this->messageBarVerticalTopMargin);
			break;
		}
		case UVMessageBarType::Left: {
			closePosAnimation->setEndValue(minimumHeightTotal + spacing + parentHeight / 2);
			break;
		}
		case UVMessageBarType::Bottom: {
			closePosAnimation->setEndValue(parentHeight - minimumHeight - minimumHeightTotal - spacing - this->messageBarVerticalBottomMargin);
			break;
		}
		case UVMessageBarType::Right: {
			closePosAnimation->setEndValue(minimumHeightTotal + spacing + parentHeight / 2);
			break;
		}
		case UVMessageBarType::TopRight:
		case UVMessageBarType::TopLeft: {
			closePosAnimation->setEndValue(minimumHeightTotal + spacing + this->messageBarVerticalTopMargin);
			break;
		}
		case UVMessageBarType::BottomRight:
		case UVMessageBarType::BottomLeft: {
			closePosAnimation->setEndValue(parentHeight - minimumHeight - minimumHeightTotal - spacing - messageBarVerticalBottomMargin);
		}
		default: break;
	}

	closePosAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void CUVMaterialMessageBarPrivate::updateActiveMap(const bool isActive) {
	Q_Q(CUVMaterialMessageBar);

	if (isActive) {
		if (messageBarActiveMap.contains(this->policy)) {
			messageBarActiveMap[this->policy]->append(q);
		} else {
			const auto messageBarList = new QList<CUVMaterialMessageBar*>();
			messageBarList->append(q);
			messageBarActiveMap.insert(this->policy, messageBarList);
		}
		this->messageBarIndex = messageBarActiveMap[this->policy]->count();
	} else {
		if (messageBarActiveMap.contains(this->policy)) {
			if (!messageBarActiveMap[this->policy]->isEmpty()) {
				messageBarActiveMap[this->policy]->removeOne(q);
			}
		}
	}
}

void CUVMaterialMessageBarPrivate::calculatePos(int& startX, int& startY, int& endX, int& endY) {
	Q_Q(CUVMaterialMessageBar);

	const int minimumHeightTotal = this->calculateMinimumHeightTotal();
	const int spacing = this->messageBarSpacing * (this->messageBarIndex - 1);
	switch (this->policy) {
		case UVMessageBarType::Top: {
			// 25动画距离
			startX = q->parentWidget()->width() / 2 - q->minimumWidth() / 2;
			startY = minimumHeightTotal + spacing + this->messageBarVerticalTopMargin - 25;
			endX = startX;
			endY = minimumHeightTotal + spacing + this->messageBarVerticalTopMargin;
			break;
		}
		case UVMessageBarType::Left: {
			startX = -q->minimumWidth();
			startY = minimumHeightTotal + spacing + q->parentWidget()->height() / 2;
			endX = this->messageBarHorizontalMargin;
			endY = startY;
			break;
		}
		case UVMessageBarType::Bottom: {
			startX = q->parentWidget()->width() / 2 - q->minimumWidth() / 2;
			startY = q->parentWidget()->height() - q->minimumHeight() - minimumHeightTotal - spacing - this->messageBarVerticalBottomMargin - 25;
			endX = startX;
			endY = q->parentWidget()->height() - q->minimumHeight() - minimumHeightTotal - spacing - this->messageBarVerticalBottomMargin;
			break;
		}
		case UVMessageBarType::Right: {
			startX = q->parentWidget()->width();
			startY = minimumHeightTotal + spacing + q->parentWidget()->height() / 2;
			endX = q->parentWidget()->width() - q->minimumWidth() - this->messageBarHorizontalMargin;
			endY = startY;
			break;
		}
		case UVMessageBarType::TopRight: {
			startX = q->parentWidget()->width();
			startY = minimumHeightTotal + spacing + this->messageBarVerticalTopMargin;
			endX = q->parentWidget()->width() - q->minimumWidth() - this->messageBarHorizontalMargin;
			endY = startY;
			break;
		}
		case UVMessageBarType::TopLeft: {
			startX = -q->minimumWidth();
			startY = minimumHeightTotal + spacing + this->messageBarVerticalTopMargin;
			endX = this->messageBarHorizontalMargin;
			endY = startY;
			break;
		}
		case UVMessageBarType::BottomRight: {
			startX = q->parentWidget()->width();
			startY = q->parentWidget()->height() - q->minimumHeight() - minimumHeightTotal - spacing - this->messageBarVerticalBottomMargin;
			endX = q->parentWidget()->width() - q->minimumWidth() - this->messageBarHorizontalMargin;
			endY = startY;
			break;
		}
		case UVMessageBarType::BottomLeft: {
			startX = -q->minimumWidth();
			startY = q->parentWidget()->height() - q->minimumHeight() - minimumHeightTotal - spacing - this->messageBarVerticalBottomMargin;
			endX = this->messageBarHorizontalMargin;
			endY = startY;
			break;
		}
	}

	if (endY < this->messageBarVerticalTopMargin || endY > q->parentWidget()->height() - this->messageBarVerticalBottomMargin - q->minimumHeight()) {
		updateActiveMap(false);
		q->deleteLater();
	}
}

int CUVMaterialMessageBarPrivate::calculateMinimumHeightTotal(const bool isJudgeIndex) {
	Q_Q(CUVMaterialMessageBar);

	int minimumHeightTotal = 0;
	const auto messageBarList = CUVMaterialMessageBarPrivate::messageBarActiveMap[this->policy];
	if (isJudgeIndex) {
		for (const auto& messageBar : *messageBarList) {
			if (messageBar == q) {
				continue;
			}
			if (messageBar->d_ptr->messageBarIndex < messageBarIndex) {
				minimumHeightTotal += messageBar->minimumHeight();
			}
		}
	} else {
		for (const auto& messageBar : *messageBarList) {
			if (messageBar == q) {
				continue;
			}
			minimumHeightTotal += messageBar->minimumHeight();
		}
	}

	return minimumHeightTotal;
}

void CUVMaterialMessageBarPrivate::drawMessage(QPainter* painter, const QColor& backgroundColor, const QColor& iconColor, const QString& iconText,
                                               const QColor& textColor, const int iconPixelSize, const int iconX, const QColor& penColor) {
	Q_Q(CUVMaterialMessageBar);
	// 背景颜色
	painter->setBrush(backgroundColor);
	const QRect foregroundRect(shadowBorderWidth, shadowBorderWidth, q->width() - 2 * shadowBorderWidth, q->height() - 2 * shadowBorderWidth);
	painter->drawRoundedRect(foregroundRect, borderRadius, borderRadius);

	// 图标绘制
	painter->save();
	painter->setPen(penColor);
	QPainterPath textPath;
	textPath.addEllipse(QPoint(leftPadding + 6, q->height() / 2), 9, 9);
	painter->setClipPath(textPath);
	painter->fillPath(textPath, iconColor);

	auto iconFont = QFont("ElaAwesome");
	iconFont.setPixelSize(iconPixelSize);
	painter->setFont(iconFont);
	painter->drawText(iconX, 0, q->width(), q->height(), Qt::AlignVCenter, iconText);
	painter->restore();

	// 文字颜色
	painter->setPen(textColor);
}

void CUVMaterialMessageBarPrivate::drawSuccess(QPainter* painter) {
	drawMessage(painter, QColor(0xE0, 0xF6, 0xDD), QColor(0x11, 0x77, 0x10), QChar(static_cast<ushort>(CUVIconType::Check)),
	            Qt::black, 12, leftPadding);
}

void CUVMaterialMessageBarPrivate::drawError(QPainter* painter) {
	drawMessage(painter, QColor(0xFE, 0xE7, 0xEA), QColor(0xBA, 0x2D, 0x20), QChar(static_cast<ushort>(CUVIconType::Xmark)),
	            Qt::black, 13, leftPadding + 1);
}

void CUVMaterialMessageBarPrivate::drawWarning(QPainter* painter) {
	drawMessage(painter, QColor(0x6B, 0x56, 0x27), QColor(0xF8, 0xE2, 0x23), "!", QColor(0xFA, 0xFA, 0xFA), 12, leftPadding + 4, Qt::black);
}

void CUVMaterialMessageBarPrivate::drawInfo(QPainter* painter) {
	drawMessage(painter, QColor(0xF4, 0xF4, 0xF4), QColor(0x00, 0x66, 0xB4), "i", Qt::black, 12, leftPadding + 4);
}

void CUVMaterialMessageBarPrivate::showMessageBar(const UVMessageBarType::PositionPolicy& positionPolicy,
                                                  const UVMessageBarType::MessageMode& messageMode,
                                                  const QString& title, const QString& message,
                                                  const int displayMsec, QWidget* parent) {
	if (!parent) {
		const auto widgetList = QApplication::topLevelWidgets();
		for (const auto& widget : widgetList) {
			if (widget->property("CUVBaseClassName").toString() == "CUVWindow") {
				parent = widget;
			}
		}
		if (!parent) {
			return;
		}
	}

	const auto bar = new CUVMaterialMessageBar(positionPolicy, messageMode, title, message, displayMsec, parent);
	Q_UNUSED(bar)
}

void CUVMaterialMessageBarPrivate::onCloseButtonClicked() {
	Q_Q(CUVMaterialMessageBar);

	if (this->isCloseAnimationStart) {
		return;
	}
	this->isCloseAnimationStart = true;
	const auto opacityAnimation = new QPropertyAnimation(q->graphicsEffect(), "opacity");
	connect(opacityAnimation, &QPropertyAnimation::finished, q, [=]() { q->deleteLater(); });
	opacityAnimation->setStartValue(dynamic_cast<QGraphicsOpacityEffect*>(q->graphicsEffect())->opacity());
	opacityAnimation->setEndValue(0);
	opacityAnimation->setDuration(220);
	opacityAnimation->setEasingCurve(QEasingCurve::InOutSine);
	opacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
	this->isNormalDisplay = false;
	updateActiveMap(false);
	emit messageBarClosed(this->policy, this->messageBarIndex);
}

void CUVMaterialMessageBarPrivate::onOtherMessageBarClosed(const UVMessageBarType::PositionPolicy positionPolicy, const int barIndex) {
	if (this->policy == positionPolicy && !isCloseAnimationStart && this->messageBarIndex > barIndex) {
		this->messageBarIndex -= 1;
		if (!this->isMessageBarStartAnimationFinished) {
			this->isMessageBarEventAnimationInStartAnimation = true;
			return;
		}
		messageBarEventAnimation();
	}
}

/*!
 *  \class CUVMaterialMessageBar
 */
CUVMaterialMessageBar::CUVMaterialMessageBar(const UVMessageBarType::PositionPolicy& policy, const UVMessageBarType::MessageMode& messageMode,
                                             const QString& title, const QString& message, const int displayMsec, QWidget* parent)
: QWidget(parent), d_ptr(new CUVMaterialMessageBarPrivate(this)) {
	d_func()->init();
	Q_D(CUVMaterialMessageBar);

	d->title = title;
	d->text = message;
	d->policy = policy;
	d->messageMode = messageMode;
	setFixedHeight(60);
	setMouseTracking(true);
	const auto effect = new QGraphicsOpacityEffect(this);
	effect->setOpacity(1);
	setGraphicsEffect(effect);
	setFont(QFont("Microsoft YaHei"));
	parent->installEventFilter(this);
	d->closeButton = new CUVMaterialAwesomeButton(CUVIconType::Xmark, 17, d->closeButtonWidth, 30, this);
	switch (d->messageMode) {
		case UVMessageBarType::Success: {
			d->closeButton->setLightHoverColor(QColor(0xE6, 0xFC, 0xE3));
			d->closeButton->setDarkHoverColor(QColor(0xE6, 0xFC, 0xE3));
			d->closeButton->setDarkIconColor(Qt::black);
			break;
		}
		case UVMessageBarType::Warning: {
			d->closeButton->setLightHoverColor(QColor(0x5E, 0x4C, 0x22));
			d->closeButton->setDarkHoverColor(QColor(0x5E, 0x4C, 0x22));
			d->closeButton->setLightIconColor(Qt::white);
			d->closeButton->setDarkIconColor(Qt::white);
			break;
		}
		case UVMessageBarType::Info: {
			d->closeButton->setLightHoverColor(QColor(0xEB, 0xEB, 0xEB));
			d->closeButton->setDarkHoverColor(QColor(0xEB, 0xEB, 0xEB));
			d->closeButton->setDarkIconColor(Qt::black);
			break;
		}
		case UVMessageBarType::Error: {
			d->closeButton->setLightHoverColor(QColor(0xF7, 0xE1, 0xE4));
			d->closeButton->setDarkHoverColor(QColor(0xF7, 0xE1, 0xE4));
			d->closeButton->setDarkIconColor(Qt::black);
			break;
		}
	}
	d->closeButton->setBorderRadius(5);
	connect(d->closeButton, &CUVMaterialAwesomeButton::clicked, d, &CUVMaterialMessageBarPrivate::onCloseButtonClicked);
	const auto mainLayout = new QHBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 10, 0);
	mainLayout->addStretch();
	mainLayout->addWidget(d->closeButton);
	setObjectName("CUVMessageBar");
	setStyleSheet("#CUVMessageBar{ background-color: transparent; }");

	d->messageBarStartAnimation(displayMsec);

	const auto messageBarList = CUVMaterialMessageBarPrivate::messageBarActiveMap.value(d->policy);
	for (const auto& otherMessageBar : *messageBarList) {
		connect(otherMessageBar->d_func(), &CUVMaterialMessageBarPrivate::messageBarClosed, d,
		        &CUVMaterialMessageBarPrivate::onOtherMessageBarClosed);
	}
}

CUVMaterialMessageBar::~CUVMaterialMessageBar() = default;

void CUVMaterialMessageBar::success(const QString& title, const QString& message,
                                    const int displayMsec, const UVMessageBarType::PositionPolicy& positionPolicy, QWidget* parent) {
	CUVMaterialMessageBarPrivate::showMessageBar(positionPolicy, UVMessageBarType::Success, title, message, displayMsec, parent);
}

void CUVMaterialMessageBar::warning(const QString& title, const QString& message,
                                    const int displayMsec, const UVMessageBarType::PositionPolicy& positionPolicy, QWidget* parent) {
	CUVMaterialMessageBarPrivate::showMessageBar(positionPolicy, UVMessageBarType::Warning, title, message, displayMsec, parent);
}

void CUVMaterialMessageBar::infomation(const QString& title, const QString& message,
                                       const int displayMsec, const UVMessageBarType::PositionPolicy& positionPolicy, QWidget* parent) {
	CUVMaterialMessageBarPrivate::showMessageBar(positionPolicy, UVMessageBarType::Info, title, message, displayMsec, parent);
}

void CUVMaterialMessageBar::error(const QString& title, const QString& message,
                                  const int displayMsec, const UVMessageBarType::PositionPolicy& positionPolicy, QWidget* parent) {
	CUVMaterialMessageBarPrivate::showMessageBar(positionPolicy, UVMessageBarType::Error, title, message, displayMsec, parent);
}

void CUVMaterialMessageBar::paintEvent(QPaintEvent* event) {
	Q_D(CUVMaterialMessageBar);

	QPainter painter(this);
	painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
	painter.save();
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	auto color = QColor(165, 165, 165, 155);
	for (int i = 0; i < d->shadowBorderWidth; i++) {
		QPainterPath pa;
		pa.setFillRule(Qt::WindingFill);
		pa.addRoundedRect(d->shadowBorderWidth - i, d->shadowBorderWidth - i, this->width() - (d->shadowBorderWidth - i) * 2,
		                  this->height() - (d->shadowBorderWidth - i) * 2, d->borderRadius + i, d->borderRadius + i);
		const int alpha = 5 * (d->shadowBorderWidth - i + 1);
		color.setAlpha(alpha);
		painter.setPen(color);
		painter.drawPath(pa);
	}
	painter.restore();

	// 背景和图标绘制
	painter.save();
	painter.setPen(Qt::NoPen);
	switch (d->messageMode) {
		case UVMessageBarType::Success: {
			d->drawSuccess(&painter);
			break;
		}
		case UVMessageBarType::Warning: {
			d->drawWarning(&painter);
			break;
		}
		case UVMessageBarType::Error: {
			d->drawError(&painter);
			break;
		}
		case UVMessageBarType::Info: {
			d->drawInfo(&painter);
			break;
		}
		default: break;
	}
	// 标题
	QFont font = this->font();
	font.setWeight(QFont::Bold);
	font.setPixelSize(16);
	painter.setFont(font);
	int titleTextWidth = painter.fontMetrics().horizontalAdvance(d->title);
	if (titleTextWidth > 100) {
		titleTextWidth = 100;
	}
	constexpr int textFlags = Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap;
	painter.drawText(QRect(d->leftPadding + d->titleLeftSpacing, -1, titleTextWidth, height()), textFlags, d->title);
	// 正文
	font.setWeight(QFont::Light);
	font.setPixelSize(15);
	painter.setFont(font);
	painter.drawText(QRect(d->leftPadding + d->titleLeftSpacing + titleTextWidth + d->textLeftSpacing, 0,
	                       width() - (d->leftPadding + d->titleLeftSpacing + titleTextWidth + d->textLeftSpacing + d->closeButtonWidth +
		                       d->closeButtonLeftRightMargin / 2), height()), textFlags, d->text);
	if (const int textHeight = painter.fontMetrics().boundingRect(QRect(d->leftPadding + d->titleLeftSpacing + titleTextWidth + d->textLeftSpacing, 0,
	                                                                    width() - (d->leftPadding + d->titleLeftSpacing + titleTextWidth + d->
		                                                                    textLeftSpacing
		                                                                    + d->closeButtonWidth + d->closeButtonLeftRightMargin),
	                                                                    height()), textFlags, d->text).height(); textHeight >= minimumHeight() - 20) {
		setMinimumHeight(textHeight + 20);
	}
	painter.restore();
}

bool CUVMaterialMessageBar::eventFilter(QObject* watched, QEvent* event) {
	Q_D(CUVMaterialMessageBar);

	if (watched == parentWidget()) {
		switch (event->type()) {
			case QEvent::Resize: {
				const auto resizeEvent = dynamic_cast<QResizeEvent*>(event);
				const QSize offsetSize = parentWidget()->size() - resizeEvent->oldSize();
				if (d->isNormalDisplay) {
					const int parentWidth = parentWidget()->width();
					switch (d->policy) {
						case UVMessageBarType::Top: {
							this->move(parentWidth / 2 - minimumWidth() / 2, this->y());
							break;
						}
						case UVMessageBarType::Bottom: {
							this->move(parentWidth / 2 - minimumWidth() / 2, this->pos().y() + offsetSize.height());
							break;
						}
						case UVMessageBarType::Left:
						case UVMessageBarType::TopLeft: {
							this->move(d->messageBarHorizontalMargin, this->pos().y());
							break;
						}
						case UVMessageBarType::BottomLeft: {
							this->move(d->messageBarHorizontalMargin, this->pos().y() + offsetSize.height());
							break;
						}
						case UVMessageBarType::Right:
						case UVMessageBarType::TopRight: {
							this->move(parentWidth - minimumWidth() - d->messageBarHorizontalMargin, this->y());
							break;
						}
						case UVMessageBarType::BottomRight: {
							this->move(parentWidth - minimumWidth() - d->messageBarHorizontalMargin,
							           this->pos().y() + offsetSize.height());
							break;
						}
						default: break;
					}
				}
			}
			default: break;
		}
	}
	return QWidget::eventFilter(watched, event);
}
