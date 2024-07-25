#pragma once

#include <QProxyStyle>

class CUVMaterialScrollBarStyle final : public QProxyStyle {
	Q_OBJECT

public:
	explicit CUVMaterialScrollBarStyle(QStyle* style = nullptr);
	~CUVMaterialScrollBarStyle() override;

	void drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget) const override;
	int pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const override;
};
