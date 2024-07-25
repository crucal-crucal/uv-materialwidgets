#include "uvmaterialcombobox.hpp"

#include <QApplication>
#include <QLayout>
#include <QListView>
#include <QPropertyAnimation>

#include "uvmaterialcomboboxstyle.hpp"
#include "uvmaterialcombobox_p.hpp"
#include "uvmaterialscrollbar.hpp"

CUVMaterialComboBoxPrivate::CUVMaterialComboBoxPrivate(CUVMaterialComboBox* q, QObject* parent): QObject(parent), q_ptr(q) {
}

CUVMaterialComboBoxPrivate::~CUVMaterialComboBoxPrivate() = default;


CUVMaterialComboBox::CUVMaterialComboBox(QWidget* parent): QComboBox(parent), d_ptr(new CUVMaterialComboBoxPrivate(this, this)) {
	Q_D(CUVMaterialComboBox);

	d->_pBorderRadius = 3;
	setObjectName("CUVComboBox");
	setFixedHeight(35);
	d->_comboBoxStyle = new CUVMaterialComboBoxStyle(style());
	setStyle(d->_comboBoxStyle);

	// 调用view 让container初始化
	setView(new QListView(this));
	const auto comboBoxView = this->view();
	comboBoxView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	const auto scrollBar = new CUVMaterialScrollBar(this);
	comboBoxView->setVerticalScrollBar(scrollBar);
	comboBoxView->setAutoScroll(false);
	comboBoxView->setSelectionMode(QAbstractItemView::NoSelection);
	comboBoxView->setObjectName("CUVComboBoxView");
	comboBoxView->setStyleSheet("#CUVComboBoxView{ background-color: transparent; }");
	comboBoxView->setStyle(d->_comboBoxStyle);
	comboBoxView->verticalScrollBar()->setVisible(false);
	comboBoxView->horizontalScrollBar()->setVisible(false);
	if (QWidget* container = this->findChild<QFrame*>()) {
		container->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
		container->setAttribute(Qt::WA_TranslucentBackground);
		container->setObjectName("CUVComboBoxContainer");
		container->setStyle(d->_comboBoxStyle);
		QLayout* layout = container->layout();
		while (layout->count()) {
			layout->takeAt(0);
		}
		layout->addWidget(view());
		layout->setContentsMargins(6, 0, 6, 6);
	}
	QComboBox::setMaxVisibleItems(5);
}

CUVMaterialComboBox::~CUVMaterialComboBox() = default;

void CUVMaterialComboBox::setBorderRadius(const int borderRadius) {
	Q_D(CUVMaterialComboBox);

	d->_pBorderRadius = borderRadius;
	emit onBorderRadiusChanged();
}

int CUVMaterialComboBox::getBorderRadius() const {
	Q_D(const CUVMaterialComboBox);

	return d->_pBorderRadius;
}

void CUVMaterialComboBox::setNomalColor(const QColor& color) {
	Q_D(CUVMaterialComboBox);

	d->_comboBoxStyle->normalColor = color;
}

QColor CUVMaterialComboBox::getNomalColor() const {
	Q_D(const CUVMaterialComboBox);

	return d->_comboBoxStyle->normalColor;
}

void CUVMaterialComboBox::setMouseHoverColor(const QColor& color) {
	Q_D(CUVMaterialComboBox);

	d->_comboBoxStyle->mouseHoverColor = color;
}

QColor CUVMaterialComboBox::getMouseHoverColor() const {
	Q_D(const CUVMaterialComboBox);

	return d->_comboBoxStyle->mouseHoverColor;
}

void CUVMaterialComboBox::setMouseSelectedColor(const QColor& color) {
	Q_D(CUVMaterialComboBox);

	d->_comboBoxStyle->mouseSelectedColor = color;
}

QColor CUVMaterialComboBox::getMouseSelectedColor() const {
	Q_D(const CUVMaterialComboBox);

	return d->_comboBoxStyle->mouseSelectedColor;
}

void CUVMaterialComboBox::setBorderColor(const QColor& color) {
	Q_D(CUVMaterialComboBox);

	d->_comboBoxStyle->borderColor = color;
}

QColor CUVMaterialComboBox::getBorderColor() const {
	Q_D(const CUVMaterialComboBox);

	return d->_comboBoxStyle->borderColor;
}

