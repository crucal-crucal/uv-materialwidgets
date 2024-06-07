#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmaterialradiobutton/uvmaterialradiobutton.hpp"

#ifdef CUVRADIOBUTTONSETTINGSEDITOR_LIB
#define CUVRADIOBUTTONSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVRADIOBUTTONSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVRADIOBUTTONSETTINGSEDITOR_EXPORT CUVRadioButtonSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVRadioButtonSettingsEditor(QWidget* parent = nullptr);
	~CUVRadioButtonSettingsEditor() override;

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

	QLabel* m_pLbLabelPosition{ nullptr };
	QComboBox* m_pCbLabelPosition{ nullptr };

	QLabel* m_pLbLabelText{ nullptr };
	QLineEdit* m_pLeLabelText{ nullptr };

	QLabel* m_pLbUseThemeColors{ nullptr };
	QCheckBox* m_pCbUseThemeColors{ nullptr };

	QLabel* m_pLbCheckedColor{ nullptr };
	QLineEdit* m_pLeCheckedColor{ nullptr };
	QToolButton* m_pTbCheckedColor{ nullptr };

	QLabel* m_pLbUnCheckedColor{ nullptr };
	QLineEdit* m_pLeUnCheckedColor{ nullptr };
	QToolButton* m_pTbUnCheckedColor{ nullptr };

	QLabel* m_pLbTextColor{ nullptr };
	QLineEdit* m_pLeTextColor{ nullptr };
	QToolButton* m_pTbTextColor{ nullptr };

	QLabel* m_pLbDisabledColor{ nullptr };
	QLineEdit* m_pLeDisabledColor{ nullptr };
	QToolButton* m_pTbDisabledColor{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayDisabled{ nullptr };
	QHBoxLayout* m_pHLayLabelPosition{ nullptr };
	QHBoxLayout* m_pHLayLabelText{ nullptr };
	QHBoxLayout* m_pHLayUseThemeColors{ nullptr };
	QHBoxLayout* m_pHLayCheckedColor{ nullptr };
	QHBoxLayout* m_pHLayUnCheckedColor{ nullptr };
	QHBoxLayout* m_pHLayTextColor{ nullptr };
	QHBoxLayout* m_pHLayDisabledColor{ nullptr };

	// lib
	CUVMaterialRadioButton* const m_pRadioButton1{ nullptr };
	CUVMaterialRadioButton* const m_pRadioButton2{ nullptr };
	CUVMaterialRadioButton* const m_pRadioButton3{ nullptr };

private:
	int m_nLabelWidth{ 130 };
};
