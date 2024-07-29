#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QToolButton>

#include "uvmaterialcircularprogress/uvmaterialcircularprogress.hpp"

#ifdef CUVCIRCULARPROGRESS_LIB
#define CUVCIRCULARPROGRESS_EXPORT Q_DECL_EXPORT
#else
#define CUVCIRCULARPROGRESS_EXPORT Q_DECL_IMPORT
#endif

class CUVCIRCULARPROGRESS_EXPORT CUVCircularProgressSettingsEditor : public QWidget {
	Q_OBJECT

public:
	explicit CUVCircularProgressSettingsEditor(QWidget* parent = nullptr);
	~CUVCircularProgressSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initConnection();
	void initData() const;

protected slots:
	void setupForm() const;
	void updateWidget() const;
	void selectColor();

private:
	// Interface
	QLabel* m_pLbDisable{ nullptr };
	QCheckBox* m_pCbDisable{ nullptr };

	QLabel* m_pLbProgressType{ nullptr };
	QComboBox* m_pCbProgressType{ nullptr };

	QLabel* m_pLbProgress{ nullptr };
	QSlider* m_pSlProgress{ nullptr };

	QLabel* m_pLbLineWidth{ nullptr };
	QDoubleSpinBox* m_pDSBLineWidth{ nullptr };

	QLabel* m_pLbSize{ nullptr };
	QSpinBox* m_pSBSize{ nullptr };

	QLabel* m_pLbUseThemeColors{ nullptr };
	QCheckBox* m_pCbUseThemeColors{ nullptr };

	QLabel* m_pLbColor{ nullptr };
	QLineEdit* m_pLeColor{ nullptr };
	QToolButton* m_pTbColor{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayDisable{ nullptr };
	QHBoxLayout* m_pHLayProgressType{ nullptr };
	QHBoxLayout* m_pHLayProgress{ nullptr };
	QHBoxLayout* m_pHLayLineWidth{ nullptr };
	QHBoxLayout* m_pHLaySize{ nullptr };
	QHBoxLayout* m_pHLayUseThemeColors{ nullptr };
	QHBoxLayout* m_pHLayColor{ nullptr };

	// lib
	CUVMaterialCircularProgress* const m_pProgress{ nullptr };

private:
	int m_nLabelWidth{ 140 };
};
