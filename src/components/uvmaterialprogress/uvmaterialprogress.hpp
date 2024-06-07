#pragma once

#include <QtWidgets/QProgressBar>

#include "uvshared/uvmaterialtheme.hpp"

class CUVMaterialProgressPrivate;

#ifdef CUVMATERIALPROGRESS_LIB
#define CUVMATERIALPROGRESS_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALPROGRESS_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALPROGRESS_EXPORT CUVMaterialProgress final : public QProgressBar {
	Q_OBJECT

	Q_PROPERTY(QColor progressColor WRITE setProgressColor READ progressColor)
	Q_PROPERTY(QColor backgroundColor WRITE setProgressColor READ backgroundColor)

public:
	explicit CUVMaterialProgress(QWidget* parent = nullptr);
	~CUVMaterialProgress() override;

	void setProgressType(Material::ProgressType type);
	[[nodiscard]] Material::ProgressType progressType() const;

	void setUseThemeColors(bool state);
	[[nodiscard]] bool useThemeColors() const;

	void setProgressColor(const QColor& color);
	[[nodiscard]] QColor progressColor() const;

	void setBackgroundColor(const QColor& color);
	[[nodiscard]] QColor backgroundColor() const;

protected:
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVMaterialProgressPrivate> d_ptr{ nullptr };

private:
	Q_DISABLE_COPY(CUVMaterialProgress)
	Q_DECLARE_PRIVATE(CUVMaterialProgress)
};
