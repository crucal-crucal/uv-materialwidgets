#include "uvtabssettingseditor.hpp"


CUVTabsSettingsEditor::CUVTabsSettingsEditor(QWidget* parent): QWidget(parent), m_ptabs(new CUVMaterialTabs(this)) {
	createCtrl();
	customLayout();
	initData();
}

CUVTabsSettingsEditor::~CUVTabsSettingsEditor() = default;

void CUVTabsSettingsEditor::createCtrl() {
	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");

	m_ptabs->setFixedWidth(500);

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVTabsSettingsEditor::customLayout() const {
	m_pVLayBottom->addWidget(m_ptabs);
	m_pVLayBottom->setAlignment(m_ptabs, Qt::AlignHCenter);

	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVTabsSettingsEditor::initData() const {
	m_ptabs->addTab("Tab 1");
	m_ptabs->addTab("Tab 2");
	m_ptabs->addTab("Tab 3");
	m_ptabs->addTab("Tab 4");
	m_ptabs->addTab("Tab 5");
}
