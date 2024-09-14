#include "uvcombobox.hpp"

#include <QApplication>
#include <QLayout>
#include <QListView>
#include <QPropertyAnimation>

#include "uvcomboboxstyle.hpp"
#include "uvcombobox_p.hpp"
#include "uvscrollbar.hpp"

CUVComboBoxPrivate::CUVComboBoxPrivate(CUVComboBox* q, QObject* parent): QObject(parent), q_ptr(q) {
}

CUVComboBoxPrivate::~CUVComboBoxPrivate() = default;


CUVComboBox::CUVComboBox(QWidget* parent): QComboBox(parent), d_ptr(new CUVComboBoxPrivate(this, this)) {
	Q_D(CUVComboBox);

	d->_pBorderRadius = 3;
	setObjectName("CUVComboBox");
	setFixedHeight(35);
	d->_comboBoxStyle = new CUVComboBoxStyle(style());
	setStyle(d->_comboBoxStyle);

	// 调用view 让container初始化
	setView(new QListView(this));
	const auto comboBoxView = this->view();
	comboBoxView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	const auto scrollBar = new CUVScrollBar(this);
	comboBoxView->setVerticalScrollBar(scrollBar);
	comboBoxView->setAutoScroll(false);
	comboBoxView->setSelectionMode(QAbstractItemView::NoSelection);
	comboBoxView->setObjectName("CUVComboBoxView");
	comboBoxView->setStyleSheet("#CUVComboBoxView{ background-color: transparent; }");
	comboBoxView->setStyle(d->_comboBoxStyle);
	// comboBoxView->verticalScrollBar()->setVisible(false);
	// comboBoxView->horizontalScrollBar()->setVisible(false);
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

CUVComboBox::~CUVComboBox() = default;

void CUVComboBox::setBorderRadius(const int borderRadius) {
	Q_D(CUVComboBox);

	d->_pBorderRadius = borderRadius;
	emit onBorderRadiusChanged();
}

int CUVComboBox::getBorderRadius() const {
	Q_D(const CUVComboBox);

	return d->_pBorderRadius;
}

void CUVComboBox::setNomalColor(const QColor& color) {
	Q_D(CUVComboBox);

	d->_comboBoxStyle->normalColor = color;
}

QColor CUVComboBox::getNomalColor() const {
	Q_D(const CUVComboBox);

	return d->_comboBoxStyle->normalColor;
}

void CUVComboBox::setMouseHoverColor(const QColor& color) {
	Q_D(CUVComboBox);

	d->_comboBoxStyle->mouseHoverColor = color;
}

QColor CUVComboBox::getMouseHoverColor() const {
	Q_D(const CUVComboBox);

	return d->_comboBoxStyle->mouseHoverColor;
}

void CUVComboBox::setMouseSelectedColor(const QColor& color) {
	Q_D(CUVComboBox);

	d->_comboBoxStyle->mouseSelectedColor = color;
}

QColor CUVComboBox::getMouseSelectedColor() const {
	Q_D(const CUVComboBox);

	return d->_comboBoxStyle->mouseSelectedColor;
}

void CUVComboBox::setBorderColor(const QColor& color) {
	Q_D(CUVComboBox);

	d->_comboBoxStyle->borderColor = color;
}

QColor CUVComboBox::getBorderColor() const {
	Q_D(const CUVComboBox);

	return d->_comboBoxStyle->borderColor;
}

void CUVComboBox::setSelectedMarkColor(const QColor& color) {
	Q_D(CUVComboBox);

	d->_comboBoxStyle->selectedMarkColor = color;
}

QColor CUVComboBox::getSelectedMarkColor() const {
	Q_D(const CUVComboBox);

	return d->_comboBoxStyle->selectedMarkColor;
}

void CUVComboBox::setItemHoverColor(const QColor& color) {
	Q_D(CUVComboBox);

	d->_comboBoxStyle->itemHoverColor = color;
}

QColor CUVComboBox::getItemHoverColor() const {
	Q_D(const CUVComboBox);

	return d->_comboBoxStyle->itemHoverColor;
}

void CUVComboBox::setExpansionIndicatorColor(const QColor& color) {
	Q_D(CUVComboBox);

	d->_comboBoxStyle->expansionIndicatorColor = color;
}

QColor CUVComboBox::getExpansionIndicatorColor() const {
	Q_D(const CUVComboBox);

	return d->_comboBoxStyle->expansionIndicatorColor;
}

void CUVComboBox::showPopup() {
	Q_D(CUVComboBox);

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
			fixedSizeAnimation->setDuration(200);
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
			viewPosAnimation->setDuration(200);
			viewPosAnimation->start(QAbstractAnimation::DeleteWhenStopped);
		}
		// 指示器动画
		const auto rotateAnimation = new QPropertyAnimation(d->_comboBoxStyle, "pExpandIconRotate");
		connect(rotateAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
			update();
		});
		rotateAnimation->setDuration(200);
		rotateAnimation->setEasingCurve(QEasingCurve::InOutSine);
		rotateAnimation->setStartValue(d->_comboBoxStyle->getExpandIconRotate());
		rotateAnimation->setEndValue(-180);
		rotateAnimation->start(QAbstractAnimation::DeleteWhenStopped);
		const auto markAnimation = new QPropertyAnimation(d->_comboBoxStyle, "pExpandMarkWidth");
		markAnimation->setDuration(200);
		markAnimation->setEasingCurve(QEasingCurve::InOutSine);
		markAnimation->setStartValue(d->_comboBoxStyle->getExpandMarkWidth());
		markAnimation->setEndValue(width() / 2 - d->_pBorderRadius - 6);
		markAnimation->start(QAbstractAnimation::DeleteWhenStopped);
	}
}

void CUVComboBox::hidePopup() {
	Q_D(CUVComboBox);

	if (d->_isAllowHidePopup) {
		if (QWidget* container = this->findChild<QFrame*>()) {
			const int containerHeight = container->height();
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
