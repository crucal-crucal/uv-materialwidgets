#pragma once

#include <QVBoxLayout>

#include "uvmaterialshared/uvmaterialoverlaywidget.hpp"

class CUVMaterialAutoComplete;

#ifdef CUVAUTOCOMPLETESETTINGSEDITOR_LIB
#define CUVAUTOCOMPLETESETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVAUTOCOMPLETESETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVAUTOCOMPLETESETTINGSEDITOR_EXPORT CUVAutoCompleteSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVAutoCompleteSettingsEditor(QWidget* parent = nullptr);
	~CUVAutoCompleteSettingsEditor() override;

private:
	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCanvas{ nullptr };
	QVBoxLayout* m_pVLayCenter{ nullptr };

	CUVMaterialAutoComplete* const m_autocomplete{ nullptr };
};
