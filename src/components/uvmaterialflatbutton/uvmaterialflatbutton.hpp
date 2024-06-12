#pragma once

#include <QtWidgets/QPushButton>

#include "uvshared/uvmaterialtheme.hpp"

class CUVMaterialFlatButtonPrivate;

#ifdef CUVMATERIALFLATBUTTON_LIB
#define CUVMATERIALFLATBUTTON_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALFLATBUTTON_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALFLATBUTTON_EXPORT CUVMaterialFlatButton : public QPushButton {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialFlatButton)
	Q_DECLARE_PRIVATE(CUVMaterialFlatButton)

	Q_PROPERTY(QColor foregroundColor WRITE setForegroundColor READ foregroundColor)
	Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
	Q_PROPERTY(QColor overlayColor WRITE setOverlayColor READ overlayColor)
	Q_PROPERTY(QColor disabledForegroundColor WRITE setDisabledForegroundColor READ disabledForegroundColor)
	Q_PROPERTY(QColor disabledBackgroundColor WRITE setDisabledBackgroundColor READ disabledBackgroundColor)
	Q_PROPERTY(qreal fontSize WRITE setFontSize READ fontSize)

public:
	explicit CUVMaterialFlatButton(QWidget* parent = nullptr, Material::ButtonPreset preset = Material::FlatPreset);
	explicit CUVMaterialFlatButton(const QString& text, QWidget* parent = nullptr, Material::ButtonPreset preset = Material::FlatPreset);
	CUVMaterialFlatButton(const QString& text, Material::Role role, QWidget* parent = nullptr, Material::ButtonPreset preset = Material::FlatPreset);
	~CUVMaterialFlatButton() override;

	void applyPreset(Material::ButtonPreset preset);

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setRole(Material::Role role);
	[[nodiscard]] Material::Role role() const;

	void setForegroundColor(const QColor& color);
	[[nodiscard]] QColor foregroundColor() const;

	void setBackgroundColor(const QColor& color);
	[[nodiscard]] QColor backgroundColor() const;

	void setOverlayColor(const QColor& color);
	[[nodiscard]] QColor overlayColor() const;

	void setDisabledForegroundColor(const QColor& color);
	[[nodiscard]] QColor disabledForegroundColor() const;

	void setDisabledBackgroundColor(const QColor& color);
	[[nodiscard]] QColor disabledBackgroundColor() const;

	void setFontSize(qreal size);
	[[nodiscard]] qreal fontSize() const;

	void setHaloVisible(bool visible);
	[[nodiscard]] bool isHaloVisible() const;

	void setOverlayStyle(Material::OverlayStyle style);
	[[nodiscard]] Material::OverlayStyle overlayStyle() const;

	void setRippleStyle(Material::RippleStyle style);
	[[nodiscard]] Material::RippleStyle rippleStyle() const;

	void setIconPlacement(Material::ButtonIconPlacement placement);
	[[nodiscard]] Material::ButtonIconPlacement iconPlacement() const;

	void setCornerRadius(qreal radius);
	[[nodiscard]] qreal cornerRadius() const;

	void setBackgroundMode(Qt::BGMode mode);
	[[nodiscard]] Qt::BGMode backgroundMode() const;

	void setBaseOpacity(qreal opacity);
	[[nodiscard]] qreal baseOpacity() const;

	void setCheckable(bool value); // NOLINT

	void setHasFixedRippleRadius(bool value);
	[[nodiscard]] bool hasFixedRippleRadius() const;

	void setFixedRippleRadius(qreal radius);

	void setTextAlignment(Qt::Alignment alignment);
	[[nodiscard]] Qt::Alignment textAlignment() const;

	[[nodiscard]] QSize sizeHint() const override;

protected:
	enum {
		IconPadding = 12
	};

	explicit CUVMaterialFlatButton(CUVMaterialFlatButtonPrivate& d, QWidget* parent = nullptr, Material::ButtonPreset preset = Material::FlatPreset);

	void checkStateSet() override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

	virtual void paintBackground(QPainter* painter);
	virtual void paintHalo(QPainter* painter);
	virtual void paintForeground(QPainter* painter);

	virtual void updateClipPath();

	const QScopedPointer<CUVMaterialFlatButtonPrivate> d_ptr{ nullptr };
};
