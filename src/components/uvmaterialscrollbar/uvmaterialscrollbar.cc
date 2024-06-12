#include "uvmaterialscrollbar.hpp"

#include <QDebug>
#include <QPainter>
#include <QPainterPath>

#include "uvmaterialscrollbar_internal.hpp"
#include "uvmaterialscrollbar_p.hpp"
#include "uvshared/uvmaterialstyle.hpp"

/*!
 *  \class CUVMaterialScrollBarPrivate
 *  \internal
 */
CUVMaterialScrollBarPrivate::CUVMaterialScrollBarPrivate(CUVMaterialScrollBar* q) : q_ptr(q) {
}

CUVMaterialScrollBarPrivate::~CUVMaterialScrollBarPrivate() = default;

void CUVMaterialScrollBarPrivate::init() {
	Q_Q(CUVMaterialScrollBar);

	stateMachine = new CUVMaterialScrollBarStateMachine(q);
	hideOnMouseOut = true;
	useThemeColors = true;

	q->setMouseTracking(true);
	q->setStyle(&CUVMaterialStyle::instance());
	q->setStyleSheet("QScrollBar:vertical { margin: 0; }"
		"QScrollBar::add-line:vertical { height: 0; margin: 0; }"
		"QScrollBar::sub-line:vertical { height: 0; margin: 0; }");

	stateMachine->start();
}

/*!
 *  \class CUVMaterialScrollBar
 */
CUVMaterialScrollBar::CUVMaterialScrollBar(QWidget* parent)
: QScrollBar(parent),
  d_ptr(new CUVMaterialScrollBarPrivate(this)) {
	d_func()->init();
}

CUVMaterialScrollBar::~CUVMaterialScrollBar() = default;

QSize CUVMaterialScrollBar::sizeHint() const {
	if (Qt::Horizontal == orientation()) {
		return { 1, 10 };
	} else {
		return { 10, 1 };
	}
}

void CUVMaterialScrollBar::setUseThemeColors(const bool value) {
	Q_D(CUVMaterialScrollBar);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	update();
}

bool CUVMaterialScrollBar::useThemeColors() const {
	Q_D(const CUVMaterialScrollBar);

	return d->useThemeColors;
}

void CUVMaterialScrollBar::setCanvasColor(const QColor& color) {
	Q_D(CUVMaterialScrollBar);

	d->canvasColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialScrollBar::canvasColor() const {
	Q_D(const CUVMaterialScrollBar);

	if (d->useThemeColors || !d->canvasColor.isValid()) {
		return parentWidget()->palette().color(backgroundRole());
	} else {
		return d->canvasColor;
	}
}

void CUVMaterialScrollBar::setBackgroundColor(const QColor& color) {
	Q_D(CUVMaterialScrollBar);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialScrollBar::backgroundColor() const {
	Q_D(const CUVMaterialScrollBar);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("border");
	} else {
		return d->backgroundColor;
	}
}

void CUVMaterialScrollBar::setSliderColor(const QColor& color) {
	Q_D(CUVMaterialScrollBar);

	d->sliderColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialScrollBar::sliderColor() const {
	Q_D(const CUVMaterialScrollBar);

	if (d->useThemeColors || !d->sliderColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("primary1");
	} else {
		return d->sliderColor;
	}
}

void CUVMaterialScrollBar::setHideOnMouseOut(const bool value) {
	Q_D(CUVMaterialScrollBar);

	d->hideOnMouseOut = value;
	update();
}

bool CUVMaterialScrollBar::hideOnMouseOut() const {
	Q_D(const CUVMaterialScrollBar);

	return d->hideOnMouseOut;
}

void CUVMaterialScrollBar::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	Q_D(CUVMaterialScrollBar);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.fillRect(rect(), canvasColor());

	int x, y, w, h;
	rect().getRect(&x, &y, &w, &h);

	constexpr QMargins margins(2, 2, 2, 2);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(backgroundColor());
	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);

	if (d->hideOnMouseOut) {
		painter.setOpacity(d->stateMachine->opacity());
	}

	const QRect trimmed(rect().marginsRemoved(margins));

	QPainterPath path;
	path.addRoundedRect(trimmed, 3, 3);
	painter.setClipPath(path);

	painter.drawRect(trimmed);

	const qreal q = (Qt::Horizontal == orientation() ? w : h) / static_cast<qreal>(maximum() - minimum() + pageStep() - 1);

	const QRect handle = Qt::Horizontal == orientation()
		                     ? QRect(sliderPosition() * q, y, pageStep() * q, h) : QRect(x, sliderPosition() * q, w, pageStep() * q); // NOLINT

	brush.setColor(sliderColor());
	painter.setBrush(brush);

	painter.drawRoundedRect(handle, 9, 9);
}
