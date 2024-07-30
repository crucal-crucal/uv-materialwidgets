#pragma once

#include <QWidget>

class QComboBox;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QButtonGroup;
class CUVStackWidget;

class CUVStackWidgetSettingsEditor : public QWidget {
	Q_OBJECT

public:
	explicit CUVStackWidgetSettingsEditor(QWidget* parent = nullptr);
	~CUVStackWidgetSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;
	void initConnection();
	void initData();

protected slots:
	void updateWidget() const;

private:
	// Interface
	QLabel* m_pLbMoveDirection{ nullptr };
	QComboBox* m_pCbMoveDirection{ nullptr };
	QButtonGroup* m_pButtonGroup{ nullptr };

	QHBoxLayout* m_pMoveDirectionHLayout{ nullptr };
	QHBoxLayout* m_pBtnHLayout{ nullptr };
	QVBoxLayout* m_pLayout{ nullptr };
	// lib
	CUVStackWidget* m_pStackWidget{ nullptr };
};
