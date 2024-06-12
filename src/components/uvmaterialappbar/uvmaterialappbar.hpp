#pragma once

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

#ifdef CUVMATERIALAPPBAR_LIB
#define CUVMATERIALAPPBAR_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALAPPBAR_EXPORT Q_DECL_IMPORT
#endif

class CUVMaterialAppBarPrivate;

class CUVMATERIALAPPBAR_EXPORT CUVMaterialAppBar final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialAppBar)
	 Q_DECLARE_PRIVATE(CUVMaterialAppBar)
	//[[nodiscard]] inline CUVMaterialAppBarPrivate* d_func() { return reinterpret_cast<CUVMaterialAppBarPrivate*>(d_ptr.data()); }
	//[[nodiscard]] inline const CUVMaterialAppBarPrivate* d_func() const { return reinterpret_cast<const CUVMaterialAppBarPrivate*>(d_ptr.data()); }
	//friend class CUVMaterialAppBarPrivate;

	Q_PROPERTY(QColor foregroundColor WRITE setForegroundColor READ foregroundColor)
	Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)

public:
	explicit CUVMaterialAppBar(QWidget* parent = nullptr);
	~CUVMaterialAppBar() override;

	[[nodiscard]] QSize sizeHint() const override;

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setForegroundColor(const QColor& color);
	[[nodiscard]] QColor foregroundColor() const;

	void setBackgroundColor(const QColor& color);
	[[nodiscard]] QColor backgroundColor() const;

	[[nodiscard]] inline QHBoxLayout* appBarLayout() const;

protected:
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVMaterialAppBarPrivate> d_ptr{ nullptr };
};

inline QHBoxLayout* CUVMaterialAppBar::appBarLayout() const {
	return dynamic_cast<QHBoxLayout*>(layout());
}
