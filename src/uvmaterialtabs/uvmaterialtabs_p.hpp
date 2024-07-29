#pragma once

#include "uvmaterialshared/uvmaterialtheme.hpp"

class QHBoxLayout;
class CUVMaterialTabs;
class CUVMaterialTabsInkBar;

class CUVMaterialTabsPrivate {
	Q_DISABLE_COPY(CUVMaterialTabsPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialTabs)

public:
	explicit CUVMaterialTabsPrivate(CUVMaterialTabs* q);
	~CUVMaterialTabsPrivate();

	void init();

	CUVMaterialTabs* const q_ptr{ nullptr };
	CUVMaterialTabsInkBar* inkBar{ nullptr };
	QHBoxLayout* tabLayout{ nullptr };
	Material::RippleStyle rippleStyle{};
	QColor inkColor{};
	QColor backgroundColor{};
	QColor textColor{};
	int tab{};
	bool showHalo{};
	bool useThemeColors{};
};
