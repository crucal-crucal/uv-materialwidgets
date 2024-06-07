#pragma once

#include <QTextEdit>
#include <QVBoxLayout>

#include "uvmaterialscrollbar/uvmaterialscrollbar.hpp"

#ifdef CUVSCROLLBARSETTINGSEDITOR_LIB
#define CUVSCROLLBARSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVSCROLLBARSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVSCROLLBARSETTINGSEDITOR_EXPORT CUVScrollBarSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVScrollBarSettingsEditor(QWidget* parent = nullptr);
	~CUVScrollBarSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initData() const;

private:
	// Interface
	QTextEdit* m_pTextEdit{ nullptr };

	QWidget* m_pcancas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	// lib
	CUVMaterialScrollBar* const m_pVerticalScrollBar{ nullptr };
	CUVMaterialScrollBar* const m_pHorizontalScrollBar{ nullptr };
};
