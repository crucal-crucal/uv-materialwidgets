#include "uvmaterialavatar.hpp"

#include <QPainter>
#include <QPainterPath>

#include "uvmaterialavatar_p.hpp"
#include "uvshared/uvmaterialstyle.hpp"

/*!
 *  \class CUVMaterialAvatarPrivate
 *  \internal
 */
CUVMaterialAvatarPrivate::CUVMaterialAvatarPrivate(CUVMaterialAvatar* q): q_ptr(q) {
}

CUVMaterialAvatarPrivate::~CUVMaterialAvatarPrivate() = default;

void CUVMaterialAvatarPrivate::init() {
	Q_Q(CUVMaterialAvatar);

	size = 40;
	type = Material::LetterAvatar;
	useThemeColors = true;

	QFont font(q->font());
	font.setPointSizeF(16);
	q->setFont(font);

	constexpr QSizePolicy policy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	q->setSizePolicy(policy);
}

/*!
 *  \class CUVMaterialAvatar
 */
CUVMaterialAvatar::CUVMaterialAvatar(QWidget* parent)
: QWidget(parent), d_ptr(new CUVMaterialAvatarPrivate(this)) {
	d_func()->init();
}

CUVMaterialAvatar::CUVMaterialAvatar(const QIcon& icon, QWidget* parent)
: QWidget(parent), d_ptr(new CUVMaterialAvatarPrivate(this)) {
	d_func()->init();

	setIcon(icon);
}

CUVMaterialAvatar::CUVMaterialAvatar(const QChar& letter, QWidget* parent)
: QWidget(parent), d_ptr(new CUVMaterialAvatarPrivate(this)) {
	d_func()->init();

	setLetter(letter);
}

CUVMaterialAvatar::CUVMaterialAvatar(const QImage& image, QWidget* parent)
: QWidget(parent), d_ptr(new CUVMaterialAvatarPrivate(this)) {
	d_func()->init();

	setImage(image);
}

CUVMaterialAvatar::~CUVMaterialAvatar() = default;

void CUVMaterialAvatar::setUseThemeColors(const bool value) {
	Q_D(CUVMaterialAvatar);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	update();
}

bool CUVMaterialAvatar::useThemeColors() const {
	Q_D(const CUVMaterialAvatar);

	return d->useThemeColors;
}

void CUVMaterialAvatar::setTextColor(const QColor& color) {
	Q_D(CUVMaterialAvatar);

	d->textColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialAvatar::textColor() const {
	Q_D(const CUVMaterialAvatar);

	if (d->useThemeColors || !d->textColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("canvas");
	} else {
		return d->textColor;
	}
}

void CUVMaterialAvatar::setBackgroundColor(const QColor& color) {
	Q_D(CUVMaterialAvatar);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialAvatar::backgroundColor() const {
	Q_D(const CUVMaterialAvatar);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("primary1");
	} else {
		return d->backgroundColor;
	}
}

QSize CUVMaterialAvatar::sizeHint() const {
	Q_D(const CUVMaterialAvatar);

	return { d->size + 2, d->size + 2 };
}

void CUVMaterialAvatar::setSize(const int size) {
	Q_D(CUVMaterialAvatar);

	d->size = size;

	if (!d->image.isNull()) {
		d->pixmap = QPixmap::fromImage(d->image.scaled(d->size, d->size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	}

	QFont f(font());
	f.setPointSizeF(static_cast<qreal>(size) * 16 / 40);
	setFont(f);

	update();
}

int CUVMaterialAvatar::Size() const {
	Q_D(const CUVMaterialAvatar);

	return d->size;
}

void CUVMaterialAvatar::setLetter(const QChar& letter) {
	Q_D(CUVMaterialAvatar);

	d->letter = letter;
	d->type = Material::LetterAvatar;
	update();
}

void CUVMaterialAvatar::setImage(const QImage& image) {
	Q_D(CUVMaterialAvatar);

	d->image = image;
	d->type = Material::ImageAvatar;

	d->pixmap = QPixmap::fromImage(image.scaled(d->size, d->size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	update();
}

void CUVMaterialAvatar::setIcon(const QIcon& icon) {
	Q_D(CUVMaterialAvatar);

	d->icon = icon;
	d->type = Material::IconAvatar;
	update();
}

Material::AvatarType CUVMaterialAvatar::type() const {
	Q_D(const CUVMaterialAvatar);

	return d->type;
}

void CUVMaterialAvatar::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	Q_D(CUVMaterialAvatar);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	const QRect r = rect();
	const qreal hs = static_cast<qreal>(d->size) / 2;

	if (!isEnabled()) {
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(CUVMaterialStyle::instance().themeColor("disabled"));
		painter.setPen(Qt::NoPen);
		painter.setBrush(brush);
		painter.drawEllipse(QRectF(static_cast<qreal>(width() - d->size) / 2, static_cast<qreal>(height() - d->size) / 2, d->size, d->size));
		return;
	}

	if (Material::ImageAvatar != d->type) {
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(backgroundColor());
		painter.setPen(Qt::NoPen);
		painter.setBrush(brush);
		painter.drawEllipse(QRectF(static_cast<qreal>(width() - d->size) / 2, static_cast<qreal>(height() - d->size) / 2, d->size, d->size));
	}

	switch (d->type) {
		case Material::ImageAvatar: {
			QPainterPath path;
			path.addEllipse(static_cast<qreal>(width()) / 2 - hs, static_cast<qreal>(height()) / 2 - hs, d->size, d->size);
			painter.setClipPath(path);

			painter.drawPixmap(QRect(width() / 2 - static_cast<int>(hs), height() / 2 - static_cast<int>(hs), d->size, d->size), d->pixmap);
			break;
		}
		case Material::IconAvatar: {
			const QRect iconGeometry((width() - static_cast<int>(hs)) / 2, (height() - static_cast<int>(hs)) / 2, static_cast<int>(hs),
			                         static_cast<int>(hs));
			QPixmap pixmap = d->icon.pixmap(static_cast<int>(hs), static_cast<int>(hs));
			QPainter icon(&pixmap);
			icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
			icon.fillRect(pixmap.rect(), textColor());
			painter.drawPixmap(iconGeometry, pixmap);
			break;
		}
		case Material::LetterAvatar: {
			painter.setPen(textColor());
			painter.setBrush(Qt::NoBrush);
			painter.drawText(r, Qt::AlignCenter, QString(d->letter));
			break;
		}
		default: break;
	}
}
