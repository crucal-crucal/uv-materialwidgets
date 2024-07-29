#pragma once

#include <QtGlobal>

class QStateMachine;
class CUVMaterialDialog;
class QStackedLayout;
class CUVMaterialDialogWindow;
class CUVMaterialDialogProxy;

class CUVMaterialDialogPrivate {
	Q_DISABLE_COPY(CUVMaterialDialogPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialDialog)

public:
	explicit CUVMaterialDialogPrivate(CUVMaterialDialog* q);
	~CUVMaterialDialogPrivate();

	void init();

	CUVMaterialDialog* const q_ptr{ nullptr };
	CUVMaterialDialogWindow* dialogWindow{ nullptr };
	QStackedLayout* proxyStack{ nullptr };
	QStateMachine* stateMachine{ nullptr };
	CUVMaterialDialogProxy* proxy{ nullptr };
};
