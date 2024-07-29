#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmessagebutton/uvmessagebutton.hpp"

#ifdef CUVMESSAGEBTNSETTINGSEDITOR_LIB
#define CUVMESSAGEBTNSETTINGSEDITOR_EXPORT Q_DECL_EXPORT
#else
#define CUVMESSAGEBTNSETTINGSEDITOR_EXPORT Q_DECL_IMPORT
#endif

class CUVMESSAGEBTNSETTINGSEDITOR_EXPORT CUVMessageBtnSettingsEditor : public QWidget {
	Q_OBJECT

public:
	explicit CUVMessageBtnSettingsEditor(QWidget* parent = nullptr);
	~CUVMessageBtnSettingsEditor() override;

private:
	void createCtrl();
	void customLayout() const;

private:
	// Interface
	QPushButton* m_pBtnTest{ nullptr };
	QHBoxLayout* m_pHLayBtn{ nullptr };
	QVBoxLayout* m_pVLayCenter{ nullptr };

	// lib
	CUVMessageButton* m_pBtnSuccess{ nullptr };
	CUVMessageButton* m_pBtnWaring{ nullptr };
	CUVMessageButton* m_pBtnError{ nullptr };
	CUVMessageButton* m_pBtnInfo{ nullptr };
};
