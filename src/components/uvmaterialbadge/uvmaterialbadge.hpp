#pragma once

#include "uvshared/uvmaterialoverlaywidget.hpp"

class CUVMaterialBadgePrivate;

#ifdef CUVMATERIALBADGE_LIB
#define CUVMATERIALBADGE_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALBADGE_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALBADGE_EXPORT CUVMaterialBadge final : public CUVMaterialOverlayWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialBadge)
	Q_DECLARE_PRIVATE(CUVMaterialBadge)

	Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
	Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
	Q_PROPERTY(QPointF relativePosition WRITE setRelativePosition READ relativePosition)

public:
	explicit CUVMaterialBadge(QWidget* parent = nullptr);
	explicit CUVMaterialBadge(const QIcon& icon, QWidget* parent = nullptr);
	explicit CUVMaterialBadge(const QString& text, QWidget* parent = nullptr);
	~CUVMaterialBadge() override;

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setTextColor(const QColor& color);
	[[nodiscard]] QColor textColor() const;

	void setBackgroundColor(const QColor& color);
	[[nodiscard]] QColor backgroundColor() const;

	void setRelativePosition(const QPointF& pos);
	void setRelativePosition(qreal x, qreal y);
	[[nodiscard]] QPointF relativePosition() const;

	void setRelativeXPosition(qreal x);
	[[nodiscard]] qreal relativeXPosition() const;

	void setRelativeYPosition(qreal y);
	[[nodiscard]] qreal relativeYPosition() const;

	[[nodiscard]] QSize sizeHint() const override;

	void setIcon(const QIcon& icon);
	[[nodiscard]] QIcon icon() const;

	void setText(const QString& text);
	[[nodiscard]] QString text() const;

protected:
	void paintEvent(QPaintEvent* event) override;

	[[nodiscard]] int getDiameter() const;

	const QScopedPointer<CUVMaterialBadgePrivate> d_ptr{ nullptr };
};
