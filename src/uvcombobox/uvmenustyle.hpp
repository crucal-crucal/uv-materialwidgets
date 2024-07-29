#pragma once

#include <QProxyStyle>

class CUVMenuStyle final : public QProxyStyle {
	Q_OBJECT

	Q_PROPERTY(int MenuItemHeight READ getMenuItemHeight WRITE setMenuItemHeight NOTIFY onMenuItemHeightChanged)

public:
	explicit CUVMenuStyle(QStyle* style = nullptr);
	~CUVMenuStyle() override;
	void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const override;
	void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const override;
	int pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const override;
	QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const override;

	void setMenuItemHeight(int height);
	[[nodiscard]] int getMenuItemHeight() const;

signals:
	void onMenuItemHeightChanged();

private:
	int _pMenuItemHeight{};
	mutable bool _isAnyoneItemHasIcon{ false };
	int _shadowBorderWidth{ 6 };
	QLinearGradient* _windowLinearGradient{ nullptr };
	int _iconWidth{ 22 };
};
