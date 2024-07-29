#pragma once

#include <QProxyStyle>

class CUVComboBoxStyle final : public QProxyStyle {
	Q_OBJECT

	Q_PROPERTY(qreal pExpandIconRotate READ getExpandIconRotate WRITE setExpandIconRotate NOTIFY onExpandIconRotateChanged)
	Q_PROPERTY(qreal pExpandMarkWidth READ getExpandMarkWidth WRITE setExpandMarkWidth NOTIFY onExpandMarkWidthChanged)

public:
	explicit CUVComboBoxStyle(QStyle* style = nullptr);
	~CUVComboBoxStyle() override;

	void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const override;
	void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const override;
	void drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget) const override;

	QRect subControlRect(ComplexControl cc, const QStyleOptionComplex* opt, SubControl sc, const QWidget* widget) const override;
	QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const override;

	void setExpandIconRotate(qreal ExpandIconRotate);
	[[nodiscard]] qreal getExpandIconRotate() const;

	void setExpandMarkWidth(qreal ExpandMarkWidth);
	[[nodiscard]] qreal getExpandMarkWidth() const;

signals:
	void onExpandIconRotateChanged();
	void onExpandMarkWidthChanged();

private:
	qreal _pExpandIconRotate{};
	qreal _pExpandMarkWidth{};
	int _shadowBorderWidth{ 6 };

public:
	QColor normalColor{};
	QColor mouseHoverColor{};
	QColor mouseSelectedColor{};
	QColor borderColor{};
	QColor selectedMarkColor{};
	QColor itemHoverColor{};
	QColor expansionIndicatorColor{};
};
