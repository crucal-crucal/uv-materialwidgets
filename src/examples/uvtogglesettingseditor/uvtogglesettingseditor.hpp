#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmaterialtoggle/uvmaterialtoggle.hpp"

#ifdef CUVTOGGLESETTINGSEDITOR_LIB
#define CUVTOGGLESETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVTOGGLESETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVTOGGLESETTINGSEDITOR_EXPORT CUVToggleSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVToggleSettingsEditor(QWidget* parent = nullptr);
	~CUVToggleSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initData() const;
	void initConnection();

protected slots:
	void setupForm() const;
	void updateWidget() const;
	void selectColor();

private:
	// Interface
	QLabel* m_pLbDisabled{ nullptr };
	QCheckBox* m_pCbDisabled{ nullptr };

	QLabel* m_pLbChecked{ nullptr };
	QCheckBox* m_pCbChecked{ nullptr };

	QLabel* m_pLbOrientation{ nullptr };
	QComboBox* m_pCbOrientation{ nullptr };

	QLabel* m_pLbUseThemeColors{ nullptr };
	QCheckBox* m_pCbUseThemeColors{ nullptr };

	QLabel* m_pLbActiceColor{ nullptr };
	QLineEdit* m_pLeActiveColor{ nullptr };
	QToolButton* m_pTbActiveColor{ nullptr };

	QLabel* m_pLbInactiveColor{ nullptr };
	QLineEdit* m_pLeInactiveColor{ nullptr };
	QToolButton* m_pTbInactiveColor{ nullptr };

	QLabel* m_pLbDisabledColor{ nullptr };
	QLineEdit* m_pLeDisabledColor{ nullptr };
	QToolButton* m_pTbDisabledColor{ nullptr };

	QLabel* m_pLbTrackColor{ nullptr };
	QLineEdit* m_pLeTrackColor{ nullptr };
	QToolButton* m_pTbTrackColor{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayDisabled{ nullptr };
	QHBoxLayout* m_pHLayChecked{ nullptr };
	QHBoxLayout* m_pHLayOrientation{ nullptr };
	QHBoxLayout* m_pHLayUseThemeColors{ nullptr };
	QHBoxLayout* m_pHLayActiveColor{ nullptr };
	QHBoxLayout* m_pHLayInactiveColor{ nullptr };
	QHBoxLayout* m_pHLayDisabledColor{ nullptr };
	QHBoxLayout* m_pHLayTrackColor{ nullptr };

	// lib
	CUVMaterialToggle* const m_pToggle{ nullptr };

private:
	int m_nLabelWidth{ 120 };
};
