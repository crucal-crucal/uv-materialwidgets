#include "uvmenu.hpp"

#include <algorithm>
#include <QPainter>
#include <QPropertyAnimation>

#include "uvmenustyle.hpp"
#include "uvmenu_p.hpp"

CUVMenuPrivate::CUVMenuPrivate(CUVMenu* q, QObject* parent): QObject(parent), q_ptr(q) {
}

CUVMenuPrivate::~CUVMenuPrivate() = default;

void CUVMenuPrivate::setAnimationImagePosY(const int pos) {
	_pAnimationImagePosY = pos;
	emit onAnimationImagePosYChanged();
}

int CUVMenuPrivate::getAnimationImagePosY() const {
	return _pAnimationImagePosY;
}

CUVMenu::CUVMenu(QWidget* parent): QMenu(parent), d_ptr(new CUVMenuPrivate(this, this)) {
	Q_D(CUVMenu);

	setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setObjectName("CUVMenu");
	d->_menuStyle = new CUVMenuStyle(style());
	setStyle(d->_menuStyle);
	d->_pAnimationImagePosY = 0;
}

CUVMenu::CUVMenu(const QString& title, QWidget* parent): QMenu(title, parent), d_ptr(new CUVMenuPrivate(this, this)) {
	Q_D(CUVMenu);

	setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setObjectName("CUVMenu");
	d->_menuStyle = new CUVMenuStyle(style());
	setStyle(d->_menuStyle);
	d->_pAnimationImagePosY = 0;
}

CUVMenu::~CUVMenu() = default;

void CUVMenu::setMenuItemHeight(const int menuItemHeight) {
	Q_D(CUVMenu);

	d->_menuStyle->setMenuItemHeight(menuItemHeight);
}

int CUVMenu::getMenuItemHeight() const {
	Q_D(const CUVMenu);

	return d->_menuStyle->getMenuItemHeight();
}

QAction* CUVMenu::addMenu(QMenu* menu) {
	return QMenu::addMenu(menu);
}

CUVMenu* CUVMenu::addMenu(const QString& title) {
	const auto menu = new CUVMenu(title, this);
	QMenu::addAction(menu->menuAction());
	return menu;
}

CUVMenu* CUVMenu::addMenu(const QIcon& icon, const QString& title) {
	const auto menu = new CUVMenu(title, this);
	menu->setIcon(icon);
	QMenu::addAction(menu->menuAction());
	return menu;
}

bool CUVMenu::isHasChildMenu() const {
	auto actionList = this->actions();
	const bool hasMenu = std::any_of(actionList.begin(), actionList.end(), [](const auto& action) {
		return !action->isSeparator() && action->menu();
	});

	return hasMenu;
}

bool CUVMenu::isHasIcon() const {
	auto actionList = this->actions();
	const bool hasIcon = std::any_of(actionList.begin(), actionList.end(), [](const auto& action) {
		// Skip separators
		if (action->isSeparator()) {
			return false;
		}
		// Check menu for icons or property
		if (const QMenu* menu = action->menu(); menu && (!menu->icon().isNull() || !menu->property("CUVIconType").toString().isEmpty())) {
			return true;
		}
		// Check action itself for icons or property
		return !action->icon().isNull() || !action->property("CUVIconType").toString().isEmpty();
	});

	return hasIcon;
}

void CUVMenu::showEvent(QShowEvent* event) {
	Q_EMIT menuShow();
	Q_D(CUVMenu);

	//消除阴影偏移
	move(this->pos().x() - 6, this->pos().y());
	if (!d->_animationPix.isNull()) {
		d->_animationPix = QPixmap();
	}
	d->_animationPix = this->grab(this->rect());
	const auto posAnimation = new QPropertyAnimation(d, "pAnimationImagePosY");
	connect(posAnimation, &QPropertyAnimation::finished, this, [=]() {
		d->_animationPix = QPixmap();
		update();
	});
	connect(posAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
		update();
	});
	posAnimation->setEasingCurve(QEasingCurve::OutCubic);
	posAnimation->setDuration(400);
	int targetPosY = height();
	if (targetPosY > 160) {
		if (targetPosY < 320) {
			targetPosY = 160;
		} else {
			targetPosY /= 2;
		}
	}

	if (pos().y() + d->_menuStyle->getMenuItemHeight() + 9 >= QCursor::pos().y()) {
		posAnimation->setStartValue(-targetPosY);
	} else {
		posAnimation->setStartValue(targetPosY);
	}

	posAnimation->setEndValue(0);
	posAnimation->start(QAbstractAnimation::DeleteWhenStopped);
	QMenu::showEvent(event);
}

void CUVMenu::paintEvent(QPaintEvent* event) {
	Q_D(CUVMenu);
	QPainter painter(this);
	painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
	if (!d->_animationPix.isNull()) {
		painter.drawPixmap(QRect(0, d->_pAnimationImagePosY, width(), height()), d->_animationPix);
	} else {
		QMenu::paintEvent(event);
	}
}
