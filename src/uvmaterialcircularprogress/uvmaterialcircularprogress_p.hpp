#pragma once

#include <QObject>

#include "uvmaterialshared/uvmaterialtheme.hpp"

class CUVMaterialCircularProgress;
class CUVMaterialCircularProgressDelegate;

class CUVMaterialCircularProgressPrivate : public QObject {
	Q_DISABLE_COPY(CUVMaterialCircularProgressPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialCircularProgress)

public:
	explicit CUVMaterialCircularProgressPrivate(CUVMaterialCircularProgress* q, QObject* parent = nullptr);
	~CUVMaterialCircularProgressPrivate() override;

	void init();
	Q_SLOT void _updateAnimation();
	void drawIndeterminate(QPainter& painter, QPen& pen);
	void drawDeterminate(QPainter& painter, const QPen& pen);
	void drawDiscontinuous(QPainter& painter, const QPen& pen);
	void drawContinuous(QPainter& painter, const QPen& pen);
	void drawValue(QPainter& painter, QPen& pen);

	CUVMaterialCircularProgress* const q_ptr{ nullptr };
	CUVMaterialCircularProgressDelegate* delegate{ nullptr };
	Material::ProgressType progressType{};
	QColor color{};
	qreal penWidth{};
	QTimer* timer{ nullptr };
	int size{};
	bool useThemeColors{ false };
	bool showValue{ false };

	int startIndex1{ 0xe052 };
	int endIndex1{ 0xe0cb };
	int currentIndex1{ 0xe052 };

	int startIndex2{ 0xe100 };
	int endIndex2{ 0xe176 };
	int currentIndex2{ 0xe100 };
};
