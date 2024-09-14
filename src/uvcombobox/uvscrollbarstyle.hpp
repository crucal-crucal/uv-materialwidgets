#pragma once

#include <QProxyStyle>

class CUVScrollBar;

class CUVScrollBarStyle final : public QProxyStyle {
	Q_OBJECT
	Q_PROPERTY(qreal pOpacity MEMBER _pOpacity NOTIFY pOpacityChanged)
	Q_PROPERTY(qreal pSliderExtent MEMBER _pSliderExtent NOTIFY pSliderExtentChanged)

public:
	explicit CUVScrollBarStyle(QStyle* style = nullptr);
	~CUVScrollBarStyle() override;

	void drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget) const override;
	int pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const override;
	int styleHint(StyleHint stylehint, const QStyleOption* opt, const QWidget* widget, QStyleHintReturn* returnData) const override;
	void startExpandAnimation(bool isExpand);

	void setOpacity(qreal opacity);
	[[nodiscard]] qreal getOpacity() const;

	void setSliderExtent(qreal sliderExtent);
	[[nodiscard]] qreal getSliderExtent() const;

	void setIsExpand(bool isExpand);
	[[nodiscard]] bool getIsExpand() const;

	void setScrollBar(CUVScrollBar* scrollBar);
	[[nodiscard]] CUVScrollBar* getScrollBar() const;

signals:
	void pOpacityChanged();
	void pSliderExtentChanged();

private:
	bool _pIsExpand{};
	qreal _pOpacity{};
	qreal _pSliderExtent{};
	CUVScrollBar* _pScrollBar{ nullptr };
	qreal _sliderMargin{2.5};
	int _scrollBarExtent{10};
};

inline void CUVScrollBarStyle::setOpacity(const qreal opacity) {
	_pOpacity = opacity;
}

inline qreal CUVScrollBarStyle::getOpacity() const {
	return _pOpacity;
}

inline void CUVScrollBarStyle::setSliderExtent(const qreal sliderExtent) {
	_pSliderExtent = sliderExtent;
}

inline qreal CUVScrollBarStyle::getSliderExtent() const {
	return _pSliderExtent;
}

inline void CUVScrollBarStyle::setIsExpand(const bool isExpand) {
	_pIsExpand = isExpand;
}

inline bool CUVScrollBarStyle::getIsExpand() const {
	return _pIsExpand;
}

inline void CUVScrollBarStyle::setScrollBar(CUVScrollBar* scrollBar) {
	_pScrollBar = scrollBar;
}

inline CUVScrollBar* CUVScrollBarStyle::getScrollBar() const {
	return _pScrollBar;
}
