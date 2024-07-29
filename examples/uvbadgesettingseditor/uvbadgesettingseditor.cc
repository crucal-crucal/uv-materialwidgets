#include "uvbadgesettingseditor.hpp"

#include <QColorDialog>
#include <QDebug>

CUVBadgeSettingsEditor::CUVBadgeSettingsEditor(QWidget* parent)
: QWidget(parent), m_pAvatar(new CUVMaterialAvatar(QImage(":/images/assets/sikh.jpg"))), m_pBadge(new CUVMaterialBadge) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVBadgeSettingsEditor::~CUVBadgeSettingsEditor() = default;

void CUVBadgeSettingsEditor::createCtrl() {
	m_pLbDisable = new QLabel(tr("Disable"), this);
	m_pLbDisable->setFixedWidth(m_nLabelWidth);
	m_pCbDisable = new QCheckBox(this);

	m_pLbUseThemeColors = new QLabel(tr("Use theme color"), this);
	m_pLbUseThemeColors->setFixedWidth(m_nLabelWidth);
	m_pCbUseThemeColors = new QCheckBox(this);

	m_pLbTextColor = new QLabel(tr("Text color"), this);
	m_pLbTextColor->setFixedWidth(m_nLabelWidth);
	m_pLeTextColor = new QLineEdit(this);
	m_pTbTextColor = new QToolButton(this);
	m_pTbTextColor->setObjectName("textColorToolButton");
	m_pTbTextColor->setText("...");

	m_pLbBackgroundColor = new QLabel(tr("Background color"), this);
	m_pLbBackgroundColor->setFixedWidth(m_nLabelWidth);
	m_pLeBackgroundColor = new QLineEdit(this);
	m_pTbBackgroundColor = new QToolButton(this);
	m_pTbBackgroundColor->setObjectName("backgroundColorToolButton");
	m_pTbBackgroundColor->setText("...");

	m_pLbHorizontalOffset = new QLabel(tr("Horizontal Offset"), this);
	m_pLbHorizontalOffset->setFixedWidth(m_nLabelWidth);
	m_pSbHorizontalOffset = new QSpinBox(this);
	m_pSbHorizontalOffset->setRange(-40, 40);

	m_pLbVerticalOffset = new QLabel(tr("Vertical Offset"), this);
	m_pLbVerticalOffset->setFixedWidth(m_nLabelWidth);
	m_pSbVerticalOffset = new QSpinBox(this);
	m_pSbVerticalOffset->setRange(-40, 40);

	m_pLbType = new QLabel(tr("Type"), this);
	m_pLbType->setFixedWidth(m_nLabelWidth);
	m_pCbType = new QComboBox(this);

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");

	m_pAvatar->setSize(60);
	m_pBadge->setParent(m_pAvatar);
	m_pBadge->setRelativePosition(18, 18);
	m_pBadge->setText("3");

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayDisable = new QHBoxLayout;
	m_pHLayUseThemeColors = new QHBoxLayout;
	m_pHLayTextColor = new QHBoxLayout;
	m_pHLayBackgroundColor = new QHBoxLayout;
	m_pHLayHorizontalOffset = new QHBoxLayout;
	m_pHLayVerticalOffset = new QHBoxLayout;
	m_pHLayType = new QHBoxLayout;

	this->setLayout(m_pVLayCenter);
	m_pcanvas->setLayout(m_pVLayBottom);
}

