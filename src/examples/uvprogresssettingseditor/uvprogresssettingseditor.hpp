#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmaterialprogress/uvmaterialprogress.hpp"

#ifdef CUVPROGRESSSETTINGSEDITOR_LIB
#define CUVPROGRESSSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVPROGRESSSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVPROGRESSSETTINGSEDITOR_EXPORT CUVProgressSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVProgressSettingsEditor(QWidget* parent = nullptr);
	~CUVProgressSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initData() const;
	void initConnection();

protected slots:
	void setupForm() const;
	void updateWidget() const;
	void selectColor();

private:
	// Interface
	QLabel* m_pLbDisabled{ nullptr };
	QCheckBox* m_pCbDisabled{ nullptr };

	QLabel* m_pLbProgressType{ nullptr };
	QComboBox* m_pCbProgressType{ nullptr };

	QLabel* m_pLbProgress{ nullptr };
	QSlider* m_pSlProgress{ nullptr };

	QLabel* m_pLbUseThemeColors{ nullptr };
	QCheckBox* m_pCbUseThemeColors{ nullptr };

	QLabel* m_pLbProgressColor{ nullptr };
	QLineEdit* m_pLeProgressColor{ nullptr };
	QToolButton* m_pTbProgressColor{ nullptr };

	QLabel* m_pLbBackgroundColor{ nullptr };
	QLineEdit* m_pLeBackgroundColor{ nullptr };
	QToolButton* m_pTbBackgroundColor{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayDisabled{ nullptr };
	QHBoxLayout* m_pHLayProgressType{ nullptr };
	QHBoxLayout* m_pHLayProgress{ nullptr };
	QHBoxLayout* m_pHLayUseThemeColors{ nullptr };
	QHBoxLayout* m_pHLayProgressColor{ nullptr };
	QHBoxLayout* m_pHLayBackgroundColor{ nullptr };

	// lib
	CUVMaterialProgress* const m_pProgress{ nullptr };

private:
	int m_nLabelWidth{ 130 };
};
