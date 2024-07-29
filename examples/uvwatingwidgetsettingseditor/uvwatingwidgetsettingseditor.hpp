#pragma once

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QToolButton>
#include <QVBoxLayout>

#include "uvwaitingwidget/uvwaitingwidget.hpp"

#ifdef CUVWATINGWIDGETSETTINGSEDITOR_LIB
#define CUVWATINGWIDGETSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVWATINGWIDGETSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVWATINGWIDGETSETTINGSEDITOR_EXPORT CUVWatingWidgetSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVWatingWidgetSettingsEditor(QWidget* parent = nullptr);
	~CUVWatingWidgetSettingsEditor() override;

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
	QLabel* m_pLbTextPosition{ nullptr };
	QComboBox* m_pCbTextPosition{ nullptr };

	QLabel* m_pLbText{ nullptr };
	QLineEdit* m_pLeText{ nullptr };

	QLabel* m_pLbTextColor{ nullptr };
	QLineEdit* m_pLeTextColor{ nullptr };
	QToolButton* m_pTbTextColor{ nullptr };

	QLabel* m_pLbColor{ nullptr };
	QLineEdit* m_pLeColor{ nullptr };
	QToolButton* m_pTbColor{ nullptr };

	QLabel* m_pLbRoundness{ nullptr };
	QDoubleSpinBox* m_pDSpinRoundness{ nullptr };

	QLabel* m_pLbOpacity{ nullptr };
	QDoubleSpinBox* m_pDSpinOpacity{ nullptr };

	QLabel* m_pLbFadePerc{ nullptr };
	QDoubleSpinBox* m_pDSpinFadePerc{ nullptr };

	QLabel* m_pLbLines{ nullptr };
	QSpinBox* m_pSpinLines{ nullptr };

	QLabel* m_pLbLineLength{ nullptr };
	QSpinBox* m_pSpinLineLength{ nullptr };

	QLabel* m_pLbLineWidth{ nullptr };
	QSpinBox* m_pSpinLineWidth{ nullptr };

	QLabel* m_pLbInnerRadius{ nullptr };
	QSpinBox* m_pSpinInnerRadius{ nullptr };

	QLabel* m_pLbRev{ nullptr };
	QDoubleSpinBox* m_pDSpinRev{ nullptr };

	QPushButton* m_pBtnStart{ nullptr };
	QPushButton* m_pBtnStop{ nullptr };
	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayTextPosition{ nullptr };
	QHBoxLayout* m_pHLayText{ nullptr };
	QHBoxLayout* m_pHLayTextColor{ nullptr };
	QHBoxLayout* m_pHLayColor{ nullptr };
	QHBoxLayout* m_pHLayRoundness{ nullptr };
	QHBoxLayout* m_pHLayOpacity{ nullptr };
	QHBoxLayout* m_pHLayFadePerc{ nullptr };
	QHBoxLayout* m_pHLayLines{ nullptr };
	QHBoxLayout* m_pHLayLineLength{ nullptr };
	QHBoxLayout* m_pHLayLineWidth{ nullptr };
	QHBoxLayout* m_pHLayInnerRadius{ nullptr };
	QHBoxLayout* m_pHLayRev{ nullptr };
	QHBoxLayout* m_pHLayBtn{ nullptr };
	// lib
	CUVWatingWidget* const m_pWating{ nullptr };

private:
	int m_nLabelWidth{ 130 };
};