void CUVBadgeSettingsEditor::customLayout() const {
	m_pHLayDisable->addWidget(m_pLbDisable);
	m_pHLayDisable->addWidget(m_pCbDisable);
	m_pHLayDisable->addStretch();

	m_pHLayUseThemeColors->addWidget(m_pLbUseThemeColors);
	m_pHLayUseThemeColors->addWidget(m_pCbUseThemeColors);
	m_pHLayUseThemeColors->addStretch();

	m_pHLayTextColor->addWidget(m_pLbTextColor);
	m_pHLayTextColor->addWidget(m_pLeTextColor);
	m_pHLayTextColor->addWidget(m_pTbTextColor);
	m_pHLayTextColor->addStretch();

	m_pHLayBackgroundColor->addWidget(m_pLbBackgroundColor);
	m_pHLayBackgroundColor->addWidget(m_pLeBackgroundColor);
	m_pHLayBackgroundColor->addWidget(m_pTbBackgroundColor);
	m_pHLayBackgroundColor->addStretch();

	m_pHLayHorizontalOffset->addWidget(m_pLbHorizontalOffset);
	m_pHLayHorizontalOffset->addWidget(m_pSbHorizontalOffset);
	m_pHLayHorizontalOffset->addStretch();

	m_pHLayVerticalOffset->addWidget(m_pLbVerticalOffset);
	m_pHLayVerticalOffset->addWidget(m_pSbVerticalOffset);
	m_pHLayVerticalOffset->addStretch();

	m_pHLayType->addWidget(m_pLbType);
	m_pHLayType->addWidget(m_pCbType);
	m_pHLayType->addStretch();

	m_pVLayBottom->addWidget(m_pAvatar);
	m_pVLayBottom->setAlignment(m_pAvatar, Qt::AlignHCenter);

	m_pVLayCenter->addLayout(m_pHLayDisable);
	m_pVLayCenter->addLayout(m_pHLayUseThemeColors);
	m_pVLayCenter->addLayout(m_pHLayTextColor);
	m_pVLayCenter->addLayout(m_pHLayBackgroundColor);
	m_pVLayCenter->addLayout(m_pHLayHorizontalOffset);
	m_pVLayCenter->addLayout(m_pHLayVerticalOffset);
	m_pVLayCenter->addLayout(m_pHLayType);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVBadgeSettingsEditor::initConnection() {
	connect(m_pCbDisable, &QCheckBox::toggled, this, &CUVBadgeSettingsEditor::updateWidget);
	connect(m_pCbUseThemeColors, &QCheckBox::toggled, this, &CUVBadgeSettingsEditor::updateWidget);
	connect(m_pSbHorizontalOffset, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVBadgeSettingsEditor::updateWidget);
	connect(m_pSbVerticalOffset, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVBadgeSettingsEditor::updateWidget);
	connect(m_pCbType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVBadgeSettingsEditor::updateWidget);
	connect(m_pTbBackgroundColor, &QToolButton::clicked, this, &CUVBadgeSettingsEditor::selectColor);
	connect(m_pTbTextColor, &QToolButton::clicked, this, &CUVBadgeSettingsEditor::selectColor);
}

void CUVBadgeSettingsEditor::initData() const {
	m_pCbType->addItem(tr("Text"));
	m_pCbType->addItem(tr("Icon"));

	m_pSbHorizontalOffset->setValue(17);
	m_pSbVerticalOffset->setValue(17);

	m_pCbUseThemeColors->setChecked(true);
}

void CUVBadgeSettingsEditor::setupForm() const {
	m_pCbType->setCurrentIndex(!m_pBadge->icon().isNull());
	m_pCbDisable->setChecked(!m_pBadge->isEnabled());
	m_pCbUseThemeColors->setChecked(m_pBadge->useThemeColors());
	m_pSbHorizontalOffset->setValue(static_cast<int>(m_pBadge->relativeXPosition()));
	m_pSbVerticalOffset->setValue(static_cast<int>(m_pBadge->relativeYPosition()));
}

void CUVBadgeSettingsEditor::updateWidget() const {
	switch (m_pCbType->currentIndex()) {
		case 0: {
			m_pBadge->setText("7");
			break;
		}
		case 1: {
			m_pBadge->setIcon(QIcon(CUVMaterialTheme::icon("communication", "message")));
			break;
		}
		default: break;
	}
	m_pBadge->setDisabled(m_pCbDisable->isChecked());
	m_pBadge->setUseThemeColors(m_pCbUseThemeColors->isChecked());
	m_pBadge->setRelativeXPosition(m_pSbHorizontalOffset->value());
	m_pBadge->setRelativeYPosition(m_pSbVerticalOffset->value());
}

void CUVBadgeSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if (const QString senderName = sender()->objectName(); "textColorToolButton" == senderName) {
			m_pBadge->setTextColor(color);
			m_pLeTextColor->setText(color.name(QColor::HexRgb));
		} else if ("backgroundColorToolButton" == senderName) {
			m_pBadge->setBackgroundColor(color);
			m_pLeBackgroundColor->setText(color.name(QColor::HexRgb));
		}
	}
	setupForm();
}
