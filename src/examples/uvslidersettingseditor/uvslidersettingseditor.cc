#include "uvslidersettingseditor.hpp"

CUVSliderSettingsEditor::CUVSliderSettingsEditor(QWidget* parent): QWidget(parent), m_pSlider(new CUVMaterialSlider) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVSliderSettingsEditor::~CUVSliderSettingsEditor() = default;

void CUVSliderSettingsEditor::createCtrl() {
	m_pLbDisabled = new QLabel(tr("Disabled"), this);
	m_pLbDisabled->setFixedWidth(m_nLabelWidth);
	m_pCbDisabled = new QCheckBox(this);

	m_pLbValue = new QLabel(tr("Value"), this);
	m_pLbValue->setFixedWidth(m_nLabelWidth);
	m_pLeValue = new QLineEdit(this);

	m_pLbOrientation = new QLabel(tr("Orientation"), this);
	m_pLbOrientation->setFixedWidth(m_nLabelWidth);
	m_pCbOrientation = new QComboBox(this);

	m_pLbInverted = new QLabel(tr("Inverted"), this);
	m_pLbInverted->setFixedWidth(m_nLabelWidth);
	m_pCbInverted = new QCheckBox(this);

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayDisabled = new QHBoxLayout;
	m_pHLayValue = new QHBoxLayout;
	m_pHLayOrientation = new QHBoxLayout;
	m_pHLayInverted = new QHBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVSliderSettingsEditor::customLayout() const {
	m_pHLayDisabled->addWidget(m_pLbDisabled);
	m_pHLayDisabled->addWidget(m_pCbDisabled);
	m_pHLayDisabled->addStretch();

	m_pHLayValue->addWidget(m_pLbValue);
	m_pHLayValue->addWidget(m_pLeValue);
	m_pHLayValue->addStretch();

	m_pHLayOrientation->addWidget(m_pLbOrientation);
	m_pHLayOrientation->addWidget(m_pCbOrientation);
	m_pHLayOrientation->addStretch();

	m_pHLayInverted->addWidget(m_pLbInverted);
	m_pHLayInverted->addWidget(m_pCbInverted);
	m_pHLayInverted->addStretch();

	m_pVLayBottom->addWidget(m_pSlider);
	m_pVLayBottom->setAlignment(m_pSlider, Qt::AlignCenter);

	m_pVLayCenter->addLayout(m_pHLayDisabled);
	m_pVLayCenter->addLayout(m_pHLayValue);
	m_pVLayCenter->addLayout(m_pHLayOrientation);
	m_pVLayCenter->addLayout(m_pHLayInverted);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVSliderSettingsEditor::initData() const {
	m_pCbOrientation->addItem("Horizontal", Qt::Horizontal);
	m_pCbOrientation->addItem("Vertical", Qt::Vertical);
}

void CUVSliderSettingsEditor::initConnection() {
	connect(m_pCbDisabled, &QCheckBox::toggled, this, &CUVSliderSettingsEditor::updateWidget);
	connect(m_pLeValue, &QLineEdit::textChanged, this, &CUVSliderSettingsEditor::updateWidget);
	connect(m_pCbOrientation, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVSliderSettingsEditor::updateWidget);
	connect(m_pCbInverted, &QCheckBox::toggled, this, &CUVSliderSettingsEditor::updateWidget);
	connect(m_pSlider, &CUVMaterialSlider::valueChanged, this, &CUVSliderSettingsEditor::setupForm);
}

void CUVSliderSettingsEditor::setupForm() const {
	switch (m_pSlider->orientation()) {
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

	m_pCbDisabled->setChecked(!m_pSlider->isEnabled());
	m_pLeValue->setText(QString::number(m_pSlider->value()));
	m_pCbInverted->setChecked(m_pSlider->invertedAppearance());
}

void CUVSliderSettingsEditor::updateWidget() const {
	switch (m_pCbOrientation->currentIndex()) {
		case 0: {
			m_pSlider->setOrientation(Qt::Horizontal);
			break;
		}
		case 1: {
			m_pSlider->setOrientation(Qt::Vertical);
			break;
		}
		default: break;
	}

	m_pSlider->setDisabled(m_pCbDisabled->isChecked());
	m_pSlider->setValue(m_pLeValue->text().toInt());
	m_pSlider->setInvertedAppearance(m_pCbInverted->isChecked());
}
