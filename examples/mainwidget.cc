#include "mainwidget.hpp"

#include "uvappbarsettingseditor/uvappbarsettingseditor.hpp"
#include "uvautocompletesettingseditor/uvautocompletesettingseditor.hpp"
#include "uvavatarsettingseditor/uvavatarsettingseditor.hpp"
#include "uvbadgesettingseditor/uvbadgesettingseditor.hpp"
#include "uvcheckboxsettingseditor/uvcheckboxsettingseditor.hpp"
#include "uvcircularprogresssettingseditor/uvcircularprogresssettingseditor.hpp"
#include "uvdialogsettingseditor/uvdialogsettingseditor.hpp"
#include "uvdrawersettingseditor/uvdrawersettingseditor.hpp"
#include "uvfabsettingseditor/uvfabsettingseditor.hpp"
#include "uvflatbuttonsettingseditor/uvflatbuttonsettingseditor.hpp"
#include "uviconbuttonsettingseditor/uviconbuttonsettingseditor.hpp"
#include "uvmessagebtnsettingseditor/uvmessagebtnsettingseditor.hpp"
#include "uvprogresssettingseditor/uvprogresssettingseditor.hpp"
#include "uvradiobuttonsettingseditor/uvradiobuttonsettingseditor.hpp"
#include "uvscrollbarsettingseditor/uvscrollbarsettingseditor.hpp"
#include "uvslidersettingseditor/uvslidersettingseditor.hpp"
#include "uvsnackbarsettingseditor/uvsnackbarsettingseditor.hpp"
#include "uvswitchbtnsettingseditor/uvswitchbtnsettingseditor.hpp"
#include "uvtabssettingseditor/uvtabssettingseditor.hpp"
#include "uvtogglesettingseditor/uvtogglesettingseditor.hpp"
#include "uvtoggleswitchsettingseditor/uvtoggleswitchsettingseditor.hpp"
#include "uvwatingwidgetsettingseditor/uvwatingwidgetsettingseditor.hpp"
#include "uvcomboboxsettingseditor/uvcomboboxsettingseditor.hpp"

MainWidget::MainWidget(QWidget* parent): QMainWindow(parent) {
	createCtrl();
	customLayout();
	initConnection();
	initData();
	resize(800, 600);
}

MainWidget::~MainWidget() = default;

void MainWidget::createCtrl() {
	m_pCenterWidget = new QWidget(this);
	m_pListWidget = new QListWidget(this);
	m_pListWidget->setFixedWidth(200);

	m_pAppBarSettingsEditor = new CUVAppBarSettingsEditor(this);
	m_pAutoCompleteSettingsEditor = new CUVAutoCompleteSettingsEditor(this);
	m_pAvatarSettingsEditor = new CUVAvatarSettingsEditor(this);
	m_pBadgeSettingsEditor = new CUVBadgeSettingsEditor(this);
	m_pCheckBoxSettingsEditor = new CUVCheckBoxSettingsEditor(this);
	m_pCircularProgressSettingsEditor = new CUVCircularProgressSettingsEditor(this);
	m_pFabSettingsEditor = new CUVFabSettingsEditor(this);
	m_pFloatingActionButtonSettingsEditor = new CUVFlatButtonSettingsEditor(this);
	m_pDialogSettingsEditor = new CUVDialogSettingsEditor(this);
	m_pDrawerSettingsEditor = new CUVDrawerSettingsEditor(this);
	m_pIconButtonSettingsEditor = new CUVIconButtonSettingsEditor(this);
	m_pProgressSettingsEditor = new CUVProgressSettingsEditor(this);
	m_pRadioButtonSettingsEditor = new CUVRadioButtonSettingsEditor(this);
	m_pScrollBarSettingsEditor = new CUVScrollBarSettingsEditor(this);
	m_pSliderSettingsEditor = new CUVSliderSettingsEditor(this);
	m_pSnackBarSettingsEditor = new CUVSnackBarSettingsEditor(this);
	m_pTabsSettingsEditor = new CUVTabsSettingsEditor(this);
	m_pToggleSettingsEditor = new CUVToggleSettingsEditor(this);
	m_pWatingWidgetSettingsEditor = new CUVWatingWidgetSettingsEditor(this);
	m_pSwitchBtnSettingsEditor = new CUVSwitchBtnSettingsEditor(this);
	m_pToggleSwitchSettingsEditor = new CUVToggleSwitchSettingsEditor(this);
	m_pMessageBarSettingsEditor = new CUVMessageBtnSettingsEditor(this);
	m_pComboxBoxSettingsEditor = new CUVComboBoxSettingsEditor(this);

	m_pHBoxLayout = new QHBoxLayout;
	m_pStackedLayout = new QStackedLayout;

	setCentralWidget(m_pCenterWidget);
	m_pCenterWidget->setLayout(m_pHBoxLayout);
}

