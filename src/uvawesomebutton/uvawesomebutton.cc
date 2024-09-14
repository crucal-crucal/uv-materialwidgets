#include "uvawesomebutton.hpp"

#include <QPainter>

#include "uvawesomebutton_p.hpp"

/*!
 *  \class CUVAwesomeButtonPrivate
 *  \internal
 */
CUVAwesomeButtonPrivate::CUVAwesomeButtonPrivate(CUVAwesomeButton* q, QObject* parent): QObject(parent), q_ptr(q) {
}

CUVAwesomeButtonPrivate::~CUVAwesomeButtonPrivate() = default;

void CUVAwesomeButtonPrivate::init() {
	Q_Q(CUVAwesomeButton);

	lightHoverColor = QColor(0xEA, 0xE9, 0xF0);
	darkHoverColor = QColor(0x2F, 0x2E, 0x2C);
	lightIconColor = Qt::black;
	darkIconColor = Qt::white;
	isSelected = false;
	borderRaius = 0;
}

/*!
 *  \class CUVAwesomeButtonPrivate
 */
CUVAwesomeButton::CUVAwesomeButton(const CUVIconType& iconType, QWidget* parent)
: QPushButton(parent), d_ptr(new CUVAwesomeButtonPrivate(this)) {
	Q_D(CUVAwesomeButton);

	d->init();
	auto iconFont = QFont("CUVAwesome");
	iconFont.setPixelSize(15);
	this->setFont(iconFont);
	d->iconType = iconType;
	this->setText(QChar(static_cast<ushort>(iconType)));
	connect(this, &CUVAwesomeButton::isSelectedChanged, this, [=]() {
		this->update();
	});
}

CUVAwesomeButton::CUVAwesomeButton(const CUVIconType& iconType, const int pixelSize, QWidget* parent)
: QPushButton(parent), d_ptr(new CUVAwesomeButtonPrivate(this)) {
	Q_D(CUVAwesomeButton);

	d->init();
	auto iconFont = QFont("CUVAwesome");
	iconFont.setPixelSize(pixelSize);
	this->setFont(iconFont);
	d->iconType = iconType;
	this->setText(QChar(static_cast<unsigned short>(iconType)));
	connect(this, &CUVAwesomeButton::isSelectedChanged, this, [=]() {
		this->update();
	});
}

CUVAwesomeButton::CUVAwesomeButton(const CUVIconType& iconType, const int pixelSize, const int fixedWidth,
                                             const int fixedHeight, QWidget* parent)
: QPushButton(parent), d_ptr(new CUVAwesomeButtonPrivate(this)) {
	Q_D(CUVAwesomeButton);

	d->init();
	auto iconFont = QFont("CUVAwesome");
	iconFont.setPixelSize(pixelSize);
	this->setFont(iconFont);
	d->iconType = iconType;
	this->setText(QChar(static_cast<ushort>(iconType)));
	this->setFixedSize(fixedWidth, fixedHeight);
	connect(this, &CUVAwesomeButton::isSelectedChanged, this, [=]() {
		this->update();
	});
}

CUVAwesomeButton::~CUVAwesomeButton() = default;

void CUVAwesomeButton::setIconType(const CUVIconType& iconType) {
	Q_D(CUVAwesomeButton);

	if (d->iconType != iconType) {
		d->iconType = iconType;
		this->setText(QChar(static_cast<ushort>(iconType)));
	}
}

CUVIconType CUVAwesomeButton::iconType() const {
	Q_D(const CUVAwesomeButton);

	return d->iconType;
}

void CUVAwesomeButton::setBorderRadius(const int radius) {
	Q_D(CUVAwesomeButton);

	if (d->borderRaius != radius) {
		d->borderRaius = radius;
		emit borderRadiusChanged(radius);
	}
}

int CUVAwesomeButton::borderRadius() const {
	Q_D(const CUVAwesomeButton);

	return d->borderRaius;
}

void CUVAwesomeButton::setLightHoverColor(const QColor& color) {
	Q_D(CUVAwesomeButton);

	if (d->lightHoverColor != color) {
		d->lightHoverColor = color;
		emit lightHoverColorChanged(color);
	}
}

QColor CUVAwesomeButton::lightHoverColor() const {
	Q_D(const CUVAwesomeButton);

	return d->lightHoverColor;
}

void CUVAwesomeButton::setDarkHoverColor(const QColor& color) {
	Q_D(CUVAwesomeButton);

	if (d->darkHoverColor != color) {
		d->darkHoverColor = color;
		emit darkHoverColorChanged(color);
	}
}

QColor CUVAwesomeButton::darkHoverColor() const {
	Q_D(const CUVAwesomeButton);

	return d->darkHoverColor;
}

void CUVAwesomeButton::setLightIconColor(const QColor& color) {
	Q_D(CUVAwesomeButton);

	if (d->lightIconColor != color) {
		d->lightIconColor = color;
		emit lightIconColorChanged(color);
	}
}

QColor CUVAwesomeButton::lightIconColor() const {
	Q_D(const CUVAwesomeButton);

	return d->lightIconColor;
}

void CUVAwesomeButton::setDarkIconColor(const QColor& color) {
	Q_D(CUVAwesomeButton);

	if (d->darkIconColor != color) {
		d->darkIconColor = color;
		emit darkIconColorChanged(color);
	}
}

QColor CUVAwesomeButton::darkIconColor() const {
	Q_D(const CUVAwesomeButton);

	return d->darkIconColor;
}

void CUVAwesomeButton::setIsSelected(const bool isSelected) {
	Q_D(CUVAwesomeButton);

	if (d->isSelected != isSelected) {
		d->isSelected = isSelected;
		emit isSelectedChanged(isSelected);
	}
}

bool CUVAwesomeButton::isSelected() const {
	Q_D(const CUVAwesomeButton);

	return d->isSelected;
}

void CUVAwesomeButton::paintEvent(QPaintEvent* event) {
	Q_D(CUVAwesomeButton);

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
