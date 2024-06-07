#pragma once

#include <QColor>

class CUVMaterialIconButton;
class CUVMaterialRippleOverlay;
class QColor;

class CUVMaterialIconButtonPrivate final {
	Q_DISABLE_COPY(CUVMaterialIconButtonPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialIconButton)

public:
	explicit CUVMaterialIconButtonPrivate(CUVMaterialIconButton* q);
	~CUVMaterialIconButtonPrivate();

	void init();
	void updateRipple();

	CUVMaterialIconButton* const q_ptr{ nullptr };
	CUVMaterialRippleOverlay* rippleOverlay{ nullptr };
	QColor color{};
	QColor disabledColor{};
	bool useThemeColors{};
};
