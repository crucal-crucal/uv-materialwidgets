#pragma once

#include <QtWidgets/QProgressBar>

#include "uvshared/uvmaterialtheme.hpp"

class CUVMaterialCircularProgressPrivate;

#ifdef CUVMATERIALCIRCULARPROGRESS_LIB
#define CUVMATERIALCIRCULARPROGRESS_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALCIRCULARPROGRESS_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALCIRCULARPROGRESS_EXPORT CUVMaterialCircularProgress : public QProgressBar {
	Q_OBJECT

	Q_PROPERTY(qreal lineWidth WRITE setLineWidth READ lineWidth)
	Q_PROPERTY(int size WRITE setSize READ Size)
	Q_PROPERTY(QColor color WRITE setColor READ color)

public:
	explicit CUVMaterialCircularProgress(QWidget* parent = nullptr);
	~CUVMaterialCircularProgress() override;

	void setProgressType(Material::ProgressType type);
	[[nodiscard]] Material::ProgressType progressType() const;

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setLineWidth(qreal width);
	[[nodiscard]] qreal lineWidth() const;

	void setSize(int size);
	[[nodiscard]] int Size() const;

	void setColor(const QColor& color);
	[[nodiscard]] QColor color() const;

	[[nodiscard]] QSize sizeHint() const override;

protected:
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVMaterialCircularProgressPrivate> d_ptr{ nullptr };

private:
	Q_DISABLE_COPY(CUVMaterialCircularProgress)
	Q_DECLARE_PRIVATE(CUVMaterialCircularProgress)
};
