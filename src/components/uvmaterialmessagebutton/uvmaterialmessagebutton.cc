#include "uvmaterialmessagebutton.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

#include "uvmaterialmessagebutton_p.hpp"
#include "uvmaterialmessagebar/uvmaterialmessagebar.hpp"

/*!
 *  \class CUVMaterialMessageBarPrivate
 *  \internal
 */

CUVMaterialMessageButtonPrivate::CUVMaterialMessageButtonPrivate(CUVMaterialMessageButton* q, QObject* parent) : QObject(parent), q_ptr(q) {
}

CUVMaterialMessageButtonPrivate::~CUVMaterialMessageButtonPrivate() = default;

void CUVMaterialMessageButtonPrivate::init() {
	borderRadius = 3;
	displayMsec = 2000;
	messageMode = UVMessageBarType::Success;
	policy = UVMessageBarType::TopLeft;
	shadowBorderWidth = 3;
	penBorderWidth = 1;
}

/*!
 *  \class CUVMaterialMessageBarPrivate
 */
CUVMaterialMessageButton::CUVMaterialMessageButton(QWidget* parent): QPushButton(parent), d_ptr(new CUVMaterialMessageButtonPrivate(this)) {
	Q_D(CUVMaterialMessageButton);

	d_func()->init();
	setFixedSize(80, 38);
	QFont font = this->font();
	font.setPixelSize(11);
	setFont(font);
	setMouseTracking(true);
	setText("Message");
	setObjectName("CUVMessageButton");
	setStyleSheet("#CUVMessageButton { background-color: transparent; }");
	connect(this, &CUVMaterialMessageButton::clicked, this, [=]() {
		switch (d->messageMode) {
			case UVMessageBarType::Success: {
				CUVMaterialMessageBar::success(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Error: {
				CUVMaterialMessageBar::error(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Warning: {
				CUVMaterialMessageBar::warning(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Info: {
				CUVMaterialMessageBar::infomation(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
		}
	});
}

CUVMaterialMessageButton::CUVMaterialMessageButton(const QString& text, QWidget* parent)
: QPushButton(text, parent), d_ptr(new CUVMaterialMessageButtonPrivate(this)) {
	Q_D(CUVMaterialMessageButton);

	d_func()->init();
	setFixedSize(80, 38);
	QFont font = this->font();
	font.setPixelSize(11);
	setFont(font);
	setMouseTracking(true);
	setObjectName("CUVMessageButton");
	setStyleSheet("#CUVMessageButton { background-color: transparent; }");
	connect(this, &CUVMaterialMessageButton::clicked, this, [=]() {
		switch (d->messageMode) {
			case UVMessageBarType::Success: {
				CUVMaterialMessageBar::success(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Error: {
				CUVMaterialMessageBar::error(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Warning: {
				CUVMaterialMessageBar::warning(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Info: {
				CUVMaterialMessageBar::infomation(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
		}
	});
}

CUVMaterialMessageButton::CUVMaterialMessageButton(const QString& text, const UVMessageBarType::MessageMode& messageMode, QWidget* parent)
: QPushButton(text, parent), d_ptr(new CUVMaterialMessageButtonPrivate(this)) {
	Q_D(CUVMaterialMessageButton);

	d_func()->init();
	d->messageMode = messageMode;
	setFixedSize(80, 38);
	QFont font = this->font();
	font.setPixelSize(11);
	setFont(font);
	setMouseTracking(true);
	setObjectName("CUVMessageButton");
	setStyleSheet("#CUVMessageButton { background-color: transparent; }");
	connect(this, &CUVMaterialMessageButton::clicked, this, [=]() {
		switch (d->messageMode) {
			case UVMessageBarType::Success: {
				CUVMaterialMessageBar::success(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Error: {
				CUVMaterialMessageBar::error(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Warning: {
				CUVMaterialMessageBar::warning(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Info: {
				CUVMaterialMessageBar::infomation(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
		}
	});
}

CUVMaterialMessageButton::~CUVMaterialMessageButton() = default;

void CUVMaterialMessageButton::setBorderRadius(const int radius) {
	Q_D(CUVMaterialMessageButton);

	if (d->borderRadius != radius) {
		d->borderRadius = radius;
		emit borderRadiusChanged(radius);
	}
}

int CUVMaterialMessageButton::borderRadius() const {
	Q_D(const CUVMaterialMessageButton);

	return d->borderRadius;
}

void CUVMaterialMessageButton::setBarTitle(const QString& title) {
	Q_D(CUVMaterialMessageButton);

	if (d->title != title) {
		d->title = title;
		emit barTitleChanged(title);
	}
}

QString CUVMaterialMessageButton::barTitle() const {
	Q_D(const CUVMaterialMessageButton);

	return d->title;
}

void CUVMaterialMessageButton::setBarText(const QString& text) {
	Q_D(CUVMaterialMessageButton);

	if (d->text != text) {
		d->text = text;
		emit barTextChanged(text);
	}
}

QString CUVMaterialMessageButton::barText() const {
	Q_D(const CUVMaterialMessageButton);

	return d->text;
}

void CUVMaterialMessageButton::setDisplayMsec(const int msec) {
	Q_D(CUVMaterialMessageButton);

	if (d->displayMsec != msec) {
		d->displayMsec = msec;
		emit displayMsecChanged(msec);
	}
}

int CUVMaterialMessageButton::displayMsec() const {
	Q_D(const CUVMaterialMessageButton);

	return d->displayMsec;
}

void CUVMaterialMessageButton::setMessageMode(const UVMessageBarType::MessageMode& messageMode) {
	Q_D(CUVMaterialMessageButton);

	if (d->messageMode != messageMode) {
		d->messageMode = messageMode;
		emit messageModeChanged(messageMode);
	}
}

UVMessageBarType::MessageMode CUVMaterialMessageButton::messageMode() const {
	Q_D(const CUVMaterialMessageButton);

	return d->messageMode;
}

void CUVMaterialMessageButton::setPositionPolicy(const UVMessageBarType::PositionPolicy& positionPolicy) {
	Q_D(CUVMaterialMessageButton);

	if (d->policy != positionPolicy) {
		d->policy = positionPolicy;
		emit positionPolicyChanged(positionPolicy);
	}
}

UVMessageBarType::PositionPolicy CUVMaterialMessageButton::positionPolicy() const {
	Q_D(const CUVMaterialMessageButton);

	return d->policy;
}

void CUVMaterialMessageButton::mousePressEvent(QMouseEvent* event) {
	Q_D(CUVMaterialMessageButton);

	if (event->button() == Qt::LeftButton) {
		QPalette palette;
		palette.setColor(QPalette::ButtonText, QColor(0x64, 0x66, 0x73));
		setPalette(palette);
	}
	QPushButton::mousePressEvent(event);
}

void CUVMaterialMessageButton::mouseReleaseEvent(QMouseEvent* event) {
	Q_D(CUVMaterialMessageButton);

	if (event->button() == Qt::LeftButton) {
		QPalette palette;
		palette.setColor(QPalette::ButtonText, Qt::black);
		setPalette(palette);
	}
	QPushButton::mouseReleaseEvent(event);
}

void CUVMaterialMessageButton::paintEvent(QPaintEvent* event) {
	Q_D(CUVMaterialMessageButton);

	QPainter painter(this);
	painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
	painter.save();

	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	auto color = QColor(165, 165, 165, 155);
	for (int i = 0; i < d->shadowBorderWidth; i++) {
		QPainterPath pa;
		pa.setFillRule(Qt::WindingFill);
		pa.addRoundedRect(d->shadowBorderWidth - i, d->shadowBorderWidth - i, this->width() - (d->shadowBorderWidth - i) * 2,
		                  this->height() - (d->shadowBorderWidth - i) * 2, d->borderRadius + i, d->borderRadius + i);
		const int alpha = 5 * (d->shadowBorderWidth - i + 1);
		color.setAlpha(alpha);
		painter.setPen(color);
		painter.drawPath(pa);
	}
	painter.restore();

	// 背景绘制
	painter.save();
	const QRect foregroundRect(d->penBorderWidth + d->shadowBorderWidth, d->penBorderWidth + d->shadowBorderWidth,
	                           width() - 2 * (d->penBorderWidth + d->shadowBorderWidth), height() - 2 * (d->penBorderWidth + d->shadowBorderWidth));
	painter.setPen(QPen(QColor(0xDF, 0xDF, 0xDF), d->penBorderWidth));
	painter.setBrush(underMouse() ? QColor(0xF6, 0xF6, 0xF6) : QColor(0xFD, 0xFD, 0xFD));
	painter.drawRoundedRect(foregroundRect, d->borderRadius, d->borderRadius);
	painter.restore();
	QPushButton::paintEvent(event);
}
