#include "uvcomboboxsettingseditor.hpp"

#include <QColorDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QToolButton>
#include <QVBoxLayout>

#include "uvmaterialcombobox/uvmaterialcombobox.hpp"

CUVComboBoxSettingsEditor::CUVComboBoxSettingsEditor(QWidget* parent): QWidget(parent) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVComboBoxSettingsEditor::~CUVComboBoxSettingsEditor() = default;

void CUVComboBoxSettingsEditor::createCtrl() {
	m_pLbBorderRaidus = new QLabel("Border Radius", this);
	m_pLbBorderRaidus->setFixedWidth(m_nLabelWidth);
	m_pSpinBorderRadius = new QSpinBox(this);

	m_pLbNormalColor = new QLabel("Normal Color", this);
	m_pLbNormalColor->setFixedWidth(m_nLabelWidth);
	m_pEditNormalColor = new QLineEdit(this);
	m_pBtnNormalColor = new QToolButton(this);
	m_pBtnNormalColor->setText("...");
	m_pBtnNormalColor->setObjectName("BtnNormalColor");

	m_pLbMouseHoverColor = new QLabel("Mouse Hover Color", this);
	m_pLbMouseHoverColor->setFixedWidth(m_nLabelWidth);
	m_pEditMouseHoverColor = new QLineEdit(this);
	m_pBtnMouseHoverColor = new QToolButton(this);
	m_pBtnMouseHoverColor->setText("...");
	m_pBtnMouseHoverColor->setObjectName("BtnMouseHoverColor");

	m_pLbMouseSelectedColor = new QLabel("Mouse Selected Color", this);
	m_pLbMouseSelectedColor->setFixedWidth(m_nLabelWidth);
	m_pEditMouseSelectedColor = new QLineEdit(this);
	m_pBtnMouseSelectedColor = new QToolButton(this);
	m_pBtnMouseSelectedColor->setText("...");
	m_pBtnMouseSelectedColor->setObjectName("BtnMouseSelectedColor");

	m_pLbBorderColor = new QLabel("Border Color", this);
	m_pLbBorderColor->setFixedWidth(m_nLabelWidth);
	m_pEditBorderColor = new QLineEdit(this);
	m_pBtnBorderColor = new QToolButton(this);
	m_pBtnBorderColor->setText("...");
	m_pBtnBorderColor->setObjectName("BtnBorderColor");

	m_pLbSelectedMarkColor = new QLabel("Selected Mark Color", this);
	m_pLbSelectedMarkColor->setFixedWidth(m_nLabelWidth);
	m_pEditSelectedMarkColor = new QLineEdit(this);
	m_pBtnSelectedMarkColor = new QToolButton(this);
	m_pBtnSelectedMarkColor->setText("...");
	m_pBtnSelectedMarkColor->setObjectName("BtnSelectedMarkColor");

	m_pLbItemHoverColor = new QLabel("Item Hover Color", this);
	m_pLbItemHoverColor->setFixedWidth(m_nLabelWidth);
	m_pEditItemHoverColor = new QLineEdit(this);
	m_pBtnItemHoverColor = new QToolButton(this);
	m_pBtnItemHoverColor->setText("...");
	m_pBtnItemHoverColor->setObjectName("BtnItemHoverColor");

	m_pLbExpansionIndicatorColor = new QLabel("Expansion Indicator Color", this);
	m_pLbExpansionIndicatorColor->setFixedWidth(m_nLabelWidth);
	m_pEditExpansionIndicatorColor = new QLineEdit(this);
	m_pBtnExpansionIndicatorColor = new QToolButton(this);
	m_pBtnExpansionIndicatorColor->setText("...");
	m_pBtnExpansionIndicatorColor->setObjectName("BtnExpansionIndicatorColor");

	m_pcanvas = new QWidget(this);
	m_pcanvas->setObjectName("Canvas");
	m_pcanvas->setStyleSheet("#Canvas { background-color: white; }");

	m_pComboBox = new CUVMaterialComboBox(this);

	m_pBorderRadiusHLayout = new QHBoxLayout;
	m_pNormalColorHLayout = new QHBoxLayout;
	m_pMouseHoverColorHLayout = new QHBoxLayout;
	m_pMouseSelectedColorHLayout = new QHBoxLayout;
	m_pBorderColorHLayout = new QHBoxLayout;
	m_pSelectedMarkColorHLayout = new QHBoxLayout;
	m_pItemHoverColorHLayout = new QHBoxLayout;
	m_pExpansionIndicatorColorHLayout = new QHBoxLayout;

	m_pCanvasVLayout = new QVBoxLayout(m_pcanvas);
	m_pCenterVLayout = new QVBoxLayout;

	this->setLayout(m_pCenterVLayout);
}

