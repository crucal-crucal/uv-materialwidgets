#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmaterialavatar/uvmaterialavatar.hpp"
#include "uvmaterialbadge/uvmaterialbadge.hpp"

#ifdef CUVBADGESETTINGSEDITOR_LIB
#define CUVBADGESETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVBADGESETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVBADGESETTINGSEDITOR_EXPORT CUVBadgeSettingsEditor final : public QWidget {
	Q_OBJECT

public:
	explicit CUVBadgeSettingsEditor(QWidget* parent = nullptr);
	~CUVBadgeSettingsEditor() override;

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

	QLabel* m_pLbUseThemeColors{ nullptr };
	QCheckBox* m_pCbUseThemeColors{ nullptr };

	QLabel* m_pLbTextColor{ nullptr };
	QLineEdit* m_pLeTextColor{ nullptr };
	QToolButton* m_pTbTextColor{ nullptr };

	QLabel* m_pLbBackgroundColor{ nullptr };
	QLineEdit* m_pLeBackgroundColor{ nullptr };
	QToolButton* m_pTbBackgroundColor{ nullptr };

	QLabel* m_pLbHorizontalOffset{ nullptr };
	QSpinBox* m_pSbHorizontalOffset{ nullptr };

	QLabel* m_pLbVerticalOffset{ nullptr };
	QSpinBox* m_pSbVerticalOffset{ nullptr };

	QLabel* m_pLbType{ nullptr };
	QComboBox* m_pCbType{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QVBoxLayout* m_pVLayCenter{ nullptr };
	QVBoxLayout* m_pVLayBottom{ nullptr };

	QHBoxLayout* m_pHLayDisable{ nullptr };
	QHBoxLayout* m_pHLayUseThemeColors{ nullptr };
	QHBoxLayout* m_pHLayTextColor{ nullptr };
	QHBoxLayout* m_pHLayBackgroundColor{ nullptr };
	QHBoxLayout* m_pHLayHorizontalOffset{ nullptr };
	QHBoxLayout* m_pHLayVerticalOffset{ nullptr };
	QHBoxLayout* m_pHLayType{ nullptr };

	// lib
	CUVMaterialAvatar* const m_pAvatar{ nullptr };
	CUVMaterialBadge* const m_pBadge{ nullptr };

private:
	int m_nLabelWidth{ 140 };
};
