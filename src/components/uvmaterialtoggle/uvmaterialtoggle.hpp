#pragma once

#include <QtWidgets/QAbstractButton>

class CUVMaterialTogglePrivate;

#ifdef CUVMATERIALTOGGLE_LIB
#define CUVMATERIALTOGGLE_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALTOGGLE_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALTOGGLE_EXPORT CUVMaterialToggle final : public QAbstractButton {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialToggle)
	Q_DECLARE_PRIVATE(CUVMaterialToggle)

	Q_PROPERTY(QColor disabledColor WRITE setDisabledColor READ disabledColor)
	Q_PROPERTY(QColor activeColor WRITE setActiveColor READ activeColor)
	Q_PROPERTY(QColor inactiveColor WRITE setInactiveColor READ inactiveColor)
	Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)

public:
	explicit CUVMaterialToggle(QWidget* parent = nullptr);
	~CUVMaterialToggle() override;

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setDisabledColor(const QColor& color);
	[[nodiscard]] QColor disabledColor() const;

	void setActiveColor(const QColor& color);
	[[nodiscard]] QColor activeColor() const;

	void setInactiveColor(const QColor& color);
	[[nodiscard]] QColor inactiveColor() const;

	void setTrackColor(const QColor& color);
	[[nodiscard]] QColor trackColor() const;

	void setOrientation(Qt::Orientation orientation);
	[[nodiscard]] Qt::Orientation orientation() const;

	[[nodiscard]] QSize sizeHint() const override;

protected:
	bool event(QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVMaterialTogglePrivate> d_ptr{ nullptr };
};
