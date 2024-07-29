#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmaterialflatbutton/uvmaterialflatbutton.hpp"

#ifdef CUVFAGBUTTONSETTINGSEDITOR_LIB
#define CUVFAGBUTTONSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVFAGBUTTONSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVFAGBUTTONSETTINGSEDITOR_EXPORT CUVFlatButtonSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVFlatButtonSettingsEditor(QWidget* parent = nullptr);

	~CUVFlatButtonSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initData() const;
	void initConnection();

protected slots:
	void setupForm() const;
	void updateWidget() const;
	void selectColor();
	void applyDefaultPreset() const;
	void applyCheckablePreset() const;

private:
	// Interface
	QLabel* m_pLbDisable{ nullptr };
	QCheckBox* m_pCbDisable{ nullptr };

	QLabel* m_pLbCheckable{ nullptr };
	QCheckBox* m_pCbCheckable{ nullptr };

	QLabel* m_pLbChecked{ nullptr };
	QCheckBox* m_pCbChecked{ nullptr };

	QLabel* m_pLbShowHalo{ nullptr };
	QCheckBox* m_pCbShowHalo{ nullptr };

	QLabel* m_pLbTransparent{ nullptr };
	QCheckBox* m_pCbTransparent{ nullptr };

	QLabel* m_pLbIcon{ nullptr };
	QCheckBox* m_pCbIcon{ nullptr };

	QLabel* m_pLbButtonRole{ nullptr };
	QComboBox* m_pCbButtonRole{ nullptr };

	QLabel* m_pLbRippleStyle{ nullptr };
	QComboBox* m_pCbRippleStyle{ nullptr };

	QLabel* m_pLbHoverStyle{ nullptr };
	QComboBox* m_pCbHoverStyle{ nullptr };

	QLabel* m_pLbIconPlacement{ nullptr };
	QComboBox* m_pCbIconPlacement{ nullptr };

	QLabel* m_pLbCornerRadius{ nullptr };
	QSpinBox* m_pSpCornerRadius{ nullptr };

	QLabel* m_pLbTextAlignment{ nullptr };
	QComboBox* m_pCbTextAlignment{ nullptr };

	QLabel* m_pLbOverlayOpacity{ nullptr };
	QDoubleSpinBox* m_pDSpOverlayOpacity{ nullptr };

	QLabel* m_pLbIconSize{ nullptr };
	QSpinBox* m_pSpIconSize{ nullptr };

	QLabel* m_pLbFontSize{ nullptr };
	QDoubleSpinBox* m_pDSpFontSize{ nullptr };

	QLabel* m_pLbButtonText{ nullptr };
	QLineEdit* m_pLeButtonText{ nullptr };

	QLabel* m_pLbUseThemeColors{ nullptr };
	QCheckBox* m_pCbUseThemeColors{ nullptr };

	QLabel* m_pLbBackgroundColor{ nullptr };
	QLineEdit* m_pLeBackgroundColor{ nullptr };
	QToolButton* m_pTbBackgroundColor{ nullptr };

	QLabel* m_pLbForegroundColor{ nullptr };
	QLineEdit* m_pLeForegroundColor{ nullptr };
	QToolButton* m_pTbForegroundColor{ nullptr };

	QLabel* m_pLbOverlayColor{ nullptr };
	QLineEdit* m_pLeOverlayColor{ nullptr };
	QToolButton* m_pTbOverlayColor{ nullptr };

	QLabel* m_pLbDisabledBgColor{ nullptr };
	QLineEdit* m_pLeDisabledBgColor{ nullptr };
	QToolButton* m_pTbDisabledBgColor{ nullptr };

	QLabel* m_pLbDisableFgColor{ nullptr };
	QLineEdit* m_pLeDisableFgColor{ nullptr };
	QToolButton* m_pTbDisableFgColor{ nullptr };

	QPushButton* m_pBtnApplyDefaultPreset{ nullptr };
	QPushButton* m_pBtnApplyCheckablePreset{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayDisabled{ nullptr };
	QHBoxLayout* m_pHLayCheckable{ nullptr };
	QHBoxLayout* m_pHLayChecked{ nullptr };
	QHBoxLayout* m_pHLayShowHalo{ nullptr };
	QHBoxLayout* m_pHLayTransparent{ nullptr };
	QHBoxLayout* m_pHLayIcon{ nullptr };

	QHBoxLayout* m_pHLayButtonRole{ nullptr };
	QHBoxLayout* m_pHLayRippleStyle{ nullptr };
	QHBoxLayout* m_pHLayHoverStyle{ nullptr };
	QHBoxLayout* m_pHLayIconPlacement{ nullptr };
	QHBoxLayout* m_pHLayCornerRadius{ nullptr };
	QHBoxLayout* m_pHLayTextAlignment{ nullptr };
	QHBoxLayout* m_pHLayOverlayOpacity{ nullptr };
	QHBoxLayout* m_pHLayIconSize{ nullptr };
	QHBoxLayout* m_pHLayFontSize{ nullptr };
	QHBoxLayout* m_pHLayButtonText{ nullptr };

	QHBoxLayout* m_pHLayUseThemeColors{ nullptr };
	QHBoxLayout* m_pHLayBackgroundColor{ nullptr };
	QHBoxLayout* m_pHLayForegroundColor{ nullptr };
	QHBoxLayout* m_pHLayOverlayColor{ nullptr };
	QHBoxLayout* m_pHLayDisabledBgColor{ nullptr };
	QHBoxLayout* m_pHLayDisableFgColor{ nullptr };

	QVBoxLayout* m_pVLayFirst{ nullptr };
	QVBoxLayout* m_pVLaySecond{ nullptr };
	QVBoxLayout* m_pVLayThird{ nullptr };

	QHBoxLayout* m_pHLayFirst{ nullptr };

	QHBoxLayout* m_pHLayButton{ nullptr };

	// lib
	CUVMaterialFlatButton* m_button{ nullptr };

private:
	int m_nLabelWidth{ 140 };
};
