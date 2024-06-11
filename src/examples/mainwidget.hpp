#pragma once

#include <QListWidget>
#include <QMainWindow>
#include <QStackedLayout>

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
#include "uvprogresssettingseditor/uvprogresssettingseditor.hpp"
#include "uvradiobuttonsettingseditor/uvradiobuttonsettingseditor.hpp"
#include "uvscrollbarsettingseditor/uvscrollbarsettingseditor.hpp"
#include "uvslidersettingseditor/uvslidersettingseditor.hpp"
#include "uvsnackbarsettingseditor/uvsnackbarsettingseditor.hpp"
#include "uvtabssettingseditor/uvtabssettingseditor.hpp"
#include "uvtogglesettingseditor/uvtogglesettingseditor.hpp"
#include "uvwatingwidgetsettingseditor/uvwatingwidgetsettingseditor.hpp"
#include "uvswitchbtnsettingseditor/uvswitchbtnsettingseditor.hpp"

class MainWidget final : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWidget(QWidget* parent = nullptr);
	~MainWidget() override;

private:
	void createCtrl();
	void customLayout() const;
	void initConnection();
	void initData() const;

private:
	QWidget* m_pCenterWidget{ nullptr };
	QListWidget* m_pListWidget{ nullptr };

	QHBoxLayout* m_pHBoxLayout{ nullptr };
	QStackedLayout* m_pStackedLayout{ nullptr };

private:
	CUVAppBarSettingsEditor* m_pAppBarSettingsEditor{ nullptr };
	CUVAutoCompleteSettingsEditor* m_pAutoCompleteSettingsEditor{ nullptr };
	CUVAvatarSettingsEditor* m_pAvatarSettingsEditor{ nullptr };
	CUVBadgeSettingsEditor* m_pBadgeSettingsEditor{ nullptr };
	CUVCheckBoxSettingsEditor* m_pCheckBoxSettingsEditor{ nullptr };
	CUVCircularProgressSettingsEditor* m_pCircularProgressSettingsEditor{ nullptr };
	CUVFabSettingsEditor* m_pFabSettingsEditor{ nullptr };
	CUVFlatButtonSettingsEditor* m_pFloatingActionButtonSettingsEditor{ nullptr };
	CUVDialogSettingsEditor* m_pDialogSettingsEditor{ nullptr };
	CUVDrawerSettingsEditor* m_pDrawerSettingsEditor{ nullptr };
	CUVIconButtonSettingsEditor* m_pIconButtonSettingsEditor{ nullptr };
	CUVProgressSettingsEditor* m_pProgressSettingsEditor{ nullptr };
	CUVRadioButtonSettingsEditor* m_pRadioButtonSettingsEditor{ nullptr };
	CUVScrollBarSettingsEditor* m_pScrollBarSettingsEditor{ nullptr };
	CUVSliderSettingsEditor* m_pSliderSettingsEditor{ nullptr };
	CUVSnackBarSettingsEditor* m_pSnackBarSettingsEditor{ nullptr };
	CUVTabsSettingsEditor* m_pTabsSettingsEditor{ nullptr };
	CUVToggleSettingsEditor* m_pToggleSettingsEditor{ nullptr };
	CUVWatingWidgetSettingsEditor* m_pWatingWidgetSettingsEditor{ nullptr };
	CUVSwitchBtnSettingsEditor* m_pSwitchBtnSettingsEditor{ nullptr };
};
