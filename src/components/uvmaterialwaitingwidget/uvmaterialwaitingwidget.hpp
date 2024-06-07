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
	 * ������ɫ��������������ɫ
	 * @param color ��ɫ
	 */
	void setColor(const QColor& color);
	/**
	 * ����Բ��
	 * @param roundness Բ�� [ 0.0, 100.0 ]
	 */
	void setRoundness(qreal roundness);
	/**
	 * ������ת��������������С��͸����
	 * @param minimumTrailOpacity ��ת��������������С��͸���� [ 0.0, 1.0 ]
	 */
	void setMinimumTrailOpacity(qreal minimumTrailOpacity);
	/**
	 * ������������ʧ�İٷֱ�
	 * @param trail ��������ʧ�İٷֱ� [ 0.0, 100.0 ]
	 */
	void setTrailFadePercentage(qreal trail);
	/**
	 * ������ת�������ٶȣ���ÿ����ת��Ȧ��
	 * @param revolutionsPerSecond ��ת�������ٶ� (seconds)
	 */
	void setRevolutionsPerSecond(qreal revolutionsPerSecond);
	/**
	 * ������ת����������������
	 * @param lines ��ת����������������
	 */
	void setNumberOfLines(int lines);
	/**
	 * ������ת�����������ĳ���
	 * @param length ��ת�����������ĳ���
	 */
	void setLineLength(int length);
	/**
	 * ������ת�����������Ŀ��
	 * @param width ��ת�����������Ŀ��
	 */
	void setLineWidth(int width);
	/**
	 * ������ת�������������ڰ뾶
	 * @param radius ��ת�������������ڰ뾶
	 */
	void setInnerRadius(int radius);
	/**
	 * ������ʾ�ڵȴ�ָʾ���·����ı�����
	 * @param text Ҫ��ʾ���ı�����
	 */
	void setText(const QString& text);
	/**
	 * ������ʾ�ı�����ɫ
	 * @param color �ı�����ɫ
	 */
	void setTextColor(const QColor& color);
	/**
	 * ������ʾ�ı��������С
	 * @param size �ı��������С
	 */
	void setFontSize(int size);
	/**
	 * ������ʾ�ı���λ��
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
