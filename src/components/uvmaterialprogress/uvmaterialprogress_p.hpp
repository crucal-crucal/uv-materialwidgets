#pragma once

#include "uvshared/uvmaterialtheme.hpp"

class CUVMaterialProgress;
class CUVMaterialProgressDelegate;

class CUVMaterialProgressPrivate {
	Q_DISABLE_COPY(CUVMaterialProgressPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialProgress)

public:
	explicit CUVMaterialProgressPrivate(CUVMaterialProgress* q);
	~CUVMaterialProgressPrivate();

	void init();

	CUVMaterialProgress* const q_ptr{ nullptr };
	CUVMaterialProgressDelegate* delegate{ nullptr };
	Material::ProgressType progressType{};
	QColor progressColor{};
	QColor backgroundColor{};
	bool useThemeColors{};
};
