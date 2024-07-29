#pragma once

#include <QColor>
#include <QtGlobal>

class CUVMaterialAppBar;

class CUVMaterialAppBarPrivate {
	Q_DISABLE_COPY(CUVMaterialAppBarPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialAppBar)

public:
	explicit CUVMaterialAppBarPrivate(CUVMaterialAppBar* q);
	~CUVMaterialAppBarPrivate();

	void init();

	CUVMaterialAppBar* const q_ptr{ nullptr };
	bool useThemeColors{};
	QColor foregroundColor{};
	QColor backgroundColor{};
};
