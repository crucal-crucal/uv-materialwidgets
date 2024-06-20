#include "uvmessagebtnsettingseditor.hpp"

#include "uvmaterialmessagebar/uvmaterialmessagebar.hpp"

CUVMessageBtnSettingsEditor::CUVMessageBtnSettingsEditor(QWidget* parent): QWidget(parent) {
	createCtrl();
	customLayout();
}

CUVMessageBtnSettingsEditor::~CUVMessageBtnSettingsEditor() = default;

void CUVMessageBtnSettingsEditor::createCtrl() {
	m_pBtnSuccess = new CUVMaterialMessageButton("Success", this);
	m_pBtnSuccess->setBarTitle("Success");
	m_pBtnSuccess->setBarText("Successfully message ...");

	m_pBtnError = new CUVMaterialMessageButton("Error", UVMessageBarType::Error, this);
	m_pBtnError->setBarTitle("Error");
	m_pBtnError->setBarText("Error message ...");
	m_pBtnError->setPositionPolicy(UVMessageBarType::BottomRight);

	m_pBtnWaring = new CUVMaterialMessageButton("Waring", UVMessageBarType::Warning, this);
	m_pBtnWaring->setBarTitle("Waring");
	m_pBtnWaring->setBarText("Waring message ...");
	m_pBtnWaring->setPositionPolicy(UVMessageBarType::BottomLeft);

	m_pBtnInfo = new CUVMaterialMessageButton("Infomation", UVMessageBarType::Info, this);
	m_pBtnInfo->setBarTitle("Infomation");
	m_pBtnInfo->setBarText("Infomation message ...");
	m_pBtnInfo->setPositionPolicy(UVMessageBarType::TopRight);

	m_pBtnTest = new QPushButton("Test", this);
	connect(m_pBtnTest, &QPushButton::clicked, this, [this]() {
		CUVMaterialMessageBar::success("test test test test", "test message ...", 2000, UVMessageBarType::PositionPolicy::Top, window());
	});

	m_pHLayBtn = new QHBoxLayout;
	m_pVLayCenter = new QVBoxLayout;

	this->setLayout(m_pVLayCenter);
}

void CUVMessageBtnSettingsEditor::customLayout() const {
	m_pHLayBtn->addWidget(m_pBtnSuccess);
	m_pHLayBtn->addWidget(m_pBtnError);
	m_pHLayBtn->addWidget(m_pBtnWaring);
	m_pHLayBtn->addWidget(m_pBtnInfo);
	m_pHLayBtn->addWidget(m_pBtnTest);

	m_pHLayBtn->setAlignment(Qt::AlignCenter);

	m_pVLayCenter->addLayout(m_pHLayBtn);
	m_pVLayCenter->setAlignment(Qt::AlignCenter);
}
