#include "uvmaterialflatbutton.hpp"

#include <QBitmap>
#include <QIcon>
#include <QPainter>
#include <QResizeEvent>

#include "uvmaterialflatbutton_internal.hpp"
#include "uvmaterialflatbutton_p.hpp"
#include "uvshared/uvmaterialripple.hpp"
#include "uvshared/uvmaterialrippleoverlay.hpp"
#include "uvshared/uvmaterialstyle.hpp"

/*!
 *  \class CUVMaterialFlatButtonPrivate
 */
CUVMaterialFlatButtonPrivate::CUVMaterialFlatButtonPrivate(CUVMaterialFlatButton* q): q_ptr(q) {
}

CUVMaterialFlatButtonPrivate::~CUVMaterialFlatButtonPrivate() = default;

void CUVMaterialFlatButtonPrivate::init() {
	Q_Q(CUVMaterialFlatButton);

	rippleOverlay = new CUVMaterialRippleOverlay(q);
	stateMachine = new CUVMaterialFlatButtonStateMachine(q);
	role = Material::Default;
	rippleStyle = Material::PositionedRipple;
	iconPlacement = Material::LeftIcon;
	overlayStyle = Material::GrayOverlay;
	bgMode = Qt::TransparentMode;
	textAlignment = Qt::AlignHCenter;
	fixedRippleRadius = 64;
	cornerRadius = 3;
	baseOpacity = 0.13;
	fontSize = 10; // 10.5;
	useThemeColors = true;
	useFixedRippleRadius = false;
	haloVisible = true;

	q->setStyle(&CUVMaterialStyle::instance());
	q->setAttribute(Qt::WA_Hover);
	q->setMouseTracking(true);

	QFont font("Roboto", static_cast<int>(fontSize), QFont::Medium);
	font.setCapitalization(QFont::AllUppercase);
	q->setFont(font);

	QPainterPath path;
	path.addRoundedRect(q->rect(), cornerRadius, cornerRadius);
	rippleOverlay->setClipPath(path);
	rippleOverlay->setClipping(true);

	stateMachine->setupProperties();
	stateMachine->startAnimations();
}

/*!
 *  \class CUVMaterialFlatButton
 */
CUVMaterialFlatButton::CUVMaterialFlatButton(QWidget* parent, const Material::ButtonPreset preset)
: QPushButton(parent), d_ptr(new CUVMaterialFlatButtonPrivate(this)) {
	d_func()->init();

	applyPreset(preset);
}

CUVMaterialFlatButton::CUVMaterialFlatButton(const QString& text, QWidget* parent, const Material::ButtonPreset preset)
: QPushButton(text, parent), d_ptr(new CUVMaterialFlatButtonPrivate(this)) {
	d_func()->init();

	applyPreset(preset);
}

CUVMaterialFlatButton::CUVMaterialFlatButton(const QString& text, const Material::Role role, QWidget* parent, const Material::ButtonPreset preset)
: QPushButton(text, parent), d_ptr(new CUVMaterialFlatButtonPrivate(this)) {
	d_func()->init();

	applyPreset(preset);
	setRole(role);
}

CUVMaterialFlatButton::~CUVMaterialFlatButton() = default;

void CUVMaterialFlatButton::applyPreset(const Material::ButtonPreset preset) {
	switch (preset) {
		case Material::FlatPreset:
			setOverlayStyle(Material::NoOverlay);
			break;
		case Material::CheckablePreset:
			setOverlayStyle(Material::NoOverlay);
			setCheckable(true);
			setHaloVisible(false);
			break;
		default:
			break;
	}
}

void CUVMaterialFlatButton::setUseThemeColors(const bool value) {
	Q_D(CUVMaterialFlatButton);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	d->stateMachine->setupProperties();
}

bool CUVMaterialFlatButton::useThemeColors() const {
	Q_D(const CUVMaterialFlatButton);

	return d->useThemeColors;
}

void CUVMaterialFlatButton::setRole(const Material::Role role) {
	Q_D(CUVMaterialFlatButton);

	d->role = role;
	d->stateMachine->setupProperties();
}

Material::Role CUVMaterialFlatButton::role() const {
	Q_D(const CUVMaterialFlatButton);

	return d->role;
}

