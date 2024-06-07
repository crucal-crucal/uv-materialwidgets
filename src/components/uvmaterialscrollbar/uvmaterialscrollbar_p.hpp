#pragma once

#include <QColor>
#include <QtGlobal>

class CUVMaterialScrollBar;
class CUVMaterialScrollBarStateMachine;

class CUVMaterialScrollBarPrivate {
	Q_DISABLE_COPY(CUVMaterialScrollBarPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialScrollBar)

public:
	explicit CUVMaterialScrollBarPrivate(CUVMaterialScrollBar* q);
	~CUVMaterialScrollBarPrivate();

	void init();

	CUVMaterialScrollBar* const q_ptr{ nullptr };
	CUVMaterialScrollBarStateMachine* stateMachine{ nullptr };
	QColor backgroundColor{};
	QColor sliderColor{};
	QColor canvasColor{};
	bool hideOnMouseOut{};
	bool useThemeColors{};
};
