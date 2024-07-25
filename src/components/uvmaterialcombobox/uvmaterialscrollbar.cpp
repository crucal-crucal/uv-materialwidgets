#include "uvmaterialscrollbar.hpp"

#include <QPointer>
#include <QPropertyAnimation>
#include <QStyleOptionSlider>
#include <QWheelEvent>

#include "uvmaterialmenu.hpp"
#include "uvmaterialscrollbarstyle.hpp"
#include "uvmaterialscrollbar_p.hpp"

/**
 * class CUVMaterialScrollBarPrivate
 * @param q pointer to the public class
 * @param parent pointer to the parent object
 */
CUVMaterialScrollBarPrivate::CUVMaterialScrollBarPrivate(CUVMaterialScrollBar* q, QObject* parent): QObject(parent), q_ptr(q) {
}

CUVMaterialScrollBarPrivate::~CUVMaterialScrollBarPrivate() = default;

void CUVMaterialScrollBarPrivate::onRangeChanged(const int min, const int max) {
	Q_Q(CUVMaterialScrollBar);

	if (q->isVisible() && _pIsAnimation) {
		const auto rangeSmoothAnimation = new QPropertyAnimation(this, "pTargetMaximum");
		connect(rangeSmoothAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
			q->blockSignals(true);
			q->setMinimum(value.toInt());
			q->blockSignals(false);
			q->update();
		});
		rangeSmoothAnimation->setEasingCurve(QEasingCurve::OutSine);
		rangeSmoothAnimation->setDuration(250);
		rangeSmoothAnimation->setStartValue(_pTargetMaximum);
		rangeSmoothAnimation->setEndValue(max);
		rangeSmoothAnimation->start(QAbstractAnimation::DeleteWhenStopped);
	} else {
		_pTargetMaximum = max;
	}
}

void CUVMaterialScrollBarPrivate::setTargetMaximum(const int targetMaximum) {
	_pTargetMaximum = targetMaximum;
	emit targetMaximumChanged();
}

int CUVMaterialScrollBarPrivate::getTargetMaximum() const {
	return _pTargetMaximum;
}

void CUVMaterialScrollBarPrivate::_scroll(const int value) {
	Q_Q(CUVMaterialScrollBar);

	_scrollValue -= value;
	_slideSmoothAnimation->stop();
	_slideSmoothAnimation->setStartValue(q->value());
	_slideSmoothAnimation->setEndValue(_scrollValue);
	_slideSmoothAnimation->start();
}

int CUVMaterialScrollBarPrivate::_pixelPosToRangeValue(const int pos) const {
	Q_Q(const CUVMaterialScrollBar);

	QStyleOptionSlider opt;
	q->initStyleOption(&opt);
	const QRect gr = q->style()->subControlRect(QStyle::CC_ScrollBar, &opt, QStyle::SC_ScrollBarGroove, q);
	const QRect sr = q->style()->subControlRect(QStyle::CC_ScrollBar, &opt, QStyle::SC_ScrollBarSlider, q);
	int sliderMin, sliderMax, sliderLength;
	if (q->orientation() == Qt::Horizontal) {
		sliderLength = sr.width();
		sliderMin = gr.x();
		sliderMax = gr.right() - sliderLength + 1;
		if (q->layoutDirection() == Qt::RightToLeft) {
			opt.upsideDown = !opt.upsideDown;
		}
	} else {
		sliderLength = sr.height();
		sliderMin = gr.y();
		sliderMax = gr.bottom() - sliderLength + 1;
	}
	return QStyle::sliderValueFromPosition(q->minimum(), q->maximum(), pos - sliderMin, sliderMax - sliderMin, opt.upsideDown);
}

/**
 * class CUVMaterialScrollBar
 * @param parent parent widget
 */
CUVMaterialScrollBar::CUVMaterialScrollBar(QWidget* parent): QScrollBar(parent), d_ptr(new CUVMaterialScrollBarPrivate(this, this)) {
	Q_D(CUVMaterialScrollBar);

	setSingleStep(1);
	setAttribute(Qt::WA_OpaquePaintEvent, false);
	d->_pTargetMaximum = 0;
	d->_pIsAnimation = false;
	connect(this, &CUVMaterialScrollBar::rangeChanged, d, &CUVMaterialScrollBarPrivate::onRangeChanged);
	setStyle(new CUVMaterialScrollBarStyle(style()));
	d->_slideSmoothAnimation = new QPropertyAnimation(this, "value");
	d->_slideSmoothAnimation->setEasingCurve(QEasingCurve::OutSine);
	d->_slideSmoothAnimation->setDuration(300);
	connect(d->_slideSmoothAnimation, &QPropertyAnimation::finished, this, [=]() { d->_scrollValue = value(); });
}

