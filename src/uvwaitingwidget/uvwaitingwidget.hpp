#pragma once

#include <QColor>
#include <QTimer>
#include <QWidget>

#ifdef CUVWAITINGWIDGET_LIB
#define CUVWAITINGWIDGET_EXPORT Q_DECL_EXPORT
#else
#define CUVWAITINGWIDGET_EXPORT Q_DECL_IMPORT
#endif

class CUVWatingWidgetPrivate;

class CUVWAITINGWIDGET_EXPORT CUVWatingWidget final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVWatingWidget)
	Q_DECLARE_PRIVATE(CUVWatingWidget)

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

	explicit CUVWatingWidget(QWidget* parent = nullptr, bool centerOnParent = true, bool disableParentWhenSpinning = true);

	explicit CUVWatingWidget(Qt::WindowModality modality, QWidget* parent = nullptr, bool centerOnParent = true,
	                                 bool disableParentWhenSpinning = true);

	~CUVWatingWidget() override;

public slots:
	void start();
	void stop();

public:
	/**
	 * ������ɫ��������������ɫ
	 * @param color ��ɫ
	 */
	void setColor(const QColor& color);
	[[nodiscard]] QColor color();
	/**
	 * ����Բ��
	 * @param roundness Բ�� [ 0.0, 100.0 ]
	 */
	void setRoundness(qreal roundness);
	[[nodiscard]] qreal roundness() const;
	/**
	 * ������ת��������������С��͸����
	 * @param minimumTrailOpacity ��ת��������������С��͸���� [ 0.0, 1.0 ]
	 */
	void setMinimumTrailOpacity(qreal minimumTrailOpacity);
	[[nodiscard]] qreal minimumTrailOpacity() const;
	/**
	 * ������������ʧ�İٷֱ�
	 * @param trail ��������ʧ�İٷֱ� [ 0.0, 100.0 ]
	 */
	void setTrailFadePercentage(qreal trail);
	[[nodiscard]] qreal trailFadePercentage() const;
	/**
	 * ������ת�������ٶȣ���ÿ����ת��Ȧ��
	 * @param revolutionsPerSecond ��ת�������ٶ� (seconds)
	 */
	void setRevolutionsPerSecond(qreal revolutionsPerSecond);
	[[nodiscard]] qreal revolutionsPersSecond() const;
	/**
	 * ������ת����������������
	 * @param lines ��ת����������������
	 */
	void setNumberOfLines(int lines);
	[[nodiscard]] int numberOfLines() const;
	/**
	 * ������ת�����������ĳ���
	 * @param length ��ת�����������ĳ���
	 */
	void setLineLength(int length);
	[[nodiscard]] int lineLength() const;
	/**
	 * ������ת�����������Ŀ��
	 * @param width ��ת�����������Ŀ��
	 */
	void setLineWidth(int width);
	[[nodiscard]] int lineWidth() const;
	/**
	 * ������ת�������������ڰ뾶
	 * @param radius ��ת�������������ڰ뾶
	 */
	void setInnerRadius(int radius);
	[[nodiscard]] int innerRadius() const;
	/**
	 * ������ʾ�ڵȴ�ָʾ���·����ı�����
	 * @param text Ҫ��ʾ���ı�����
	 */
	void setText(const QString& text);
	[[nodiscard]] QString text() const;
	/**
	 * ������ʾ�ı�����ɫ
	 * @param color �ı�����ɫ
	 */
	void setTextColor(const QColor& color);
	[[nodiscard]] QColor textColor() const;
	/**
	 * ������ʾ�ı��������С
	 * @param size �ı��������С
	 */
	void setFontSize(int size);
	[[nodiscard]] int fontSize() const;
	/**
	 * ������ʾ�ı���λ��
	 * @param position see TextPosition
	 */
	void setTextPosition(const TextPosition& position);
	[[nodiscard]] TextPosition textPosition() const;

	[[nodiscard]] bool isSpinning() const;

protected:
	void paintEvent(QPaintEvent* paintEvent) override;

	const QScopedPointer<CUVWatingWidgetPrivate> d_ptr{ nullptr };
};
