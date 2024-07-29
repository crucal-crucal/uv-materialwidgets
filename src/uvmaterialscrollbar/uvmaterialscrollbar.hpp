#pragma once

#include <QtWidgets/QScrollBar>

class CUVMaterialScrollBarPrivate;

#ifdef CUVMATERIALSCROLLBAR_LIB
#define CUVMATERIALSCROLLBAR_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALSCROLLBAR_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALSCROLLBAR_EXPORT CUVMaterialScrollBar final : public QScrollBar {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialScrollBar)
	Q_DECLARE_PRIVATE(CUVMaterialScrollBar)

	Q_PROPERTY(QColor canvasColor WRITE setCanvasColor READ canvasColor)
	Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
	Q_PROPERTY(QColor sliderColor WRITE setSliderColor READ sliderColor)

public:
	explicit CUVMaterialScrollBar(QWidget* parent = nullptr);
	~CUVMaterialScrollBar() override;

	[[nodiscard]] QSize sizeHint() const override;

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setCanvasColor(const QColor& color);
	[[nodiscard]] QColor canvasColor() const;

	void setBackgroundColor(const QColor& color);
	[[nodiscard]] QColor backgroundColor() const;

	void setSliderColor(const QColor& color);
	[[nodiscard]] QColor sliderColor() const;

	void setHideOnMouseOut(bool value);
	[[nodiscard]] bool hideOnMouseOut() const;

protected:
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVMaterialScrollBarPrivate> d_ptr{ nullptr };
};
