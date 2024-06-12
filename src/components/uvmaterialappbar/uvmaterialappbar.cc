#include "uvmaterialappbar.hpp"

#include <QPainter>
#include <QtWidgets/QGraphicsDropShadowEffect>

#include "uvmaterialappbar_p.hpp"
#include "uvshared/uvmaterialstyle.hpp"

/*!
 *  \class CUVMaterialAppBarPrivate
 *  \internal
 */
CUVMaterialAppBarPrivate::CUVMaterialAppBarPrivate(CUVMaterialAppBar* q): q_ptr(q) {
}

CUVMaterialAppBarPrivate::~CUVMaterialAppBarPrivate() = default;

void CUVMaterialAppBarPrivate::init() {
	Q_Q(CUVMaterialAppBar);

	useThemeColors = true;

	auto* effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(11);
	effect->setColor(QColor(0, 0, 0, 50));
	effect->setOffset(0, 3);

	q->setGraphicsEffect(effect);

	auto* layout = new QHBoxLayout;
	q->setLayout(layout);
}

/*!
 *  \class CUVMaterialAppBar
 */
CUVMaterialAppBar::CUVMaterialAppBar(QWidget* parent): QWidget(parent), d_ptr(new CUVMaterialAppBarPrivate(this)) {
	d_func()->init();
}

CUVMaterialAppBar::~CUVMaterialAppBar() = default;

QSize CUVMaterialAppBar::sizeHint() const {
	return { -1, 64 };
}

void CUVMaterialAppBar::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	QPainter painter(this);

	painter.fillRect(rect(), backgroundColor());
}

void CUVMaterialAppBar::setUseThemeColors(const bool value) {
	Q_D(CUVMaterialAppBar);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	update();
}

bool CUVMaterialAppBar::useThemeColors() const {
	Q_D(const CUVMaterialAppBar);

	return d->useThemeColors;
}

void CUVMaterialAppBar::setForegroundColor(const QColor& color) {
	Q_D(CUVMaterialAppBar);

	d->foregroundColor = color;

	if (d->useThemeColors == true) {
		d->useThemeColors = false;
	}
	update();
}

QColor CUVMaterialAppBar::foregroundColor() const {
	Q_D(const CUVMaterialAppBar);

	if (d->useThemeColors || !d->foregroundColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("primary1");
	} else {
		return d->foregroundColor;
	}
}

void CUVMaterialAppBar::setBackgroundColor(const QColor& color) {
	Q_D(CUVMaterialAppBar);

	d->backgroundColor = color;

	if (d->useThemeColors == true) {
		d->useThemeColors = false;
	}
	update();
}

QColor CUVMaterialAppBar::backgroundColor() const {
	Q_D(const CUVMaterialAppBar);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("primary1");
	} else {
		return d->backgroundColor;
	}
}
