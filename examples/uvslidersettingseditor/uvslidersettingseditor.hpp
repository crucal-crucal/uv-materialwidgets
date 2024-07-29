#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmaterialslider/uvmaterialslider.hpp"

#ifdef CUVSLIDERSETTINGSEDITOR_LIB
#define CUVSLIDERSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVSLIDERSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVSLIDERSETTINGSEDITOR_EXPORT CUVSliderSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVSliderSettingsEditor(QWidget* parent = nullptr);
	~CUVSliderSettingsEditor() override;

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
	QLabel* m_pLbDisabled{ nullptr };
	QCheckBox* m_pCbDisabled{ nullptr };

	QLabel* m_pLbValue{ nullptr };
	QLineEdit* m_pLeValue{ nullptr };

	QLabel* m_pLbOrientation{ nullptr };
	QComboBox* m_pCbOrientation{ nullptr };

	QLabel* m_pLbInverted{ nullptr };
	QCheckBox* m_pCbInverted{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayDisabled{ nullptr };
	QHBoxLayout* m_pHLayValue{ nullptr };
	QHBoxLayout* m_pHLayOrientation{ nullptr };
	QHBoxLayout* m_pHLayInverted{ nullptr };

	// lib
	CUVMaterialSlider* const m_pSlider{ nullptr };

private:
	int m_nLabelWidth{ 100 };
};
