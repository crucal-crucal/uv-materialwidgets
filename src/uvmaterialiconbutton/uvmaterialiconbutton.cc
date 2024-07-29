#include "uvmaterialiconbutton.hpp"

#include <QEvent>
#include <QPainter>

#include "uvmaterialiconbutton_p.hpp"
#include "uvmaterialshared/uvmaterialrippleoverlay.hpp"
#include "uvmaterialshared/uvmaterialstyle.hpp"

/*!
 *  \class CUVMaterialIconButtonPrivate
 *  \internal
 */
CUVMaterialIconButtonPrivate::CUVMaterialIconButtonPrivate(CUVMaterialIconButton* q): q_ptr(q) {
}

CUVMaterialIconButtonPrivate::~CUVMaterialIconButtonPrivate() = default;

void CUVMaterialIconButtonPrivate::init() {
	Q_Q(CUVMaterialIconButton);

	rippleOverlay = new CUVMaterialRippleOverlay(q->parentWidget());
	useThemeColors = true;

	rippleOverlay->installEventFilter(q);

	q->setStyle(&CUVMaterialStyle::instance());

	QSizePolicy policy;
	policy.setWidthForHeight(true);
	q->setSizePolicy(policy);
}

void CUVMaterialIconButtonPrivate::updateRipple() {
	Q_Q(CUVMaterialIconButton);

	QRect r(q->rect());
	r.setSize(QSize(q->width() * 2, q->height() * 2));
	r.moveCenter(q->geometry().center());
	rippleOverlay->setGeometry(r);
}

/*!
 *  \class CUVMaterialIconButton
 */
CUVMaterialIconButton::CUVMaterialIconButton(const QIcon& icon, QWidget* parent)
: QAbstractButton(parent), d_ptr(new CUVMaterialIconButtonPrivate(this)) {
	d_func()->init();

	setIcon(icon);
}

CUVMaterialIconButton::~CUVMaterialIconButton() = default;

QSize CUVMaterialIconButton::sizeHint() const {
	return iconSize();
}

void CUVMaterialIconButton::setUseThemeColors(const bool value) {
	Q_D(CUVMaterialIconButton);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	update();
}

bool CUVMaterialIconButton::useThemeColors() const {
	Q_D(const CUVMaterialIconButton);

	return d->useThemeColors;
}

void CUVMaterialIconButton::setColor(const QColor& color) {
	Q_D(CUVMaterialIconButton);

	d->color = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialIconButton::color() const {
	Q_D(const CUVMaterialIconButton);

	if (d->useThemeColors || !d->color.isValid()) {
		return CUVMaterialStyle::instance().themeColor("text");
	}
	return d->color;
}

void CUVMaterialIconButton::setDisabledColor(const QColor& color) {
	Q_D(CUVMaterialIconButton);

	d->disabledColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialIconButton::disabledColor() const {
	Q_D(const CUVMaterialIconButton);

	if (d->useThemeColors || !d->disabledColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("disabled");
	}
	return d->disabledColor;
}

CUVMaterialIconButton::CUVMaterialIconButton(CUVMaterialIconButtonPrivate& d, QWidget* parent)
: QAbstractButton(parent), d_ptr(&d) {
	d_func()->init();
}

bool CUVMaterialIconButton::event(QEvent* event) {
	Q_D(CUVMaterialIconButton);

	switch (event->type()) {
		case QEvent::Move:
		case QEvent::Resize:
			d->updateRipple();
			break;
		case QEvent::ParentChange: {
			if (QWidget* widget; (widget = parentWidget())) {
				d->rippleOverlay->setParent(widget);
			}
			break;
		}
		default:
			break;
	}
	return QAbstractButton::event(event);
}

bool CUVMaterialIconButton::eventFilter(QObject* watched, QEvent* event) {
	if (QEvent::Resize == event->type()) {
		Q_D(CUVMaterialIconButton);

		d->updateRipple();
	}
	return QAbstractButton::eventFilter(watched, event);
}

void CUVMaterialIconButton::mousePressEvent(QMouseEvent* event) {
	Q_D(CUVMaterialIconButton);

	d->rippleOverlay->addRipple(QPoint(d->rippleOverlay->width(), d->rippleOverlay->height()) / 2, iconSize().width());
	emit clicked();

	QAbstractButton::mousePressEvent(event);
}

void CUVMaterialIconButton::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	QPainter painter(this);

	QPixmap pixmap = icon().pixmap(iconSize());
	QPainter icon(&pixmap);
	icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
	icon.fillRect(pixmap.rect(), isEnabled() ? color() : disabledColor());

	const QRect r(rect());
	const int w = pixmap.width();
	const int h = pixmap.height();
	painter.drawPixmap(QRect((r.width() - w) / 2, (r.height() - h) / 2, w, h), pixmap);
}
