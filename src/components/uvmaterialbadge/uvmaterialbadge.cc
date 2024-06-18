#include "uvmaterialbadge.hpp"

#include <QPainter>

#include "uvmaterialbadge_p.hpp"
#include "uvshared/uvmaterialstyle.hpp"

/*!
 *  \class CUVMaterialBadgePrivate
 *  \internal
 */
CUVMaterialBadgePrivate::CUVMaterialBadgePrivate(CUVMaterialBadge* q): q_ptr(q) {
}

CUVMaterialBadgePrivate::~CUVMaterialBadgePrivate() = default;

void CUVMaterialBadgePrivate::init() {
	Q_Q(CUVMaterialBadge);

	x = 0;
	y = 0;
	padding = 10;
	useThemeColors = true;

	q->setAttribute(Qt::WA_TransparentForMouseEvents);

	QFont font(q->font());
	font.setPointSizeF(10);
	font.setStyleName("Bold");
	q->setFont(font);

	q->setText("+1");
}

/*!
 *  \class CUVMaterialBadge
 */
CUVMaterialBadge::CUVMaterialBadge(QWidget* parent)
: CUVMaterialOverlayWidget(parent), d_ptr(new CUVMaterialBadgePrivate(this)) {
	d_func()->init();
}

CUVMaterialBadge::CUVMaterialBadge(const QIcon& icon, QWidget* parent)
: CUVMaterialOverlayWidget(parent), d_ptr(new CUVMaterialBadgePrivate(this)) {
	d_func()->init();

	setIcon(icon);
}

CUVMaterialBadge::CUVMaterialBadge(const QString& text, QWidget* parent)
: CUVMaterialOverlayWidget(parent), d_ptr(new CUVMaterialBadgePrivate(this)) {
	d_func()->init();

	setText(text);
}

CUVMaterialBadge::~CUVMaterialBadge() = default;

void CUVMaterialBadge::setUseThemeColors(const bool value) {
	Q_D(CUVMaterialBadge);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	update();
}

bool CUVMaterialBadge::useThemeColors() const {
	Q_D(const CUVMaterialBadge);

	return d->useThemeColors;
}

void CUVMaterialBadge::setTextColor(const QColor& color) {
	Q_D(CUVMaterialBadge);

	d->textColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialBadge::textColor() const {
	Q_D(const CUVMaterialBadge);

	if (d->useThemeColors || !d->textColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("canvas");
	} else {
		return d->textColor;
	}
}

void CUVMaterialBadge::setBackgroundColor(const QColor& color) {
	Q_D(CUVMaterialBadge);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialBadge::backgroundColor() const {
	Q_D(const CUVMaterialBadge);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("accent1");
	} else {
		return d->backgroundColor;
	}
}

void CUVMaterialBadge::setRelativePosition(const QPointF& pos) {
	setRelativePosition(pos.x(), pos.y());
}

void CUVMaterialBadge::setRelativePosition(const qreal x, const qreal y) {
	Q_D(CUVMaterialBadge);

	d->x = x;
	d->y = y;
	update();
}

QPointF CUVMaterialBadge::relativePosition() const {
	Q_D(const CUVMaterialBadge);

	return { d->x, d->y };
}

void CUVMaterialBadge::setRelativeXPosition(const qreal x) {
	Q_D(CUVMaterialBadge);

	d->x = x;
	update();
}

qreal CUVMaterialBadge::relativeXPosition() const {
	Q_D(const CUVMaterialBadge);

	return d->x;
}

void CUVMaterialBadge::setRelativeYPosition(const qreal y) {
	Q_D(CUVMaterialBadge);

	d->y = y;
	update();
}

qreal CUVMaterialBadge::relativeYPosition() const {
	Q_D(const CUVMaterialBadge);

	return d->y;
}

QSize CUVMaterialBadge::sizeHint() const {
	const int s = getDiameter();
	return { s + 4, s + 4 };
}

void CUVMaterialBadge::setIcon(const QIcon& icon) {
	Q_D(CUVMaterialBadge);

	d->icon = icon;
	update();
}

QIcon CUVMaterialBadge::icon() const {
	Q_D(const CUVMaterialBadge);

	return d->icon;
}

void CUVMaterialBadge::setText(const QString& text) {
	Q_D(CUVMaterialBadge);

	d->text = text;

	if (!d->icon.isNull()) {
		d->icon = QIcon();
	}

	d->size = fontMetrics().size(Qt::TextShowMnemonic, text);

	update();
}

QString CUVMaterialBadge::text() const {
	Q_D(const CUVMaterialBadge);

	return d->text;
}

void CUVMaterialBadge::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	Q_D(CUVMaterialBadge);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.translate(d->x, d->y);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(isEnabled() ? backgroundColor() : CUVMaterialStyle::instance().themeColor("disabled"));
	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);

	const int s = getDiameter();

	QRectF r(0, 0, s, s);
	r.translate(QPointF((width() - s), (height() - s)) / 2);

	if (d->icon.isNull()) {
		painter.drawEllipse(r);
		painter.setPen(textColor());
		painter.setBrush(Qt::NoBrush);
		painter.drawText(r.translated(0, -0.5), Qt::AlignCenter, d->text);
	} else {
		painter.drawEllipse(r);
		QRectF q(0, 0, 16, 16);
		q.moveCenter(r.center());
		QPixmap pixmap = icon().pixmap(16, 16);
		QPainter icon(&pixmap);
		icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
		icon.fillRect(pixmap.rect(), textColor());
		painter.drawPixmap(q.toRect(), pixmap);
	}
}

int CUVMaterialBadge::getDiameter() const {
	Q_D(const CUVMaterialBadge);

	if (d->icon.isNull()) {
		return qMax(d->size.width(), d->size.height()) + d->padding;
	} else {
		return 24;
	}
}
