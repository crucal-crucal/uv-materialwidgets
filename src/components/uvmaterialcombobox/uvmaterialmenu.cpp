#include "uvmaterialmenu.hpp"

#include <algorithm>
#include <QPainter>
#include <QPropertyAnimation>

#include "uvmaterialmenustyle.hpp"
#include "uvmaterialmenu_p.hpp"

CUVMaterialMenuPrivate::CUVMaterialMenuPrivate(CUVMaterialMenu* q, QObject* parent): QObject(parent), q_ptr(q) {
}

CUVMaterialMenuPrivate::~CUVMaterialMenuPrivate() = default;

void CUVMaterialMenuPrivate::setAnimationImagePosY(const int pos) {
	_pAnimationImagePosY = pos;
	emit onAnimationImagePosYChanged();
}

int CUVMaterialMenuPrivate::getAnimationImagePosY() const {
	return _pAnimationImagePosY;
}

CUVMaterialMenu::CUVMaterialMenu(QWidget* parent): QMenu(parent), d_ptr(new CUVMaterialMenuPrivate(this, this)) {
	Q_D(CUVMaterialMenu);

	setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setObjectName("CUVMaterialMenu");
	d->_menuStyle = new CUVMaterialMenuStyle(style());
	setStyle(d->_menuStyle);
	d->_pAnimationImagePosY = 0;
}

CUVMaterialMenu::CUVMaterialMenu(const QString& title, QWidget* parent): QMenu(title, parent), d_ptr(new CUVMaterialMenuPrivate(this, this)) {
	Q_D(CUVMaterialMenu);

	setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setObjectName("CUVMaterialMenu");
	d->_menuStyle = new CUVMaterialMenuStyle(style());
	setStyle(d->_menuStyle);
	d->_pAnimationImagePosY = 0;
}

CUVMaterialMenu::~CUVMaterialMenu() = default;

void CUVMaterialMenu::setMenuItemHeight(const int menuItemHeight) {
	Q_D(CUVMaterialMenu);

	d->_menuStyle->setMenuItemHeight(menuItemHeight);
}

int CUVMaterialMenu::getMenuItemHeight() const {
	Q_D(const CUVMaterialMenu);

	return d->_menuStyle->getMenuItemHeight();
}

QAction* CUVMaterialMenu::addMenu(QMenu* menu) {
	return QMenu::addMenu(menu);
}

CUVMaterialMenu* CUVMaterialMenu::addMenu(const QString& title) {
	const auto menu = new CUVMaterialMenu(title, this);
	QMenu::addAction(menu->menuAction());
	return menu;
}

CUVMaterialMenu* CUVMaterialMenu::addMenu(const QIcon& icon, const QString& title) {
	const auto menu = new CUVMaterialMenu(title, this);
	menu->setIcon(icon);
	QMenu::addAction(menu->menuAction());
	return menu;
}

bool CUVMaterialMenu::isHasChildMenu() const {
	auto actionList = this->actions();
	const bool hasMenu = std::any_of(actionList.begin(), actionList.end(), [](const auto& action) {
		return !action->isSeparator() && action->menu();
	});

	return hasMenu;
}

bool CUVMaterialMenu::isHasIcon() const {
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

void CUVMaterialMenu::showEvent(QShowEvent* event) {
	Q_EMIT menuShow();
	Q_D(CUVMaterialMenu);

	//������Ӱƫ��
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

void CUVMaterialMenu::paintEvent(QPaintEvent* event) {
	Q_D(CUVMaterialMenu);
	QPainter painter(this);
	painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
	if (!d->_animationPix.isNull()) {
		painter.drawPixmap(QRect(0, d->_pAnimationImagePosY, width(), height()), d->_animationPix);
	} else {
		QMenu::paintEvent(event);
	}
}
