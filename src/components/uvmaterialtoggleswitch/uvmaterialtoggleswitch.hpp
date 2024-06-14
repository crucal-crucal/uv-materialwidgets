#pragma once

#include <QPushButton>

class CUVMaterialToggleSwitchPrivate;

#ifdef CUVMATERIALTOGGLESWITCH_LIB
#define CUVMATERIALTOGGLESWITCH_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALTOGGLESWITCH_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALTOGGLESWITCH_EXPORT CUVMaterialToggleSwitch final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialToggleSwitch)
	Q_DECLARE_PRIVATE(CUVMaterialToggleSwitch)

public:
	explicit CUVMaterialToggleSwitch(QWidget* parent = nullptr);
	~CUVMaterialToggleSwitch() override;

	void setChecked(bool checked);
	[[nodiscard]] bool isChecked() const;

	void setShowText(bool showText);
	[[nodiscard]] bool showText() const;

	void setOnText(const QString& text);
	[[nodiscard]] QString onText() const;

	void setOffText(const QString& text);
	[[nodiscard]] QString offText() const;

	void setTextBold(bool bold);
	[[nodiscard]] bool textBold() const;

	void setOnTextColor(const QColor& color);
	[[nodiscard]] QColor onTextColor() const;

	void setOffTextColor(const QColor& color);
	[[nodiscard]] QColor offTextColor() const;

	void setcircleOffColor(const QColor& color);
	[[nodiscard]] QColor circleOffColor() const;

	void setcircleOnColor(const QColor& color);
	[[nodiscard]] QColor circleOnColor() const;

	void setbackgroundOffColor(const QColor& color);
	[[nodiscard]] QColor backgroundOffColor() const;

	void setbackgroundOnColor(const QColor& color);
	[[nodiscard]] QColor backgroundOnColor() const;

signals:
	void clicked(bool checked);

protected:
	bool event(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVMaterialToggleSwitchPrivate> d_ptr{ nullptr };
};
