#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmaterialfab/uvmaterialfab.hpp"

#ifdef CUVFABSETTINGSEDITOR_LIB
#define CUVFABSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVFABSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVFABSETTINGSEDITOR_EXPORT CUVFabSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVFabSettingsEditor(QWidget* parent = nullptr);
	~CUVFabSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initData() const;
	void initConnection();

protected slots:
	void setupForm() const;
	void updateWidget() const;
	void selectColor() const;

private:
	// Interface
	QLabel* m_pLbDisabled{ nullptr };
	QCheckBox* m_pCbDisabled{ nullptr };

	QLabel* m_pLbCorner{ nullptr };
	QComboBox* m_pCbCorner{ nullptr };

	QLabel* m_pLbButtonRole{ nullptr };
	QComboBox* m_pCbButtonRole{ nullptr };

	QLabel* m_pLbHorizonOffset{ nullptr };
	QSpinBox* m_pSbHorizonOffset{ nullptr };

	QLabel* m_pLbVerticalOffset{ nullptr };
	QSpinBox* m_pSbVerticalOffset{ nullptr };

	QLabel* m_pLbMini{ nullptr };
	QCheckBox* m_pCbMini{ nullptr };

	QLabel* m_pLbRippleStyle{ nullptr };
	QComboBox* m_pCbRippleStyle{ nullptr };

	QLabel* m_pLbUseThemeColors{ nullptr };
	QCheckBox* m_pCbUseThemeColors{ nullptr };

	QLabel* m_pLbBackgroundColor{ nullptr };
	QLineEdit* m_pLeBackgroundColor{ nullptr };
	QToolButton* m_pTbBackgroundColor{ nullptr };

	QLabel* m_pLbForegroundColor{ nullptr };
	QLineEdit* m_pLeForegroundColor{ nullptr };
	QToolButton* m_pTbForegroundColor{ nullptr };

	QLabel* m_pLbDisabledBgColor{ nullptr };
	QLineEdit* m_pLeDisabledBgColor{ nullptr };
	QToolButton* m_pTbDisabledBgColor{ nullptr };

	QLabel* m_pLbDisabledFgColor{ nullptr };
	QLineEdit* m_pLeDisabledFgColor{ nullptr };
	QToolButton* m_pTbDisabledFgColor{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayDisabled{ nullptr };
	QHBoxLayout* m_pHLayCorner{ nullptr };
	QHBoxLayout* m_pHLayButtonRole{ nullptr };
	QHBoxLayout* m_pHLayHorizonOffset{ nullptr };
	QHBoxLayout* m_pHLayVerticalOffset{ nullptr };
	QHBoxLayout* m_pHLayMini{ nullptr };
	QHBoxLayout* m_pHLayRippleStyle{ nullptr };
	QHBoxLayout* m_pHLayUseThemeColors{ nullptr };
	QHBoxLayout* m_pHLayBackgroundColor{ nullptr };
	QHBoxLayout* m_pHLayForegroundColor{ nullptr };
	QHBoxLayout* m_pHLayDisabledBgColor{ nullptr };
	QHBoxLayout* m_pHLayDisabledFgColor{ nullptr };

	// lib
	CUVMaterialFloatingActionButton* m_pfab{ nullptr };

private:
	int m_nLabelWidth{ 150 };
};
