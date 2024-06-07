#include "uvradiobuttonsettingseditor.hpp"

#include <QColorDialog>

CUVRadioButtonSettingsEditor::CUVRadioButtonSettingsEditor(QWidget* parent)
: QWidget(parent), m_pRadioButton1(new CUVMaterialRadioButton), m_pRadioButton2(new CUVMaterialRadioButton),
  m_pRadioButton3(new CUVMaterialRadioButton) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVRadioButtonSettingsEditor::~CUVRadioButtonSettingsEditor() = default;

void CUVRadioButtonSettingsEditor::createCtrl() {
	m_pLbDisabled = new QLabel(tr("Disabled"), this);
	m_pLbDisabled->setFixedWidth(m_nLabelWidth);
	m_pCbDisabled = new QCheckBox(this);

	m_pLbLabelPosition = new QLabel(tr("Label Position"), this);
	m_pLbLabelPosition->setFixedWidth(m_nLabelWidth);
	m_pCbLabelPosition = new QComboBox(this);

	m_pLbLabelText = new QLabel(tr("Label Text"), this);
	m_pLbLabelText->setFixedWidth(m_nLabelWidth);
	m_pLeLabelText = new QLineEdit(this);

	m_pLbUseThemeColors = new QLabel(tr("Use Theme Colors"), this);
	m_pLbUseThemeColors->setFixedWidth(m_nLabelWidth);
	m_pCbUseThemeColors = new QCheckBox(this);

	m_pLbCheckedColor = new QLabel(tr("Checked Color"), this);
	m_pLbCheckedColor->setFixedWidth(m_nLabelWidth);
	m_pLeCheckedColor = new QLineEdit(this);
	m_pTbCheckedColor = new QToolButton(this);
	m_pTbCheckedColor->setText("...");
	m_pTbCheckedColor->setObjectName("checkedColorToolButton");

	m_pLbUnCheckedColor = new QLabel(tr("UnChecked Color"), this);
	m_pLbUnCheckedColor->setFixedWidth(m_nLabelWidth);
	m_pLeUnCheckedColor = new QLineEdit(this);
	m_pTbUnCheckedColor = new QToolButton(this);
	m_pTbUnCheckedColor->setText("...");
	m_pTbUnCheckedColor->setObjectName("uncheckedColorToolButton");

	m_pLbTextColor = new QLabel(tr("Text Color"), this);
	m_pLbTextColor->setFixedWidth(m_nLabelWidth);
	m_pLeTextColor = new QLineEdit(this);
	m_pTbTextColor = new QToolButton(this);
	m_pTbTextColor->setText("...");
	m_pTbTextColor->setObjectName("textColorToolButton");

	m_pLbDisabledColor = new QLabel(tr("Disabled Color"), this);
	m_pLbDisabledColor->setFixedWidth(m_nLabelWidth);
	m_pLeDisabledColor = new QLineEdit(this);
	m_pTbDisabledColor = new QToolButton(this);
	m_pTbDisabledColor->setText("...");
	m_pTbDisabledColor->setObjectName("disabledColorToolButton");

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayDisabled = new QHBoxLayout;
	m_pHLayLabelPosition = new QHBoxLayout;
	m_pHLayLabelText = new QHBoxLayout;
	m_pHLayUseThemeColors = new QHBoxLayout;
	m_pHLayCheckedColor = new QHBoxLayout;
	m_pHLayUnCheckedColor = new QHBoxLayout;
	m_pHLayTextColor = new QHBoxLayout;
	m_pHLayDisabledColor = new QHBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVRadioButtonSettingsEditor::customLayout() const {
	m_pHLayDisabled->addWidget(m_pLbDisabled);
	m_pHLayDisabled->addWidget(m_pCbDisabled);
	m_pHLayDisabled->addStretch();

	m_pHLayLabelPosition->addWidget(m_pLbLabelPosition);
	m_pHLayLabelPosition->addWidget(m_pCbLabelPosition);
	m_pHLayLabelPosition->addStretch();

	m_pHLayLabelText->addWidget(m_pLbLabelText);
	m_pHLayLabelText->addWidget(m_pLeLabelText);
	m_pHLayLabelText->addStretch();

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

	m_pVLayBottom->addWidget(m_pRadioButton1);
	m_pVLayBottom->addWidget(m_pRadioButton2);
	m_pVLayBottom->addWidget(m_pRadioButton3);
	m_pVLayBottom->setAlignment(Qt::AlignCenter);

	m_pVLayCenter->addLayout(m_pHLayDisabled);
	m_pVLayCenter->addLayout(m_pHLayLabelPosition);
	m_pVLayCenter->addLayout(m_pHLayLabelText);
	m_pVLayCenter->addLayout(m_pHLayUseThemeColors);
	m_pVLayCenter->addLayout(m_pHLayCheckedColor);
	m_pVLayCenter->addLayout(m_pHLayUnCheckedColor);
	m_pVLayCenter->addLayout(m_pHLayTextColor);
	m_pVLayCenter->addLayout(m_pHLayDisabledColor);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVRadioButtonSettingsEditor::initData() const {
	m_pRadioButton1->setText("Radio 1");
	m_pRadioButton2->setText("Radio 2");
	m_pRadioButton3->setText("Radio 3");

	m_pCbLabelPosition->addItem("Left");
	m_pCbLabelPosition->addItem("Right");
}

void CUVRadioButtonSettingsEditor::initConnection() {
	connect(m_pCbDisabled, &QCheckBox::toggled, this, &CUVRadioButtonSettingsEditor::updateWidget);
	connect(m_pLeLabelText, &QLineEdit::textChanged, this, &CUVRadioButtonSettingsEditor::updateWidget);
	connect(m_pCbLabelPosition, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVRadioButtonSettingsEditor::updateWidget);
	connect(m_pCbUseThemeColors, &QCheckBox::toggled, this, &CUVRadioButtonSettingsEditor::updateWidget);
	connect(m_pTbCheckedColor, &QToolButton::clicked, this, &CUVRadioButtonSettingsEditor::selectColor);
	connect(m_pTbUnCheckedColor, &QToolButton::clicked, this, &CUVRadioButtonSettingsEditor::selectColor);
	connect(m_pTbDisabledColor, &QToolButton::clicked, this, &CUVRadioButtonSettingsEditor::selectColor);
	connect(m_pTbTextColor, &QToolButton::clicked, this, &CUVRadioButtonSettingsEditor::selectColor);
}

void CUVRadioButtonSettingsEditor::setupForm() const {
	switch (m_pRadioButton1->labelPosition()) {
		case CUVMaterialCheckable::LabelPositionLeft: {
			m_pCbLabelPosition->setCurrentIndex(0);
			break;
		}
		case CUVMaterialCheckable::LabelPositionRight: {
			m_pCbLabelPosition->setCurrentIndex(1);
			break;
		}
		default: break;
	}

	m_pCbDisabled->setChecked(!m_pRadioButton1->isEnabled());
	m_pLeLabelText->setText(m_pRadioButton1->text());
	m_pCbUseThemeColors->setChecked(m_pRadioButton1->useThemeColors());
}

void CUVRadioButtonSettingsEditor::updateWidget() const {
	switch (m_pCbLabelPosition->currentIndex()) {
		case 0: {
			m_pRadioButton1->setLabelPosition(CUVMaterialCheckable::LabelPositionLeft);
			m_pRadioButton2->setLabelPosition(CUVMaterialCheckable::LabelPositionLeft);
			m_pRadioButton3->setLabelPosition(CUVMaterialCheckable::LabelPositionLeft);
			break;
		}
		case 1: {
			m_pRadioButton1->setLabelPosition(CUVMaterialCheckable::LabelPositionRight);
			m_pRadioButton2->setLabelPosition(CUVMaterialCheckable::LabelPositionRight);
			m_pRadioButton3->setLabelPosition(CUVMaterialCheckable::LabelPositionRight);
			break;
		}
		default: break;
	}

	m_pRadioButton1->setDisabled(m_pCbDisabled->isChecked());
	m_pRadioButton2->setDisabled(m_pCbDisabled->isChecked());
	m_pRadioButton3->setDisabled(m_pCbDisabled->isChecked());

	m_pRadioButton1->setText(m_pLeLabelText->text());

	m_pRadioButton1->setUseThemeColors(m_pCbUseThemeColors->isChecked());
	m_pRadioButton2->setUseThemeColors(m_pCbUseThemeColors->isChecked());
	m_pRadioButton3->setUseThemeColors(m_pCbUseThemeColors->isChecked());
}

void CUVRadioButtonSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if (const QString senderName = sender()->objectName(); senderName == "textColorToolButton") {
			m_pRadioButton1->setTextColor(color);
			m_pRadioButton2->setTextColor(color);
			m_pRadioButton3->setTextColor(color);
			m_pLeTextColor->setText(color.name(QColor::HexRgb));
		} else if (senderName == "disabledColorToolButton") {
			m_pRadioButton1->setDisabledColor(color);
			m_pRadioButton2->setDisabledColor(color);
			m_pRadioButton3->setDisabledColor(color);
			m_pLeDisabledColor->setText(color.name(QColor::HexRgb));
		} else if (senderName == "checkedColorToolButton") {
			m_pRadioButton1->setCheckedColor(color);
			m_pRadioButton2->setCheckedColor(color);
			m_pRadioButton3->setCheckedColor(color);
			m_pLeCheckedColor->setText(color.name(QColor::HexRgb));
		} else if (senderName == "uncheckedColorToolButton") {
			m_pRadioButton1->setUncheckedColor(color);
			m_pRadioButton2->setUncheckedColor(color);
			m_pRadioButton3->setUncheckedColor(color);
			m_pLeUnCheckedColor->setText(color.name(QColor::HexRgb));
		}
	}
	setupForm();
}
