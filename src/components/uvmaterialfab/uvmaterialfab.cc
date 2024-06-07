#include "uvmaterialfab.hpp"

#include <QEvent>
#include <QPainter>
#include <QState>
#include <QtWidgets/QGraphicsDropShadowEffect>

#include "uvmaterialfab_p.hpp"
#include "uvshared/uvmaterialrippleoverlay.hpp"

/*!
 *  \class CUVMaterialFloatingActionButtonPrivate
 *  \internal
 */
CUVMaterialFloatingActionButtonPrivate::CUVMaterialFloatingActionButtonPrivate(CUVMaterialFloatingActionButton* q)
: CUVMaterialRaisedButtonPrivate(q) {
}

/*!
 *  \internal
 */
CUVMaterialFloatingActionButtonPrivate::~CUVMaterialFloatingActionButtonPrivate() = default;

/*!
 *  \internal
 */
void CUVMaterialFloatingActionButtonPrivate::init() {
	Q_Q(CUVMaterialFloatingActionButton);

	corner = Qt::BottomRightCorner;
	mini = false;
	offsX = 34;
	offsY = 36;

	q->setRole(Material::Primary);
	q->setFixedSize(DefaultDiameter, DefaultDiameter);
	q->setGeometry(fabGeometry());

	setupProperties();

	if (q->parentWidget()) {
		q->parentWidget()->installEventFilter(q);
	}

	q->setFixedRippleRadius(50);
}

/*!
 *  \internal
 */
QRect CUVMaterialFloatingActionButtonPrivate::fabGeometry() const {
	Q_Q(const CUVMaterialFloatingActionButton);

	const QWidget* parent = q->parentWidget();
	if (!parent) {
		return {};
	}

	const int s = mini ? MiniDiameter : DefaultDiameter;

	switch (corner) {
		case Qt::TopLeftCorner:
			return { offsX, offsY, s, s };
		case Qt::TopRightCorner:
			return { parent->width() - (offsX + s), offsY, s, s };
		case Qt::BottomLeftCorner:
			return { offsX, parent->height() - (offsY + s), s, s };
		case Qt::BottomRightCorner:
		default: break;
	}
	return { parent->width() - (offsX + s), parent->height() - (offsY + s), s, s };
}

/*!
 *  \internal
 */
void CUVMaterialFloatingActionButtonPrivate::setupProperties() const {
	if (mini) {
		effect->setColor(QColor(0, 0, 0, 80));
		normalState->assignProperty(effect, "offset", QPointF(0, 3));
		normalState->assignProperty(effect, "blurRadius", 13);
		pressedState->assignProperty(effect, "offset", QPointF(0, 7));
		pressedState->assignProperty(effect, "blurRadius", 20);
	} else {
		effect->setColor(QColor(0, 0, 0, 105));
		normalState->assignProperty(effect, "offset", QPointF(0, 6));
		normalState->assignProperty(effect, "blurRadius", 16);
		pressedState->assignProperty(effect, "offset", QPointF(0, 11));
		pressedState->assignProperty(effect, "blurRadius", 28);
	}
}

/*!
 *  \class CUVMaterialFloatingActionButton
 */

CUVMaterialFloatingActionButton::CUVMaterialFloatingActionButton(const QIcon& icon, QWidget* parent)
: CUVMaterialRaisedButton(*new CUVMaterialFloatingActionButtonPrivate(this), parent) {
	d_func()->init();

	setIcon(icon);
}

CUVMaterialFloatingActionButton::~CUVMaterialFloatingActionButton() = default;

/*!
 *  \reimp
 */
QSize CUVMaterialFloatingActionButton::sizeHint() const {
	Q_D(const CUVMaterialFloatingActionButton);

	if (d->mini) {
		return {
			CUVMaterialFloatingActionButtonPrivate::MiniDiameter,
			CUVMaterialFloatingActionButtonPrivate::MiniDiameter
		};
	} else {
		return {
			CUVMaterialFloatingActionButtonPrivate::DefaultDiameter,
			CUVMaterialFloatingActionButtonPrivate::DefaultDiameter
		};
	}
}

