#pragma once

#include <QWidget>

#include <QPushButton>
#include <QVBoxLayout>

#include "uvmaterialsnackbar/uvmaterialsnackbar.hpp"

#ifdef CUVSNACKBARSETTINGSEDITOR_LIB
#define CUVSNACKBARSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVSNACKBARSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVSNACKBARSETTINGSEDITOR_EXPORT CUVSnackBarSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVSnackBarSettingsEditor(QWidget* parent = nullptr);
	~CUVSnackBarSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initConnection();

protected slots:
	void showSnackbar() const;

private:
	// Interface
	QPushButton* m_pBtnShowSnackBar{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };
	// lib
	CUVMaterialSnackbar* const m_pSnackBar{ nullptr };
};
