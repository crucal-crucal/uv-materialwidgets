#include "uvmaterialawesomebutton.hpp"

#include <QPainter>

#include "uvmaterialawesomebutton_p.hpp"

/*!
 *  \class CUVMaterialAwesomeButtonPrivate
 *  \internal
 */
CUVMaterialAwesomeButtonPrivate::CUVMaterialAwesomeButtonPrivate(CUVMaterialAwesomeButton* q, QObject* parent): QObject(parent), q_ptr(q) {
}

CUVMaterialAwesomeButtonPrivate::~CUVMaterialAwesomeButtonPrivate() = default;

void CUVMaterialAwesomeButtonPrivate::init() {
	Q_Q(CUVMaterialAwesomeButton);

	lightHoverColor = QColor(0xEA, 0xE9, 0xF0);
	darkHoverColor = QColor(0x2F, 0x2E, 0x2C);
	lightIconColor = Qt::black;
	darkIconColor = Qt::white;
	isSelected = false;
	borderRaius = 0;
}

/*!
 *  \class CUVMaterialAwesomeButtonPrivate
 */
CUVMaterialAwesomeButton::CUVMaterialAwesomeButton(const CUVIconType& iconType, QWidget* parent)
: QPushButton(parent), d_ptr(new CUVMaterialAwesomeButtonPrivate(this)) {
	Q_D(CUVMaterialAwesomeButton);

	d->init();
	auto iconFont = QFont("ElaAwesome");
	iconFont.setPixelSize(15);
	this->setFont(iconFont);
	d->iconType = iconType;
	this->setText(QChar(static_cast<ushort>(iconType)));
	connect(this, &CUVMaterialAwesomeButton::isSelectedChanged, this, [=]() {
		this->update();
	});
}

CUVMaterialAwesomeButton::CUVMaterialAwesomeButton(const CUVIconType& iconType, const int pixelSize, QWidget* parent)
: QPushButton(parent), d_ptr(new CUVMaterialAwesomeButtonPrivate(this)) {
	Q_D(CUVMaterialAwesomeButton);

	d->init();
	auto iconFont = QFont("ElaAwesome");
	iconFont.setPixelSize(pixelSize);
	this->setFont(iconFont);
	d->iconType = iconType;
	this->setText(QChar(static_cast<unsigned short>(iconType)));
	connect(this, &CUVMaterialAwesomeButton::isSelectedChanged, this, [=]() {
		this->update();
	});
}

CUVMaterialAwesomeButton::CUVMaterialAwesomeButton(const CUVIconType& iconType, const int pixelSize, const int fixedWidth,
                                             const int fixedHeight, QWidget* parent)
: QPushButton(parent), d_ptr(new CUVMaterialAwesomeButtonPrivate(this)) {
	Q_D(CUVMaterialAwesomeButton);

	d->init();
	auto iconFont = QFont("ElaAwesome");
	iconFont.setPixelSize(pixelSize);
	this->setFont(iconFont);
	d->iconType = iconType;
	this->setText(QChar(static_cast<ushort>(iconType)));
	this->setFixedSize(fixedWidth, fixedHeight);
	connect(this, &CUVMaterialAwesomeButton::isSelectedChanged, this, [=]() {
		this->update();
	});
}

CUVMaterialAwesomeButton::~CUVMaterialAwesomeButton() = default;

void CUVMaterialAwesomeButton::setIconType(const CUVIconType& iconType) {
	Q_D(CUVMaterialAwesomeButton);

	if (d->iconType != iconType) {
		d->iconType = iconType;
		this->setText(QChar(static_cast<ushort>(iconType)));
	}
}

CUVIconType CUVMaterialAwesomeButton::iconType() const {
	Q_D(const CUVMaterialAwesomeButton);

	return d->iconType;
}

void CUVMaterialAwesomeButton::setBorderRadius(const int radius) {
	Q_D(CUVMaterialAwesomeButton);

	if (d->borderRaius != radius) {
		d->borderRaius = radius;
		emit borderRadiusChanged(radius);
	}
}

int CUVMaterialAwesomeButton::borderRadius() const {
	Q_D(const CUVMaterialAwesomeButton);

	return d->borderRaius;
}

void CUVMaterialAwesomeButton::setLightHoverColor(const QColor& color) {
	Q_D(CUVMaterialAwesomeButton);

	if (d->lightHoverColor != color) {
		d->lightHoverColor = color;
		emit lightHoverColorChanged(color);
	}
}

QColor CUVMaterialAwesomeButton::lightHoverColor() const {
	Q_D(const CUVMaterialAwesomeButton);

	return d->lightHoverColor;
}

void CUVMaterialAwesomeButton::setDarkHoverColor(const QColor& color) {
	Q_D(CUVMaterialAwesomeButton);

	if (d->darkHoverColor != color) {
		d->darkHoverColor = color;
		emit darkHoverColorChanged(color);
	}
}

QColor CUVMaterialAwesomeButton::darkHoverColor() const {
	Q_D(const CUVMaterialAwesomeButton);

	return d->darkHoverColor;
}

void CUVMaterialAwesomeButton::setLightIconColor(const QColor& color) {
	Q_D(CUVMaterialAwesomeButton);

	if (d->lightIconColor != color) {
		d->lightIconColor = color;
		emit lightIconColorChanged(color);
	}
}

QColor CUVMaterialAwesomeButton::lightIconColor() const {
	Q_D(const CUVMaterialAwesomeButton);

	return d->lightIconColor;
}

void CUVMaterialAwesomeButton::setDarkIconColor(const QColor& color) {
	Q_D(CUVMaterialAwesomeButton);

	if (d->darkIconColor != color) {
		d->darkIconColor = color;
		emit darkIconColorChanged(color);
	}
}

QColor CUVMaterialAwesomeButton::darkIconColor() const {
	Q_D(const CUVMaterialAwesomeButton);

	return d->darkIconColor;
}

void CUVMaterialAwesomeButton::setIsSelected(const bool isSelected) {
	Q_D(CUVMaterialAwesomeButton);

	if (d->isSelected != isSelected) {
		d->isSelected = isSelected;
		emit isSelectedChanged(isSelected);
	}
}

bool CUVMaterialAwesomeButton::isSelected() const {
	Q_D(const CUVMaterialAwesomeButton);

	return d->isSelected;
}

void CUVMaterialAwesomeButton::paintEvent(QPaintEvent* event) {
	Q_D(CUVMaterialAwesomeButton);

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
