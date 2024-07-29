#include "uvfabsettingseditor.hpp"

#include <QColorDialog>

CUVFabSettingsEditor::CUVFabSettingsEditor(QWidget* parent)
: QWidget(parent), m_pfab(new CUVMaterialFloatingActionButton(CUVMaterialTheme::icon("toggle", "star"))) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVFabSettingsEditor::~CUVFabSettingsEditor() = default;

void CUVFabSettingsEditor::createCtrl() {
	m_pLbDisabled = new QLabel(tr("Disabled"), this);
	m_pLbDisabled->setFixedWidth(m_nLabelWidth);
	m_pCbDisabled = new QCheckBox(this);

	m_pLbCorner = new QLabel(tr("Corner"), this);
	m_pLbCorner->setFixedWidth(m_nLabelWidth);
	m_pCbCorner = new QComboBox(this);

	m_pLbButtonRole = new QLabel(tr("Button Role"), this);
	m_pLbButtonRole->setFixedWidth(m_nLabelWidth);
	m_pCbButtonRole = new QComboBox(this);

	m_pLbHorizonOffset = new QLabel(tr("Horizon Offset"), this);
	m_pLbHorizonOffset->setFixedWidth(m_nLabelWidth);
	m_pSbHorizonOffset = new QSpinBox(this);

	m_pLbVerticalOffset = new QLabel(tr("Vertical Offset"), this);
	m_pLbVerticalOffset->setFixedWidth(m_nLabelWidth);
	m_pSbVerticalOffset = new QSpinBox(this);

	m_pLbMini = new QLabel(tr("Mini"), this);
	m_pLbMini->setFixedWidth(m_nLabelWidth);
	m_pCbMini = new QCheckBox(this);

	m_pLbRippleStyle = new QLabel(tr("Ripple Style"), this);
	m_pLbRippleStyle->setFixedWidth(m_nLabelWidth);
	m_pCbRippleStyle = new QComboBox(this);

	m_pLbUseThemeColors = new QLabel(tr("Use Theme Colors"), this);
	m_pLbUseThemeColors->setFixedWidth(m_nLabelWidth);
	m_pCbUseThemeColors = new QCheckBox(this);

	m_pLbBackgroundColor = new QLabel(tr("Background Color"), this);
	m_pLbBackgroundColor->setFixedWidth(m_nLabelWidth);
	m_pLeBackgroundColor = new QLineEdit(this);
	m_pTbBackgroundColor = new QToolButton(this);
	m_pTbBackgroundColor->setObjectName("backgroundColorToolButton");
	m_pTbBackgroundColor->setText("...");

	m_pLbForegroundColor = new QLabel(tr("Foreground Color"), this);
	m_pLbForegroundColor->setFixedWidth(m_nLabelWidth);
	m_pLeForegroundColor = new QLineEdit(this);
	m_pTbForegroundColor = new QToolButton(this);
	m_pTbForegroundColor->setObjectName("foregroundColorToolButton");
	m_pTbForegroundColor->setText("...");

	m_pLbDisabledBgColor = new QLabel(tr("Disabled Bg Color"), this);
	m_pLbDisabledBgColor->setFixedWidth(m_nLabelWidth);
	m_pLeDisabledBgColor = new QLineEdit(this);
	m_pTbDisabledBgColor = new QToolButton(this);
	m_pTbDisabledBgColor->setObjectName("disabledBgColorToolButton");
	m_pTbDisabledBgColor->setText("...");

	m_pLbDisabledFgColor = new QLabel(tr("Disabled Fg Color"), this);
	m_pLbDisabledFgColor->setFixedWidth(m_nLabelWidth);
	m_pLeDisabledFgColor = new QLineEdit(this);
	m_pTbDisabledFgColor = new QToolButton(this);
	m_pTbDisabledFgColor->setObjectName("disabledFgColorToolButton");
	m_pTbDisabledFgColor->setText("...");

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");
	m_pfab->setParent(m_pcanvas);

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayDisabled = new QHBoxLayout;
	m_pHLayCorner = new QHBoxLayout;
	m_pHLayButtonRole = new QHBoxLayout;
	m_pHLayHorizonOffset = new QHBoxLayout;
	m_pHLayVerticalOffset = new QHBoxLayout;
	m_pHLayMini = new QHBoxLayout;
	m_pHLayRippleStyle = new QHBoxLayout;
	m_pHLayUseThemeColors = new QHBoxLayout;
	m_pHLayBackgroundColor = new QHBoxLayout;
	m_pHLayForegroundColor = new QHBoxLayout;
	m_pHLayDisabledBgColor = new QHBoxLayout;
	m_pHLayDisabledFgColor = new QHBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVFabSettingsEditor::customLayout() const {
	m_pHLayDisabled->addWidget(m_pLbDisabled);
	m_pHLayDisabled->addWidget(m_pCbDisabled);
	m_pHLayDisabled->addStretch();

	m_pHLayCorner->addWidget(m_pLbCorner);
	m_pHLayCorner->addWidget(m_pCbCorner);
	m_pHLayCorner->addStretch();

	m_pHLayButtonRole->addWidget(m_pLbButtonRole);
	m_pHLayButtonRole->addWidget(m_pCbButtonRole);
	m_pHLayButtonRole->addStretch();

	m_pHLayHorizonOffset->addWidget(m_pLbHorizonOffset);
	m_pHLayHorizonOffset->addWidget(m_pSbHorizonOffset);
	m_pHLayHorizonOffset->addStretch();

	m_pHLayVerticalOffset->addWidget(m_pLbVerticalOffset);
	m_pHLayVerticalOffset->addWidget(m_pSbVerticalOffset);
	m_pHLayVerticalOffset->addStretch();

	m_pHLayMini->addWidget(m_pLbMini);
	m_pHLayMini->addWidget(m_pCbMini);
	m_pHLayMini->addStretch();

	m_pHLayRippleStyle->addWidget(m_pLbRippleStyle);
	m_pHLayRippleStyle->addWidget(m_pCbRippleStyle);
	m_pHLayRippleStyle->addStretch();

	m_pHLayUseThemeColors->addWidget(m_pLbUseThemeColors);
	m_pHLayUseThemeColors->addWidget(m_pCbUseThemeColors);
	m_pHLayUseThemeColors->addStretch();

	m_pHLayBackgroundColor->addWidget(m_pLbBackgroundColor);
	m_pHLayBackgroundColor->addWidget(m_pLeBackgroundColor);
	m_pHLayBackgroundColor->addWidget(m_pTbBackgroundColor);
	m_pHLayBackgroundColor->addStretch();

	m_pHLayForegroundColor->addWidget(m_pLbForegroundColor);
	m_pHLayForegroundColor->addWidget(m_pLeForegroundColor);
	m_pHLayForegroundColor->addWidget(m_pTbForegroundColor);
	m_pHLayForegroundColor->addStretch();

	m_pHLayDisabledBgColor->addWidget(m_pLbDisabledBgColor);
	m_pHLayDisabledBgColor->addWidget(m_pLeDisabledBgColor);
	m_pHLayDisabledBgColor->addWidget(m_pTbDisabledBgColor);
	m_pHLayDisabledBgColor->addStretch();

	m_pHLayDisabledFgColor->addWidget(m_pLbDisabledFgColor);
	m_pHLayDisabledFgColor->addWidget(m_pLeDisabledFgColor);
	m_pHLayDisabledFgColor->addWidget(m_pTbDisabledFgColor);
	m_pHLayDisabledFgColor->addStretch();

	m_pVLayCenter->addLayout(m_pHLayDisabled);
	m_pVLayCenter->addLayout(m_pHLayCorner);
	m_pVLayCenter->addLayout(m_pHLayButtonRole);
	m_pVLayCenter->addLayout(m_pHLayHorizonOffset);
	m_pVLayCenter->addLayout(m_pHLayVerticalOffset);
	m_pVLayCenter->addLayout(m_pHLayMini);
	m_pVLayCenter->addLayout(m_pHLayRippleStyle);
	m_pVLayCenter->addLayout(m_pHLayUseThemeColors);
	m_pVLayCenter->addLayout(m_pHLayBackgroundColor);
	m_pVLayCenter->addLayout(m_pHLayForegroundColor);
	m_pVLayCenter->addLayout(m_pHLayDisabledBgColor);
	m_pVLayCenter->addLayout(m_pHLayDisabledFgColor);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVFabSettingsEditor::initData() const {
	m_pCbCorner->addItem("TopLeftCorner");
	m_pCbCorner->addItem("TopRightCorner");
	m_pCbCorner->addItem("BottomLeftCorner");
	m_pCbCorner->addItem("BottomRightCorner");

	m_pCbButtonRole->addItem("Default");
	m_pCbButtonRole->addItem("Primary");
	m_pCbButtonRole->addItem("Secondary");

	m_pCbRippleStyle->addItem("CenteredRipple");
	m_pCbRippleStyle->addItem("PositionedRipple");
	m_pCbRippleStyle->addItem("NoRipple");

	m_pCbUseThemeColors->setChecked(true);
}

void CUVFabSettingsEditor::initConnection() {
	connect(m_pCbDisabled, &QCheckBox::toggled, this, &CUVFabSettingsEditor::updateWidget);
	connect(m_pCbButtonRole, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVFabSettingsEditor::updateWidget);
	connect(m_pCbCorner, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVFabSettingsEditor::updateWidget);
	connect(m_pSbHorizonOffset, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVFabSettingsEditor::updateWidget);
	connect(m_pSbVerticalOffset, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVFabSettingsEditor::updateWidget);
	connect(m_pCbMini, &QCheckBox::toggled, this, &CUVFabSettingsEditor::updateWidget);
	connect(m_pCbRippleStyle, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVFabSettingsEditor::updateWidget);
	connect(m_pCbUseThemeColors, &QCheckBox::toggled, this, &CUVFabSettingsEditor::updateWidget);
	connect(m_pTbBackgroundColor, &QToolButton::clicked, this, &CUVFabSettingsEditor::selectColor);
	connect(m_pTbForegroundColor, &QToolButton::clicked, this, &CUVFabSettingsEditor::selectColor);
	connect(m_pTbDisabledBgColor, &QToolButton::clicked, this, &CUVFabSettingsEditor::selectColor);
	connect(m_pTbDisabledFgColor, &QToolButton::clicked, this, &CUVFabSettingsEditor::selectColor);
}

void CUVFabSettingsEditor::setupForm() const {
	switch (m_pfab->role()) {
		case Material::Default: {
			m_pCbButtonRole->setCurrentIndex(0);
			break;
		}
		case Material::Primary: {
			m_pCbButtonRole->setCurrentIndex(1);
			break;
		}
		case Material::Secondary: {
			m_pCbButtonRole->setCurrentIndex(2);
			break;
		}
		default: break;
	}

	switch (m_pfab->corner()) {
		case Qt::TopLeftCorner: {
			m_pCbCorner->setCurrentIndex(0);
			break;
		}
		case Qt::TopRightCorner: {
			m_pCbCorner->setCurrentIndex(1);
			break;
		}
		case Qt::BottomLeftCorner: {
			m_pCbCorner->setCurrentIndex(2);
			break;
		}
		case Qt::BottomRightCorner: {
			m_pCbCorner->setCurrentIndex(3);
			break;
		}
		default: break;
	}

	switch (m_pfab->rippleStyle()) {
		case Material::CenteredRipple: {
			m_pCbRippleStyle->setCurrentIndex(0);
			break;
		}
		case Material::PositionedRipple: {
			m_pCbRippleStyle->setCurrentIndex(1);
			break;
		}
		case Material::NoRipple: {
			m_pCbRippleStyle->setCurrentIndex(2);
			break;
		}
		default: break;
	}

	m_pCbDisabled->setChecked(!m_pfab->isEnabled());
	m_pSbHorizonOffset->setValue(m_pfab->xOffset());
	m_pSbVerticalOffset->setValue(m_pfab->yOffset());
	m_pCbMini->setChecked(m_pfab->isMini());
	m_pCbUseThemeColors->setChecked(m_pfab->useThemeColors());
}

void CUVFabSettingsEditor::updateWidget() const {
	switch (m_pCbButtonRole->currentIndex()) {
		case 0:
			m_pfab->setRole(Material::Default);
			break;
		case 1:
			m_pfab->setRole(Material::Primary);
			break;
		case 2:
			m_pfab->setRole(Material::Secondary);
			break;
		default:
			break;
	}

	switch (m_pCbCorner->currentIndex()) {
		case 0:
			m_pfab->setCorner(Qt::TopLeftCorner);
			break;
		case 1:
			m_pfab->setCorner(Qt::TopRightCorner);
			break;
		case 2:
			m_pfab->setCorner(Qt::BottomLeftCorner);
			break;
		case 3:
			m_pfab->setCorner(Qt::BottomRightCorner);
			break;
		default:
			break;
	}

	switch (m_pCbRippleStyle->currentIndex()) {
		case 0:
			m_pfab->setRippleStyle(Material::CenteredRipple);
			break;
		case 1:
			m_pfab->setRippleStyle(Material::PositionedRipple);
			break;
		case 2:
			m_pfab->setRippleStyle(Material::NoRipple);
			break;
		default:
			break;
	}

	m_pfab->setDisabled(m_pCbDisabled->isChecked());
	m_pfab->setXOffset(m_pSbHorizonOffset->value());
	m_pfab->setYOffset(m_pSbVerticalOffset->value());
	m_pfab->setMini(m_pCbMini->isChecked());
	m_pfab->setUseThemeColors(m_pCbUseThemeColors->isChecked());
}

void CUVFabSettingsEditor::selectColor() const {
	if (QColorDialog dialog; dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if (const QString senderName = sender()->objectName(); "foregroundColorToolButton" == senderName) {
			m_pfab->setForegroundColor(color);
			m_pLeForegroundColor->setText(color.name(QColor::HexRgb));
		} else if ("backgroundColorToolButton" == senderName) {
			m_pfab->setBackgroundColor(color);
			m_pLeBackgroundColor->setText(color.name(QColor::HexRgb));
		} else if ("disabledFgColorToolButton" == senderName) {
			m_pfab->setDisabledForegroundColor(color);
			m_pLeDisabledFgColor->setText(color.name(QColor::HexRgb));
		} else if ("disabledBgColorToolButton" == senderName) {
			m_pfab->setDisabledBackgroundColor(color);
			m_pLeDisabledBgColor->setText(color.name(QColor::HexRgb));
		}
	}
	setupForm();
}
