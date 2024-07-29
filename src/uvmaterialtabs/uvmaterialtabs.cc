#include "uvmaterialtabs.hpp"

#include <QtWidgets/QHBoxLayout>

#include "uvmaterialtabs_internal.hpp"
#include "uvmaterialtabs_p.hpp"
#include "uvmaterialshared/uvmaterialstyle.hpp"

/*!
 *  \CUVMaterialTabsPrivate
 *  \internal
 */
CUVMaterialTabsPrivate::CUVMaterialTabsPrivate(CUVMaterialTabs* q): q_ptr(q) {
}

CUVMaterialTabsPrivate::~CUVMaterialTabsPrivate() = default;

void CUVMaterialTabsPrivate::CUVMaterialTabsPrivate::init() {
	Q_Q(CUVMaterialTabs);

	inkBar = new CUVMaterialTabsInkBar(q);
	tabLayout = new QHBoxLayout;
	rippleStyle = Material::CenteredRipple;
	tab = -1;
	showHalo = true;
	useThemeColors = true;

	q->setLayout(tabLayout);
	q->setStyle(&CUVMaterialStyle::instance());

	tabLayout->setSpacing(0);
	tabLayout->setMargin(0);
}

/*!
 *  \CUVMaterialTabs
 */
CUVMaterialTabs::CUVMaterialTabs(QWidget* parent)
: QWidget(parent), d_ptr(new CUVMaterialTabsPrivate(this)) {
	d_func()->init();
}

CUVMaterialTabs::~CUVMaterialTabs() = default;

void CUVMaterialTabs::setUseThemeColors(const bool value) {
	Q_D(CUVMaterialTabs);

	d->useThemeColors = value;
}

bool CUVMaterialTabs::useThemeColors() const {
	Q_D(const CUVMaterialTabs);

	return d->useThemeColors;
}

void CUVMaterialTabs::setHaloVisible(const bool value) {
	Q_D(CUVMaterialTabs);

	d->showHalo = value;
	updateTabs();
}

bool CUVMaterialTabs::isHaloVisible() const {
	Q_D(const CUVMaterialTabs);

	return d->showHalo;
}

void CUVMaterialTabs::setRippleStyle(const Material::RippleStyle style) {
	Q_D(CUVMaterialTabs);

	d->rippleStyle = style;
	updateTabs();
}

Material::RippleStyle CUVMaterialTabs::rippleStyle() const {
	Q_D(const CUVMaterialTabs);

	return d->rippleStyle;
}

void CUVMaterialTabs::setInkColor(const QColor& color) {
	Q_D(CUVMaterialTabs);

	d->inkColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	d->inkBar->update();
	update();
}

QColor CUVMaterialTabs::inkColor() const {
	Q_D(const CUVMaterialTabs);

	if (d->useThemeColors || !d->inkColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("accent1");
	} else {
		return d->inkColor;
	}
}

void CUVMaterialTabs::setBackgroundColor(const QColor& color) {
	Q_D(CUVMaterialTabs);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	updateTabs();
	update();
}

QColor CUVMaterialTabs::backgroundColor() const {
	Q_D(const CUVMaterialTabs);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("primary1");
	} else {
		return d->backgroundColor;
	}
}

void CUVMaterialTabs::setTextColor(const QColor& color) {
	Q_D(CUVMaterialTabs);

	d->textColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	updateTabs();
	update();
}

QColor CUVMaterialTabs::textColor() const {
	Q_D(const CUVMaterialTabs);

	if (d->useThemeColors || !d->textColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("canvas");
	} else {
		return d->textColor;
	}
}

void CUVMaterialTabs::setCurrentTab(CUVMaterialTab* tab) {
	Q_D(CUVMaterialTabs);

	setCurrentTab(d->tabLayout->indexOf(tab));
}

void CUVMaterialTabs::setCurrentTab(const int index) {
	Q_D(CUVMaterialTabs);

	setTabActive(d->tab, false);
	d->tab = index;
	setTabActive(index, true);
	d->inkBar->animate();

	emit currentChanged(index);
}

void CUVMaterialTabs::addTab(const QString& text, const QIcon& icon) {
	Q_D(CUVMaterialTabs);

	const auto tab = new CUVMaterialTab(this);
	tab->setText(text);
	tab->setHaloVisible(isHaloVisible());
	tab->setRippleStyle(rippleStyle());

	if (!icon.isNull()) {
		tab->setIcon(icon);
		tab->setIconSize(QSize(22, 22));
	}

	d->tabLayout->addWidget(tab);

	if (-1 == d->tab) {
		d->tab = 0;
		d->inkBar->refreshGeometry();
		d->inkBar->raise();
		tab->setActive(true);
	}
}

int CUVMaterialTabs::currentIndex() const {
	Q_D(const CUVMaterialTabs);

	return d->tab;
}

void CUVMaterialTabs::setTabActive(const int index, const bool active) {
	Q_D(CUVMaterialTabs);

	if (index > -1) {
		if (const auto tab = dynamic_cast<CUVMaterialTab*>(d->tabLayout->itemAt(index)->widget())) {
			tab->setActive(active);
		}
	}
}

void CUVMaterialTabs::updateTabs() {
	Q_D(CUVMaterialTabs);

	CUVMaterialTab* tab;
	for (int i = 0; i < d->tabLayout->count(); ++i) {
		if (QLayoutItem* item = d->tabLayout->itemAt(i); (tab = dynamic_cast<CUVMaterialTab*>(item->widget()))) {
			tab->setRippleStyle(d->rippleStyle);
			tab->setHaloVisible(d->showHalo);
			tab->setBackgroundColor(backgroundColor());
			tab->setForegroundColor(textColor());
		}
	}
}
