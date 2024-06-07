#include "uviconbuttonsettingseditor.hpp"

#include <QColorDialog>
#include <uvshared/uvmaterialtheme.hpp>

CUVIconButtonSettingsEditor::CUVIconButtonSettingsEditor(QWidget* parent)
: QWidget(parent), m_pButton(new CUVMaterialIconButton(CUVMaterialTheme::icon("toggle", "star"))) {
	createCtrl();
	customLayout();
	setupForm();
	initConnection();
}

CUVIconButtonSettingsEditor::~CUVIconButtonSettingsEditor() = default;

void CUVIconButtonSettingsEditor::createCtrl() {
	m_pLbDisabled = new QLabel(tr("Disabled"), this);
	m_pLbDisabled->setFixedWidth(m_nLabelWidth);
	m_pCbDisabled = new QCheckBox(this);

	m_pLbSize = new QLabel(tr("Size"), this);
	m_pLbSize->setFixedWidth(m_nLabelWidth);
	m_pSbSize = new QSpinBox(this);

	m_pLbUseThemeColors = new QLabel(tr("Use theme colors"), this);
	m_pLbUseThemeColors->setFixedWidth(m_nLabelWidth);
	m_pCbUseThemeColors = new QCheckBox(this);

	m_pLbColor = new QLabel(tr("Color"), this);
	m_pLbColor->setFixedWidth(m_nLabelWidth);
	m_pLeColor = new QLineEdit(this);
	m_pTbColor = new QToolButton(this);
	m_pTbColor->setObjectName("colorToolButton");
	m_pTbColor->setText("...");

	m_pLbDisableedColor = new QLabel(tr("Disabled color"), this);
	m_pLbDisableedColor->setFixedWidth(m_nLabelWidth);
	m_pLeDisableedColor = new QLineEdit(this);
	m_pTbDisableedColor = new QToolButton(this);
	m_pTbDisableedColor->setObjectName("disabledColorToolButton");
	m_pTbDisableedColor->setText("...");

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayDisabled = new QHBoxLayout;
	m_pHLaySize = new QHBoxLayout;
	m_pHLayUseThemeColors = new QHBoxLayout;
	m_pHLayColor = new QHBoxLayout;
	m_pHLayDisableedColor = new QHBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVIconButtonSettingsEditor::customLayout() const {
	m_pHLayDisabled->addWidget(m_pLbDisabled);
	m_pHLayDisabled->addWidget(m_pCbDisabled);
	m_pHLayDisabled->addStretch();

	m_pHLaySize->addWidget(m_pLbSize);
	m_pHLaySize->addWidget(m_pSbSize);
	m_pHLaySize->addStretch();

	m_pHLayUseThemeColors->addWidget(m_pLbUseThemeColors);
	m_pHLayUseThemeColors->addWidget(m_pCbUseThemeColors);
	m_pHLayUseThemeColors->addStretch();

	m_pHLayColor->addWidget(m_pLbColor);
	m_pHLayColor->addWidget(m_pLeColor);
	m_pHLayColor->addWidget(m_pTbColor);
	m_pHLayColor->addStretch();

	m_pHLayDisableedColor->addWidget(m_pLbDisableedColor);
	m_pHLayDisableedColor->addWidget(m_pLeDisableedColor);
	m_pHLayDisableedColor->addWidget(m_pTbDisableedColor);
	m_pHLayDisableedColor->addStretch();

	m_pVLayBottom->addWidget(m_pButton);
	m_pVLayBottom->setAlignment(m_pButton, Qt::AlignHCenter);

	m_pVLayCenter->addLayout(m_pHLayDisabled);
	m_pVLayCenter->addLayout(m_pHLaySize);
	m_pVLayCenter->addLayout(m_pHLayUseThemeColors);
	m_pVLayCenter->addLayout(m_pHLayColor);
	m_pVLayCenter->addLayout(m_pHLayDisableedColor);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVIconButtonSettingsEditor::initConnection() {
	connect(m_pCbDisabled, &QCheckBox::toggled, this, &CUVIconButtonSettingsEditor::updateWidget);
	connect(m_pSbSize, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVIconButtonSettingsEditor::updateWidget);
	connect(m_pCbUseThemeColors, &QCheckBox::toggled, this, &CUVIconButtonSettingsEditor::updateWidget);
	connect(m_pTbColor, &QToolButton::clicked, this, &CUVIconButtonSettingsEditor::selectColor);
	connect(m_pTbDisableedColor, &QToolButton::clicked, this, &CUVIconButtonSettingsEditor::selectColor);
}

void CUVIconButtonSettingsEditor::setupForm() const {
	m_pCbDisabled->setChecked(!m_pButton->isEnabled());
	m_pCbUseThemeColors->setChecked(m_pButton->useThemeColors());
	m_pSbSize->setValue(m_pButton->iconSize().width());
}

void CUVIconButtonSettingsEditor::updateWidget() const {
	m_pButton->setDisabled(m_pCbDisabled->isChecked());
	m_pButton->setUseThemeColors(m_pCbUseThemeColors->isChecked());
	m_pButton->setIconSize({ m_pSbSize->value(), m_pSbSize->value() });
}

void CUVIconButtonSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if (const QString senderName = sender()->objectName(); "colorToolButton" == senderName) {
			m_pButton->setColor(color);
			m_pLeColor->setText(color.name(QColor::HexRgb));
		} else if ("disabledColorToolButton" == senderName) {
			m_pButton->setDisabledColor(color);
			m_pLeDisableedColor->setText(color.name(QColor::HexRgb));
		}
	}
	setupForm();
}
