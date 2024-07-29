#pragma once

#include <QVBoxLayout>

#include "uvmaterialtabs/uvmaterialtabs.hpp"

#ifdef CUVTABSSETTINGSEDITOR_LIB
#define CUVTABSSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVTABSSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVTABSSETTINGSEDITOR_EXPORT CUVTabsSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVTabsSettingsEditor(QWidget* parent = nullptr);
	~CUVTabsSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initData() const;

private:
	// Interface
	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	// lib
	CUVMaterialTabs* const m_ptabs{ nullptr };
};