CUVMaterialScrollBar::CUVMaterialScrollBar(const Qt::Orientation orientation, QWidget* parent): QScrollBar(orientation, parent), d_ptr(new CUVMaterialScrollBarPrivate(this, this)) {
	Q_D(CUVMaterialScrollBar);

	setSingleStep(1);
	setAttribute(Qt::WA_OpaquePaintEvent, false);
	d->_pTargetMaximum = 0;
	d->_pIsAnimation = false;
	connect(this, &CUVMaterialScrollBar::rangeChanged, d, &CUVMaterialScrollBarPrivate::onRangeChanged);
	setStyle(new CUVMaterialScrollBarStyle(style()));
	d->_slideSmoothAnimation = new QPropertyAnimation(this, "value");
	d->_slideSmoothAnimation->setEasingCurve(QEasingCurve::OutSine);
	d->_slideSmoothAnimation->setDuration(300);
	connect(d->_slideSmoothAnimation, &QPropertyAnimation::finished, this, [=]() { d->_scrollValue = value(); });
}

CUVMaterialScrollBar::~CUVMaterialScrollBar() = default;

void CUVMaterialScrollBar::setIsAnimation(const bool isAnimation) {
	Q_D(CUVMaterialScrollBar);

	d->_pIsAnimation = isAnimation;
	emit isAnimationChanged();
}

bool CUVMaterialScrollBar::getIsAnimation() const {
	Q_D(const CUVMaterialScrollBar);

	return d->_pIsAnimation;
}

void CUVMaterialScrollBar::mousePressEvent(QMouseEvent* event) {
	Q_D(CUVMaterialScrollBar);

	d->_slideSmoothAnimation->stop();
	QScrollBar::mousePressEvent(event);
	d->_scrollValue = value();
}

void CUVMaterialScrollBar::mouseReleaseEvent(QMouseEvent* event) {
	Q_D(CUVMaterialScrollBar);

	d->_slideSmoothAnimation->stop();
	QScrollBar::mouseReleaseEvent(event);
	d->_scrollValue = value();
}

void CUVMaterialScrollBar::mouseMoveEvent(QMouseEvent* event) {
	Q_D(CUVMaterialScrollBar);

	d->_slideSmoothAnimation->stop();
	QScrollBar::mouseMoveEvent(event);
	d->_scrollValue = value();
}

void CUVMaterialScrollBar::wheelEvent(QWheelEvent* event) {
	Q_D(CUVMaterialScrollBar);

	if (this->orientation() == Qt::Horizontal) {
		const int horizontalDelta = event->angleDelta().x();
		if (d->_lastHorizontalDeltaAngle != horizontalDelta) {
			d->_scrollValue = value();
			d->_lastHorizontalDeltaAngle = horizontalDelta;
		}
		d->_scroll(horizontalDelta);
	} else {
		const int verticalDelta = event->angleDelta().y();
		if (d->_lastVerticalDeltaAngle != verticalDelta) {
			d->_scrollValue = value();
			d->_lastVerticalDeltaAngle = verticalDelta;
		}
		d->_scroll(verticalDelta);
	}
}

void CUVMaterialScrollBar::contextMenuEvent(QContextMenuEvent* event) {
	Q_D(CUVMaterialScrollBar);

	const bool horiz = this->orientation() == Qt::Horizontal;
	QPointer<CUVMaterialMenu> menu = new CUVMaterialMenu(this);
	menu->setMenuItemHeight(27);
	const QAction* actScrollHere = menu->addAction(tr("Scroll here"));
	menu->addSeparator();
	const QAction* actScrollTop = menu->addAction(horiz ? tr("Left edge") : tr("Top"));
	const QAction* actScrollBottom = menu->addAction(horiz ? tr("Right edge") : tr("Bottom"));
	menu->addSeparator();
	const QAction* actPageUp = menu->addAction(horiz ? tr("Page left") : tr("Page up"));
	const QAction* actPageDn = menu->addAction(horiz ? tr("Page right") : tr("Page down"));
	menu->addSeparator();
	const QAction* actScrollUp = menu->addAction(horiz ? tr("Scroll left") : tr("Scroll up"));
	const QAction* actScrollDn = menu->addAction(horiz ? tr("Scroll right") : tr("Scroll down"));
	const QAction* actionSelected = menu->exec(event->globalPos());
	delete menu;
	if (!actionSelected) {
		return;
	}
	if (actionSelected == actScrollHere) {
		setValue(d->_pixelPosToRangeValue(horiz ? event->pos().x() : event->pos().y()));
	} else if (actionSelected == actScrollTop) {
		triggerAction(QAbstractSlider::SliderToMinimum);
	} else if (actionSelected == actScrollBottom) {
		triggerAction(QAbstractSlider::SliderToMaximum);
	} else if (actionSelected == actPageUp) {
		triggerAction(QAbstractSlider::SliderPageStepSub);
	} else if (actionSelected == actPageDn) {
		triggerAction(QAbstractSlider::SliderPageStepAdd);
	} else if (actionSelected == actScrollUp) {
		triggerAction(QAbstractSlider::SliderSingleStepSub);
	} else if (actionSelected == actScrollDn) {
		triggerAction(QAbstractSlider::SliderSingleStepAdd);
	}
}
