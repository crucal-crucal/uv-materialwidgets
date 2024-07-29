#include "uvmaterialtoggle.hpp"

#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QStateMachine>
#include <QtWidgets/QApplication>

#include "uvmaterialtoggle_internal.hpp"
#include "uvmaterialtoggle_p.hpp"
#include "uvmaterialshared/uvmaterialstyle.hpp"

/*!
 *  \class CUVMaterialTogglePrivate
 *  \internal
 */
CUVMaterialTogglePrivate::CUVMaterialTogglePrivate(CUVMaterialToggle* q): q_ptr(q) {
}

CUVMaterialTogglePrivate::~CUVMaterialTogglePrivate() = default;

void CUVMaterialTogglePrivate::init() {
	Q_Q(CUVMaterialToggle);

	track = new CUVMaterialToggleTrack(q);
	thumb = new CUVMaterialToggleThumb(q);
	rippleOverlay = new CUVMaterialToggleRippleOverlay(thumb, track, q);
	stateMachine = new QStateMachine(q);
	offState = new QState;
	onState = new QState;
	orientation = Qt::Horizontal;
	useThemeColors = true;

	q->setCheckable(true);
	q->setChecked(false);
	q->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	stateMachine->addState(offState);
	stateMachine->addState(onState);
	stateMachine->setInitialState(offState);

	offState->assignProperty(thumb, "shift", 0);
	onState->assignProperty(thumb, "shift", 1);

	auto transition = new QSignalTransition(q, &QAbstractButton::toggled);
	transition->setTargetState(onState);
	offState->addTransition(transition);

	auto animation = new QPropertyAnimation(q);
	animation->setPropertyName("shift");
	animation->setTargetObject(thumb);
	animation->setDuration(200);
	animation->setEasingCurve(QEasingCurve::OutQuad);
	transition->addAnimation(animation);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("trackColor");
	animation->setTargetObject(track);
	animation->setDuration(150);
	transition->addAnimation(animation);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("thumbColor");
	animation->setTargetObject(thumb);
	animation->setDuration(150);
	transition->addAnimation(animation);

	transition = new QSignalTransition(q, &QAbstractButton::toggled);
	transition->setTargetState(offState);
	onState->addTransition(transition);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("shift");
	animation->setTargetObject(thumb);
	animation->setDuration(200);
	animation->setEasingCurve(QEasingCurve::OutQuad);
	transition->addAnimation(animation);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("trackColor");
	animation->setTargetObject(track);
	animation->setDuration(150);
	transition->addAnimation(animation);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("thumbColor");
	animation->setTargetObject(thumb);
	animation->setDuration(150);
	transition->addAnimation(animation);

	setupProperties();

	stateMachine->start();
	QCoreApplication::processEvents();
}

void CUVMaterialTogglePrivate::setupProperties() {
	Q_Q(CUVMaterialToggle);

	if (q->isEnabled()) {
		if (const qreal shift = thumb->shift(); qFuzzyCompare(shift, 1)) {
			thumb->setThumbColor(q->activeColor());
			track->setTrackColor(q->activeColor().lighter(110));
		} else if (qFuzzyCompare(1 + shift, 1)) {
			thumb->setThumbColor(q->inactiveColor());
			track->setTrackColor(q->trackColor());
		}
	}

	offState->assignProperty(track, "trackColor", q->trackColor().lighter(110));
	onState->assignProperty(track, "trackColor", q->activeColor().lighter(110));

	offState->assignProperty(thumb, "thumbColor", q->inactiveColor());
	onState->assignProperty(thumb, "thumbColor", q->activeColor());

	q->update();
}

/*!
 *  \class CUVMaterialToggle
 */
CUVMaterialToggle::CUVMaterialToggle(QWidget* parent)
: QAbstractButton(parent), d_ptr(new CUVMaterialTogglePrivate(this)) {
	d_func()->init();
}

CUVMaterialToggle::~CUVMaterialToggle() = default;

void CUVMaterialToggle::setUseThemeColors(const bool value) {
	Q_D(CUVMaterialToggle);

	d->useThemeColors = value;
	d->setupProperties();
}

bool CUVMaterialToggle::useThemeColors() const {
	Q_D(const CUVMaterialToggle);

	return d->useThemeColors;
}

void CUVMaterialToggle::setDisabledColor(const QColor& color) {
	Q_D(CUVMaterialToggle);

	d->disabledColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	d->setupProperties();
}

QColor CUVMaterialToggle::disabledColor() const {
	Q_D(const CUVMaterialToggle);

	if (d->useThemeColors || !d->disabledColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("disabled");
	} else {
		return d->disabledColor;
	}
}

void CUVMaterialToggle::setActiveColor(const QColor& color) {
	Q_D(CUVMaterialToggle);

	d->activeColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	d->setupProperties();
}

QColor CUVMaterialToggle::activeColor() const {
	Q_D(const CUVMaterialToggle);

	if (d->useThemeColors || !d->activeColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("primary1");
	} else {
		return d->activeColor;
	}
}

void CUVMaterialToggle::setInactiveColor(const QColor& color) {
	Q_D(CUVMaterialToggle);

	d->inactiveColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	d->setupProperties();
}

QColor CUVMaterialToggle::inactiveColor() const {
	Q_D(const CUVMaterialToggle);

	if (d->useThemeColors || !d->inactiveColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("canvas");
	} else {
		return d->inactiveColor;
	}
}

void CUVMaterialToggle::setTrackColor(const QColor& color) {
	Q_D(CUVMaterialToggle);

	d->trackColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	d->setupProperties();
}

QColor CUVMaterialToggle::trackColor() const {
	Q_D(const CUVMaterialToggle);

	if (d->useThemeColors || !d->trackColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("accent3");
	} else {
		return d->trackColor;
	}
}

void CUVMaterialToggle::setOrientation(const Qt::Orientation orientation) {
	Q_D(CUVMaterialToggle);

	if (d->orientation == orientation) {
		return;
	}

	d->orientation = orientation;
	updateGeometry();
}

Qt::Orientation CUVMaterialToggle::orientation() const {
	Q_D(const CUVMaterialToggle);

	return d->orientation;
}

QSize CUVMaterialToggle::sizeHint() const {
	Q_D(const CUVMaterialToggle);

	return Qt::Horizontal == d->orientation ? QSize(64, 48) : QSize(48, 64);
}

bool CUVMaterialToggle::event(QEvent* event) {
	Q_D(CUVMaterialToggle);

	switch (event->type()) {
		case QEvent::ParentChange: {
			if (const auto widget = parentWidget()) {
				d->rippleOverlay->setParent(widget);
			}
			break;
		}
		default: break;
	}
	return QAbstractButton::event(event);
}

void CUVMaterialToggle::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)
}
