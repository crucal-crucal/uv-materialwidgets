#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmaterialdrawer/uvmaterialdrawer.hpp"

#ifdef CUVDRAWERSETTINGSEDITOR_LIB
#define CUVDRAWERSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVDRAWERSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVDRAWERSETTINGSEDITOR_EXPORT CUVDrawerSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVDrawerSettingsEditor(QWidget* parent = nullptr);
	~CUVDrawerSettingsEditor() override;

private:
	void createCtrl();
	void customLayout();
	void initData();
	void initConnection();

protected slots:
	void setupForm();
	void updateWidget();

private:
	// Interface
	QLabel* m_pLbOverlayMode{ nullptr };
	QCheckBox* m_pCbOverlayMode{ nullptr };

	QLabel* m_pLbClickToClose{ nullptr };
	QCheckBox* m_pCbClickToClose{ nullptr };

	QPushButton* m_pBtnShowDrawer{ nullptr };
	QPushButton* m_pBtnHideDrawer{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayOverlayMode{ nullptr };
	QHBoxLayout* m_pHLayClickToClose{ nullptr };
	QHBoxLayout* m_pHLayShowHide{ nullptr };

	QVBoxLayout* m_pVLayDrawer{ nullptr };

	// lib
	CUVMaterialDrawer* const m_pdrawer{ nullptr };

private:
	int m_nLabelWidth{ 130 };
};
