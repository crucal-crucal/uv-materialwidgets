#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmaterialiconbutton1/uvmaterialiconbutton.hpp"

#ifdef CUVICONBUTTONSETTINGSEDITOR_LIB
#define CUVICONBUTTONSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVICONBUTTONSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVICONBUTTONSETTINGSEDITOR_EXPORT CUVIconButtonSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVIconButtonSettingsEditor(QWidget* parent = nullptr);
	~CUVIconButtonSettingsEditor() override;

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

	QLabel* m_pLbSize{ nullptr };
	QSpinBox* m_pSbSize{ nullptr };

	QLabel* m_pLbUseThemeColors{ nullptr };
	QCheckBox* m_pCbUseThemeColors{ nullptr };

	QLabel* m_pLbColor{ nullptr };
	QLineEdit* m_pLeColor{ nullptr };
	QToolButton* m_pTbColor{ nullptr };

	QLabel* m_pLbDisableedColor{ nullptr };
	QLineEdit* m_pLeDisableedColor{ nullptr };
	QToolButton* m_pTbDisableedColor{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayDisabled{ nullptr };
	QHBoxLayout* m_pHLaySize{ nullptr };
	QHBoxLayout* m_pHLayUseThemeColors{ nullptr };
	QHBoxLayout* m_pHLayColor{ nullptr };
	QHBoxLayout* m_pHLayDisableedColor{ nullptr };

	// lib
	CUVMaterialIconButton* const m_pButton{ nullptr };

private:
	int m_nLabelWidth{ 150 };
};
