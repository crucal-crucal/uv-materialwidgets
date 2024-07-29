#pragma once

#include <QObject>

class CUVToggleSwitch;

class CUVToggleSwitchPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVToggleSwitchPrivate)
	Q_DECLARE_PUBLIC(CUVToggleSwitch)

	Q_PROPERTY(qreal circleCenterX READ circleCenterX WRITE setcircleCenterX)
	Q_PROPERTY(qreal circleRadius READ circleRadius WRITE setcircleRadius)

public:
	explicit CUVToggleSwitchPrivate(CUVToggleSwitch* q, QObject* parent = nullptr);
	~CUVToggleSwitchPrivate() override;

	CUVToggleSwitch* const q_ptr{ nullptr };

	void init();

	void setcircleCenterX(qreal centerX);
	[[nodiscard]] qreal circleCenterX() const;

	void setcircleRadius(qreal radius);
	[[nodiscard]] qreal circleRadius() const;

	[[nodiscard]] int getTextWidth() const;

	void startPosAnimation(qreal startX, qreal endX, bool isToggle);

	void startRadiusAnimation(qreal startRadius, qreal endRadius);

	void adjustCircleCenterX();

	bool isToggled{ false };
	bool isAnimationFinished{ true };
	int margin{ 1 };
	qreal m_circleCenterX{ 0 };
	qreal m_circleRadius{ 0 };
	bool isLeftButtonPress{ false };
	bool isMousePressMove{ false };
	int lastMouseX{ 0 };
	bool showText{};
	// 滑块
	QColor circleOffColor{};
	QColor circleOnColor{};
	// 背景
	QColor backgroundOffColor{};
	QColor backgroundOnColor{};
	// text
	int spaceText{}; // 文字距离滑块的距离
	int fontSize{};
	bool fontBold{};
	QString offText{};
	QString onText{};
	QColor offTextColor{};
	QColor onTextColor{};
};
