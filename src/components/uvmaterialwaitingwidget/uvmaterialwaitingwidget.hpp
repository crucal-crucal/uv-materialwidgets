#pragma once

#include <QColor>
#include <QTimer>
#include <QWidget>

#ifdef CUVMATERIALWAITINGWIDGET_LIB
#define CUVMATERIALWAITINGWIDGET_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALWAITINGWIDGET_EXPORT Q_DECL_IMPORT
#endif

class CUVMaterialWatingWidgetPrivate;

class CUVMATERIALWAITINGWIDGET_EXPORT CUVMaterialWatingWidget final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialWatingWidget)
	Q_DECLARE_PRIVATE(CUVMaterialWatingWidget)

	Q_PROPERTY(QColor color WRITE setColor READ color)
	Q_PROPERTY(qreal roundness WRITE setRoundness READ roundness)
	Q_PROPERTY(qreal minimumTrailOpacity WRITE setMinimumTrailOpacity READ minimumTrailOpacity)
	Q_PROPERTY(qreal trailFadePercentage WRITE setTrailFadePercentage READ trailFadePercentage)
	Q_PROPERTY(qreal revolutionsPersSecond WRITE setRevolutionsPerSecond READ revolutionsPersSecond)
	Q_PROPERTY(int numberOfLines WRITE setNumberOfLines READ numberOfLines)
	Q_PROPERTY(int lineLength WRITE setLineLength READ lineLength)
	Q_PROPERTY(int lineWidth WRITE setLineWidth READ lineWidth)
	Q_PROPERTY(int innerRadius WRITE setInnerRadius READ innerRadius)
	Q_PROPERTY(QString text WRITE setText READ text)
	Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
	Q_PROPERTY(int fontSize WRITE setFontSize READ fontSize)
	Q_PROPERTY(TextPosition textPosition WRITE setTextPosition READ textPosition)

public:
	enum TextPosition {
		Top    = 0x00000000,
		Bottom = 0x0000001,
	};
	Q_ENUM(TextPosition)

	explicit CUVMaterialWatingWidget(QWidget* parent = nullptr, bool centerOnParent = true, bool disableParentWhenSpinning = true);

	explicit CUVMaterialWatingWidget(Qt::WindowModality modality, QWidget* parent = nullptr, bool centerOnParent = true,
	                                 bool disableParentWhenSpinning = true);

	~CUVMaterialWatingWidget() override;

public slots:
	void start();
	void stop();

public:
	/**
	 * 设置颜色，不包括字体颜色
	 * @param color 颜色
	 */
	void setColor(const QColor& color);
	[[nodiscard]] QColor color();
	/**
	 * 设置圆度
	 * @param roundness 圆度 [ 0.0, 100.0 ]
	 */
	void setRoundness(qreal roundness);
	[[nodiscard]] qreal roundness() const;
	/**
	 * 设置旋转动画中线条的最小不透明度
	 * @param minimumTrailOpacity 旋转动画中线条的最小不透明度 [ 0.0, 1.0 ]
	 */
	void setMinimumTrailOpacity(qreal minimumTrailOpacity);
	[[nodiscard]] qreal minimumTrailOpacity() const;
	/**
	 * 设置线条逐渐消失的百分比
	 * @param trail 线条逐渐消失的百分比 [ 0.0, 100.0 ]
	 */
	void setTrailFadePercentage(qreal trail);
	[[nodiscard]] qreal trailFadePercentage() const;
	/**
	 * 设置旋转动画的速度，即每秒旋转的圈数
	 * @param revolutionsPerSecond 旋转动画的速度 (seconds)
	 */
	void setRevolutionsPerSecond(qreal revolutionsPerSecond);
	[[nodiscard]] qreal revolutionsPersSecond() const;
	/**
	 * 设置旋转动画中线条的数量
	 * @param lines 旋转动画中线条的数量
	 */
	void setNumberOfLines(int lines);
	[[nodiscard]] int numberOfLines() const;
	/**
	 * 设置旋转动画中线条的长度
	 * @param length 旋转动画中线条的长度
	 */
	void setLineLength(int length);
	[[nodiscard]] int lineLength() const;
	/**
	 * 设置旋转动画中线条的宽度
	 * @param width 旋转动画中线条的宽度
	 */
	void setLineWidth(int width);
	[[nodiscard]] int lineWidth() const;
	/**
	 * 设置旋转动画中线条的内半径
	 * @param radius 旋转动画中线条的内半径
	 */
	void setInnerRadius(int radius);
	[[nodiscard]] int innerRadius() const;
	/**
	 * 设置显示在等待指示器下方的文本内容
	 * @param text 要显示的文本内容
	 */
	void setText(const QString& text);
	[[nodiscard]] QString text() const;
	/**
	 * 设置显示文本的颜色
	 * @param color 文本的颜色
	 */
	void setTextColor(const QColor& color);
	[[nodiscard]] QColor textColor() const;
	/**
	 * 设置显示文本的字体大小
	 * @param size 文本的字体大小
	 */
	void setFontSize(int size);
	[[nodiscard]] int fontSize() const;
	/**
	 * 设置显示文本的位置
	 * @param position see TextPosition
	 */
	void setTextPosition(const TextPosition& position);
	[[nodiscard]] TextPosition textPosition() const;

	[[nodiscard]] bool isSpinning() const;

protected:
	void paintEvent(QPaintEvent* paintEvent) override;

	const QScopedPointer<CUVMaterialWatingWidgetPrivate> d_ptr{ nullptr };
};