void CUVMaterialFlatButton::setForegroundColor(const QColor& color) {
	Q_D(CUVMaterialFlatButton);

	d->foregroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialFlatButton::foregroundColor() const {
	Q_D(const CUVMaterialFlatButton);

	if (d->useThemeColors || !d->foregroundColor.isValid()) {
		if (Qt::OpaqueMode == d->bgMode) {
			return CUVMaterialStyle::instance().themeColor("canvas");
		}
		switch (d->role) {
			case Material::Primary:
				return CUVMaterialStyle::instance().themeColor("primary1");
			case Material::Secondary:
				return CUVMaterialStyle::instance().themeColor("accent1");
			case Material::Default:
			default:
				return CUVMaterialStyle::instance().themeColor("text");
		}
	}
	return d->foregroundColor;
}

void CUVMaterialFlatButton::setBackgroundColor(const QColor& color) {
	Q_D(CUVMaterialFlatButton);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialFlatButton::backgroundColor() const {
	Q_D(const CUVMaterialFlatButton);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		switch (d->role) {
			case Material::Primary:
				return CUVMaterialStyle::instance().themeColor("primary1");
			case Material::Secondary:
				return CUVMaterialStyle::instance().themeColor("accent1");
			case Material::Default:
			default:
				return CUVMaterialStyle::instance().themeColor("text");
		}
	}
	return d->backgroundColor;
}

void CUVMaterialFlatButton::setOverlayColor(const QColor& color) {
	Q_D(CUVMaterialFlatButton);

	d->overlayColor = color;

	MATERIAL_DISABLE_THEME_COLORS

	setOverlayStyle(Material::TintedOverlay);
	update();
}

QColor CUVMaterialFlatButton::overlayColor() const {
	Q_D(const CUVMaterialFlatButton);

	if (d->useThemeColors || !d->overlayColor.isValid()) {
		return foregroundColor();
	}
	return d->overlayColor;
}

void CUVMaterialFlatButton::setDisabledForegroundColor(const QColor& color) {
	Q_D(CUVMaterialFlatButton);

	d->disabledColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialFlatButton::disabledForegroundColor() const {
	Q_D(const CUVMaterialFlatButton);

	if (d->useThemeColors || !d->disabledColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("disabled");
	} else {
		return d->disabledColor;
	}
}

void CUVMaterialFlatButton::setDisabledBackgroundColor(const QColor& color) {
	Q_D(CUVMaterialFlatButton);

	d->disabledBackgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialFlatButton::disabledBackgroundColor() const {
	Q_D(const CUVMaterialFlatButton);

	if (d->useThemeColors || !d->disabledBackgroundColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("disabled3");
	} else {
		return d->disabledBackgroundColor;
	}
}

void CUVMaterialFlatButton::setFontSize(const qreal size) {
	Q_D(CUVMaterialFlatButton);

	d->fontSize = size;

	QFont f(font());
	f.setPointSizeF(size);
	setFont(f);

	update();
}

qreal CUVMaterialFlatButton::fontSize() const {
	Q_D(const CUVMaterialFlatButton);

	return d->fontSize;
}

void CUVMaterialFlatButton::setHaloVisible(const bool visible) {
	Q_D(CUVMaterialFlatButton);

	d->haloVisible = visible;
	update();
}

bool CUVMaterialFlatButton::isHaloVisible() const {
	Q_D(const CUVMaterialFlatButton);

	return d->haloVisible;
}

void CUVMaterialFlatButton::setOverlayStyle(const Material::OverlayStyle style) {
	Q_D(CUVMaterialFlatButton);

	d->overlayStyle = style;
	update();
}

Material::OverlayStyle CUVMaterialFlatButton::overlayStyle() const {
	Q_D(const CUVMaterialFlatButton);

	return d->overlayStyle;
}

void CUVMaterialFlatButton::setRippleStyle(const Material::RippleStyle style) {
	Q_D(CUVMaterialFlatButton);

	d->rippleStyle = style;
}

Material::RippleStyle CUVMaterialFlatButton::rippleStyle() const {
	Q_D(const CUVMaterialFlatButton);

	return d->rippleStyle;
}

void CUVMaterialFlatButton::setIconPlacement(const Material::ButtonIconPlacement placement) {
	Q_D(CUVMaterialFlatButton);

	d->iconPlacement = placement;
	update();
}

Material::ButtonIconPlacement CUVMaterialFlatButton::iconPlacement() const {
	Q_D(const CUVMaterialFlatButton);

	return d->iconPlacement;
}

void CUVMaterialFlatButton::setCornerRadius(const qreal radius) {
	Q_D(CUVMaterialFlatButton);

	d->cornerRadius = radius;
	updateClipPath();
	update();
}

qreal CUVMaterialFlatButton::cornerRadius() const {
	Q_D(const CUVMaterialFlatButton);

	return d->cornerRadius;
}

void CUVMaterialFlatButton::setBackgroundMode(const Qt::BGMode mode) {
	Q_D(CUVMaterialFlatButton);

	d->bgMode = mode;
	d->stateMachine->setupProperties();
}

Qt::BGMode CUVMaterialFlatButton::backgroundMode() const {
	Q_D(const CUVMaterialFlatButton);

	return d->bgMode;
}

void CUVMaterialFlatButton::setBaseOpacity(const qreal opacity) {
	Q_D(CUVMaterialFlatButton);

	d->baseOpacity = opacity;
	d->stateMachine->setupProperties();
}

qreal CUVMaterialFlatButton::baseOpacity() const {
	Q_D(const CUVMaterialFlatButton);

	return d->baseOpacity;
}

void CUVMaterialFlatButton::setCheckable(const bool value) {
	Q_D(CUVMaterialFlatButton);

	d->stateMachine->updateCheckedStatus();

	QPushButton::setCheckable(value);
}

void CUVMaterialFlatButton::setHasFixedRippleRadius(const bool value) {
	Q_D(CUVMaterialFlatButton);

	d->useFixedRippleRadius = value;
}

bool CUVMaterialFlatButton::hasFixedRippleRadius() const {
	Q_D(const CUVMaterialFlatButton);

	return d->useFixedRippleRadius;
}

void CUVMaterialFlatButton::setFixedRippleRadius(const qreal radius) {
	Q_D(CUVMaterialFlatButton);

	d->fixedRippleRadius = radius;
	setHasFixedRippleRadius(true);
}

void CUVMaterialFlatButton::setTextAlignment(const Qt::Alignment alignment) {
	Q_D(CUVMaterialFlatButton);

	d->textAlignment = alignment;
}

Qt::Alignment CUVMaterialFlatButton::textAlignment() const {
	Q_D(const CUVMaterialFlatButton);

	return d->textAlignment;
}

QSize CUVMaterialFlatButton::sizeHint() const {
	ensurePolished();

	const QSize label(fontMetrics().size(Qt::TextSingleLine, text()));

	int w = 20 + label.width();
	int h = label.height();
	if (!icon().isNull()) {
		w += iconSize().width() + CUVMaterialFlatButton::IconPadding;
		h = qMax(h, iconSize().height());
	}
	return { w, 20 + h };
}

CUVMaterialFlatButton::CUVMaterialFlatButton(CUVMaterialFlatButtonPrivate& d, QWidget* parent, const Material::ButtonPreset preset)
: QPushButton(parent), d_ptr(&d) {
	d_func()->init();

	applyPreset(preset);
}

void CUVMaterialFlatButton::checkStateSet() {
	Q_D(CUVMaterialFlatButton);

	d->stateMachine->updateCheckedStatus();

	QPushButton::checkStateSet();
}

void CUVMaterialFlatButton::mousePressEvent(QMouseEvent* event) {
	Q_D(CUVMaterialFlatButton);

	if (Material::NoRipple != d->rippleStyle) {
		QPoint pos;
		qreal radiusEndValue;

		if (Material::CenteredRipple == d->rippleStyle) {
			pos = rect().center();
		} else {
			pos = event->pos();
		}

		if (d->useFixedRippleRadius) {
			radiusEndValue = d->fixedRippleRadius;
		} else {
			radiusEndValue = static_cast<qreal>(width()) / 2;
		}

		auto* ripple = new CUVMaterialRipple(pos);

		ripple->setRadiusEndValue(radiusEndValue);
		ripple->setOpacityStartValue(0.35);
		ripple->setColor(foregroundColor());
		ripple->radiusAnimation()->setDuration(600);
		ripple->opacityAnimation()->setDuration(1300);

		d->rippleOverlay->addRipple(ripple);
	}

	QPushButton::mousePressEvent(event);
}

void CUVMaterialFlatButton::mouseReleaseEvent(QMouseEvent* event) {
	Q_D(CUVMaterialFlatButton);

	QPushButton::mouseReleaseEvent(event);

	d->stateMachine->updateCheckedStatus();
}

void CUVMaterialFlatButton::resizeEvent(QResizeEvent* event) {
	QPushButton::resizeEvent(event);

	updateClipPath();
}

void CUVMaterialFlatButton::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	Q_D(CUVMaterialFlatButton);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	if (const qreal cr = d->cornerRadius; cr > 0) {
		QPainterPath path;
		path.addRoundedRect(rect(), cr, cr);

		painter.setClipPath(path);
		painter.setClipping(true);
	}

	paintBackground(&painter);
	paintHalo(&painter);

	painter.setOpacity(1);
	painter.setClipping(false);

	paintForeground(&painter);
}

void CUVMaterialFlatButton::paintBackground(QPainter* painter) {
	Q_D(CUVMaterialFlatButton);

	const qreal overlayOpacity = d->stateMachine->overlayOpacity();
	const qreal checkedProgress = d->stateMachine->checkedOverlayProgress();

	if (Qt::OpaqueMode == d->bgMode) {
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		if (isEnabled()) {
			brush.setColor(backgroundColor());
		} else {
			brush.setColor(disabledBackgroundColor());
		}
		painter->setOpacity(1);
		painter->setBrush(brush);
		painter->setPen(Qt::NoPen);
		painter->drawRect(rect());
	}

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	painter->setPen(Qt::NoPen);

	if (!isEnabled()) {
		return;
	}

	if ((Material::NoOverlay != d->overlayStyle) && (overlayOpacity > 0)) {
		if (Material::TintedOverlay == d->overlayStyle) {
			brush.setColor(overlayColor());
		} else {
			brush.setColor(Qt::gray);
		}
		painter->setOpacity(overlayOpacity);
		painter->setBrush(brush);
		painter->drawRect(rect());
	}

	if (isCheckable() && checkedProgress > 0) {
		const qreal q = Qt::TransparentMode == d->bgMode ? 0.45 : 0.7;
		brush.setColor(foregroundColor());
		painter->setOpacity(q * checkedProgress);
		painter->setBrush(brush);
		QRect r(rect());
		r.setHeight(r.height() * static_cast<int>(checkedProgress));
		painter->drawRect(r);
	}
}

void CUVMaterialFlatButton::paintHalo(QPainter* painter) {
	Q_D(CUVMaterialFlatButton);

	if (!d->haloVisible) {
		return;
	}

	const qreal opacity = d->stateMachine->haloOpacity();
	const qreal s = d->stateMachine->haloScaleFactor() * d->stateMachine->haloSize();
	const qreal radius = static_cast<qreal>(width()) * s;

	if (isEnabled() && opacity > 0) {
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(foregroundColor());
		painter->setOpacity(opacity);
		painter->setBrush(brush);
		painter->setPen(Qt::NoPen);
		const QPointF center = rect().center();
		painter->drawEllipse(center, radius, radius);
	}
}

#define COLOR_INTERPOLATE(CH) ((1 - progress) * source.CH() + progress * dest.CH())

void CUVMaterialFlatButton::paintForeground(QPainter* painter) {
	Q_D(CUVMaterialFlatButton);

	if (isEnabled()) {
		painter->setPen(foregroundColor());
		if (const qreal progress = d->stateMachine->checkedOverlayProgress(); isCheckable() && progress > 0) {
			QColor source = foregroundColor();
			QColor dest = Qt::TransparentMode == d->bgMode ? Qt::white : backgroundColor();
			if (qFuzzyCompare(1, progress)) {
				painter->setPen(dest);
			} else {
				painter->setPen(QColor(COLOR_INTERPOLATE(red), COLOR_INTERPOLATE(green), COLOR_INTERPOLATE(blue), COLOR_INTERPOLATE(alpha)));
			}
		}
	} else {
		painter->setPen(disabledForegroundColor());
	}

	if (icon().isNull()) {
		if (Qt::AlignLeft == d->textAlignment) {
			painter->drawText(rect().adjusted(12, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text());
		} else {
			painter->drawText(rect(), Qt::AlignCenter, text());
		}
		return;
	}

	QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));
	QSize base(size() - textSize);

	const int iw = iconSize().width() + IconPadding;
	QPoint pos(Qt::AlignLeft == d->textAlignment ? 12 : (base.width() - iw) / 2, 0);

	QRect textGeometry(pos + QPoint(0, base.height() / 2), textSize);
	QRect iconGeometry(pos + QPoint(0, (height() - iconSize().height()) / 2), iconSize());

	if (Material::LeftIcon == d->iconPlacement) {
		textGeometry.translate(iw, 0);
	} else {
		iconGeometry.translate(textSize.width() + IconPadding, 0);
	}

	painter->drawText(textGeometry, Qt::AlignCenter, text());

	QPixmap pixmap = icon().pixmap(iconSize());
	QPainter icon(&pixmap);
	icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
	icon.fillRect(pixmap.rect(), painter->pen().color());
	painter->drawPixmap(iconGeometry, pixmap);
}

void CUVMaterialFlatButton::updateClipPath() {
	Q_D(CUVMaterialFlatButton);

	const qreal radius = d->cornerRadius;

	QPainterPath path;
	path.addRoundedRect(rect(), radius, radius);
	d->rippleOverlay->setClipPath(path);
}
