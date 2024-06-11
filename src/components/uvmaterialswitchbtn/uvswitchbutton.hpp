#pragma once

#include <QColor>
#include <QWidget>

#ifdef CUVMATERIALSWITCHBTN_LIB
#define CUVMATERIALSWITCHBTN_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALSWITCHBTN_EXPORT Q_DECL_IMPORT
#endif

class CUVSwitchButtonPrivate;

class CUVMATERIALSWITCHBTN_EXPORT CUVSwitchButton final : public QWidget {
	Q_OBJECT
	Q_DECLARE_PRIVATE(CUVSwitchButton)

	Q_PROPERTY(bool isChecked WRITE setChecked READ isChecked)
	Q_PROPERTY(bool showText WRITE setShowText READ showText)
	Q_PROPERTY(bool fontBold WRITE setFontBold READ fontBold)
	Q_PROPERTY(bool showAnimation WRITE setShowAnimation READ showAnimation)
	Q_PROPERTY(int spaceSlider WRITE setSpaceSlider READ spaceSlider)
	Q_PROPERTY(int spaceText WRITE setSpaceText READ spaceText)
	Q_PROPERTY(int radius WRITE setRadius READ radius)
	Q_PROPERTY(int fontSize WRITE setFontSize READ fontSize)
	Q_PROPERTY(QColor bgColorOn WRITE setBgColorOn READ bgColorOn)
	Q_PROPERTY(QColor bgColorOff WRITE setBgColorOff READ bgColorOff)
	Q_PROPERTY(QColor sliderColorOn WRITE setSliderColorOn READ sliderColorOn)
	Q_PROPERTY(QColor sliderColorOff WRITE setSliderColorOff READ sliderColorOff)
	Q_PROPERTY(QColor textColorOn WRITE setTextColorOn READ textColorOn)
	Q_PROPERTY(QColor textColorOff WRITE setTextColorOff READ textColorOff)
	Q_PROPERTY(QString textOn WRITE setTextOn READ textOn)
	Q_PROPERTY(QString textOff WRITE setTextOff READ textOff)
	Q_PROPERTY(CUVSwitchButton::TextPosition textPosition WRITE setTextPosition READ textPosition)

public:
	enum TextPosition {
		Center = 0x00000000,
		Right  = 0x00000001,
		Left   = 0x00000002,
	};
	Q_ENUM(TextPosition)

	explicit CUVSwitchButton(QWidget* parent = nullptr);
	~CUVSwitchButton() override;

	/**
	 * 设置当前状态, 默认为 false
	 * @param checked true 开启 false 关闭
	 */
	void setChecked(bool checked);
	[[nodiscard]] bool isChecked() const;

	/**
	 * see CUVSwitchButton::TextPosition
	 * @param position 文字位置
	 */
	void setTextPosition(const CUVSwitchButton::TextPosition& position);
	[[nodiscard]] TextPosition textPosition() const;

	/**
	 * 设置滑块距离边界距离, 默认为 2
	 * @param spaceslider 滑块距离边界距离
	 */
	void setSpaceSlider(int spaceslider);
	[[nodiscard]] int spaceSlider() const;

	/**
	 * 设置文字距离滑块右边界距离, 默认为 15
	 * @param spacetext 文字距离滑块右边界距离
	 */
	void setSpaceText(int spacetext);
	[[nodiscard]] int spaceText() const;

	/**
	 * 设置圆角角度, 默认为 5
	 * @param radius 圆角角度
	 */
	void setRadius(int radius);
	[[nodiscard]] int radius() const;

	/**
	 * 设置是否显示文字, 默认为 true
	 * @param showtext 是否显示文字
	 */
	void setShowText(bool showtext);
	[[nodiscard]] bool showText() const;

	/**
	 * 设置是否使用动画, 默认为 true
	 * @param showanimation 是否使用动画
	 */
	void setShowAnimation(bool showanimation);
	[[nodiscard]] bool showAnimation() const;

	/**
	 * 设置打开时候的背景色, 默认为 qRgb(82, 164, 255);
	 * @param color 打开时候的背景色
	 */
	void setBgColorOn(const QColor& color);
	[[nodiscard]] QColor bgColorOn() const;

	/**
	 * 设置关闭时候的背景色, 默认为 qRgb(170, 170, 170);
	 * @param color 关闭时候的背景色
	 */
	void setBgColorOff(const QColor& color);
	[[nodiscard]] QColor bgColorOff() const;

	/**
	 * 设置打开时候滑块颜色, 默认为 Qt::white;
	 * @param color 打开时候滑块颜色
	 */
	void setSliderColorOn(const QColor& color);
	[[nodiscard]] QColor sliderColorOn() const;

	/**
	 * 设置关闭时候滑块颜色, 默认为 Qt::white;
	 * @param color 关闭时候滑块颜色
	 */
	void setSliderColorOff(const QColor& color);
	[[nodiscard]] QColor sliderColorOff() const;

	/**
	 * 设置打开时候文字颜色, 默认为 qRgb(51, 145, 255);
	 * @param color 打开时候文字颜色
	 */
	void setTextColorOn(const QColor& color);
	[[nodiscard]] QColor textColorOn() const;

	/**
	 * 设置关闭时候文字颜色, 默认为 qRgb(91, 91, 91);
	 * @param color 关闭时候文字颜色
	 */
	void setTextColorOff(const QColor& color);
	[[nodiscard]] QColor textColorOff() const;

	/**
	 * 打开时候的文字设置, 默认为 tr("Open")
	 * @param text 打开时候的文字
	 */
	void setTextOn(const QString& text);
	[[nodiscard]] QString textOn() const;

	/**
	 * 设置关闭时候的文字, 默认为 tr("Close")
	 * @param text 关闭时候的文字
	 */
	void setTextOff(const QString& text);
	[[nodiscard]] QString textOff() const;

	/**
	 * 设置文字字体大小, 默认为 10
	 * @param fontsize 文字字体大小
	 */
	void setFontSize(int fontsize);
	[[nodiscard]] int fontSize() const;

	/**
	 * 设置字体加粗, 默认不加粗
	 * @param fontbold true 加粗; false 不加粗
	 */
	void setFontBold(bool fontbold);
	[[nodiscard]] bool fontBold() const;

	[[nodiscard]] int step() const;   // 动画步长
	[[nodiscard]] int startX() const; // 滑块开始X轴坐标
	[[nodiscard]] int endX() const;   // 滑块结束X轴坐标

signals:
	void statusChanged(bool checked);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

	const QScopedPointer<CUVSwitchButtonPrivate> d_ptr{ nullptr };

private:
	Q_DISABLE_COPY(CUVSwitchButton)
};