void CUVMaterialFloatingActionButton::setMini(const bool state) {
	Q_D(CUVMaterialFloatingActionButton);

	if (d->mini == state) {
		return;
	}

	d->mini = state;

	setFixedSize(d->diameter(), d->diameter());
	setFixedRippleRadius(state ? 30 : 50);

	d->setupProperties();
	updateClipPath();
	setGeometry(d->fabGeometry());
	update();
}

bool CUVMaterialFloatingActionButton::isMini() const {
	Q_D(const CUVMaterialFloatingActionButton);

	return d->mini;
}

void CUVMaterialFloatingActionButton::setCorner(const Qt::Corner corner) {
	Q_D(CUVMaterialFloatingActionButton);

	if (d->corner == corner) {
		return;
	}

	d->corner = corner;
	setGeometry(d->fabGeometry());
	update();
}

Qt::Corner CUVMaterialFloatingActionButton::corner() const {
	Q_D(const CUVMaterialFloatingActionButton);

	return d->corner;
}

void CUVMaterialFloatingActionButton::setOffset(const int x, const int y) {
	Q_D(CUVMaterialFloatingActionButton);

	d->offsX = x;
	d->offsY = y;
	setGeometry(d->fabGeometry());
	update();
}

QSize CUVMaterialFloatingActionButton::offset() const {
	Q_D(const CUVMaterialFloatingActionButton);

	return { d->offsX, d->offsY };
}

void CUVMaterialFloatingActionButton::setXOffset(const int x) {
	Q_D(CUVMaterialFloatingActionButton);

	d->offsX = x;
	setGeometry(d->fabGeometry());
	update();
}

int CUVMaterialFloatingActionButton::xOffset() const {
	Q_D(const CUVMaterialFloatingActionButton);

	return d->offsX;
}

void CUVMaterialFloatingActionButton::setYOffset(const int y) {
	Q_D(CUVMaterialFloatingActionButton);

	d->offsY = y;
	setGeometry(d->fabGeometry());
	update();
}

int CUVMaterialFloatingActionButton::yOffset() const {
	Q_D(const CUVMaterialFloatingActionButton);

	return d->offsY;
}

/*!
 *  \reimp
 */
bool CUVMaterialFloatingActionButton::event(QEvent* event) {
	Q_D(CUVMaterialFloatingActionButton);

	if (!parent()) {
		return CUVMaterialRaisedButton::event(event);
	}
	switch (event->type()) {
		case QEvent::ParentChange: {
			parent()->installEventFilter(this);
			setGeometry(d->fabGeometry());
			break;
		}
		case QEvent::ParentAboutToChange: {
			parent()->removeEventFilter(this);
			break;
		}
		default:
			break;
	}
	return CUVMaterialRaisedButton::event(event);
}

/*!
 *  \reimp
 */
bool CUVMaterialFloatingActionButton::eventFilter(QObject* watched, QEvent* event) {
	if (const QEvent::Type type = event->type(); QEvent::Move == type || QEvent::Resize == type) {
		Q_D(CUVMaterialFloatingActionButton);
		setGeometry(d->fabGeometry());
	}

	return CUVMaterialRaisedButton::eventFilter(watched, event);
}

/*!
 *  \reimp
 */
void CUVMaterialFloatingActionButton::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	Q_D(CUVMaterialFloatingActionButton);

	auto square = QRect(0, 0, d->diameter(), d->diameter());
	square.moveCenter(rect().center());

	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);

	if (isEnabled()) {
		brush.setColor(backgroundColor());
	} else {
		brush.setColor(disabledBackgroundColor());
	}

	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);
	painter.drawEllipse(square);

	QRect iconGeometry(0, 0, d->iconSize(), d->iconSize());
	iconGeometry.moveCenter(square.center());

	QPixmap pixmap = icon().pixmap(QSize(d->iconSize(), d->iconSize()));
	QPainter icon(&pixmap);
	icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
	icon.fillRect(pixmap.rect(), isEnabled() ? foregroundColor()
		                             : disabledForegroundColor());
	painter.drawPixmap(iconGeometry, pixmap);
}

void CUVMaterialFloatingActionButton::updateClipPath() {
	Q_D(CUVMaterialFloatingActionButton);

	QPainterPath path;
	path.addEllipse(0, 0, d->diameter(), d->diameter());
	d->rippleOverlay->setClipPath(path);
}
