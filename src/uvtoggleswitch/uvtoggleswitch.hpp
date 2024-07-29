#pragma once

#include <QWidget>

class CUVToggleSwitchPrivate;

#ifdef CUVTOGGLESWITCH_LIB
#define CUVTOGGLESWITCH_EXPORT Q_DECL_EXPORT
#else
#define CUVTOGGLESWITCH_EXPORT Q_DECL_IMPORT
#endif

class CUVTOGGLESWITCH_EXPORT CUVToggleSwitch final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVToggleSwitch)
	Q_DECLARE_PRIVATE(CUVToggleSwitch)

public:
	explicit CUVToggleSwitch(QWidget* parent = nullptr);
	~CUVToggleSwitch() override;

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

	void setFontSize(int size);
	[[nodiscard]] int fontSize() const;

	void setOnTextColor(const QColor& color);
	[[nodiscard]] QColor onTextColor() const;

	void setOffTextColor(const QColor& color);
	[[nodiscard]] QColor offTextColor() const;

	void setOffCircleColor(const QColor& color);
	[[nodiscard]] QColor circleOffColor() const;

	void setOnCircleColor(const QColor& color);
	[[nodiscard]] QColor circleOnColor() const;

	void setOffBackgroundColor(const QColor& color);
	[[nodiscard]] QColor backgroundOffColor() const;

	void setOnBackgroundColor(const QColor& color);
	[[nodiscard]] QColor backgroundOnColor() const;

signals:
	void clicked(bool checked);

protected:
	bool event(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVToggleSwitchPrivate> d_ptr{ nullptr };
};
