#pragma once
#include <QColor>
#include <QWidget>

#ifdef CUVMATERIALSWITCHBTN_LIB
#define CUVMATERIALSWITCHBTN_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALSWITCHBTN_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALSWITCHBTN_EXPORT CUVSwitchButton final : public QWidget {
	Q_OBJECT

public:
	enum class TextPosition {
		Center = 0x00000000,
		Right  = 0x00000001,
		Left   = 0x00000002,
	};
	explicit CUVSwitchButton(QWidget* parent = nullptr);
	~CUVSwitchButton() override = default;

	[[nodiscard]] bool status() const; // 当前状态

	[[nodiscard]] TextPosition textPosition() const; // 文字位置
	[[nodiscard]] int spaceSlider() const;           // 滑块距离边界距离
	[[nodiscard]] int spaceText() const;             // 文字距离滑块右边界距离
	[[nodiscard]] int radius() const;                // 圆角角度
	[[nodiscard]] bool checked() const;              // 是否选中
	[[nodiscard]] bool showText() const;             // 是否显示文字
	[[nodiscard]] bool showCircel() const;           // 是否显示圆圈
	[[nodiscard]] bool animation() const;            // 是否使用动画

	[[nodiscard]] QColor bgColorOn() const;      // 打开时候的背景色
	[[nodiscard]] QColor bgColorOff() const;     // 关闭时候的背景色
	[[nodiscard]] QColor sliderColorOn() const;  // 打开时候滑块颜色
	[[nodiscard]] QColor sliderColorOff() const; // 关闭时候滑块颜色
	[[nodiscard]] QColor textColorOn() const;    // 打开时候文字颜色
	[[nodiscard]] QColor textColorOff() const;   // 关闭时候文字颜色

	[[nodiscard]] QString textOn() const;  // 打开时候的文字
	[[nodiscard]] QString textOff() const; // 关闭时候的文字

	[[nodiscard]] int step() const;   // 动画步长
	[[nodiscard]] int startX() const; // 滑块开始X轴坐标
	[[nodiscard]] int endX() const;   // 滑块结束X轴坐标

public Q_SLOTS:
	void setSpaceSlider(int space);
	void setSpaceText(int space);
	void setRadius(int radius);
	void setChecked(bool checked);
	void setShowText(bool show);
	void setShowCircle(bool show);
	void setAnimation(bool ok);

	void setBgColorOn(const QColor& color);
	void setBgColorOff(const QColor& color);
	void setSliderColorOn(const QColor& color);
	void setSliderColorOff(const QColor& color);
	void setTextColorOn(const QColor& color);
	void setTextColorOff(const QColor& color);

	void setTextOn(const QString& text);
	void setTextOff(const QString& text);

	void setTextShowInBtn(bool show);

	void setTextPosition(const CUVSwitchButton::TextPosition& position);

signals:
	void statusChanged(bool checked);

private slots:
	void updateValue();

private:
	void init();
	void drawBackGround(QPainter* painter) const;
	void drawSlider(QPainter* painter) const;
	void drawText(QPainter* painter) const;
	[[nodiscard]] inline int getTextWidth() const;
	[[nodiscard]] QRect getBackgroundRect() const;
	[[nodiscard]] QPainterPath getBackgroundPath(const QRect& rect) const;
	[[nodiscard]] QRect getSliderRect() const;
	[[nodiscard]] QRect getTextRect(const TextPosition& position, bool isChecked) const;
	[[nodiscard]] std::pair<int, int> getEndXandStep(const TextPosition& position) const;

protected:
	void paintEvent(QPaintEvent* ev) override;
	void mousePressEvent(QMouseEvent* ev) override;

private:
	int m_spaceSlider{}; // 滑块距离边界距离
	int m_radius{};      // 圆角角度
	int m_spaceText{};   // 文字距离滑块的距离

	bool m_checked{};    // 是否选中
	bool m_showText{};   // 是否显示文字
	bool m_showCircle{}; // 是否显示圆圈
	bool m_animation{};  // 是否使用动画

	QColor m_bgColorOn{};      // 打开时候的背景色
	QColor m_bgColorOff{};     // 关闭时候的背景色
	QColor m_sliderColorOn{};  // 打开时候滑块颜色
	QColor m_sliderColorOff{}; // 关闭时候滑块颜色
	QColor m_textColorOn{};    // 打开时候文字颜色
	QColor m_textColorOff{};   // 关闭时候文字颜色

	QString m_textOn{};  // 打开时候的文字
	QString m_textOff{}; // 关闭时候的文字

	QTimer* m_timer{ nullptr }; // 动画定时器
	int m_step{};               // 动画步长
	int m_startX{};             // 滑块开始X轴坐标
	int m_endX{};               // 滑块结束X轴坐标

	bool m_showInCenter{ false }; // 显示在按钮中心
	TextPosition m_textPostion{}; // 文字位置
};
