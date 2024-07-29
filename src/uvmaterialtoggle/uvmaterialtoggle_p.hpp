#pragma once

#include <QColor>
#include <Qt>

class QStateMachine;
class QState;
class QColor;
class CUVMaterialToggle;
class CUVMaterialToggleTrack;
class CUVMaterialToggleThumb;
class CUVMaterialToggleRippleOverlay;

class CUVMaterialTogglePrivate {
	Q_DISABLE_COPY(CUVMaterialTogglePrivate)
	Q_DECLARE_PUBLIC(CUVMaterialToggle)

public:
	explicit CUVMaterialTogglePrivate(CUVMaterialToggle* q);
	~CUVMaterialTogglePrivate();

	void init();
	void setupProperties();

	CUVMaterialToggle* const q_ptr{ nullptr };
	CUVMaterialToggleTrack* track{ nullptr };
	CUVMaterialToggleThumb* thumb{ nullptr };
	CUVMaterialToggleRippleOverlay* rippleOverlay{ nullptr };
	QStateMachine* stateMachine{ nullptr };
	QState* offState{ nullptr };
	QState* onState{ nullptr };
	Qt::Orientation orientation{};
	QColor disabledColor{};
	QColor activeColor{};
	QColor inactiveColor{};
	QColor trackColor{};
	bool useThemeColors{};
};
