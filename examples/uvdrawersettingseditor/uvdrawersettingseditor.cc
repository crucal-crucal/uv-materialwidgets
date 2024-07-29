#include "uvdrawersettingseditor.hpp"

CUVDrawerSettingsEditor::CUVDrawerSettingsEditor(QWidget* parent): QWidget(parent), m_pdrawer(new CUVMaterialDrawer) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVDrawerSettingsEditor::~CUVDrawerSettingsEditor() = default;

void CUVDrawerSettingsEditor::createCtrl() {
	m_pLbOverlayMode = new QLabel(tr("Overlay Mode"), this);
	m_pLbOverlayMode->setFixedWidth(m_nLabelWidth);
	m_pCbOverlayMode = new QCheckBox(this);

	m_pLbClickToClose = new QLabel(tr("Click to Close"), this);
	m_pLbClickToClose->setFixedWidth(m_nLabelWidth);
	m_pCbClickToClose = new QCheckBox(this);

	m_pBtnShowDrawer = new QPushButton(tr("Show Drawer"), this);
	m_pBtnHideDrawer = new QPushButton(tr("Hide Drawer"), this);

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");
	m_pdrawer->setParent(m_pcanvas);
	m_pdrawer->setClickOutsideToClose(true);
	m_pdrawer->setOverlayMode(true);

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayOverlayMode = new QHBoxLayout;
	m_pHLayClickToClose = new QHBoxLayout;
	m_pHLayShowHide = new QHBoxLayout;

	m_pVLayDrawer = new QVBoxLayout;

	m_pdrawer->setDrawerLayout(m_pVLayDrawer);
	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVDrawerSettingsEditor::customLayout() {
	m_pHLayOverlayMode->addWidget(m_pLbOverlayMode);
	m_pHLayOverlayMode->addWidget(m_pCbOverlayMode);
	m_pHLayOverlayMode->addStretch();

	m_pHLayClickToClose->addWidget(m_pLbClickToClose);
	m_pHLayClickToClose->addWidget(m_pCbClickToClose);
	m_pHLayClickToClose->addStretch();

	m_pHLayShowHide->addWidget(m_pBtnShowDrawer);
	m_pHLayShowHide->addWidget(m_pBtnHideDrawer);
	m_pHLayShowHide->addStretch();

	m_pVLayCenter->addLayout(m_pHLayOverlayMode);
	m_pVLayCenter->addLayout(m_pHLayClickToClose);
	m_pVLayCenter->addLayout(m_pHLayShowHide);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVDrawerSettingsEditor::initData() {
	std::vector<QString> labels;
	labels.reserve(10);
	for (int i = 0; i < 10; i++) {
		labels.emplace_back(QString("test %1").arg(i));
	}

	for (auto& text : labels) {
		auto label = new QLabel(text);
		label->setMinimumHeight(30);
		label->setFont(QFont("Roboto", 10, QFont::Medium));
		m_pVLayDrawer->addWidget(label);
	}

	m_pVLayDrawer->addStretch(3);
	m_pdrawer->setContentsMargins(10, 0, 0, 0);

	m_pVLayDrawer->addWidget(new QPushButton("abc"));
}

void CUVDrawerSettingsEditor::initConnection() {
	connect(m_pCbOverlayMode, &QCheckBox::toggled, this, &CUVDrawerSettingsEditor::updateWidget);
	connect(m_pCbClickToClose, &QCheckBox::toggled, this, &CUVDrawerSettingsEditor::updateWidget);
	connect(m_pBtnShowDrawer, &QPushButton::clicked, m_pdrawer, &CUVMaterialDrawer::openDrawer);
	connect(m_pBtnHideDrawer, &QPushButton::clicked, m_pdrawer, &CUVMaterialDrawer::closeDrawer);
}

void CUVDrawerSettingsEditor::setupForm() {
	m_pCbOverlayMode->setChecked(m_pdrawer->overlayMode());
	m_pCbClickToClose->setChecked(m_pdrawer->clickOutsideToClose());
}

void CUVDrawerSettingsEditor::updateWidget() {
	m_pdrawer->setOverlayMode(m_pCbOverlayMode->isChecked());
	m_pdrawer->setClickOutsideToClose(m_pCbClickToClose->isChecked());
}
