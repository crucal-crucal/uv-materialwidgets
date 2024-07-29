#pragma once

#include <QWidget>

class CUVMaterialComboBox;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QToolButton;
class QSpinBox;

class CUVComboBoxSettingsEditor : public QWidget {
	Q_OBJECT

public:
	explicit CUVComboBoxSettingsEditor(QWidget* parent = nullptr);
	~CUVComboBoxSettingsEditor() override;

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
	QLabel* m_pLbBorderRaidus{ nullptr };
	QSpinBox* m_pSpinBorderRadius{ nullptr };

	QLabel* m_pLbNormalColor{ nullptr };
	QLineEdit* m_pEditNormalColor{ nullptr };
	QToolButton* m_pBtnNormalColor{ nullptr };

	QLabel* m_pLbMouseHoverColor{ nullptr };
	QLineEdit* m_pEditMouseHoverColor{ nullptr };
	QToolButton* m_pBtnMouseHoverColor{ nullptr };

	QLabel* m_pLbMouseSelectedColor{ nullptr };
	QLineEdit* m_pEditMouseSelectedColor{ nullptr };
	QToolButton* m_pBtnMouseSelectedColor{ nullptr };

	QLabel* m_pLbBorderColor{ nullptr };
	QLineEdit* m_pEditBorderColor{ nullptr };
	QToolButton* m_pBtnBorderColor{ nullptr };

	QLabel* m_pLbSelectedMarkColor{ nullptr };
	QLineEdit* m_pEditSelectedMarkColor{ nullptr };
	QToolButton* m_pBtnSelectedMarkColor{ nullptr };

	QLabel* m_pLbItemHoverColor{ nullptr };
	QLineEdit* m_pEditItemHoverColor{ nullptr };
	QToolButton* m_pBtnItemHoverColor{ nullptr };

	QLabel* m_pLbExpansionIndicatorColor{ nullptr };
	QLineEdit* m_pEditExpansionIndicatorColor{ nullptr };
	QToolButton* m_pBtnExpansionIndicatorColor{ nullptr };

	QWidget* m_pcanvas{ nullptr };

	QHBoxLayout* m_pBorderRadiusHLayout{ nullptr };
	QHBoxLayout* m_pNormalColorHLayout{ nullptr };
	QHBoxLayout* m_pMouseHoverColorHLayout{ nullptr };
	QHBoxLayout* m_pMouseSelectedColorHLayout{ nullptr };
	QHBoxLayout* m_pBorderColorHLayout{ nullptr };
	QHBoxLayout* m_pSelectedMarkColorHLayout{ nullptr };
	QHBoxLayout* m_pItemHoverColorHLayout{ nullptr };
	QHBoxLayout* m_pExpansionIndicatorColorHLayout{ nullptr };


	QVBoxLayout* m_pCanvasVLayout{ nullptr };
	QVBoxLayout* m_pCenterVLayout{ nullptr };
	// lib
	CUVMaterialComboBox* m_pComboBox{ nullptr };

	int m_nLabelWidth{ 120 };
};
