#include "uvmaterialiconbutton.hpp"

#include <QPainter>

#include "uvmaterialiconbutton_p.hpp"

/*!
 *  \class CUVMaterialIconButtonPrivate
 *  \internal
 */
CUVMaterialIconButtonPrivate::CUVMaterialIconButtonPrivate(CUVMaterialIconButton* q, QObject* parent): QObject(parent), q_ptr(q) {
}

CUVMaterialIconButtonPrivate::~CUVMaterialIconButtonPrivate() = default;

void CUVMaterialIconButtonPrivate::init() {
	this->lightHoverColor = QColor(0xEA, 0xE9, 0xF0);
	this->darkHoverColor = QColor(0x2F, 0x2E, 0x2C);
	this->lightIconColor = Qt::black;
	this->darkIconColor = Qt::white;
	this->isSelected = false;
	this->borderRaius = 0;
}

/*!
 *  \class CUVMaterialIconButtonPrivate
 */
CUVMaterialIconButton::CUVMaterialIconButton(const CUVIconType& iconType, QWidget* parent)
: QPushButton(parent), d_ptr(new CUVMaterialIconButtonPrivate(this)) {
	Q_D(CUVMaterialIconButton);

	d->init();
	auto iconFont = QFont("ElaAwesome");
	iconFont.setPixelSize(15);
	this->setFont(iconFont);
	d->iconType = iconType;
	this->setText(QChar(static_cast<ushort>(iconType)));
	connect(this, &CUVMaterialIconButton::isSelectedChanged, this, [=]() {
		this->update();
	});
}

CUVMaterialIconButton::CUVMaterialIconButton(const CUVIconType& iconType, const int pixelSize, QWidget* parent)
: QPushButton(parent), d_ptr(new CUVMaterialIconButtonPrivate(this)) {
	Q_D(CUVMaterialIconButton);

	d->init();
	auto iconFont = QFont("ElaAwesome");
	iconFont.setPixelSize(pixelSize);
	this->setFont(iconFont);
	d->iconType = iconType;
	this->setText(QChar(static_cast<unsigned short>(iconType)));
	connect(this, &CUVMaterialIconButton::isSelectedChanged, this, [=]() {
		this->update();
	});
}

CUVMaterialIconButton::CUVMaterialIconButton(const CUVIconType& iconType, const int pixelSize, const int fixedWidth,
                                             const int fixedHeight, QWidget* parent)
: QPushButton(parent), d_ptr(new CUVMaterialIconButtonPrivate(this)) {
	Q_D(CUVMaterialIconButton);

	d->init();
	auto iconFont = QFont("ElaAwesome");
	iconFont.setPixelSize(pixelSize);
	this->setFont(iconFont);
	d->iconType = iconType;
	this->setText(QChar(static_cast<ushort>(iconType)));
	this->setFixedSize(fixedWidth, fixedHeight);
	connect(this, &CUVMaterialIconButton::isSelectedChanged, this, [=]() {
		this->update();
	});
}

CUVMaterialIconButton::~CUVMaterialIconButton() = default;

void CUVMaterialIconButton::setIconType(const CUVIconType& iconType) {
	Q_D(CUVMaterialIconButton);

	if (d->iconType != iconType) {
		d->iconType = iconType;
		this->setText(QChar(static_cast<ushort>(iconType)));
	}
}

CUVIconType CUVMaterialIconButton::iconType() const {
	Q_D(const CUVMaterialIconButton);

	return d->iconType;
}

void CUVMaterialIconButton::setBorderRadius(const int radius) {
	Q_D(CUVMaterialIconButton);

	if (d->borderRaius != radius) {
		d->borderRaius = radius;
		emit borderRadiusChanged(radius);
	}
}

int CUVMaterialIconButton::borderRadius() const {
	Q_D(const CUVMaterialIconButton);

	return d->borderRaius;
}

void CUVMaterialIconButton::setLightHoverColor(const QColor& color) {
	Q_D(CUVMaterialIconButton);

	if (d->lightHoverColor != color) {
		d->lightHoverColor = color;
		emit lightHoverColorChanged(color);
	}
}

QColor CUVMaterialIconButton::lightHoverColor() const {
	Q_D(const CUVMaterialIconButton);

	return d->lightHoverColor;
}

void CUVMaterialIconButton::setDarkHoverColor(const QColor& color) {
	Q_D(CUVMaterialIconButton);

	if (d->darkHoverColor != color) {
		d->darkHoverColor = color;
		emit darkHoverColorChanged(color);
	}
}

QColor CUVMaterialIconButton::darkHoverColor() const {
	Q_D(const CUVMaterialIconButton);

	return d->darkHoverColor;
}

void CUVMaterialIconButton::setLightIconColor(const QColor& color) {
	Q_D(CUVMaterialIconButton);

	if (d->lightIconColor != color) {
		d->lightIconColor = color;
		emit lightIconColorChanged(color);
	}
}

QColor CUVMaterialIconButton::lightIconColor() const {
	Q_D(const CUVMaterialIconButton);

	return d->lightIconColor;
}

void CUVMaterialIconButton::setDarkIconColor(const QColor& color) {
	Q_D(CUVMaterialIconButton);

	if (d->darkIconColor != color) {
		d->darkIconColor = color;
		emit darkIconColorChanged(color);
	}
}

QColor CUVMaterialIconButton::darkIconColor() const {
	Q_D(const CUVMaterialIconButton);

	return d->darkIconColor;
}

void CUVMaterialIconButton::setIsSelected(const bool isSelected) {
	Q_D(CUVMaterialIconButton);

	if (d->isSelected != isSelected) {
		d->isSelected = isSelected;
		emit isSelectedChanged(isSelected);
	}
}

bool CUVMaterialIconButton::isSelected() const {
	Q_D(const CUVMaterialIconButton);

	return d->isSelected;
}

void CUVMaterialIconButton::paintEvent(QPaintEvent* event) {
	Q_D(CUVMaterialIconButton);

	QPainter painter(this);
	painter.save();
	painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
	painter.setPen(Qt::NoPen);
	painter.setBrush(d->isSelected ? d->lightHoverColor : isEnabled() ? underMouse() ? d->lightHoverColor : Qt::transparent : Qt::transparent);
	painter.drawRoundedRect(rect(), d->borderRaius, d->borderRaius);

	// 图标绘制
	painter.setPen(isEnabled() ? d->darkIconColor : QColor(0xA1, 0xA1, 0xA4));
	painter.drawText(0, 0, width(), height(), Qt::AlignCenter, QChar(static_cast<unsigned short>(d->iconType)));
	painter.restore();
}
