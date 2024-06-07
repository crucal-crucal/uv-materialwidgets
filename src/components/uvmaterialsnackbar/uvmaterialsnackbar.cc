#include "uvmaterialsnackbar.hpp"

#include <QDebug>
#include <QPainter>
#include <QtWidgets/QApplication>

#include "uvmaterialsnackbar_internal.hpp"
#include "uvmaterialsnackbar_p.hpp"
#include "uvshared/uvmaterialstatetransition.hpp"
#include "uvshared/uvmaterialstyle.hpp"

/*!
 *  \class CUVMaterialSnackbarPrivate
 *  \internal
 */
CUVMaterialSnackbarPrivate::CUVMaterialSnackbarPrivate(CUVMaterialSnackbar* q): q_ptr(q) {
}

CUVMaterialSnackbarPrivate::~CUVMaterialSnackbarPrivate() = default;

void CUVMaterialSnackbarPrivate::init(const CUVMaterialSnackbar::SnackBarPosition& postion) {
	Q_Q(CUVMaterialSnackbar);

	stateMachine = new CUVMaterialSnackbarStateMachine(q, postion);
	bgOpacity = 0.9;
	duration = 1000;
	boxWidth = 300;
	clickDismiss = false;
	useThemeColors = true;

	q->setAttribute(Qt::WA_TransparentForMouseEvents);

	QFont font("Roboto", 10, QFont::Medium);
	font.setCapitalization(QFont::AllUppercase);
	q->setFont(font);

	stateMachine->start();
	QCoreApplication::processEvents();
}

/*!
 *  \class CUVMaterialSnackbar
 */
CUVMaterialSnackbar::CUVMaterialSnackbar(QWidget* parent, const SnackBarPosition position)
: CUVMaterialOverlayWidget(parent), d_ptr(new CUVMaterialSnackbarPrivate(this)) {
	d_func()->init(position);
}

CUVMaterialSnackbar::~CUVMaterialSnackbar() = default;

void CUVMaterialSnackbar::setAutoHideDuration(const int duration) {
	Q_D(CUVMaterialSnackbar);

	d->duration = duration;
}

int CUVMaterialSnackbar::autoHideDuration() const {
	Q_D(const CUVMaterialSnackbar);

	return d->duration;
}

void CUVMaterialSnackbar::setUseThemeColors(const bool value) {
	Q_D(CUVMaterialSnackbar);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	update();
}

bool CUVMaterialSnackbar::useThemeColors() const {
	Q_D(const CUVMaterialSnackbar);

	return d->useThemeColors;
}

void CUVMaterialSnackbar::setBackgroundColor(const QColor& color) {
	Q_D(CUVMaterialSnackbar);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialSnackbar::backgroundColor() const {
	Q_D(const CUVMaterialSnackbar);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("text");
	} else {
		return d->backgroundColor;
	}
}

void CUVMaterialSnackbar::setBackgroundOpacity(const qreal opacity) {
	Q_D(CUVMaterialSnackbar);

	d->bgOpacity = opacity;
	update();
}

qreal CUVMaterialSnackbar::backgroundOpacity() const {
	Q_D(const CUVMaterialSnackbar);

	return d->bgOpacity;
}

void CUVMaterialSnackbar::setTextColor(const QColor& color) {
	Q_D(CUVMaterialSnackbar);

	d->textColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialSnackbar::textColor() const {
	Q_D(const CUVMaterialSnackbar);

	if (d->useThemeColors || !d->textColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("canvas");
	} else {
		return d->textColor;
	}
}

void CUVMaterialSnackbar::setFontSize(const qreal size) {
	QFont f(font());
	f.setPointSizeF(size);
	setFont(f);

	update();
}

qreal CUVMaterialSnackbar::fontSize() const {
	return font().pointSizeF();
}

void CUVMaterialSnackbar::setBoxWidth(const int width) {
	Q_D(CUVMaterialSnackbar);

	d->boxWidth = width;
	update();
}

int CUVMaterialSnackbar::boxWidth() const {
	Q_D(const CUVMaterialSnackbar);

	return d->boxWidth;
}

void CUVMaterialSnackbar::setClickToDismissMode(const bool value) {
	Q_D(CUVMaterialSnackbar);

	d->clickDismiss = value;
}

bool CUVMaterialSnackbar::clickToDismissMode() const {
	Q_D(const CUVMaterialSnackbar);

	return d->clickDismiss;
}

void CUVMaterialSnackbar::setSnackBarPosition(const SnackBarPosition position) {
	Q_D(CUVMaterialSnackbar);

	d->stateMachine->setPosition(position);
}

void CUVMaterialSnackbar::addMessage(const QString& message) {
	Q_D(CUVMaterialSnackbar);

	d->messages.push_back(message);
	d->stateMachine->postEvent(new CUVMaterialStateTransitionEvent(SnackbarShowTransition));
	raise();
}

void CUVMaterialSnackbar::addInstantMessage(const QString& message) {
	Q_D(CUVMaterialSnackbar);

	if (d->messages.isEmpty()) {
		d->messages.push_back(message);
	} else {
		d->messages.insert(1, message);
	}

	d->stateMachine->progress();
}

void CUVMaterialSnackbar::dequeue() {
	Q_D(CUVMaterialSnackbar);

	if (d->messages.isEmpty()) {
		return;
	}

	d->messages.removeFirst();

	if (!d->messages.isEmpty()) {
		d->stateMachine->postEvent(new CUVMaterialStateTransitionEvent(SnackbarNextTransition));
	} else {
		d->stateMachine->postEvent(new CUVMaterialStateTransitionEvent(SnackbarWaitTransition));
	}
}

void CUVMaterialSnackbar::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	Q_D(CUVMaterialSnackbar);

	if (d->messages.isEmpty()) {
		return;
	}

	const QString message = d->messages.first();

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(backgroundColor());
	painter.setBrush(brush);
	painter.setOpacity(d->bgOpacity);

	QRect r(0, 0, d->boxWidth, 40);

	painter.setPen(Qt::white);
	QRect br = painter.boundingRect(r, Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, message);

	painter.setPen(Qt::NoPen);
	r = br.united(r).adjusted(-10, -10, 10, 20);

	if (d->stateMachine->position() == SnackBarPosition::TOP) {
		const qreal s = d->stateMachine->offset();
		painter.translate(static_cast<float>(width() - (r.width() - 20)) / 2, -r.height() + s * (r.height() + 10));
	} else {
		const qreal s = 1 - d->stateMachine->offset();
		painter.translate((width() - (r.width() - 20)) / 2, height() + 10 - s * (r.height())); // NOLINT
	}

	br.moveCenter(r.center());
	painter.drawRoundedRect(r.adjusted(0, 0, 0, 3), 3, 3);
	painter.setPen(textColor());
	painter.drawText(br, Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, message);
}
