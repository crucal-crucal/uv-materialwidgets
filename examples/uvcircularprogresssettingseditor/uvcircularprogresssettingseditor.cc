#include "uvcircularprogresssettingseditor.hpp"

#include <QColorDialog>

CUVCircularProgressSettingsEditor::CUVCircularProgressSettingsEditor(QWidget* parent)
: QWidget(parent), m_pProgress(new CUVMaterialCircularProgress) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVCircularProgressSettingsEditor::~CUVCircularProgressSettingsEditor() = default;

void CUVCircularProgressSettingsEditor::createCtrl() {
	m_pLbDisable = new QLabel(tr("Disable"), this);
	m_pLbDisable->setFixedWidth(m_nLabelWidth);
	m_pCbDisable = new QCheckBox(this);

	m_pLbProgressType = new QLabel(tr("Progress Type"), this);
	m_pLbProgressType->setFixedWidth(m_nLabelWidth);
	m_pCbProgressType = new QComboBox(this);

	m_pLbProgress = new QLabel(tr("Progress"), this);
	m_pLbProgress->setFixedWidth(m_nLabelWidth);
	m_pSlProgress = new QSlider(Qt::Horizontal, this);

	m_pLbLineWidth = new QLabel(tr("Line Width"), this);
	m_pLbLineWidth->setFixedWidth(m_nLabelWidth);
	m_pDSBLineWidth = new QDoubleSpinBox(this);

	m_pLbSize = new QLabel(tr("Size"), this);
	m_pLbSize->setFixedWidth(m_nLabelWidth);
	m_pSBSize = new QSpinBox(this);

	m_pLbUseThemeColors = new QLabel(tr("Use Theme Colors"), this);
	m_pLbUseThemeColors->setFixedWidth(m_nLabelWidth);
	m_pCbUseThemeColors = new QCheckBox(this);

	m_pLbColor = new QLabel(tr("Color"), this);
	m_pLbColor->setFixedWidth(m_nLabelWidth);
	m_pLeColor = new QLineEdit(this);
	m_pTbColor = new QToolButton(this);
	m_pTbColor->setObjectName("colorToolButton");
	m_pTbColor->setText("...");

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: white");

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayDisable = new QHBoxLayout;
	m_pHLayProgressType = new QHBoxLayout;
	m_pHLayProgress = new QHBoxLayout;
	m_pHLayLineWidth = new QHBoxLayout;
	m_pHLaySize = new QHBoxLayout;
	m_pHLayUseThemeColors = new QHBoxLayout;
	m_pHLayColor = new QHBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVCircularProgressSettingsEditor::customLayout() const {
	m_pHLayDisable->addWidget(m_pLbDisable);
	m_pHLayDisable->addWidget(m_pCbDisable);
	m_pHLayDisable->addStretch();

	m_pHLayProgressType->addWidget(m_pLbProgressType);
	m_pHLayProgressType->addWidget(m_pCbProgressType);
	m_pHLayProgressType->addStretch();

	m_pHLayProgress->addWidget(m_pLbProgress);
	m_pHLayProgress->addWidget(m_pSlProgress);
	m_pHLayProgress->addStretch();

	m_pHLayLineWidth->addWidget(m_pLbLineWidth);
	m_pHLayLineWidth->addWidget(m_pDSBLineWidth);
	m_pHLayLineWidth->addStretch();

	m_pHLaySize->addWidget(m_pLbSize);
	m_pHLaySize->addWidget(m_pSBSize);
	m_pHLaySize->addStretch();

	m_pHLayUseThemeColors->addWidget(m_pLbUseThemeColors);
	m_pHLayUseThemeColors->addWidget(m_pCbUseThemeColors);
	m_pHLayUseThemeColors->addStretch();

	m_pHLayColor->addWidget(m_pLbColor);
	m_pHLayColor->addWidget(m_pLeColor);
	m_pHLayColor->addWidget(m_pTbColor);
	m_pHLayColor->addStretch();

	m_pVLayBottom->addWidget(m_pProgress);
	m_pVLayBottom->setAlignment(m_pProgress, Qt::AlignHCenter);

	m_pVLayCenter->addLayout(m_pHLayDisable);
	m_pVLayCenter->addLayout(m_pHLayProgressType);
	m_pVLayCenter->addLayout(m_pHLayProgress);
	m_pVLayCenter->addLayout(m_pHLayLineWidth);
	m_pVLayCenter->addLayout(m_pHLaySize);
	m_pVLayCenter->addLayout(m_pHLayUseThemeColors);
	m_pVLayCenter->addLayout(m_pHLayColor);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVCircularProgressSettingsEditor::initConnection() {
	connect(m_pCbDisable, &QCheckBox::clicked, this, &CUVCircularProgressSettingsEditor::updateWidget);
	connect(m_pCbProgressType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVCircularProgressSettingsEditor::updateWidget);
	connect(m_pSlProgress, &QSlider::valueChanged, this, &CUVCircularProgressSettingsEditor::updateWidget);
	connect(m_pDSBLineWidth, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CUVCircularProgressSettingsEditor::updateWidget);
	connect(m_pSBSize, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVCircularProgressSettingsEditor::updateWidget);
	connect(m_pCbUseThemeColors, &QCheckBox::clicked, this, &CUVCircularProgressSettingsEditor::updateWidget);
	connect(m_pTbColor, &QToolButton::clicked, this, &CUVCircularProgressSettingsEditor::selectColor);
}

void CUVCircularProgressSettingsEditor::initData() const {
	m_pSBSize->setRange(10, 200);
	m_pSlProgress->setRange(0, 100);

	m_pCbProgressType->addItem("DeterminateProgress");
	m_pCbProgressType->addItem("IndeterminateProgress");
}

void CUVCircularProgressSettingsEditor::setupForm() const {
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

	m_pCbDisable->setChecked(!m_pProgress->isEnabled());
	m_pSlProgress->setValue(m_pProgress->value());
	m_pDSBLineWidth->setValue(m_pProgress->lineWidth());
	m_pSBSize->setValue(m_pProgress->Size());
	m_pCbUseThemeColors->setChecked(m_pProgress->useThemeColors());
}

void CUVCircularProgressSettingsEditor::updateWidget() const {
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

	m_pProgress->setDisabled(m_pCbDisable->isChecked());
	m_pProgress->setValue(m_pSlProgress->value());
	m_pProgress->setLineWidth(m_pDSBLineWidth->value());
	m_pProgress->setSize(m_pSBSize->value());
	m_pProgress->setUseThemeColors(m_pCbUseThemeColors->isChecked());
}

void CUVCircularProgressSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if ("colorToolButton" == sender()->objectName()) {
			m_pProgress->setColor(color);
			m_pLeColor->setText(color.name(QColor::HexRgb));
		}
	}
	setupForm();
}
