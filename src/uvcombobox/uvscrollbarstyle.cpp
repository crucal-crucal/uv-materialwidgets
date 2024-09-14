#include "uvscrollbarstyle.hpp"

#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QStyleOptionSlider>
#include <QtMath>

#include "uvscrollbar.hpp"

CUVScrollBarStyle::CUVScrollBarStyle(QStyle* style): QProxyStyle(style) {
	_pIsExpand = false;
	_pOpacity = 0;
	_pScrollBar = nullptr;
	_pSliderExtent = 2.4;
}

CUVScrollBarStyle::~CUVScrollBarStyle() = default;

void CUVScrollBarStyle::drawComplexControl(const ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget) const {
	switch (control) {
		case QStyle::CC_ScrollBar: {
			if (const auto sopt = qstyleoption_cast<const QStyleOptionSlider*>(option)) {
				painter->save();
				painter->setRenderHint(QPainter::Antialiasing);
				painter->setPen(Qt::NoPen);
				const QRect scrollBarRect = sopt->rect;
				if (_pIsExpand) {
					// 背景绘制
					painter->setOpacity(_pOpacity);
					painter->setPen(Qt::NoPen);
					painter->setBrush(QColor(0x38, 0x38, 0x38));
					painter->drawRoundedRect(scrollBarRect, 6, 6);
					// 指示器绘制
					constexpr int sideLength = 8;
					painter->setBrush(QColor(0x9F, 0x9F, 0x9F));
					if (sopt->orientation == Qt::Horizontal) {
						const QRect leftIndicatorRect = subControlRect(control, sopt, QStyle::SC_ScrollBarSubLine, widget);
						const QRect rightIndicatorRect = subControlRect(control, sopt, QStyle::SC_ScrollBarAddLine, widget);
						// 左三角
						const qreal centerLeftX = leftIndicatorRect.x() + leftIndicatorRect.width() / 2.0;
						const qreal centerRightX = rightIndicatorRect.x() + rightIndicatorRect.width() / 2.0;
						const qreal centerY = leftIndicatorRect.height() / 2.0;
						QPainterPath leftPath;
						leftPath.moveTo(centerLeftX - qCos(30 * M_PI / 180.0) * sideLength / 2, centerY);
						leftPath.lineTo(centerLeftX + qCos(30 * M_PI / 180.0) * sideLength / 2, centerY + sideLength / 2.0);
						leftPath.lineTo(centerLeftX + qCos(30 * M_PI / 180.0) * sideLength / 2, centerY - sideLength / 2.0);
						leftPath.closeSubpath();
						painter->drawPath(leftPath);

						// 右三角
						QPainterPath rightPath;
						rightPath.moveTo(centerRightX + qCos(30 * M_PI / 180.0) * sideLength / 2, centerY);
						rightPath.lineTo(centerRightX - qCos(30 * M_PI / 180.0) * sideLength / 2, centerY + sideLength / 2.0);
						rightPath.lineTo(centerRightX - qCos(30 * M_PI / 180.0) * sideLength / 2, centerY - sideLength / 2.0);
						rightPath.closeSubpath();
						painter->drawPath(rightPath);
					} else {
						const QRect upIndicatorRect = subControlRect(control, sopt, QStyle::SC_ScrollBarSubLine, widget);
						const QRect downIndicatorRect = subControlRect(control, sopt, QStyle::SC_ScrollBarAddLine, widget);
						const qreal centerToTop = (sideLength / 2.0) / qCos(30 * M_PI / 180.0);
						const qreal centerToBottom = (sideLength / 2.0) * qTan(30 * M_PI / 180.0);
						// 上三角
						const qreal centerX = upIndicatorRect.width() / 2.0;
						const qreal centerUpY = upIndicatorRect.center().y() + 2.0;
						const qreal centerDownY = downIndicatorRect.center().y() + 2.0;
						QPainterPath upPath;
						upPath.moveTo(centerX, centerUpY - centerToTop);
						upPath.lineTo(centerX + sideLength / 2.0, centerUpY + centerToBottom);
						upPath.lineTo(centerX - sideLength / 2.0, centerUpY + centerToBottom);
						upPath.closeSubpath();
						painter->drawPath(upPath);

						// 下三角
						QPainterPath downPath;
						downPath.moveTo(centerX, centerDownY + centerToBottom);
						downPath.lineTo(centerX + sideLength / 2.0, centerDownY - centerToTop);
						downPath.lineTo(centerX - sideLength / 2.0, centerDownY - centerToTop);
						downPath.closeSubpath();
						painter->drawPath(downPath);
					}
				}
				painter->setOpacity(1);
				// 滑块绘制
				QRectF sliderRect = subControlRect(control, option, SC_ScrollBarSlider, widget);
				painter->setBrush(QColor(0x9F, 0x9F, 0x9F));
				if (sopt->orientation == Qt::Horizontal) {
					sliderRect.setRect(sliderRect.x(), sliderRect.bottom() - _sliderMargin - _pSliderExtent, sliderRect.width(), _pSliderExtent);
				} else {
					sliderRect.setRect(sliderRect.right() - _sliderMargin - _pSliderExtent, sliderRect.y(), _pSliderExtent, sliderRect.height());
				}
				painter->drawRoundedRect(sliderRect, _pSliderExtent / 2.0, _pSliderExtent / 2.0);
				painter->restore();
			}
			return;
		}
		default: {
			break;
		}
	}

	QProxyStyle::drawComplexControl(control, option, painter, widget);
}