void CUVComboBoxSettingsEditor::customLayout() const {
	m_pBorderRadiusHLayout->addWidget(m_pLbBorderRaidus);
	m_pBorderRadiusHLayout->addWidget(m_pSpinBorderRadius);
	m_pBorderRadiusHLayout->addStretch();

	m_pNormalColorHLayout->addWidget(m_pLbNormalColor);
	m_pNormalColorHLayout->addWidget(m_pEditNormalColor);
	m_pNormalColorHLayout->addWidget(m_pBtnNormalColor);
	m_pNormalColorHLayout->addStretch();

	m_pMouseHoverColorHLayout->addWidget(m_pLbMouseHoverColor);
	m_pMouseHoverColorHLayout->addWidget(m_pEditMouseHoverColor);
	m_pMouseHoverColorHLayout->addWidget(m_pBtnMouseHoverColor);
	m_pMouseHoverColorHLayout->addStretch();

	m_pMouseSelectedColorHLayout->addWidget(m_pLbMouseSelectedColor);
	m_pMouseSelectedColorHLayout->addWidget(m_pEditMouseSelectedColor);
	m_pMouseSelectedColorHLayout->addWidget(m_pBtnMouseSelectedColor);
	m_pMouseSelectedColorHLayout->addStretch();

	m_pBorderColorHLayout->addWidget(m_pLbBorderColor);
	m_pBorderColorHLayout->addWidget(m_pEditBorderColor);
	m_pBorderColorHLayout->addWidget(m_pBtnBorderColor);
	m_pBorderColorHLayout->addStretch();

	m_pSelectedMarkColorHLayout->addWidget(m_pLbSelectedMarkColor);
	m_pSelectedMarkColorHLayout->addWidget(m_pEditSelectedMarkColor);
	m_pSelectedMarkColorHLayout->addWidget(m_pBtnSelectedMarkColor);
	m_pSelectedMarkColorHLayout->addStretch();

	m_pItemHoverColorHLayout->addWidget(m_pLbItemHoverColor);
	m_pItemHoverColorHLayout->addWidget(m_pEditItemHoverColor);
	m_pItemHoverColorHLayout->addWidget(m_pBtnItemHoverColor);
	m_pItemHoverColorHLayout->addStretch();

	m_pExpansionIndicatorColorHLayout->addWidget(m_pLbExpansionIndicatorColor);
	m_pExpansionIndicatorColorHLayout->addWidget(m_pEditExpansionIndicatorColor);
	m_pExpansionIndicatorColorHLayout->addWidget(m_pBtnExpansionIndicatorColor);
	m_pExpansionIndicatorColorHLayout->addStretch();

	m_pCenterVLayout->addLayout(m_pBorderRadiusHLayout);
	m_pCenterVLayout->addLayout(m_pNormalColorHLayout);
	m_pCenterVLayout->addLayout(m_pMouseHoverColorHLayout);
	m_pCenterVLayout->addLayout(m_pMouseSelectedColorHLayout);
	m_pCenterVLayout->addLayout(m_pBorderColorHLayout);
	m_pCenterVLayout->addLayout(m_pSelectedMarkColorHLayout);
	m_pCenterVLayout->addLayout(m_pItemHoverColorHLayout);
	m_pCenterVLayout->addLayout(m_pExpansionIndicatorColorHLayout);
	m_pCenterVLayout->addWidget(m_pcanvas);

	m_pCanvasVLayout->addWidget(m_pComboBox);
	m_pCanvasVLayout->setAlignment(m_pComboBox, Qt::AlignCenter);
}

void CUVComboBoxSettingsEditor::initConnection() {
	connect(m_pSpinBorderRadius, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVComboBoxSettingsEditor::updateWidget);
	connect(m_pBtnBorderColor, &QToolButton::clicked, this, &CUVComboBoxSettingsEditor::selectColor);
	connect(m_pBtnMouseSelectedColor, &QToolButton::clicked, this, &CUVComboBoxSettingsEditor::selectColor);
	connect(m_pBtnMouseHoverColor, &QToolButton::clicked, this, &CUVComboBoxSettingsEditor::selectColor);
	connect(m_pBtnNormalColor, &QToolButton::clicked, this, &CUVComboBoxSettingsEditor::selectColor);
	connect(m_pBtnSelectedMarkColor, &QToolButton::clicked, this, &CUVComboBoxSettingsEditor::selectColor);
	connect(m_pBtnItemHoverColor, &QToolButton::clicked, this, &CUVComboBoxSettingsEditor::selectColor);
	connect(m_pBtnExpansionIndicatorColor, &QToolButton::clicked, this, &CUVComboBoxSettingsEditor::selectColor);
}

void CUVComboBoxSettingsEditor::initData() const {
	for (int i = 0; i < 10; i++) {
		m_pComboBox->addItem(QString("Item %1").arg(i));
	}
}

void CUVComboBoxSettingsEditor::setupForm() const {
	m_pSpinBorderRadius->setValue(m_pComboBox->getBorderRadius());
}

void CUVComboBoxSettingsEditor::updateWidget() const {
	m_pComboBox->setBorderRadius(m_pSpinBorderRadius->value());
}

void CUVComboBoxSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if ("BtnNormalColor" == sender()->objectName()) {
			m_pEditNormalColor->setText(color.name(QColor::HexRgb));
			m_pComboBox->setNomalColor(color);
		} else if ("BtnMouseHoverColor" == sender()->objectName()) {
			m_pEditMouseHoverColor->setText(color.name(QColor::HexRgb));
			m_pComboBox->setMouseHoverColor(color);
		} else if ("BtnMouseSelectedColor" == sender()->objectName()) {
			m_pEditMouseSelectedColor->setText(color.name(QColor::HexRgb));
			m_pComboBox->setMouseSelectedColor(color);
		} else if ("BtnBorderColor" == sender()->objectName()) {
			m_pEditBorderColor->setText(color.name(QColor::HexRgb));
			m_pComboBox->setBorderColor(color);
		} else if ("BtnSelectedMarkColor" == sender()->objectName()) {
			m_pEditSelectedMarkColor->setText(color.name(QColor::HexRgb));
			m_pComboBox->setSelectedMarkColor(color);
		} else if ("BtnItemHoverColor" == sender()->objectName()) {
			m_pEditItemHoverColor->setText(color.name(QColor::HexRgb));
			m_pComboBox->setItemHoverColor(color);
		} else if ("BtnExpansionIndicatorColor" == sender()->objectName()) {
			m_pEditExpansionIndicatorColor->setText(color.name(QColor::HexRgb));
			m_pComboBox->setExpansionIndicatorColor(color);
		}
	}

	setupForm();
}