void CUVMaterialComboBox::showPopup() {
	Q_D(CUVMaterialComboBox);

	bool oldAnimationEffects = qApp->isEffectEnabled(Qt::UI_AnimateCombo); // NOLINT
	qApp->setEffectEnabled(Qt::UI_AnimateCombo, false);                    // NOLINT
	QComboBox::showPopup();
	qApp->setEffectEnabled(Qt::UI_AnimateCombo, oldAnimationEffects); // NOLINT

	if (count() > 0) {
		if (QWidget* container = this->findChild<QFrame*>()) {
			const int containerHeight = container->height();
			container->move(container->x(), container->y() + 3);
			QLayout* layout = container->layout();
			while (layout->count()) {
				layout->takeAt(0);
			}
			const auto fixedSizeAnimation = new QPropertyAnimation(container, "maximumHeight");
			connect(fixedSizeAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
				container->setFixedHeight(value.toInt());
			});
			fixedSizeAnimation->setStartValue(1);
			fixedSizeAnimation->setEndValue(containerHeight);
			fixedSizeAnimation->setEasingCurve(QEasingCurve::OutCubic);
			fixedSizeAnimation->setDuration(400);
			fixedSizeAnimation->start(QAbstractAnimation::DeleteWhenStopped);

			const auto viewPosAnimation = new QPropertyAnimation(view(), "pos");
			connect(viewPosAnimation, &QPropertyAnimation::finished, this, [=]() {
				d->_isAllowHidePopup = true;
				layout->addWidget(view());
			});
			const QPoint viewPos = view()->pos();
			viewPosAnimation->setStartValue(QPoint(viewPos.x(), viewPos.y() - view()->height()));
			viewPosAnimation->setEndValue(viewPos);
			viewPosAnimation->setEasingCurve(QEasingCurve::OutCubic);
			viewPosAnimation->setDuration(400);
			viewPosAnimation->start(QAbstractAnimation::DeleteWhenStopped);
		}
		// 指示器动画
		const auto rotateAnimation = new QPropertyAnimation(d->_comboBoxStyle, "pExpandIconRotate");
		connect(rotateAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
			update();
		});
		rotateAnimation->setDuration(300);
		rotateAnimation->setEasingCurve(QEasingCurve::InOutSine);
		rotateAnimation->setStartValue(d->_comboBoxStyle->getExpandIconRotate());
		rotateAnimation->setEndValue(-180);
		rotateAnimation->start(QAbstractAnimation::DeleteWhenStopped);
		const auto markAnimation = new QPropertyAnimation(d->_comboBoxStyle, "pExpandMarkWidth");
		markAnimation->setDuration(300);
		markAnimation->setEasingCurve(QEasingCurve::InOutSine);
		markAnimation->setStartValue(d->_comboBoxStyle->getExpandMarkWidth());
		markAnimation->setEndValue(width() / 2 - d->_pBorderRadius - 6);
		markAnimation->start(QAbstractAnimation::DeleteWhenStopped);
	}
}

void CUVMaterialComboBox::hidePopup() {
	Q_D(CUVMaterialComboBox);

	if (d->_isAllowHidePopup) {
		QWidget* container = this->findChild<QFrame*>();
		const int containerHeight = container->height();
		if (container) { // NOLINT
			QLayout* layout = container->layout();
			while (layout->count()) {
				layout->takeAt(0);
			}
			const auto viewPosAnimation = new QPropertyAnimation(view(), "pos");
			connect(viewPosAnimation, &QPropertyAnimation::finished, this, [=]() {
				layout->addWidget(view());
			});
			constexpr auto viewPos = QPoint(7, 1);
			connect(viewPosAnimation, &QPropertyAnimation::finished, this, [=]() { view()->move(viewPos); });
			viewPosAnimation->setStartValue(viewPos);
			viewPosAnimation->setEndValue(QPoint(viewPos.x(), viewPos.y() - view()->height()));
			viewPosAnimation->setEasingCurve(QEasingCurve::InCubic);
			viewPosAnimation->start(QAbstractAnimation::DeleteWhenStopped);

			const auto fixedSizeAnimation = new QPropertyAnimation(container, "maximumHeight");
			connect(fixedSizeAnimation, &QPropertyAnimation::finished, this, [=]() {
				QComboBox::hidePopup();
				container->setFixedHeight(containerHeight);
			});
			connect(fixedSizeAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
				container->setFixedHeight(value.toInt());
			});
			fixedSizeAnimation->setStartValue(container->height());
			fixedSizeAnimation->setEndValue(1);
			fixedSizeAnimation->setEasingCurve(QEasingCurve::InCubic);
			fixedSizeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
			d->_isAllowHidePopup = false;
		}
		// 指示器动画
		const auto rotateAnimation = new QPropertyAnimation(d->_comboBoxStyle, "pExpandIconRotate");
		connect(rotateAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
			update();
		});
		rotateAnimation->setDuration(300);
		rotateAnimation->setEasingCurve(QEasingCurve::InOutSine);
		rotateAnimation->setStartValue(d->_comboBoxStyle->getExpandIconRotate());
		rotateAnimation->setEndValue(0);
		rotateAnimation->start(QAbstractAnimation::DeleteWhenStopped);
		const auto markAnimation = new QPropertyAnimation(d->_comboBoxStyle, "pExpandMarkWidth");
		markAnimation->setDuration(300);
		markAnimation->setEasingCurve(QEasingCurve::InOutSine);
		markAnimation->setStartValue(d->_comboBoxStyle->getExpandMarkWidth());
		markAnimation->setEndValue(0);
		markAnimation->start(QAbstractAnimation::DeleteWhenStopped);
	}
}
