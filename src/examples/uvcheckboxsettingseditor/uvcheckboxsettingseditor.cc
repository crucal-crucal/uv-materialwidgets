#include "uvcheckboxsettingseditor.hpp"

#include <QColorDialog>

CUVCheckBoxSettingsEditor::CUVCheckBoxSettingsEditor(QWidget* parent): QWidget(parent), m_pCheckBox(new CUVMaterialCheckBox) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVCheckBoxSettingsEditor::~CUVCheckBoxSettingsEditor() = default;

void CUVCheckBoxSettingsEditor::createCtrl() {
	m_pLbDisable = new QLabel(tr("Disable"), this);
	m_pLbDisable->setFixedWidth(m_nLabelWidth);
	m_pCbDisable = new QCheckBox(this);

	m_pLbLabelPositing = new QLabel(tr("Label position"), this);
	m_pLbLabelPositing->setFixedWidth(m_nLabelWidth);
	m_pCbLabelPositing = new QComboBox(this);

	m_pLbLabelText = new QLabel(tr("Label text"), this);
	m_pLbLabelText->setFixedWidth(m_nLabelWidth);
	m_pLeLabelText = new QLineEdit(this);

	m_pLbChecked = new QLabel(tr("Checked"), this);
	m_pLbChecked->setFixedWidth(m_nLabelWidth);
	m_pCbChecked = new QCheckBox(this);

	m_pLbUseThemeColors = new QLabel(tr("Use theme colors"), this);
	m_pLbUseThemeColors->setFixedWidth(m_nLabelWidth);
	m_pCbUseThemeColors = new QCheckBox(this);

	m_pLbCheckedColor = new QLabel(tr("Checked color"), this);
	m_pLbCheckedColor->setFixedWidth(m_nLabelWidth);
	m_pLeCheckedColor = new QLineEdit(this);
	m_pTbCheckedColor = new QToolButton(this);
	m_pTbCheckedColor->setObjectName("checkedColorToolButton");
	m_pTbCheckedColor->setText("...");

	m_pLbUnCheckedColor = new QLabel(tr("Unchecked color"), this);
	m_pLbUnCheckedColor->setFixedWidth(m_nLabelWidth);
	m_pLeUnCheckedColor = new QLineEdit(this);
	m_pTbUnCheckedColor = new QToolButton(this);
	m_pTbUnCheckedColor->setObjectName("uncheckedColorToolButton");
	m_pTbUnCheckedColor->setText("...");

	m_pLbTextColor = new QLabel(tr("Text color"), this);
	m_pLbTextColor->setFixedWidth(m_nLabelWidth);
	m_pLeTextColor = new QLineEdit(this);
	m_pTbTextColor = new QToolButton(this);
	m_pTbTextColor->setObjectName("textColorToolButton");
	m_pTbTextColor->setText("...");

	m_pLbDisabledColor = new QLabel(tr("Disabled color"), this);
	m_pLbDisabledColor->setFixedWidth(m_nLabelWidth);
	m_pLeDisabledColor = new QLineEdit(this);
	m_pTbDisabledColor = new QToolButton(this);
	m_pTbDisabledColor->setObjectName("disabledColorToolButton");
	m_pTbDisabledColor->setText("...");

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("QWidget { background-color: white; }");

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayDisable = new QHBoxLayout;
	m_pHLayLabelPositing = new QHBoxLayout;
	m_pHLayLabelText = new QHBoxLayout;
	m_pHLayChecked = new QHBoxLayout;
	m_pHLayUseThemeColors = new QHBoxLayout;
	m_pHLayCheckedColor = new QHBoxLayout;
	m_pHLayUnCheckedColor = new QHBoxLayout;
	m_pHLayTextColor = new QHBoxLayout;
	m_pHLayDisabledColor = new QHBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVCheckBoxSettingsEditor::customLayout() const {
	m_pHLayDisable->addWidget(m_pLbDisable);
	m_pHLayDisable->addWidget(m_pCbDisable);
	m_pHLayDisable->addStretch();

	m_pHLayLabelPositing->addWidget(m_pLbLabelPositing);
	m_pHLayLabelPositing->addWidget(m_pCbLabelPositing);
	m_pHLayLabelPositing->addStretch();

	m_pHLayLabelText->addWidget(m_pLbLabelText);
	m_pHLayLabelText->addWidget(m_pLeLabelText);
	m_pHLayLabelText->addStretch();

	m_pHLayChecked->addWidget(m_pLbChecked);
	m_pHLayChecked->addWidget(m_pCbChecked);
	m_pHLayChecked->addStretch();

	m_pHLayUseThemeColors->addWidget(m_pLbUseThemeColors);
	m_pHLayUseThemeColors->addWidget(m_pCbUseThemeColors);
	m_pHLayUseThemeColors->addStretch();

	m_pHLayCheckedColor->addWidget(m_pLbCheckedColor);
	m_pHLayCheckedColor->addWidget(m_pLeCheckedColor);
	m_pHLayCheckedColor->addWidget(m_pTbCheckedColor);
	m_pHLayCheckedColor->addStretch();

	m_pHLayUnCheckedColor->addWidget(m_pLbUnCheckedColor);
	m_pHLayUnCheckedColor->addWidget(m_pLeUnCheckedColor);
	m_pHLayUnCheckedColor->addWidget(m_pTbUnCheckedColor);
	m_pHLayUnCheckedColor->addStretch();

	m_pHLayTextColor->addWidget(m_pLbTextColor);
	m_pHLayTextColor->addWidget(m_pLeTextColor);
	m_pHLayTextColor->addWidget(m_pTbTextColor);
	m_pHLayTextColor->addStretch();

	m_pHLayDisabledColor->addWidget(m_pLbDisabledColor);
	m_pHLayDisabledColor->addWidget(m_pLeDisabledColor);
	m_pHLayDisabledColor->addWidget(m_pTbDisabledColor);
	m_pHLayDisabledColor->addStretch();

	m_pVLayBottom->addWidget(m_pCheckBox);
	m_pVLayBottom->setAlignment(m_pCheckBox, Qt::AlignHCenter);

	m_pVLayCenter->addLayout(m_pHLayDisable);
	m_pVLayCenter->addLayout(m_pHLayLabelPositing);
	m_pVLayCenter->addLayout(m_pHLayLabelText);
	m_pVLayCenter->addLayout(m_pHLayChecked);
	m_pVLayCenter->addLayout(m_pHLayUseThemeColors);
	m_pVLayCenter->addLayout(m_pHLayCheckedColor);
	m_pVLayCenter->addLayout(m_pHLayUnCheckedColor);
	m_pVLayCenter->addLayout(m_pHLayTextColor);
	m_pVLayCenter->addLayout(m_pHLayDisabledColor);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVCheckBoxSettingsEditor::initConnection() {
	connect(m_pCbDisable, &QCheckBox::toggled, this, &CUVCheckBoxSettingsEditor::updateWidget);
	connect(m_pCbLabelPositing, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVCheckBoxSettingsEditor::updateWidget);
	connect(m_pLeLabelText, &QLineEdit::textChanged, this, &CUVCheckBoxSettingsEditor::updateWidget);
	connect(m_pCbUseThemeColors, &QCheckBox::toggled, this, &CUVCheckBoxSettingsEditor::updateWidget);
	connect(m_pCbChecked, &QCheckBox::toggled, this, &CUVCheckBoxSettingsEditor::updateWidget);
	connect(m_pTbTextColor, &QToolButton::clicked, this, &CUVCheckBoxSettingsEditor::selectColor);
	connect(m_pTbCheckedColor, &QToolButton::clicked, this, &CUVCheckBoxSettingsEditor::selectColor);
	connect(m_pTbUnCheckedColor, &QToolButton::clicked, this, &CUVCheckBoxSettingsEditor::selectColor);
	connect(m_pTbDisabledColor, &QToolButton::clicked, this, &CUVCheckBoxSettingsEditor::selectColor);
	connect(m_pCheckBox, &CUVMaterialCheckBox::toggled, this, &CUVCheckBoxSettingsEditor::setupForm);
}

void CUVCheckBoxSettingsEditor::initData() const {
	m_pCheckBox->setText(tr("CheckBox"));
	m_pCheckBox->setChecked(true);

	m_pCbLabelPositing->addItem(tr("LabelPositionLeft"));
	m_pCbLabelPositing->addItem(tr("LabelPositionRight"));
}

void CUVCheckBoxSettingsEditor::setupForm() const {
	switch (m_pCheckBox->labelPosition()) {
		case CUVMaterialCheckBox::LabelPositionLeft: {
			m_pCbLabelPositing->setCurrentIndex(0);
			break;
		}
		case CUVMaterialCheckBox::LabelPositionRight: {
			m_pCbLabelPositing->setCurrentIndex(1);
			break;
		}
		default: break;
	}

	m_pCbDisable->setChecked(!m_pCheckBox->isEnabled());
	m_pLeLabelText->setText(m_pCheckBox->text());
	m_pCbUseThemeColors->setChecked(m_pCheckBox->useThemeColors());
	m_pCbChecked->setChecked(m_pCheckBox->isChecked());
}

void CUVCheckBoxSettingsEditor::updateWidget() const {
	switch (m_pCbLabelPositing->currentIndex()) {
		case 0: {
			m_pCheckBox->setLabelPosition(CUVMaterialCheckBox::LabelPositionLeft);
			break;
		}
		case 1: {
			m_pCheckBox->setLabelPosition(CUVMaterialCheckBox::LabelPositionRight);
			break;
		}
		default: break;
	}

	m_pCheckBox->setDisabled(m_pCbDisable->isChecked());
	m_pCheckBox->setText(m_pLeLabelText->text());
	m_pCheckBox->setUseThemeColors(m_pCbUseThemeColors->isChecked());
	m_pCheckBox->setChecked(m_pCbChecked->isChecked());
}

void CUVCheckBoxSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if (const QString senderName = sender()->objectName(); "textColorToolButton" == senderName) {
			m_pCheckBox->setTextColor(color);
			m_pLeTextColor->setText(color.name(QColor::HexRgb));
		} else if ("disabledColorToolButton" == senderName) {
			m_pCheckBox->setDisabledColor(color);
			m_pLeDisabledColor->setText(color.name(QColor::HexRgb));
		} else if ("checkedColorToolButton" == senderName) {
			m_pCheckBox->setCheckedColor(color);
			m_pLeCheckedColor->setText(color.name(QColor::HexRgb));
		} else if ("uncheckedColorToolButton" == senderName) {
			m_pCheckBox->setUncheckedColor(color);
			m_pLeUnCheckedColor->setText(color.name(QColor::HexRgb));
		}
	}

	setupForm();
}
