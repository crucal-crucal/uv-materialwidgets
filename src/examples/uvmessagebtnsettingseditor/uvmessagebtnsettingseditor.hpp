#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "uvmaterialmessagebutton/uvmaterialmessagebutton.hpp"

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
	CUVMaterialMessageButton* m_pBtnSuccess{ nullptr };
	CUVMaterialMessageButton* m_pBtnWaring{ nullptr };
	CUVMaterialMessageButton* m_pBtnError{ nullptr };
	CUVMaterialMessageButton* m_pBtnInfo{ nullptr };
};
