#pragma once

class CUVMaterialDrawer;
class CUVMaterialDrawerWidget;
class CUVMaterialDrawerStateMachine;

class CUVMaterialDrawerPrivate {
	Q_DISABLE_COPY(CUVMaterialDrawerPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialDrawer)

public:
	explicit CUVMaterialDrawerPrivate(CUVMaterialDrawer* q);
	~CUVMaterialDrawerPrivate();

	void init();
	void setClosed(bool value = true);

	CUVMaterialDrawer* const q_ptr{ nullptr };
	CUVMaterialDrawerWidget* widget{ nullptr };
	CUVMaterialDrawerStateMachine* stateMachine{ nullptr };
	QWidget* window{ nullptr };
	int width{};
	bool clickToClose{};
	bool autoRaise{};
	bool closed{};
	bool overlay{};
};
