#pragma once

#include <QColor>
#include <QtGlobal>

#include "uvshared/uvmaterialtheme.hpp"

class CUVMaterialFlatButton;
class CUVMaterialRippleOverlay;
class CUVMaterialFlatButtonStateMachine;

class CUVMaterialFlatButtonPrivate {
	Q_DISABLE_COPY(CUVMaterialFlatButtonPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialFlatButton)

public:
	explicit CUVMaterialFlatButtonPrivate(CUVMaterialFlatButton* q);
	~CUVMaterialFlatButtonPrivate();

	void init();

	CUVMaterialFlatButton* const q_ptr{ nullptr };
	CUVMaterialRippleOverlay* rippleOverlay{ nullptr };
	CUVMaterialFlatButtonStateMachine* stateMachine{ nullptr };
	Material::Role role{};
	Material::RippleStyle rippleStyle{};
	Material::ButtonIconPlacement iconPlacement{};
	Material::OverlayStyle overlayStyle{};
	Qt::BGMode bgMode{};
	Qt::Alignment textAlignment{};
	QColor backgroundColor{};
	QColor foregroundColor{};
	QColor overlayColor{};
	QColor disabledColor{};
	QColor disabledBackgroundColor{};
	qreal fixedRippleRadius{};
	qreal cornerRadius{};
	qreal baseOpacity{};
	qreal fontSize{};
	bool useThemeColors{};
	bool useFixedRippleRadius{};
	bool haloVisible{};
};
