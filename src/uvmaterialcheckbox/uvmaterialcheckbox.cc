#include "uvmaterialcheckbox.hpp"

#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QState>

#include "uvmaterialcheckbox_p.hpp"
#include "uvmaterialshared/uvmaterialcheckable_internal.hpp"

/*!
 *  \class CUVMaterialCheckBoxPrivate
 *  \internal
 */
CUVMaterialCheckBoxPrivate::CUVMaterialCheckBoxPrivate(CUVMaterialCheckBox* q): CUVMaterialCheckablePrivate(q) {
}

CUVMaterialCheckBoxPrivate::~CUVMaterialCheckBoxPrivate() = default;

void CUVMaterialCheckBoxPrivate::init() {
	Q_Q(CUVMaterialCheckBox);

	checkedState->assignProperty(checkedIcon, "iconSize", 24);
	uncheckedState->assignProperty(checkedIcon, "iconSize", 0);

	auto animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
	animation->setDuration(300);
	uncheckedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
	animation->setDuration(1300);
	checkedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(checkedIcon, "opacity", q);
	animation->setDuration(440);
	checkedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(checkedIcon, "opacity", q);
	animation->setDuration(440);
	uncheckedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
	animation->setDuration(440);
	checkedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
	animation->setDuration(440);
	uncheckedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(uncheckedIcon, "color", q);
	animation->setDuration(440);
	checkedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(uncheckedIcon, "color", q);
	animation->setDuration(440);
	uncheckedTransition->addAnimation(animation);
}

/*!
 *  \class CUVMaterialCheckBox
 */
CUVMaterialCheckBox::CUVMaterialCheckBox(QWidget* parent)
: CUVMaterialCheckable(*new CUVMaterialCheckBoxPrivate(this), parent) {
	d_func()->init();
}

CUVMaterialCheckBox::~CUVMaterialCheckBox() = default;