void MainWidget::customLayout() const {
	m_pHBoxLayout->addWidget(m_pListWidget);
	m_pHBoxLayout->addLayout(m_pStackedLayout);

	m_pStackedLayout->addWidget(m_pAppBarSettingsEditor);
	m_pStackedLayout->addWidget(m_pAutoCompleteSettingsEditor);
	m_pStackedLayout->addWidget(m_pAvatarSettingsEditor);
	m_pStackedLayout->addWidget(m_pBadgeSettingsEditor);
	m_pStackedLayout->addWidget(m_pCheckBoxSettingsEditor);
	m_pStackedLayout->addWidget(m_pCircularProgressSettingsEditor);
	m_pStackedLayout->addWidget(m_pWatingWidgetSettingsEditor);
	m_pStackedLayout->addWidget(m_pFabSettingsEditor);
	m_pStackedLayout->addWidget(m_pFloatingActionButtonSettingsEditor);
	m_pStackedLayout->addWidget(m_pDialogSettingsEditor);
	m_pStackedLayout->addWidget(m_pDrawerSettingsEditor);
	m_pStackedLayout->addWidget(m_pIconButtonSettingsEditor);
	m_pStackedLayout->addWidget(m_pProgressSettingsEditor);
	m_pStackedLayout->addWidget(m_pRadioButtonSettingsEditor);
	m_pStackedLayout->addWidget(m_pScrollBarSettingsEditor);
	m_pStackedLayout->addWidget(m_pSliderSettingsEditor);
	m_pStackedLayout->addWidget(m_pSnackBarSettingsEditor);
	m_pStackedLayout->addWidget(m_pTabsSettingsEditor);
	m_pStackedLayout->addWidget(m_pToggleSettingsEditor);
	m_pStackedLayout->addWidget(m_pSwitchBtnSettingsEditor);
	m_pStackedLayout->addWidget(m_pToggleSwitchSettingsEditor);
	m_pStackedLayout->addWidget(m_pMessageBarSettingsEditor);
	m_pStackedLayout->addWidget(m_pComboxBoxSettingsEditor);
}

void MainWidget::initConnection() {
	connect(m_pListWidget, &QListWidget::currentItemChanged, this, [=](const QListWidgetItem* current, const QListWidgetItem* previous) {
		Q_UNUSED(current)
		Q_UNUSED(previous);
		m_pStackedLayout->setCurrentIndex(m_pListWidget->currentRow());
	});
}

void MainWidget::initData() const {
	m_pListWidget->addItem("App Bar");
	m_pListWidget->addItem("Auto Complete");
	m_pListWidget->addItem("Avatar");
	m_pListWidget->addItem("Badge");
	m_pListWidget->addItem("Checkbox");
	m_pListWidget->addItem("Circular Progress");
	m_pListWidget->addItem("Waiting Widget");
	m_pListWidget->addItem("Floating Action Button");
	m_pListWidget->addItem("Flat Button");
	m_pListWidget->addItem("Dialog");
	m_pListWidget->addItem("Drawer");
	m_pListWidget->addItem("Icon Button");
	m_pListWidget->addItem("Progress");
	m_pListWidget->addItem("Radio Button");
	m_pListWidget->addItem("ScrollBar");
	m_pListWidget->addItem("Slider");
	m_pListWidget->addItem("Snackbar");
	m_pListWidget->addItem("Tabs");
	m_pListWidget->addItem("Toggle");
	m_pListWidget->addItem("Switch Button");
	m_pListWidget->addItem("Toggle Switch");
	m_pListWidget->addItem("Message Button");
	m_pListWidget->addItem("ComboBox");

	m_pListWidget->setCurrentRow(0);
}
