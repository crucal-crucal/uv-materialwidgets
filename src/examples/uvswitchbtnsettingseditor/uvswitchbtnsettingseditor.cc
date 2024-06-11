#include "uvswitchbtnsettingseditor.hpp"

CUVSwitchBtnSettingsEditor::CUVSwitchBtnSettingsEditor(QWidget* parent): QWidget(parent), m_pswitchBtn(new CUVSwitchButton(this)) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVSwitchBtnSettingsEditor::~CUVSwitchBtnSettingsEditor() = default;

void CUVSwitchBtnSettingsEditor::createCtrl() {
	m_pLbChecked = new QLabel(tr("Checked"), this);
	m_pCbChecked = new QCheckBox(this);

	m_pLbTextPosition = new QLabel(tr("Text position"), this);
	m_pCbTextPosition = new QComboBox(this);

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: white");

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayChecked = new QHBoxLayout;
	m_pHLayTextPosition = new QHBoxLayout;

	m_pswitchBtn->setFixedSize(150, 40);

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVSwitchBtnSettingsEditor::customLayout() const {
	m_pHLayChecked->addWidget(m_pLbChecked);
	m_pHLayChecked->addWidget(m_pCbChecked);
	m_pHLayChecked->addStretch();

	m_pHLayTextPosition->addWidget(m_pLbTextPosition);
	m_pHLayTextPosition->addWidget(m_pCbTextPosition);
	m_pHLayTextPosition->addStretch();

	m_pVLayBottom->addWidget(m_pswitchBtn);
	m_pVLayBottom->setAlignment(m_pswitchBtn, Qt::AlignHCenter);

	m_pVLayCenter->addLayout(m_pHLayChecked);
	m_pVLayCenter->addLayout(m_pHLayTextPosition);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVSwitchBtnSettingsEditor::initData() const {
	m_pCbTextPosition->addItem("Center");
	m_pCbTextPosition->addItem("Left");
	m_pCbTextPosition->addItem("Right");
}

void CUVSwitchBtnSettingsEditor::initConnection() {
	connect(m_pCbChecked, &QCheckBox::toggled, this, &CUVSwitchBtnSettingsEditor::updateWidget);
	connect(m_pCbTextPosition, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVSwitchBtnSettingsEditor::updateWidget);
}

void CUVSwitchBtnSettingsEditor::setupForm() const {
	m_pCbChecked->setChecked(m_pswitchBtn->status());
	switch (m_pswitchBtn->textPosition()) {
		case CUVSwitchButton::TextPosition::Center: {
			m_pCbTextPosition->setCurrentIndex(0);
			break;
		}
		case CUVSwitchButton::TextPosition::Left: {
			m_pCbTextPosition->setCurrentIndex(1);
			break;
		}
		case CUVSwitchButton::TextPosition::Right: {
			m_pCbTextPosition->setCurrentIndex(2);
			break;
		}
		default: break;
	}
}

void CUVSwitchBtnSettingsEditor::updateWidget() const {
	m_pswitchBtn->setChecked(m_pCbChecked->isChecked());
	switch (m_pCbTextPosition->currentIndex()) {
		case 0: {
			m_pswitchBtn->setTextPosition(CUVSwitchButton::TextPosition::Center);
			break;
		}
		case 1: {
			m_pswitchBtn->setTextPosition(CUVSwitchButton::TextPosition::Left);
			break;
		}
		case 2: {
			m_pswitchBtn->setTextPosition(CUVSwitchButton::TextPosition::Right);
			break;
		}
		default: break;
	}
}
