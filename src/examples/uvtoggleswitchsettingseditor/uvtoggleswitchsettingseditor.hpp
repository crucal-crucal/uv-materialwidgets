#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmaterialtoggleswitch/uvmaterialtoggleswitch.hpp"

#ifdef CUVTOGGLESWITCHEDITOR_LIB
#define CUVTOGGLESWITCHEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVTOGGLESWITCHEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVTOGGLESWITCHEDITOR_EXPORT CUVToggleSwitchSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVToggleSwitchSettingsEditor(QWidget* parent = nullptr);
	~CUVToggleSwitchSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
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

	QLabel* m_pLbTextBold{ nullptr };
	QCheckBox* m_pCbTextBold{ nullptr };

	QLabel* m_pLbFontSize{ nullptr };
	QSpinBox* m_pSbFontSize{ nullptr };

	QLabel* m_pLbOnText{ nullptr };
	QLineEdit* m_pLeOnText{ nullptr };

	QLabel* m_pLbOffText{ nullptr };
	QLineEdit* m_pLeOffText{ nullptr };

	QLabel* m_pLbBackgroundOnColor{ nullptr };
	QLineEdit* m_pLeBackgroundOnColor{ nullptr };
	QToolButton* m_pTbBackgroundOnColor{ nullptr };

	QLabel* m_pLbBackgroundOffColor{ nullptr };
	QLineEdit* m_pLeBackgroundOffColor{ nullptr };
	QToolButton* m_pTbBackgroundOffColor{ nullptr };

	QLabel* m_pLbTextOnColor{ nullptr };
	QLineEdit* m_pLeTextOnColor{ nullptr };
	QToolButton* m_pTbTextOnColor{ nullptr };

	QLabel* m_pLbTextOffdColor{ nullptr };
	QLineEdit* m_pLeTextOffdColor{ nullptr };
	QToolButton* m_pTbTextOffdColor{ nullptr };

	QLabel* m_pLbcircleOffColor{ nullptr };
	QLineEdit* m_pLecircleOffColor{ nullptr };
	QToolButton* m_pTbcircleOffColor{ nullptr };

	QLabel* m_pLbcircleOnColor{ nullptr };
	QLineEdit* m_pLecircleOnColor{ nullptr };
	QToolButton* m_pTbcircleOnColor{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayDisabled{ nullptr };
	QHBoxLayout* m_pHLayChecked{ nullptr };
	QHBoxLayout* m_pHLayTextBold{ nullptr };
	QHBoxLayout* m_pHLayFontSize{ nullptr };
	QHBoxLayout* m_pHLayOnText{ nullptr };
	QHBoxLayout* m_pHLayOffText{ nullptr };
	QHBoxLayout* m_pHLayBackgroundOnColor{ nullptr };
	QHBoxLayout* m_pHLayBackgroundOffColor{ nullptr };
	QHBoxLayout* m_pHLayTextOnColor{ nullptr };
	QHBoxLayout* m_pHLayTextOffdColor{ nullptr };
	QHBoxLayout* m_pHLaycircleOffColor{ nullptr };
	QHBoxLayout* m_pHLaycircleOnColor{ nullptr };

	// lib
	CUVMaterialToggleSwitch* const m_pToggleSwitch{ nullptr };

private:
	int m_nLabelWidth{ 170 };
};
