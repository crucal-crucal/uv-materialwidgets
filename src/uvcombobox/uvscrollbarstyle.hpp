#pragma once

#include <QProxyStyle>

class CUVScrollBarStyle final : public QProxyStyle {
	Q_OBJECT

public:
	explicit CUVScrollBarStyle(QStyle* style = nullptr);
	~CUVScrollBarStyle() override;

	void drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget) const override;
	int pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const override;
};
