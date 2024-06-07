#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>

#include "uvmaterialcheckbox/uvmaterialcheckbox.hpp"

#ifdef CUVCHECKBOXSETTINGSEDITOR_LIB
#define CUVCHECKBOXSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVCHECKBOXSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVCHECKBOXSETTINGSEDITOR_EXPORT CUVCheckBoxSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVCheckBoxSettingsEditor(QWidget* parent = nullptr);
	~CUVCheckBoxSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initConnection();
	void initData() const;

protected slots:
	void setupForm() const;
	void updateWidget() const;
	void selectColor();

private:
	// Interface
	QLabel* m_pLbDisable{ nullptr };
	QCheckBox* m_pCbDisable{ nullptr };

	QLabel* m_pLbLabelPositing{ nullptr };
	QComboBox* m_pCbLabelPositing{ nullptr };

	QLabel* m_pLbLabelText{ nullptr };
	QLineEdit* m_pLeLabelText{ nullptr };

	QLabel* m_pLbChecked{ nullptr };
	QCheckBox* m_pCbChecked{ nullptr };

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

	QHBoxLayout* m_pHLayDisable{ nullptr };
	QHBoxLayout* m_pHLayLabelPositing{ nullptr };
	QHBoxLayout* m_pHLayLabelText{ nullptr };
	QHBoxLayout* m_pHLayChecked{ nullptr };
	QHBoxLayout* m_pHLayUseThemeColors{ nullptr };
	QHBoxLayout* m_pHLayCheckedColor{ nullptr };
	QHBoxLayout* m_pHLayUnCheckedColor{ nullptr };
	QHBoxLayout* m_pHLayTextColor{ nullptr };
	QHBoxLayout* m_pHLayDisabledColor{ nullptr };

	// lib
	CUVMaterialCheckBox* const m_pCheckBox{ nullptr };

private:
	int m_nLabelWidth{ 140 };
};
