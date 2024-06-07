#pragma once

#include <QColor>
#include <QTimer>
#include <QWidget>

#ifdef CUVMATERIALWAITINGWIDGET_LIB
#define CUVMATERIALWAITINGWIDGET_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALWAITINGWIDGET_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALWAITINGWIDGET_EXPORT CUVMaterialWatingWidget final : public QWidget {
	Q_OBJECT

public:
	enum TextPosition {
		Top,
		Bottom
	};
	explicit CUVMaterialWatingWidget(QWidget* parent = nullptr, bool centerOnParent = true, bool disableParentWhenSpinning = true);

	explicit CUVMaterialWatingWidget(Qt::WindowModality modality, QWidget* parent = nullptr, bool centerOnParent = true,
	                                 bool disableParentWhenSpinning = true);

public slots:
	void start();
	void stop();

public:
	/**
	 * 设置颜色，不包括字体颜色
	 * @param color 颜色
	 */
	void setColor(const QColor& color);
	/**
	 * 设置圆度
	 * @param roundness 圆度 [ 0.0, 100.0 ]
	 */
	void setRoundness(qreal roundness);
	/**
	 * 设置旋转动画中线条的最小不透明度
	 * @param minimumTrailOpacity 旋转动画中线条的最小不透明度 [ 0.0, 1.0 ]
	 */
	void setMinimumTrailOpacity(qreal minimumTrailOpacity);
	/**
	 * 设置线条逐渐消失的百分比
	 * @param trail 线条逐渐消失的百分比 [ 0.0, 100.0 ]
	 */
	void setTrailFadePercentage(qreal trail);
	/**
	 * 设置旋转动画的速度，即每秒旋转的圈数
	 * @param revolutionsPerSecond 旋转动画的速度 (seconds)
	 */
	void setRevolutionsPerSecond(qreal revolutionsPerSecond);
	/**
	 * 设置旋转动画中线条的数量
	 * @param lines 旋转动画中线条的数量
	 */
	void setNumberOfLines(int lines);
	/**
	 * 设置旋转动画中线条的长度
	 * @param length 旋转动画中线条的长度
	 */
	void setLineLength(int length);
	/**
	 * 设置旋转动画中线条的宽度
	 * @param width 旋转动画中线条的宽度
	 */
	void setLineWidth(int width);
	/**
	 * 设置旋转动画中线条的内半径
	 * @param radius 旋转动画中线条的内半径
	 */
	void setInnerRadius(int radius);
	/**
	 * 设置显示在等待指示器下方的文本内容
	 * @param text 要显示的文本内容
	 */
	void setText(const QString& text);
	/**
	 * 设置显示文本的颜色
	 * @param color 文本的颜色
	 */
	void setTextColor(const QColor& color);
	/**
	 * 设置显示文本的字体大小
	 * @param size 文本的字体大小
	 */
	void setFontSize(int size);
	/**
	 * 设置显示文本的位置
	 * @param position see TextPosition
	 */
	void setTextPosition(const TextPosition& position);

	[[nodiscard]] QColor color();
	[[nodiscard]] qreal roundness() const;
	[[nodiscard]] qreal minimumTrailOpacity() const;
	[[nodiscard]] qreal trailFadePercentage() const;
	[[nodiscard]] qreal revolutionsPersSecond() const;
	[[nodiscard]] int numberOfLines() const;
	[[nodiscard]] int lineLength() const;
	[[nodiscard]] int lineWidth() const;
	[[nodiscard]] int innerRadius() const;
	[[nodiscard]] QString text() const;
	[[nodiscard]] QColor textColor() const;
	[[nodiscard]] int fontSize() const;
	[[nodiscard]] bool isSpinning() const;
	[[nodiscard]] TextPosition textPosition() const;

private slots:
	void rotate();

protected:
	void paintEvent(QPaintEvent* paintEvent) override;

private:
	static int lineCountDistanceFromPrimary(int current, int primary, int totalNrOfLines);
	static QColor currentLineColor(int distance, int totalNrOfLines, qreal trailFadePerc, qreal minOpacity, QColor color);

	void initialize();
	void updateSize();
	void updateTimer() const;
	void updatePosition();

private:
	QColor m_color{};
	QString m_text{};
	QColor m_textColor{};
	int m_textHeight{};
	int m_textWidth{};
	int m_fontSize{};
	TextPosition m_textPosition{};
	qreal m_roundness{}; // 0..100
	qreal m_minimumTrailOpacity{};
	qreal m_trailFadePercentage{};
	qreal m_revolutionsPerSecond{};
	int m_numberOfLines{};
	int m_lineLength{};
	int m_lineWidth{};
	int m_innerRadius{};

private:
	Q_DISABLE_COPY(CUVMaterialWatingWidget)

	QTimer* m_timer{ nullptr };
	bool m_centerOnParent{};
	bool m_disableParentWhenSpinning{};
	int m_currentCounter{};
	bool m_isSpinning{};
};
