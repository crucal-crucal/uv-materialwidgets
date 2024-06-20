#pragma once

#include <QtWidgets/QAbstractButton>

class CUVMaterialIconButtonPrivate;

#ifdef CUVMATERIALICONBUTTON_LIB
#define CUVMATERIALICONBUTTON_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALICONBUTTON_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALICONBUTTON_EXPORT CUVMaterialIconButton final : public QAbstractButton {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialIconButton)
	Q_DECLARE_PRIVATE(CUVMaterialIconButton)

public:
	explicit CUVMaterialIconButton(const QIcon& icon, QWidget* parent = nullptr);
	~CUVMaterialIconButton() override;

	[[nodiscard]] QSize sizeHint() const override;

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setColor(const QColor& color);
	[[nodiscard]] QColor color() const;

	void setDisabledColor(const QColor& color);
	[[nodiscard]] QColor disabledColor() const;

protected:
	explicit CUVMaterialIconButton(CUVMaterialIconButtonPrivate& d, QWidget* parent = nullptr);

	bool event(QEvent* event) override;
	bool eventFilter(QObject* watched, QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVMaterialIconButtonPrivate> d_ptr{ nullptr };
};
