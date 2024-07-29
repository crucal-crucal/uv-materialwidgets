#include "uvavatarsettingseditor.hpp"

#include <QColorDialog>
#include <QDebug>

CUVAvatarSettingsEditor::CUVAvatarSettingsEditor(QWidget* parent) : QWidget(parent), m_pAvatar(new CUVMaterialAvatar(QChar('C'))) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVAvatarSettingsEditor::~CUVAvatarSettingsEditor() = default;

void CUVAvatarSettingsEditor::createCtrl() {
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

	m_pLbSize = new QLabel(tr("Size"), this);
	m_pLbSize->setFixedWidth(m_nLabelWidth);
	m_pSbSize = new QSpinBox(this);
	m_pSbSize->setRange(5, 300);

	m_pLbType = new QLabel(tr("Type"), this);
	m_pLbType->setFixedWidth(m_nLabelWidth);
	m_pCbType = new QComboBox(this);

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayDisable = new QHBoxLayout;
	m_pHLayUseThemeColors = new QHBoxLayout;
	m_pHLayTextColor = new QHBoxLayout;
	m_pHLayBackgroundColor = new QHBoxLayout;
	m_pHLaySize = new QHBoxLayout;
	m_pHLayType = new QHBoxLayout;

	this->setLayout(m_pVLayCenter);
	m_pcanvas->setLayout(m_pVLayBottom);
}

void CUVAvatarSettingsEditor::customLayout() const {
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

	m_pHLaySize->addWidget(m_pLbSize);
	m_pHLaySize->addWidget(m_pSbSize);
	m_pHLaySize->addStretch();

	m_pHLayType->addWidget(m_pLbType);
	m_pHLayType->addWidget(m_pCbType);
	m_pHLayType->addStretch();

	m_pVLayBottom->addWidget(m_pAvatar);
	m_pVLayBottom->setAlignment(m_pAvatar, Qt::AlignHCenter);

	m_pVLayCenter->addLayout(m_pHLayDisable);
	m_pVLayCenter->addLayout(m_pHLayUseThemeColors);
	m_pVLayCenter->addLayout(m_pHLayTextColor);
	m_pVLayCenter->addLayout(m_pHLayBackgroundColor);
	m_pVLayCenter->addLayout(m_pHLaySize);
	m_pVLayCenter->addLayout(m_pHLayType);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVAvatarSettingsEditor::initConnection() {
	connect(m_pCbDisable, &QCheckBox::toggled, this, &CUVAvatarSettingsEditor::updateWidget);
	connect(m_pCbUseThemeColors, &QCheckBox::toggled, this, &CUVAvatarSettingsEditor::updateWidget);
	connect(m_pSbSize, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVAvatarSettingsEditor::updateWidget);
	connect(m_pCbType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVAvatarSettingsEditor::updateWidget);
	connect(m_pTbBackgroundColor, &QToolButton::clicked, this, &CUVAvatarSettingsEditor::selectColor);
	connect(m_pTbTextColor, &QToolButton::clicked, this, &CUVAvatarSettingsEditor::selectColor);
}

void CUVAvatarSettingsEditor::initData() const {
	m_pCbType->addItem(tr("LetterAvatar"));
	m_pCbType->addItem(tr("ImageAvatar"));
	m_pCbType->addItem(tr("IconAvatar"));

	m_pSbSize->setValue(60);

	m_pCbUseThemeColors->setChecked(true);
}

void CUVAvatarSettingsEditor::setupForm() const {
	switch (m_pAvatar->type()) {
		case Material::LetterAvatar:
			m_pCbType->setCurrentIndex(0);
			break;
		case Material::ImageAvatar:
			m_pCbType->setCurrentIndex(1);
			break;
		case Material::IconAvatar:
			m_pCbType->setCurrentIndex(2);
			break;
		default:
			break;
	}
	m_pCbDisable->setChecked(!m_pAvatar->isEnabled());
	m_pCbUseThemeColors->setChecked(m_pAvatar->useThemeColors());
	m_pSbSize->setValue(m_pAvatar->Size());
}

void CUVAvatarSettingsEditor::updateWidget() const {
	switch (m_pCbType->currentIndex()) {
		case 0: {
			m_pAvatar->setLetter(QChar('C'));
			break;
		}
		case 1: {
			m_pAvatar->setImage(QImage(":/images/assets/sikh.jpg"));
			break;
		}
		case 2: {
			m_pAvatar->setIcon(CUVMaterialTheme::icon("communication", "message"));
			break;
		}
		default: break;
	}
	m_pAvatar->setDisabled(m_pCbDisable->isChecked());
	m_pAvatar->setUseThemeColors(m_pCbUseThemeColors->isChecked());
	m_pAvatar->setSize(m_pSbSize->value());
}

void CUVAvatarSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if (const QString senderName = sender()->objectName(); "textColorToolButton" == senderName) {
			m_pAvatar->setTextColor(color);
			m_pLeTextColor->setText(color.name(QColor::HexRgb));
		} else if ("backgroundColorToolButton" == senderName) {
			m_pAvatar->setBackgroundColor(color);
			m_pLeBackgroundColor->setText(color.name(QColor::HexRgb));
		}
	}
	setupForm();
}
