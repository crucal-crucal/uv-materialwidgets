#pragma once

#include <QPainter>
#include <QtGlobal>

class CUVSwitchButton;

class CUVSwitchButtonPrivate final : public QObject {
	Q_OBJECT

	Q_DISABLE_COPY(CUVSwitchButtonPrivate)
	Q_DECLARE_PUBLIC(CUVSwitchButton)

public:
	explicit CUVSwitchButtonPrivate(CUVSwitchButton* q);
	~CUVSwitchButtonPrivate() override;

public slots:
	void updateValue();

public:
	void init();
	void drawBackGround(QPainter* painter) const;
	void drawSlider(QPainter* painter) const;
	void drawText(QPainter* painter) const;
	[[nodiscard]] int getTextWidth() const;
	[[nodiscard]] QRect getBackgroundRect() const;
	[[nodiscard]] QPainterPath getBackgroundPath(const QRect& rect) const;
	[[nodiscard]] QRect getSliderRect() const;
	[[nodiscard]] QRect getTextRect(const CUVSwitchButton::TextPosition& position, bool isChecked) const;
	[[nodiscard]] std::pair<int, int> getEndXandStep(const CUVSwitchButton::TextPosition& position) const;

	CUVSwitchButton* const q_ptr{ nullptr };

	int spaceSlider{}; // 滑块距离边界距离
	int radius{};      // 圆角角度
	int spaceText{};   // 文字距离滑块的距离

	bool checked{};    // 是否选中
	bool showText{};   // 是否显示文字
	bool animation{};  // 是否使用动画

	QColor bgColorOn{};      // 打开时候的背景色
	QColor bgColorOff{};     // 关闭时候的背景色
	QColor sliderColorOn{};  // 打开时候滑块颜色
	QColor sliderColorOff{}; // 关闭时候滑块颜色
	QColor textColorOn{};    // 打开时候文字颜色
	QColor textColorOff{};   // 关闭时候文字颜色

	QString textOn{};  // 打开时候的文字
	QString textOff{}; // 关闭时候的文字
	int fontSize{};    // 文字大小
	bool fontBold{};   // 文字是否加粗

	QTimer* timer{ nullptr }; // 动画定时器
	int step{};               // 动画步长
	int startX{};             // 滑块开始X轴坐标
	int endX{};               // 滑块结束X轴坐标

	CUVSwitchButton::TextPosition textPostion{}; // 文字位置
};
