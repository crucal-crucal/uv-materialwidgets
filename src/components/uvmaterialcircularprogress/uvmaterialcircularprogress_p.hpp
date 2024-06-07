#pragma once

#include <QtGlobal>

#include "uvshared/uvmaterialtheme.hpp"

class CUVMaterialCircularProgress;
class CUVMaterialCircularProgressDelegate;

class CUVMaterialCircularProgressPrivate {
	Q_DISABLE_COPY(CUVMaterialCircularProgressPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialCircularProgress)

public:
	explicit CUVMaterialCircularProgressPrivate(CUVMaterialCircularProgress* q);
	~CUVMaterialCircularProgressPrivate();

	void init();

	CUVMaterialCircularProgress* const q_ptr{ nullptr };
	CUVMaterialCircularProgressDelegate* delegate{ nullptr };
	Material::ProgressType progressType{};
	QColor color{};
	qreal penWidth{};
	int size{};
	bool useThemeColors{};
};
