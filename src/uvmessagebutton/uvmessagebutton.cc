#include "uvmessagebutton.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

#include "uvmessagebutton_p.hpp"
#include "uvmessagebar/uvmessagebar.hpp"

/*!
 *  \class CUVMessageBarPrivate
 *  \internal
 */

CUVMessageButtonPrivate::CUVMessageButtonPrivate(CUVMessageButton* q, QObject* parent) : QObject(parent), q_ptr(q) {
}

CUVMessageButtonPrivate::~CUVMessageButtonPrivate() = default;

void CUVMessageButtonPrivate::init() {
	Q_Q(CUVMessageButton);

	borderRadius = 3;
	displayMsec = 2000;
	messageMode = UVMessageBarType::Success;
	policy = UVMessageBarType::TopLeft;
	shadowBorderWidth = 3;
	penBorderWidth = 1;
}

/*!
 *  \class CUVMessageBarPrivate
 */
CUVMessageButton::CUVMessageButton(QWidget* parent): QPushButton(parent), d_ptr(new CUVMessageButtonPrivate(this)) {
	Q_D(CUVMessageButton);

	d_func()->init();
	setFixedSize(80, 38);
	QFont font = this->font();
	font.setPixelSize(11);
	setFont(font);
	setMouseTracking(true);
	setText("Message");
	setObjectName("CUVMessageButton");
#ifdef Q_OS_UNIX
	setStyleSheet("#CUVMessageButton { background-color: white; }");
#else
	setStyleSheet("#CUVMessageButton { background-color: transparent; }");
#endif
	connect(this, &CUVMessageButton::clicked, this, [=]() {
		switch (d->messageMode) {
			case UVMessageBarType::Success: {
				CUVMessageBar::success(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Error: {
				CUVMessageBar::error(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Warning: {
				CUVMessageBar::warning(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Info: {
				CUVMessageBar::infomation(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
		}
	});
}

CUVMessageButton::CUVMessageButton(const QString& text, QWidget* parent)
: QPushButton(text, parent), d_ptr(new CUVMessageButtonPrivate(this)) {
	Q_D(CUVMessageButton);

	d_func()->init();
	setFixedSize(80, 38);
	QFont font = this->font();
	font.setPixelSize(11);
	setFont(font);
	setMouseTracking(true);
	setObjectName("CUVMessageButton");
#ifdef Q_OS_UNIX
	setStyleSheet("#CUVMessageButton { background-color: white; }");
#else
	setStyleSheet("#CUVMessageButton { background-color: transparent; }");
#endif
	connect(this, &CUVMessageButton::clicked, this, [=]() {
		switch (d->messageMode) {
			case UVMessageBarType::Success: {
				CUVMessageBar::success(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Error: {
				CUVMessageBar::error(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Warning: {
				CUVMessageBar::warning(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Info: {
				CUVMessageBar::infomation(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
		}
	});
}

CUVMessageButton::CUVMessageButton(const QString& text, const UVMessageBarType::MessageMode& messageMode, QWidget* parent)
: QPushButton(text, parent), d_ptr(new CUVMessageButtonPrivate(this)) {
	Q_D(CUVMessageButton);

	d_func()->init();
	d->messageMode = messageMode;
	setFixedSize(80, 38);
	QFont font = this->font();
	font.setPixelSize(11);
	setFont(font);
	setMouseTracking(true);
	setObjectName("CUVMessageButton");
#ifdef Q_OS_UNIX
	setStyleSheet("#CUVMessageButton { background-color: white; }");
#else
	setStyleSheet("#CUVMessageButton { background-color: transparent; }");
#endif
	connect(this, &CUVMessageButton::clicked, this, [=]() {
		switch (d->messageMode) {
			case UVMessageBarType::Success: {
				CUVMessageBar::success(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Error: {
				CUVMessageBar::error(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Warning: {
				CUVMessageBar::warning(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
			case UVMessageBarType::Info: {
				CUVMessageBar::infomation(d->title, d->text, d->displayMsec, d->policy, window());
				break;
			}
		}
	});
}

CUVMessageButton::~CUVMessageButton() = default;

void CUVMessageButton::setBorderRadius(const int radius) {
	Q_D(CUVMessageButton);

	if (d->borderRadius != radius) {
		d->borderRadius = radius;
		emit borderRadiusChanged(radius);
	}
}

int CUVMessageButton::borderRadius() const {
	Q_D(const CUVMessageButton);

	return d->borderRadius;
}

void CUVMessageButton::setBarTitle(const QString& title) {
	Q_D(CUVMessageButton);

	if (d->title != title) {
		d->title = title;
		emit barTitleChanged(title);
	}
}

QString CUVMessageButton::barTitle() const {
	Q_D(const CUVMessageButton);

	return d->title;
}

void CUVMessageButton::setBarText(const QString& text) {
	Q_D(CUVMessageButton);

	if (d->text != text) {
		d->text = text;
		emit barTextChanged(text);
	}
}

QString CUVMessageButton::barText() const {
	Q_D(const CUVMessageButton);

	return d->text;
}

void CUVMessageButton::setDisplayMsec(const int msec) {
	Q_D(CUVMessageButton);

	if (d->displayMsec != msec) {
		d->displayMsec = msec;
		emit displayMsecChanged(msec);
	}
}

int CUVMessageButton::displayMsec() const {
	Q_D(const CUVMessageButton);

	return d->displayMsec;
}

void CUVMessageButton::setMessageMode(const UVMessageBarType::MessageMode& messageMode) {
	Q_D(CUVMessageButton);

	if (d->messageMode != messageMode) {
		d->messageMode = messageMode;
		emit messageModeChanged(messageMode);
	}
}

UVMessageBarType::MessageMode CUVMessageButton::messageMode() const {
	Q_D(const CUVMessageButton);

	return d->messageMode;
}

void CUVMessageButton::setPositionPolicy(const UVMessageBarType::PositionPolicy& positionPolicy) {
	Q_D(CUVMessageButton);

	if (d->policy != positionPolicy) {
		d->policy = positionPolicy;
		emit positionPolicyChanged(positionPolicy);
	}
}

UVMessageBarType::PositionPolicy CUVMessageButton::positionPolicy() const {
	Q_D(const CUVMessageButton);

	return d->policy;
}

void CUVMessageButton::mousePressEvent(QMouseEvent* event) {
	Q_D(CUVMessageButton);

	if (event->button() == Qt::LeftButton) {
		QPalette palette;
		palette.setColor(QPalette::ButtonText, QColor(0x64, 0x66, 0x73));
		setPalette(palette);
	}
	QPushButton::mousePressEvent(event);
}

void CUVMessageButton::mouseReleaseEvent(QMouseEvent* event) {
	Q_D(CUVMessageButton);

	if (event->button() == Qt::LeftButton) {
		QPalette palette;
		palette.setColor(QPalette::ButtonText, Qt::black);
		setPalette(palette);
	}
	QPushButton::mouseReleaseEvent(event);
}

void CUVMessageButton::paintEvent(QPaintEvent* event) {
	Q_D(CUVMessageButton);

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
