#pragma once

#include <QColor>
#include <QObject>
#include <QtGlobal>

class CUVMaterialWatingWidget;

class CUVMaterialWatingWidgetPrivate final : public QObject {
	Q_OBJECT

	Q_DISABLE_COPY(CUVMaterialWatingWidgetPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialWatingWidget)

public:
	explicit CUVMaterialWatingWidgetPrivate(CUVMaterialWatingWidget* q);
	~CUVMaterialWatingWidgetPrivate() override;

public slots:
	void rotate();

public:
	static int lineCountDistanceFromPrimary(int current, int primary, int totalNrOfLines);
	static QColor currentLineColor(int distance, int totalNrOfLines, qreal trailFadePerc, qreal minOpacity, QColor color);

	void initialize();
	void updateSize();
	void updateTimer() const;
	void updatePosition();

	CUVMaterialWatingWidget* const q_ptr{ nullptr };

	QColor color{};
	QString text{};
	QColor textColor{};
	int textHeight{};
	int textWidth{};
	int fontSize{};
	CUVMaterialWatingWidget::TextPosition textPosition{};
	qreal roundness{}; // 0..100
	qreal minimumTrailOpacity{};
	qreal trailFadePercentage{};
	qreal revolutionsPerSecond{};
	int numberOfLines{};
	int lineLength{};
	int lineWidth{};
	int innerRadius{};

	QTimer* timer{ nullptr };
	bool centerOnParent{};
	bool disableParentWhenSpinning{};
	int currentCounter{};
	bool isSpinning{};
};
