#include "uvflatbuttonsettingseditor.hpp"

#include <QColorDialog>

CUVFlatButtonSettingsEditor::CUVFlatButtonSettingsEditor(QWidget* parent)
: QWidget(parent), m_button(new CUVMaterialFlatButton("flat")) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVFlatButtonSettingsEditor::~CUVFlatButtonSettingsEditor() = default;

void CUVFlatButtonSettingsEditor::createCtrl() {
	m_pLbDisable = new QLabel(tr("Disable"), this);
	m_pLbDisable->setFixedWidth(m_nLabelWidth);
	m_pCbDisable = new QCheckBox(this);

	m_pLbCheckable = new QLabel(tr("Checkable"), this);
	m_pLbCheckable->setFixedWidth(m_nLabelWidth);
	m_pCbCheckable = new QCheckBox(this);

	m_pLbChecked = new QLabel(tr("Checked"), this);
	m_pLbChecked->setFixedWidth(m_nLabelWidth);
	m_pCbChecked = new QCheckBox(this);

	m_pLbShowHalo = new QLabel(tr("Show Halo"), this);
	m_pLbShowHalo->setFixedWidth(m_nLabelWidth);
	m_pCbShowHalo = new QCheckBox(this);

	m_pLbTransparent = new QLabel(tr("Transparent"), this);
	m_pLbTransparent->setFixedWidth(m_nLabelWidth);
	m_pCbTransparent = new QCheckBox(this);

	m_pLbIcon = new QLabel(tr("Icon"), this);
	m_pLbIcon->setFixedWidth(m_nLabelWidth);
	m_pCbIcon = new QCheckBox(this);

	m_pLbButtonRole = new QLabel(tr("Button Role"), this);
	m_pLbButtonRole->setFixedWidth(m_nLabelWidth);
	m_pCbButtonRole = new QComboBox(this);

	m_pLbRippleStyle = new QLabel(tr("Ripple Style"), this);
	m_pLbRippleStyle->setFixedWidth(m_nLabelWidth);
	m_pCbRippleStyle = new QComboBox(this);

	m_pLbHoverStyle = new QLabel(tr("Hover Style"), this);
	m_pLbHoverStyle->setFixedWidth(m_nLabelWidth);
	m_pCbHoverStyle = new QComboBox(this);

	m_pLbIconPlacement = new QLabel(tr("Icon Placement"), this);
	m_pLbIconPlacement->setFixedWidth(m_nLabelWidth);
	m_pCbIconPlacement = new QComboBox(this);

	m_pLbCornerRadius = new QLabel(tr("Corner Radius"), this);
	m_pLbCornerRadius->setFixedWidth(m_nLabelWidth);
	m_pSpCornerRadius = new QSpinBox(this);

	m_pLbTextAlignment = new QLabel(tr("Text Alignment"), this);
	m_pLbTextAlignment->setFixedWidth(m_nLabelWidth);
	m_pCbTextAlignment = new QComboBox(this);

	m_pLbOverlayOpacity = new QLabel(tr("Overlay Opacity"), this);
	m_pLbOverlayOpacity->setFixedWidth(m_nLabelWidth);
	m_pDSpOverlayOpacity = new QDoubleSpinBox(this);

	m_pLbIconSize = new QLabel(tr("Icon Size"), this);
	m_pLbIconSize->setFixedWidth(m_nLabelWidth);
	m_pSpIconSize = new QSpinBox(this);

	m_pLbFontSize = new QLabel(tr("Font Size"), this);
	m_pLbFontSize->setFixedWidth(m_nLabelWidth);
	m_pDSpFontSize = new QDoubleSpinBox(this);

	m_pLbButtonText = new QLabel(tr("Button Text"), this);
	m_pLbButtonText->setFixedWidth(m_nLabelWidth);
	m_pLeButtonText = new QLineEdit(this);

	m_pLbUseThemeColors = new QLabel(tr("Use Theme Colors"), this);
	m_pLbUseThemeColors->setFixedWidth(m_nLabelWidth);
	m_pCbUseThemeColors = new QCheckBox(this);

	m_pLbBackgroundColor = new QLabel(tr("Background Color"), this);
	m_pLbBackgroundColor->setFixedWidth(m_nLabelWidth);
	m_pLeBackgroundColor = new QLineEdit(this);
	m_pTbBackgroundColor = new QToolButton(this);
	m_pTbBackgroundColor->setObjectName("backgroundColorToolButton");

	m_pLbForegroundColor = new QLabel(tr("Foreground Color"), this);
	m_pLbForegroundColor->setFixedWidth(m_nLabelWidth);
	m_pLeForegroundColor = new QLineEdit(this);
	m_pTbForegroundColor = new QToolButton(this);
	m_pTbForegroundColor->setObjectName("foregroundColorToolButton");

	m_pLbOverlayColor = new QLabel(tr("Overlay Color"), this);
	m_pLbOverlayColor->setFixedWidth(m_nLabelWidth);
	m_pLeOverlayColor = new QLineEdit(this);
	m_pTbOverlayColor = new QToolButton(this);
	m_pTbOverlayColor->setObjectName("overlayColorToolButton");

	m_pLbDisabledBgColor = new QLabel(tr("Disabled Bg Color"), this);
	m_pLbDisabledBgColor->setFixedWidth(m_nLabelWidth);
	m_pLeDisabledBgColor = new QLineEdit(this);
	m_pTbDisabledBgColor = new QToolButton(this);
	m_pTbDisabledBgColor->setObjectName("disabledBgColorToolButton");

	m_pLbDisableFgColor = new QLabel(tr("Disabled Fg Color"), this);
	m_pLbDisableFgColor->setFixedWidth(m_nLabelWidth);
	m_pLeDisableFgColor = new QLineEdit(this);
	m_pTbDisableFgColor = new QToolButton(this);
	m_pTbDisableFgColor->setObjectName("disabledFgColorToolButton");

	m_pBtnApplyDefaultPreset = new QPushButton(this);
	m_pBtnApplyDefaultPreset->setText(tr("Apply Default Preset"));
	m_pBtnApplyCheckablePreset = new QPushButton(this);
	m_pBtnApplyCheckablePreset->setText(tr("Apply Checkable Preset"));

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");

	m_button->setFixedWidth(300);

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayDisabled = new QHBoxLayout;
	m_pHLayCheckable = new QHBoxLayout;
	m_pHLayChecked = new QHBoxLayout;
	m_pHLayShowHalo = new QHBoxLayout;
	m_pHLayTransparent = new QHBoxLayout;
	m_pHLayIcon = new QHBoxLayout;

	m_pHLayButtonRole = new QHBoxLayout;
	m_pHLayRippleStyle = new QHBoxLayout;
	m_pHLayHoverStyle = new QHBoxLayout;
	m_pHLayIconPlacement = new QHBoxLayout;
	m_pHLayCornerRadius = new QHBoxLayout;
	m_pHLayTextAlignment = new QHBoxLayout;
	m_pHLayOverlayOpacity = new QHBoxLayout;
	m_pHLayIconSize = new QHBoxLayout;
	m_pHLayFontSize = new QHBoxLayout;
	m_pHLayButtonText = new QHBoxLayout;

	m_pHLayUseThemeColors = new QHBoxLayout;
	m_pHLayBackgroundColor = new QHBoxLayout;
	m_pHLayForegroundColor = new QHBoxLayout;
	m_pHLayOverlayColor = new QHBoxLayout;
	m_pHLayDisabledBgColor = new QHBoxLayout;
	m_pHLayDisableFgColor = new QHBoxLayout;

	m_pVLayFirst = new QVBoxLayout;
	m_pVLaySecond = new QVBoxLayout;
	m_pVLayThird = new QVBoxLayout;

	m_pHLayFirst = new QHBoxLayout;
	m_pHLayButton = new QHBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVFlatButtonSettingsEditor::customLayout() const {
	m_pHLayDisabled->addWidget(m_pLbDisable);
	m_pHLayDisabled->addWidget(m_pCbDisable);

	m_pHLayCheckable->addWidget(m_pLbCheckable);
	m_pHLayCheckable->addWidget(m_pCbCheckable);

	m_pHLayChecked->addWidget(m_pLbChecked);
	m_pHLayChecked->addWidget(m_pCbChecked);

	m_pHLayShowHalo->addWidget(m_pLbShowHalo);
	m_pHLayShowHalo->addWidget(m_pCbShowHalo);

	m_pHLayTransparent->addWidget(m_pLbTransparent);
	m_pHLayTransparent->addWidget(m_pCbTransparent);

	m_pHLayIcon->addWidget(m_pLbIcon);
	m_pHLayIcon->addWidget(m_pCbIcon);

	m_pVLayFirst->addLayout(m_pHLayDisabled);
	m_pVLayFirst->addLayout(m_pHLayCheckable);
	m_pVLayFirst->addLayout(m_pHLayChecked);
	m_pVLayFirst->addLayout(m_pHLayShowHalo);
	m_pVLayFirst->addLayout(m_pHLayTransparent);
	m_pVLayFirst->addLayout(m_pHLayIcon);
	m_pVLayFirst->setAlignment(Qt::AlignTop);

	m_pHLayButtonRole->addWidget(m_pLbButtonRole);
	m_pHLayButtonRole->addWidget(m_pCbButtonRole);

	m_pHLayRippleStyle->addWidget(m_pLbRippleStyle);
	m_pHLayRippleStyle->addWidget(m_pCbRippleStyle);

	m_pHLayHoverStyle->addWidget(m_pLbHoverStyle);
	m_pHLayHoverStyle->addWidget(m_pCbHoverStyle);

	m_pHLayIconPlacement->addWidget(m_pLbIconPlacement);
	m_pHLayIconPlacement->addWidget(m_pCbIconPlacement);

	m_pHLayCornerRadius->addWidget(m_pLbCornerRadius);
	m_pHLayCornerRadius->addWidget(m_pSpCornerRadius);

	m_pHLayTextAlignment->addWidget(m_pLbTextAlignment);
	m_pHLayTextAlignment->addWidget(m_pCbTextAlignment);

	m_pHLayOverlayOpacity->addWidget(m_pLbOverlayOpacity);
	m_pHLayOverlayOpacity->addWidget(m_pDSpOverlayOpacity);

	m_pHLayIconSize->addWidget(m_pLbIconSize);
	m_pHLayIconSize->addWidget(m_pSpIconSize);

	m_pHLayFontSize->addWidget(m_pLbFontSize);
	m_pHLayFontSize->addWidget(m_pDSpFontSize);

	m_pHLayButtonText->addWidget(m_pLbButtonText);
	m_pHLayButtonText->addWidget(m_pLeButtonText);

	m_pVLaySecond->addLayout(m_pHLayButtonRole);
	m_pVLaySecond->addLayout(m_pHLayRippleStyle);
	m_pVLaySecond->addLayout(m_pHLayHoverStyle);
	m_pVLaySecond->addLayout(m_pHLayIconPlacement);
	m_pVLaySecond->addLayout(m_pHLayCornerRadius);
	m_pVLaySecond->addLayout(m_pHLayTextAlignment);
	m_pVLaySecond->addLayout(m_pHLayOverlayOpacity);
	m_pVLaySecond->addLayout(m_pHLayIconSize);
	m_pVLaySecond->addLayout(m_pHLayFontSize);
	m_pVLaySecond->addLayout(m_pHLayButtonText);
	m_pVLaySecond->setAlignment(Qt::AlignTop);

	m_pHLayUseThemeColors->addWidget(m_pLbUseThemeColors);
	m_pHLayUseThemeColors->addWidget(m_pCbUseThemeColors);

	m_pHLayBackgroundColor->addWidget(m_pLbBackgroundColor);
	m_pHLayBackgroundColor->addWidget(m_pLeBackgroundColor);
	m_pHLayBackgroundColor->addWidget(m_pTbBackgroundColor);

	m_pHLayForegroundColor->addWidget(m_pLbForegroundColor);
	m_pHLayForegroundColor->addWidget(m_pLeForegroundColor);
	m_pHLayForegroundColor->addWidget(m_pTbForegroundColor);

	m_pHLayOverlayColor->addWidget(m_pLbOverlayColor);
	m_pHLayOverlayColor->addWidget(m_pLeOverlayColor);
	m_pHLayOverlayColor->addWidget(m_pTbOverlayColor);

	m_pHLayDisabledBgColor->addWidget(m_pLbDisabledBgColor);
	m_pHLayDisabledBgColor->addWidget(m_pLeDisabledBgColor);
	m_pHLayDisabledBgColor->addWidget(m_pTbDisabledBgColor);

	m_pHLayDisableFgColor->addWidget(m_pLbDisableFgColor);
	m_pHLayDisableFgColor->addWidget(m_pLeDisableFgColor);
	m_pHLayDisableFgColor->addWidget(m_pTbDisableFgColor);

	m_pVLayThird->addLayout(m_pHLayUseThemeColors);
	m_pVLayThird->addLayout(m_pHLayBackgroundColor);
	m_pVLayThird->addLayout(m_pHLayForegroundColor);
	m_pVLayThird->addLayout(m_pHLayOverlayColor);
	m_pVLayThird->addLayout(m_pHLayDisabledBgColor);
	m_pVLayThird->addLayout(m_pHLayDisableFgColor);
	m_pVLayThird->setAlignment(Qt::AlignTop);

	m_pHLayFirst->addLayout(m_pVLayFirst);
	m_pHLayFirst->addLayout(m_pVLaySecond);
	m_pHLayFirst->addLayout(m_pVLayThird);

	m_pHLayButton->addWidget(m_pBtnApplyDefaultPreset);
	m_pHLayButton->addWidget(m_pBtnApplyCheckablePreset);
	m_pHLayButton->addStretch();

	m_pVLayBottom->addWidget(m_button);
	m_pVLayBottom->setAlignment(m_button, Qt::AlignHCenter);

	m_pVLayCenter->addLayout(m_pHLayFirst);
	m_pVLayCenter->addLayout(m_pHLayButton);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVFlatButtonSettingsEditor::initData() const {
	m_pCbShowHalo->setChecked(true);
	m_pCbTransparent->setChecked(true);

	m_pCbButtonRole->addItem("Default");
	m_pCbButtonRole->addItem("Primary");
	m_pCbButtonRole->addItem("Secondary");

	m_pCbRippleStyle->addItem("CenteredRipple");
	m_pCbRippleStyle->addItem("PositionedRipple");
	m_pCbRippleStyle->addItem("NoRipple");

	m_pCbHoverStyle->addItem("NoOverlay");
	m_pCbHoverStyle->addItem("TintedOverlay");
	m_pCbHoverStyle->addItem("GrayOverlay");

	m_pCbIconPlacement->addItem("Left");
	m_pCbIconPlacement->addItem("Right");

	m_pCbTextAlignment->addItem("Left");
	m_pCbTextAlignment->addItem("Center");
}

void CUVFlatButtonSettingsEditor::initConnection() {
	connect(m_pCbDisable, &QCheckBox::toggled, this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pCbCheckable, &QCheckBox::toggled, this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pCbChecked, &QCheckBox::toggled, this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pCbShowHalo, &QCheckBox::toggled, this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pCbIcon, &QCheckBox::toggled, this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pCbTransparent, &QCheckBox::toggled, this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pCbButtonRole, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pCbRippleStyle, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pCbHoverStyle, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pCbIconPlacement, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pCbTextAlignment, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pSpCornerRadius, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pDSpOverlayOpacity, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pSpIconSize, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pDSpFontSize, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pLeButtonText, &QLineEdit::textChanged, this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pCbUseThemeColors, &QCheckBox::toggled, this, &CUVFlatButtonSettingsEditor::updateWidget);
	connect(m_pTbForegroundColor, &QToolButton::clicked, this, &CUVFlatButtonSettingsEditor::selectColor);
	connect(m_pTbBackgroundColor, &QToolButton::clicked, this, &CUVFlatButtonSettingsEditor::selectColor);
	connect(m_pTbOverlayColor, &QToolButton::clicked, this, &CUVFlatButtonSettingsEditor::selectColor);
	connect(m_pTbDisabledBgColor, &QToolButton::clicked, this, &CUVFlatButtonSettingsEditor::selectColor);
	connect(m_pTbDisableFgColor, &QToolButton::clicked, this, &CUVFlatButtonSettingsEditor::selectColor);

	connect(m_button, &CUVMaterialFlatButton::clicked, m_pCbChecked, &QCheckBox::setChecked);
	m_pCbButtonRole->setCurrentIndex(1);
}

void CUVFlatButtonSettingsEditor::setupForm() const {
	switch (m_button->role()) {
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

	switch (m_button->overlayStyle()) {
		case Material::NoOverlay: {
			m_pCbHoverStyle->setCurrentIndex(0);
			break;
		}
		case Material::TintedOverlay: {
			m_pCbHoverStyle->setCurrentIndex(1);
			break;
		}
		case Material::GrayOverlay: {
			m_pCbHoverStyle->setCurrentIndex(2);
			break;
		}
		default: break;
	}

	switch (m_button->rippleStyle()) {
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

	switch (m_button->iconPlacement()) {
		case Material::LeftIcon: {
			m_pCbIconPlacement->setCurrentIndex(0);
			break;
		}
		case Material::RightIcon: {
			m_pCbIconPlacement->setCurrentIndex(1);
			break;
		}
		default: break;
	}

	switch (m_pCbTextAlignment->currentIndex()) {
		case Qt::AlignLeft: {
			m_pCbTextAlignment->setCurrentIndex(0);
			break;
		}
		default: m_pCbTextAlignment->setCurrentIndex(1);
	}

	m_pCbChecked->setEnabled(m_button->isCheckable());

	m_pCbDisable->setChecked(!m_button->isEnabled());
	m_pCbCheckable->setChecked(m_button->isCheckable());
	m_pCbChecked->setChecked(m_button->isChecked());
	m_pCbShowHalo->setChecked(m_button->isHaloVisible());
	m_pCbIcon->setChecked(!m_button->icon().isNull());
	m_pCbUseThemeColors->setChecked(m_button->useThemeColors());
	m_pCbTransparent->setChecked(Qt::TransparentMode == m_button->backgroundMode());
	m_pSpCornerRadius->setValue(static_cast<int>(m_button->cornerRadius()));
	m_pDSpOverlayOpacity->setValue(m_button->baseOpacity());
	m_pSpIconSize->setValue(m_button->iconSize().width());
	m_pDSpFontSize->setValue(m_button->fontSize());
	m_pLeButtonText->setText(m_button->text());
}

void CUVFlatButtonSettingsEditor::updateWidget() const {
	switch (m_pCbButtonRole->currentIndex()) {
		case 0:
			m_button->setRole(Material::Default);
			break;
		case 1:
			m_button->setRole(Material::Primary);
			break;
		case 2:
			m_button->setRole(Material::Secondary);
			break;
		default:
			break;
	}

	switch (m_pCbHoverStyle->currentIndex()) {
		case 0:
			m_button->setOverlayStyle(Material::NoOverlay);
			break;
		case 1:
			m_button->setOverlayStyle(Material::TintedOverlay);
			break;
		case 2:
			m_button->setOverlayStyle(Material::GrayOverlay);
			break;
		default:
			break;
	}

	switch (m_pCbRippleStyle->currentIndex()) {
		case 0:
			m_button->setRippleStyle(Material::CenteredRipple);
			break;
		case 1:
			m_button->setRippleStyle(Material::PositionedRipple);
			break;
		case 2:
			m_button->setRippleStyle(Material::NoRipple);
			break;
		default:
			break;
	}

	switch (m_pCbIconPlacement->currentIndex()) {
		case 0:
			m_button->setIconPlacement(Material::LeftIcon);
			break;
		case 1:
			m_button->setIconPlacement(Material::RightIcon);
			break;
		default:
			break;
	}

	switch (m_pCbTextAlignment->currentIndex()) {
		case 0:
			m_button->setTextAlignment(Qt::AlignLeft);
			break;
		case 1:
		default:
			m_button->setTextAlignment(Qt::AlignHCenter);
			break;
	}

	m_button->setDisabled(m_pCbDisable->isChecked());
	m_button->setCheckable(m_pCbCheckable->isChecked());
	m_button->setChecked(m_pCbChecked->isChecked());
	m_button->setHaloVisible(m_pCbShowHalo->isChecked());
	m_button->setIcon(m_pCbIcon->isChecked() ? CUVMaterialTheme::icon("toggle", "star") : QIcon());
	m_button->setUseThemeColors(m_pCbUseThemeColors->isChecked());
	m_button->setBackgroundMode(m_pCbTransparent->isChecked() ? Qt::TransparentMode : Qt::OpaqueMode);
	m_button->setCornerRadius(m_pSpCornerRadius->value());
	m_button->setBaseOpacity(m_pDSpOverlayOpacity->value());
	m_button->setIconSize(QSize(m_pSpIconSize->value(), m_pSpIconSize->value()));
	m_button->setFontSize(m_pDSpFontSize->value());
	m_button->setText(m_pLeButtonText->text());

	m_pCbChecked->setEnabled(m_button->isCheckable());
}

void CUVFlatButtonSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if (const QString senderName = sender()->objectName(); "foregroundColorToolButton" == senderName) {
			m_button->setForegroundColor(color);
			m_pLeForegroundColor->setText(color.name(QColor::HexRgb));
		} else if ("backgroundColorToolButton" == senderName) {
			m_button->setBackgroundColor(color);
			m_pLeBackgroundColor->setText(color.name(QColor::HexRgb));
		} else if ("overlayColorToolButton" == senderName) {
			m_button->setOverlayColor(color);
			m_pLeOverlayColor->setText(color.name(QColor::HexRgb));
		} else if ("disabledFgColorToolButton" == senderName) {
			m_button->setDisabledForegroundColor(color);
			m_pLeDisableFgColor->setText(color.name(QColor::HexRgb));
		} else if ("disabledBgColorToolButton" == senderName) {
			m_button->setDisabledBackgroundColor(color);
			m_pLeDisabledBgColor->setText(color.name(QColor::HexRgb));
		}
	}
	setupForm();
}

void CUVFlatButtonSettingsEditor::applyDefaultPreset() const {
	m_pCbButtonRole->setCurrentIndex(0);
	m_pCbRippleStyle->setCurrentIndex(1);
	m_pCbIconPlacement->setCurrentIndex(0);
	m_pCbHoverStyle->setCurrentIndex(2);
	m_pCbTextAlignment->setCurrentIndex(1);
	m_pCbTransparent->setChecked(true);
	m_pSpCornerRadius->setValue(3);
	m_pDSpOverlayOpacity->setValue(0.13);
	m_pDSpFontSize->setValue(10);
	m_pCbUseThemeColors->setChecked(true);
	m_pCbShowHalo->setChecked(true);
	m_pCbCheckable->setChecked(false);
	m_pCbDisable->setChecked(false);
	updateWidget();
	m_button->applyPreset(Material::FlatPreset);
}

void CUVFlatButtonSettingsEditor::applyCheckablePreset() const {
	m_pCbButtonRole->setCurrentIndex(0);
	m_pCbRippleStyle->setCurrentIndex(1);
	m_pCbIconPlacement->setCurrentIndex(0);
	m_pCbHoverStyle->setCurrentIndex(2);
	m_pCbTextAlignment->setCurrentIndex(1);
	m_pCbTransparent->setChecked(true);
	m_pSpCornerRadius->setValue(3);
	m_pDSpOverlayOpacity->setValue(0.13);
	m_pDSpFontSize->setValue(10);
	m_pCbUseThemeColors->setChecked(true);
	m_pCbShowHalo->setChecked(true);
	m_pCbCheckable->setChecked(true);
	m_pCbDisable->setChecked(false);
	updateWidget();
	m_button->applyPreset(Material::CheckablePreset);
}
