#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmaterialdialog/uvmaterialdialog.hpp"
#include "uvmaterialflatbutton/uvmaterialflatbutton.hpp"

#ifdef CUVDIALOGSETTINGSEDITOR_LIB
#define CUVDIALOGSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVDIALOGSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVDIALOGSETTINGSEDITOR_EXPORT CUVDialogSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVDialogSettingsEditor(QWidget* parent = nullptr);
	~CUVDialogSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initConnection() const;

private:
	// Interface
	QPushButton* m_pBtnShowDialog{ nullptr };

	QWidget* m_pcanvas{ nullptr };
	QWidget* m_pdialogWidget{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QVBoxLayout* m_pVLayDialog{ nullptr };
	QVBoxLayout* m_pVLayDialogWidget{ nullptr };

	// lib
	CUVMaterialDialog* const m_pdialog{ nullptr };
	CUVMaterialFlatButton* m_pCloseButton{ nullptr };
};
