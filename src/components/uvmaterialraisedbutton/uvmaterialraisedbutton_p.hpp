#pragma once

#include "uvmaterialflatbutton/uvmaterialflatbutton_p.hpp"

class QStateMachine;
class QState;
class QGraphicsDropShadowEffect;
class CUVMaterialRaisedButton;

class CUVMaterialRaisedButtonPrivate : public CUVMaterialFlatButtonPrivate {
	Q_DISABLE_COPY(CUVMaterialRaisedButtonPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialRaisedButton) // NOLINT

public:
	explicit CUVMaterialRaisedButtonPrivate(CUVMaterialRaisedButton* q);
	~CUVMaterialRaisedButtonPrivate();

	void init();

	QStateMachine* shadowStateMachine{ nullptr };
	QState* normalState{ nullptr };
	QState* pressedState{ nullptr };
	QGraphicsDropShadowEffect* effect{ nullptr };
};
