#include "uvtogglesettingseditor.hpp"

#include <QColorDialog>

CUVToggleSettingsEditor::CUVToggleSettingsEditor(QWidget* parent): QWidget(parent), m_pToggle(new CUVMaterialToggle(this)) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVToggleSettingsEditor::~CUVToggleSettingsEditor() = default;

void CUVToggleSettingsEditor::createCtrl() {
	m_pLbDisabled = new QLabel(tr("Disabled"), this);
	m_pLbDisabled->setFixedWidth(m_nLabelWidth);
	m_pCbDisabled = new QCheckBox(this);

	m_pLbChecked = new QLabel(tr("Checked"), this);
	m_pLbChecked->setFixedWidth(m_nLabelWidth);
	m_pCbChecked = new QCheckBox(this);

	m_pLbOrientation = new QLabel(tr("Orientation"), this);
	m_pLbOrientation->setFixedWidth(m_nLabelWidth);
	m_pCbOrientation = new QComboBox(this);

	m_pLbUseThemeColors = new QLabel(tr("Use Theme Colors"), this);
	m_pLbUseThemeColors->setFixedWidth(m_nLabelWidth);
	m_pCbUseThemeColors = new QCheckBox(this);

	m_pLbActiceColor = new QLabel(tr("Active Color"), this);
	m_pLbActiceColor->setFixedWidth(m_nLabelWidth);
	m_pLeActiveColor = new QLineEdit(this);
	m_pTbActiveColor = new QToolButton(this);
	m_pTbActiveColor->setText("...");
	m_pTbActiveColor->setObjectName("activeColorToolButton");

	m_pLbInactiveColor = new QLabel(tr("Inactive Color"), this);
	m_pLbInactiveColor->setFixedWidth(m_nLabelWidth);
	m_pLeInactiveColor = new QLineEdit(this);
	m_pTbInactiveColor = new QToolButton(this);
	m_pTbInactiveColor->setText("...");
	m_pTbInactiveColor->setObjectName("inactiveColorToolButton");

	m_pLbDisabledColor = new QLabel(tr("Disabled Color"), this);
	m_pLbDisabledColor->setFixedWidth(m_nLabelWidth);
	m_pLeDisabledColor = new QLineEdit(this);
	m_pTbDisabledColor = new QToolButton(this);
	m_pTbDisabledColor->setText("...");
	m_pTbDisabledColor->setObjectName("disabledColorToolButton");

	m_pLbTrackColor = new QLabel(tr("Track Color"), this);
	m_pLbTrackColor->setFixedWidth(m_nLabelWidth);
	m_pLeTrackColor = new QLineEdit(this);
	m_pTbTrackColor = new QToolButton(this);
	m_pTbTrackColor->setText("...");
	m_pTbTrackColor->setObjectName("trackColorToolButton");

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayDisabled = new QHBoxLayout;
	m_pHLayChecked = new QHBoxLayout;
	m_pHLayOrientation = new QHBoxLayout;
	m_pHLayUseThemeColors = new QHBoxLayout;
	m_pHLayActiveColor = new QHBoxLayout;
	m_pHLayInactiveColor = new QHBoxLayout;
	m_pHLayDisabledColor = new QHBoxLayout;
	m_pHLayTrackColor = new QHBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVToggleSettingsEditor::customLayout() const {
	m_pHLayDisabled->addWidget(m_pLbDisabled);
	m_pHLayDisabled->addWidget(m_pCbDisabled);
	m_pHLayDisabled->addStretch();

	m_pHLayChecked->addWidget(m_pLbChecked);
	m_pHLayChecked->addWidget(m_pCbChecked);
	m_pHLayChecked->addStretch();

	m_pHLayOrientation->addWidget(m_pLbOrientation);
	m_pHLayOrientation->addWidget(m_pCbOrientation);
	m_pHLayOrientation->addStretch();

	m_pHLayUseThemeColors->addWidget(m_pLbUseThemeColors);
	m_pHLayUseThemeColors->addWidget(m_pCbUseThemeColors);
	m_pHLayUseThemeColors->addStretch();

	m_pHLayActiveColor->addWidget(m_pLbActiceColor);
	m_pHLayActiveColor->addWidget(m_pLeActiveColor);
	m_pHLayActiveColor->addWidget(m_pTbActiveColor);
	m_pHLayActiveColor->addStretch();

	m_pHLayInactiveColor->addWidget(m_pLbInactiveColor);
	m_pHLayInactiveColor->addWidget(m_pLeInactiveColor);
	m_pHLayInactiveColor->addWidget(m_pTbInactiveColor);
	m_pHLayInactiveColor->addStretch();

	m_pHLayDisabledColor->addWidget(m_pLbDisabledColor);
	m_pHLayDisabledColor->addWidget(m_pLeDisabledColor);
	m_pHLayDisabledColor->addWidget(m_pTbDisabledColor);
	m_pHLayDisabledColor->addStretch();

	m_pHLayTrackColor->addWidget(m_pLbTrackColor);
	m_pHLayTrackColor->addWidget(m_pLeTrackColor);
	m_pHLayTrackColor->addWidget(m_pTbTrackColor);
	m_pHLayTrackColor->addStretch();

	m_pVLayBottom->addWidget(m_pToggle);
	m_pVLayBottom->setAlignment(m_pToggle, Qt::AlignHCenter);

	m_pVLayCenter->addLayout(m_pHLayDisabled);
	m_pVLayCenter->addLayout(m_pHLayChecked);
	m_pVLayCenter->addLayout(m_pHLayOrientation);
	m_pVLayCenter->addLayout(m_pHLayUseThemeColors);
	m_pVLayCenter->addLayout(m_pHLayActiveColor);
	m_pVLayCenter->addLayout(m_pHLayInactiveColor);
	m_pVLayCenter->addLayout(m_pHLayDisabledColor);
	m_pVLayCenter->addLayout(m_pHLayTrackColor);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVToggleSettingsEditor::initData() const {
	m_pCbOrientation->addItem("Horizontal");
	m_pCbOrientation->addItem("Vertical");
}

void CUVToggleSettingsEditor::initConnection() {
	connect(m_pCbDisabled, &QCheckBox::toggled, this, &CUVToggleSettingsEditor::updateWidget);
	connect(m_pCbChecked, &QCheckBox::toggled, this, &CUVToggleSettingsEditor::updateWidget);
	connect(m_pCbOrientation, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVToggleSettingsEditor::updateWidget);
	connect(m_pCbUseThemeColors, &QCheckBox::toggled, this, &CUVToggleSettingsEditor::updateWidget);
	connect(m_pTbActiveColor, &QToolButton::clicked, this, &CUVToggleSettingsEditor::selectColor);
	connect(m_pTbInactiveColor, &QToolButton::clicked, this, &CUVToggleSettingsEditor::selectColor);
	connect(m_pTbDisabledColor, &QToolButton::clicked, this, &CUVToggleSettingsEditor::selectColor);
	connect(m_pTbTrackColor, &QToolButton::clicked, this, &CUVToggleSettingsEditor::selectColor);
	connect(m_pToggle, &CUVMaterialToggle::toggled, this, &CUVToggleSettingsEditor::setupForm);
}

void CUVToggleSettingsEditor::setupForm() const {
	switch (m_pToggle->orientation()) {
		case Qt::Horizontal: {
			m_pCbOrientation->setCurrentIndex(0);
			break;
		}
		case Qt::Vertical: {
			m_pCbOrientation->setCurrentIndex(1);
			break;
		}
		default: break;
	}

	m_pCbDisabled->setChecked(!m_pToggle->isEnabled());
	m_pCbChecked->setChecked(m_pToggle->isChecked());
	m_pCbUseThemeColors->setChecked(m_pToggle->useThemeColors());
}

void CUVToggleSettingsEditor::updateWidget() const {
	switch (m_pCbOrientation->currentIndex()) {
		case 0: {
			m_pToggle->setOrientation(Qt::Horizontal);
			break;
		}
		case 1: {
			m_pToggle->setOrientation(Qt::Vertical);
			break;
		}
		default: break;
	}

	m_pToggle->setDisabled(m_pCbDisabled->isChecked());
	m_pToggle->setChecked(m_pCbChecked->isChecked());
	m_pToggle->setUseThemeColors(m_pCbUseThemeColors->isChecked());
}

void CUVToggleSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if (const QString senderName = sender()->objectName(); "disabledColorToolButton" == senderName) {
			m_pToggle->setDisabledColor(color);
			m_pLeDisabledColor->setText(color.name(QColor::HexRgb));
		} else if ("activeColorToolButton" == senderName) {
			m_pToggle->setActiveColor(color);
			m_pLeActiveColor->setText(color.name(QColor::HexRgb));
		} else if ("inactiveColorToolButton" == senderName) {
			m_pToggle->setInactiveColor(color);
			m_pLeInactiveColor->setText(color.name(QColor::HexRgb));
		} else if ("trackColorToolButton" == senderName) {
			m_pToggle->setTrackColor(color);
			m_pLeTrackColor->setText(color.name(QColor::HexRgb));
		}
	}

	setupForm();
}
