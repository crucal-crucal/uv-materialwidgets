#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>

#include "uvmaterialappbar/uvmaterialappbar.hpp"
#include "uvmaterialiconbutton/uvmaterialiconbutton.hpp"

#ifdef CUVAPPBARSETTINGSEDITOR_LIB
#define CUVAPPBARSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVAPPBARSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVAPPBARSETTINGSEDITOR_EXPORT CUVAppBarSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVAppBarSettingsEditor(QWidget* parent = nullptr);
	~CUVAppBarSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initConnection();

protected:
	void setUpForm() const;
	void updateWidget() const;
	void selectColor();

private:
	// Interface
	QLabel* m_pLbuseThemeColor{ nullptr };
	QCheckBox* m_pCbuseThemeColor{ nullptr };

	QLabel* m_pLbBackgroundColor{ nullptr };
	QLineEdit* m_pLeBackgroundColor{ nullptr };
	QToolButton* m_pTbBackgroundColor{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayuseThemeColor{ nullptr };
	QHBoxLayout* m_pHLayuseBackgroundColor{ nullptr };

	// lib
	CUVMaterialAppBar* const m_pMaterialAppBar{ nullptr };
	CUVMaterialIconButton* m_pMaterialIconButton{ nullptr };
	QLabel* m_pLbAppBarText{ nullptr };
};
