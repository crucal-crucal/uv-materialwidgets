#pragma once

#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QCheckBox>

#include "uvmaterialswitchbtn/uvswitchbutton.hpp"

#ifdef CUVSWITCHBTNSETTTINGSEDITOR_LIB
#define CUVSWITCHBTNSETTTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVSWITCHBTNSETTTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVSWITCHBTNSETTTINGSEDITOR_EXPORT CUVSwitchBtnSettingsEditor : public QWidget {
	Q_OBJECT

public:
	explicit CUVSwitchBtnSettingsEditor(QWidget* parent = nullptr);
	~CUVSwitchBtnSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initData() const;
	void initConnection();

protected slots:
	void setupForm() const;
	void updateWidget() const;

private:
	// Interface
	QLabel* m_pLbChecked{ nullptr };
	QCheckBox* m_pCbChecked{ nullptr };

	QLabel* m_pLbTextPosition{ nullptr };
	QComboBox* m_pCbTextPosition{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayChecked{ nullptr };
	QHBoxLayout* m_pHLayTextPosition{ nullptr };
	// lib
	CUVSwitchButton* const m_pswitchBtn{ nullptr };
};
