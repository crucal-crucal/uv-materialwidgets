#pragma once

#include <QListWidget>
#include <QMainWindow>
#include <QStackedLayout>

class CUVStackWidgetSettingsEditor;
class CUVComboBoxSettingsEditor;
class CUVMessageBtnSettingsEditor;
class CUVToggleSwitchSettingsEditor;
class CUVSwitchBtnSettingsEditor;
class CUVWatingWidgetSettingsEditor;
class CUVToggleSettingsEditor;
class CUVTabsSettingsEditor;
class CUVSnackBarSettingsEditor;
class CUVSliderSettingsEditor;
class CUVScrollBarSettingsEditor;
class CUVAppBarSettingsEditor;
class CUVAutoCompleteSettingsEditor;
class CUVAvatarSettingsEditor;
class CUVBadgeSettingsEditor;
class CUVCheckBoxSettingsEditor;
class CUVCircularProgressSettingsEditor;
class CUVFabSettingsEditor;
class CUVFlatButtonSettingsEditor;
class CUVDialogSettingsEditor;
class CUVDrawerSettingsEditor;
class CUVIconButtonSettingsEditor;
class CUVProgressSettingsEditor;
class CUVRadioButtonSettingsEditor;

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
	CUVToggleSwitchSettingsEditor* m_pToggleSwitchSettingsEditor{ nullptr };
	CUVMessageBtnSettingsEditor* m_pMessageBarSettingsEditor{ nullptr };
	CUVComboBoxSettingsEditor* m_pComboxBoxSettingsEditor{ nullptr };
	CUVStackWidgetSettingsEditor* m_pStackWidgetSettingsEditor{ nullptr };
};
