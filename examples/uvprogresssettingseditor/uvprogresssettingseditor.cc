#include "uvprogresssettingseditor.hpp"

#include <QColorDialog>

CUVProgressSettingsEditor::CUVProgressSettingsEditor(QWidget* parent): QWidget(parent), m_pProgress(new CUVMaterialProgress) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVProgressSettingsEditor::~CUVProgressSettingsEditor() = default;

void CUVProgressSettingsEditor::createCtrl() {
	m_pLbDisabled = new QLabel(tr("Disabled"), this);
	m_pLbDisabled->setFixedWidth(m_nLabelWidth);
	m_pCbDisabled = new QCheckBox(this);

	m_pLbProgressType = new QLabel(tr("Progress Type"), this);
	m_pLbProgressType->setFixedWidth(m_nLabelWidth);
	m_pCbProgressType = new QComboBox(this);

	m_pLbProgress = new QLabel(tr("Progress"), this);
	m_pLbProgress->setFixedWidth(m_nLabelWidth);
	m_pSlProgress = new QSlider(Qt::Horizontal, this);

	m_pLbUseThemeColors = new QLabel(tr("Use Theme Colors"), this);
	m_pLbUseThemeColors->setFixedWidth(m_nLabelWidth);
	m_pCbUseThemeColors = new QCheckBox(this);

	m_pLbProgressColor = new QLabel(tr("Progress Color"), this);
	m_pLbProgressColor->setFixedWidth(m_nLabelWidth);
	m_pLeProgressColor = new QLineEdit(this);
	m_pTbProgressColor = new QToolButton(this);
	m_pTbProgressColor->setText("...");
	m_pTbProgressColor->setObjectName("progressColorToolButton");

	m_pLbBackgroundColor = new QLabel(tr("Background Color"), this);
	m_pLbBackgroundColor->setFixedWidth(m_nLabelWidth);
	m_pLeBackgroundColor = new QLineEdit(this);
	m_pTbBackgroundColor = new QToolButton(this);
	m_pTbBackgroundColor->setText("...");
	m_pTbBackgroundColor->setObjectName("backgroundColorToolButton");

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayDisabled = new QHBoxLayout;
	m_pHLayProgressType = new QHBoxLayout;
	m_pHLayProgress = new QHBoxLayout;
	m_pHLayUseThemeColors = new QHBoxLayout;
	m_pHLayProgressColor = new QHBoxLayout;
	m_pHLayBackgroundColor = new QHBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVProgressSettingsEditor::customLayout() const {
	m_pHLayDisabled->addWidget(m_pLbDisabled);
	m_pHLayDisabled->addWidget(m_pCbDisabled);
	m_pHLayDisabled->addStretch();

	m_pHLayProgressType->addWidget(m_pLbProgressType);
	m_pHLayProgressType->addWidget(m_pCbProgressType);
	m_pHLayProgressType->addStretch();

	m_pHLayProgress->addWidget(m_pLbProgress);
	m_pHLayProgress->addWidget(m_pSlProgress);
	m_pHLayProgress->addStretch();

	m_pHLayUseThemeColors->addWidget(m_pLbUseThemeColors);
	m_pHLayUseThemeColors->addWidget(m_pCbUseThemeColors);
	m_pHLayUseThemeColors->addStretch();

	m_pHLayProgressColor->addWidget(m_pLbProgressColor);
	m_pHLayProgressColor->addWidget(m_pLeProgressColor);
	m_pHLayProgressColor->addWidget(m_pTbProgressColor);
	m_pHLayProgressColor->addStretch();

	m_pHLayBackgroundColor->addWidget(m_pLbBackgroundColor);
	m_pHLayBackgroundColor->addWidget(m_pLeBackgroundColor);
	m_pHLayBackgroundColor->addWidget(m_pTbBackgroundColor);
	m_pHLayBackgroundColor->addStretch();

	m_pVLayBottom->addWidget(m_pProgress);
	m_pVLayBottom->setAlignment(m_pProgress, Qt::AlignHCenter);

	m_pVLayCenter->addLayout(m_pHLayDisabled);
	m_pVLayCenter->addLayout(m_pHLayProgressType);
	m_pVLayCenter->addLayout(m_pHLayProgress);
	m_pVLayCenter->addLayout(m_pHLayUseThemeColors);
	m_pVLayCenter->addLayout(m_pHLayProgressColor);
	m_pVLayCenter->addLayout(m_pHLayBackgroundColor);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVProgressSettingsEditor::initData() const {
	m_pCbProgressType->addItem("DeterminateProgress");
	m_pCbProgressType->addItem("IndeterminateProgress");

	m_pSlProgress->setRange(0, 100);
}

void CUVProgressSettingsEditor::initConnection() {
	connect(m_pCbDisabled, &QCheckBox::toggled, this, &CUVProgressSettingsEditor::updateWidget);
	connect(m_pCbProgressType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVProgressSettingsEditor::updateWidget);
	connect(m_pSlProgress, QOverload<int>::of(&QSlider::valueChanged), this, &CUVProgressSettingsEditor::updateWidget);
	connect(m_pCbUseThemeColors, &QCheckBox::toggled, this, &CUVProgressSettingsEditor::updateWidget);
	connect(m_pTbBackgroundColor, &QToolButton::clicked, this, &CUVProgressSettingsEditor::selectColor);
	connect(m_pTbProgressColor, &QToolButton::clicked, this, &CUVProgressSettingsEditor::selectColor);
}

void CUVProgressSettingsEditor::setupForm() const {
	switch (m_pProgress->progressType()) {
		case Material::DeterminateProgress: {
			m_pCbProgressType->setCurrentIndex(0);
			break;
		}
		case Material::IndeterminateProgress: {
			m_pCbProgressType->setCurrentIndex(1);
			break;
		}
		default: break;
	}

	m_pCbDisabled->setChecked(!m_pProgress->isEnabled());
	m_pSlProgress->setValue(m_pProgress->value());
	m_pCbUseThemeColors->setChecked(m_pProgress->useThemeColors());
}

void CUVProgressSettingsEditor::updateWidget() const {
	switch (m_pCbProgressType->currentIndex()) {
		case 0: {
			m_pProgress->setProgressType(Material::DeterminateProgress);
			break;
		}
		case 1: {
			m_pProgress->setProgressType(Material::IndeterminateProgress);
			break;
		}
		default: break;
	}

	m_pProgress->setDisabled(m_pCbDisabled->isChecked());
	m_pProgress->setValue(m_pSlProgress->value());
	m_pProgress->setUseThemeColors(m_pCbUseThemeColors->isChecked());
}

void CUVProgressSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if (const QString senderName = sender()->objectName(); "progressColorToolButton" == senderName) {
			m_pProgress->setProgressColor(color);
			m_pLeProgressColor->setText(color.name(QColor::HexRgb));
		} else if ("backgroundColorToolButton" == senderName) {
			m_pProgress->setBackgroundColor(color);
			m_pLeBackgroundColor->setText(color.name(QColor::HexRgb));
		}
	}
	setupForm();
}