int CUVScrollBarStyle::pixelMetric(const PixelMetric metric, const QStyleOption* option, const QWidget* widget) const {
	switch (metric) {
		case QStyle::PM_ScrollBarExtent: {
			return _scrollBarExtent;
		}
		default: {
			break;
		}
	}

	return QProxyStyle::pixelMetric(metric, option, widget);
}

int CUVScrollBarStyle::styleHint(const StyleHint stylehint, const QStyleOption* opt, const QWidget* widget, QStyleHintReturn* returnData) const {
	if (stylehint == QStyle::SH_ScrollBar_LeftClickAbsolutePosition) {
		return true;
	}
	return QProxyStyle::styleHint(stylehint, opt, widget, returnData);
}

void CUVScrollBarStyle::startExpandAnimation(const bool isExpand) {
	if (isExpand) {
		_pIsExpand = true;
		const auto opacityAnimation = new QPropertyAnimation(this, "pOpacity");
		connect(opacityAnimation, &QPropertyAnimation::valueChanged, this, [=]() {
			_pScrollBar->update();
		});
		opacityAnimation->setDuration(250);
		opacityAnimation->setEasingCurve(QEasingCurve::InOutSine);
		opacityAnimation->setStartValue(_pOpacity);
		opacityAnimation->setEndValue(1);
		opacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);

		const auto extentAnimation = new QPropertyAnimation(this, "pSliderExtent");
		extentAnimation->setDuration(250);
		extentAnimation->setEasingCurve(QEasingCurve::InOutSine);
		extentAnimation->setStartValue(_pSliderExtent);
		extentAnimation->setEndValue(_scrollBarExtent - 2 * _sliderMargin);
		extentAnimation->start(QAbstractAnimation::DeleteWhenStopped);
	} else {
		const auto opacityAnimation = new QPropertyAnimation(this, "pOpacity");
		connect(opacityAnimation, &QPropertyAnimation::finished, this, [=]() {
			_pIsExpand = false;
		});
		connect(opacityAnimation, &QPropertyAnimation::valueChanged, this, [=]() {
			_pScrollBar->update();
		});
		opacityAnimation->setDuration(250);
		opacityAnimation->setEasingCurve(QEasingCurve::InOutSine);
		opacityAnimation->setStartValue(_pOpacity);
		opacityAnimation->setEndValue(0);
		opacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);

		const auto extentAnimation = new QPropertyAnimation(this, "pSliderExtent");
		extentAnimation->setDuration(250);
		extentAnimation->setEasingCurve(QEasingCurve::InOutSine);
		extentAnimation->setStartValue(_pSliderExtent);
		extentAnimation->setEndValue(2.4);
		extentAnimation->start(QAbstractAnimation::DeleteWhenStopped);
	}
}
