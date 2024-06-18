#include "uvtoggleswitchsettingseditor.hpp"

#include <QColorDialog>
#include <QDebug>

CUVToggleSwitchSettingsEditor::CUVToggleSwitchSettingsEditor(QWidget* parent)
: QWidget(parent), m_pToggleSwitch(new CUVMaterialToggleSwitch(this)) {
	createCtrl();
	customLayout();
	setupForm();
	initConnection();
}

CUVToggleSwitchSettingsEditor::~CUVToggleSwitchSettingsEditor() = default;

void CUVToggleSwitchSettingsEditor::createCtrl() {
	m_pLbDisabled = new QLabel(tr("Disabled"), this);
	m_pLbDisabled->setFixedWidth(m_nLabelWidth);
	m_pCbDisabled = new QCheckBox(this);

	m_pLbChecked = new QLabel(tr("Checked"), this);
	m_pLbChecked->setFixedWidth(m_nLabelWidth);
	m_pCbChecked = new QCheckBox(this);

	m_pLbTextBold = new QLabel(tr("Text Bold"), this);
	m_pLbTextBold->setFixedWidth(m_nLabelWidth);
	m_pCbTextBold = new QCheckBox(this);

	m_pLbFontSize = new QLabel(tr("Font Size"), this);
	m_pLbFontSize->setFixedWidth(m_nLabelWidth);
	m_pSbFontSize = new QSpinBox(this);

	m_pLbOnText = new QLabel(tr("On Text"), this);
	m_pLbOnText->setFixedWidth(m_nLabelWidth);
	m_pLeOnText = new QLineEdit(this);

	m_pLbOffText = new QLabel(tr("Off Text"), this);
	m_pLbOffText->setFixedWidth(m_nLabelWidth);
	m_pLeOffText = new QLineEdit(this);

	m_pLbBackgroundOnColor = new QLabel(tr("Background On Color"), this);
	m_pLbBackgroundOnColor->setFixedWidth(m_nLabelWidth);
	m_pLeBackgroundOnColor = new QLineEdit(this);
	m_pTbBackgroundOnColor = new QToolButton(this);
	m_pTbBackgroundOnColor->setText("...");
	m_pTbBackgroundOnColor->setObjectName("BackgroundOnColorToolButton");

	m_pLbBackgroundOffColor = new QLabel(tr("Background Off Color"), this);
	m_pLbBackgroundOffColor->setFixedWidth(m_nLabelWidth);
	m_pLeBackgroundOffColor = new QLineEdit(this);
	m_pTbBackgroundOffColor = new QToolButton(this);
	m_pTbBackgroundOffColor->setText("...");
	m_pTbBackgroundOffColor->setObjectName("BackgroundOffColorToolButton");

	m_pLbTextOnColor = new QLabel(tr("Text On Color"), this);
	m_pLbTextOnColor->setFixedWidth(m_nLabelWidth);
	m_pLeTextOnColor = new QLineEdit(this);
	m_pTbTextOnColor = new QToolButton(this);
	m_pTbTextOnColor->setText("...");
	m_pTbTextOnColor->setObjectName("TextOnColorToolButton");

	m_pLbTextOffdColor = new QLabel(tr("Text Off Color"), this);
	m_pLbTextOffdColor->setFixedWidth(m_nLabelWidth);
	m_pLeTextOffdColor = new QLineEdit(this);
	m_pTbTextOffdColor = new QToolButton(this);
	m_pTbTextOffdColor->setText("...");
	m_pTbTextOffdColor->setObjectName("TextOffdColorToolButton");

	m_pLbcircleOffColor = new QLabel(tr("circle Off Color"), this);
	m_pLbcircleOffColor->setFixedWidth(m_nLabelWidth);
	m_pLecircleOffColor = new QLineEdit(this);
	m_pTbcircleOffColor = new QToolButton(this);
	m_pTbcircleOffColor->setText("...");
	m_pTbcircleOffColor->setObjectName("circleOffColorToolButton");

	m_pLbcircleOnColor = new QLabel(tr("circle On Color"), this);
	m_pLbcircleOnColor->setFixedWidth(m_nLabelWidth);
	m_pLecircleOnColor = new QLineEdit(this);
	m_pTbcircleOnColor = new QToolButton(this);
	m_pTbcircleOnColor->setText("...");
	m_pTbcircleOnColor->setObjectName("circleOnColorToolButton");

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayDisabled = new QHBoxLayout;
	m_pHLayChecked = new QHBoxLayout;
	m_pHLayTextBold = new QHBoxLayout;
	m_pHLayFontSize = new QHBoxLayout;
	m_pHLayOnText = new QHBoxLayout;
	m_pHLayOffText = new QHBoxLayout;
	m_pHLayBackgroundOnColor = new QHBoxLayout;
	m_pHLayBackgroundOffColor = new QHBoxLayout;
	m_pHLayTextOnColor = new QHBoxLayout;
	m_pHLayTextOffdColor = new QHBoxLayout;
	m_pHLaycircleOnColor = new QHBoxLayout;
	m_pHLaycircleOffColor = new QHBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVToggleSwitchSettingsEditor::customLayout() const {
	m_pHLayDisabled->addWidget(m_pLbDisabled);
	m_pHLayDisabled->addWidget(m_pCbDisabled);
	m_pHLayDisabled->addStretch();

	m_pHLayChecked->addWidget(m_pLbChecked);
	m_pHLayChecked->addWidget(m_pCbChecked);
	m_pHLayChecked->addStretch();

	m_pHLayTextBold->addWidget(m_pLbTextBold);
	m_pHLayTextBold->addWidget(m_pCbTextBold);
	m_pHLayTextBold->addStretch();

	m_pHLayFontSize->addWidget(m_pLbFontSize);
	m_pHLayFontSize->addWidget(m_pSbFontSize);
	m_pHLayFontSize->addStretch();

	m_pHLayOnText->addWidget(m_pLbOnText);
	m_pHLayOnText->addWidget(m_pLeOnText);
	m_pHLayOnText->addStretch();

	m_pHLayOffText->addWidget(m_pLbOffText);
	m_pHLayOffText->addWidget(m_pLeOffText);
	m_pHLayOffText->addStretch();

	m_pHLayBackgroundOnColor->addWidget(m_pLbBackgroundOnColor);
	m_pHLayBackgroundOnColor->addWidget(m_pLeBackgroundOnColor);
	m_pHLayBackgroundOnColor->addWidget(m_pTbBackgroundOnColor);
	m_pHLayBackgroundOnColor->addStretch();

	m_pHLayBackgroundOffColor->addWidget(m_pLbBackgroundOffColor);
	m_pHLayBackgroundOffColor->addWidget(m_pLeBackgroundOffColor);
	m_pHLayBackgroundOffColor->addWidget(m_pTbBackgroundOffColor);
	m_pHLayBackgroundOffColor->addStretch();

	m_pHLayTextOnColor->addWidget(m_pLbTextOnColor);
	m_pHLayTextOnColor->addWidget(m_pLeTextOnColor);
	m_pHLayTextOnColor->addWidget(m_pTbTextOnColor);
	m_pHLayTextOnColor->addStretch();

	m_pHLayTextOffdColor->addWidget(m_pLbTextOffdColor);
	m_pHLayTextOffdColor->addWidget(m_pLeTextOffdColor);
	m_pHLayTextOffdColor->addWidget(m_pTbTextOffdColor);
	m_pHLayTextOffdColor->addStretch();

	m_pHLaycircleOnColor->addWidget(m_pLbcircleOnColor);
	m_pHLaycircleOnColor->addWidget(m_pLecircleOnColor);
	m_pHLaycircleOnColor->addWidget(m_pTbcircleOnColor);
	m_pHLaycircleOnColor->addStretch();

	m_pHLaycircleOffColor->addWidget(m_pLbcircleOffColor);
	m_pHLaycircleOffColor->addWidget(m_pLecircleOffColor);
	m_pHLaycircleOffColor->addWidget(m_pTbcircleOffColor);
	m_pHLaycircleOffColor->addStretch();

	m_pVLayBottom->addWidget(m_pToggleSwitch);
	m_pVLayBottom->setAlignment(m_pToggleSwitch, Qt::AlignHCenter);

	m_pVLayCenter->addLayout(m_pHLayDisabled);
	m_pVLayCenter->addLayout(m_pHLayChecked);
	m_pVLayCenter->addLayout(m_pHLayTextBold);
	m_pVLayCenter->addLayout(m_pHLayFontSize);
	m_pVLayCenter->addLayout(m_pHLayOnText);
	m_pVLayCenter->addLayout(m_pHLayOffText);
	m_pVLayCenter->addLayout(m_pHLayBackgroundOnColor);
	m_pVLayCenter->addLayout(m_pHLayBackgroundOffColor);
	m_pVLayCenter->addLayout(m_pHLayTextOnColor);
	m_pVLayCenter->addLayout(m_pHLayTextOffdColor);
	m_pVLayCenter->addLayout(m_pHLaycircleOnColor);
	m_pVLayCenter->addLayout(m_pHLaycircleOffColor);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVToggleSwitchSettingsEditor::initConnection() {
	connect(m_pCbDisabled, &QCheckBox::toggled, this, &CUVToggleSwitchSettingsEditor::updateWidget);
	connect(m_pCbChecked, &QCheckBox::toggled, this, &CUVToggleSwitchSettingsEditor::updateWidget);
	connect(m_pCbTextBold, &QCheckBox::toggled, this, &CUVToggleSwitchSettingsEditor::updateWidget);
	connect(m_pSbFontSize, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVToggleSwitchSettingsEditor::updateWidget);
	connect(m_pLeOnText, &QLineEdit::textChanged, this, &CUVToggleSwitchSettingsEditor::updateWidget);
	connect(m_pLeOffText, &QLineEdit::textChanged, this, &CUVToggleSwitchSettingsEditor::updateWidget);
	connect(m_pTbBackgroundOnColor, &QToolButton::clicked, this, &CUVToggleSwitchSettingsEditor::selectColor);
	connect(m_pTbBackgroundOffColor, &QToolButton::clicked, this, &CUVToggleSwitchSettingsEditor::selectColor);
	connect(m_pTbTextOnColor, &QToolButton::clicked, this, &CUVToggleSwitchSettingsEditor::selectColor);
	connect(m_pTbTextOffdColor, &QToolButton::clicked, this, &CUVToggleSwitchSettingsEditor::selectColor);
	connect(m_pTbcircleOffColor, &QToolButton::clicked, this, &CUVToggleSwitchSettingsEditor::selectColor);
	connect(m_pTbcircleOnColor, &QToolButton::clicked, this, &CUVToggleSwitchSettingsEditor::selectColor);
	connect(m_pToggleSwitch, &CUVMaterialToggleSwitch::clicked, this, &CUVToggleSwitchSettingsEditor::setupForm);
}

void CUVToggleSwitchSettingsEditor::setupForm() const {
	m_pLeOnText->setText(m_pToggleSwitch->onText());
	m_pLeOffText->setText(m_pToggleSwitch->offText());

	m_pCbDisabled->setChecked(!m_pToggleSwitch->isEnabled());
	m_pCbChecked->setChecked(m_pToggleSwitch->isChecked());
	m_pCbTextBold->setChecked(m_pToggleSwitch->textBold());
	m_pSbFontSize->setValue(m_pToggleSwitch->fontSize());
}

void CUVToggleSwitchSettingsEditor::updateWidget() const {
	m_pToggleSwitch->setDisabled(m_pCbDisabled->isChecked());
	m_pToggleSwitch->setChecked(m_pCbChecked->isChecked());

	m_pToggleSwitch->setOnText(m_pLeOnText->text());
	m_pToggleSwitch->setOffText(m_pLeOffText->text());

	m_pToggleSwitch->setTextBold(m_pCbTextBold->isChecked());
	m_pToggleSwitch->setFontSize(m_pSbFontSize->value());
}

void CUVToggleSwitchSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if (const QString senderName = sender()->objectName(); "BackgroundOnColorToolButton" == senderName) {
			m_pToggleSwitch->setOnBackgroundColor(color);
			m_pLeBackgroundOnColor->setText(color.name(QColor::HexRgb));
		} else if ("BackgroundOffColorToolButton" == senderName) {
			m_pToggleSwitch->setOffBackgroundColor(color);
			m_pLeBackgroundOffColor->setText(color.name(QColor::HexRgb));
		} else if ("TextOnColorToolButton" == senderName) {
			m_pToggleSwitch->setOnTextColor(color);
			m_pLeTextOnColor->setText(color.name(QColor::HexRgb));
		} else if ("TextOffdColorToolButton" == senderName) {
			m_pToggleSwitch->setOffTextColor(color);
			m_pLeTextOffdColor->setText(color.name(QColor::HexRgb));
		} else if ("circleOffColorToolButton" == senderName) {
			m_pToggleSwitch->setOffCircleColor(color);
			m_pLecircleOffColor->setText(color.name(QColor::HexRgb));
		} else if ("circleOnColorToolButton" == senderName) {
			m_pToggleSwitch->setOnCircleColor(color);
			m_pLecircleOnColor->setText(color.name(QColor::HexRgb));
		}
	}

	setupForm();
}
