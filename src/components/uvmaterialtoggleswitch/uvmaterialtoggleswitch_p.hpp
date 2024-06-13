#pragma once

#include <QObject>

#include <uvmaterialtoggleswitch.hpp>

class CUVMaterialToggleSwitch;

class CUVMaterialToggleSwitchPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialToggleSwitchPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialToggleSwitch)

	Q_PROPERTY(qreal circleCenterX READ circleCenterX WRITE setcircleCenterX)
	Q_PROPERTY(qreal circleRadius READ circleRadius WRITE setcircleRadius)

public:
	explicit CUVMaterialToggleSwitchPrivate(CUVMaterialToggleSwitch* q, QObject* parent = nullptr);
	~CUVMaterialToggleSwitchPrivate() override;

	CUVMaterialToggleSwitch* const q_ptr{ nullptr };

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
	// »¬¿é
	QColor circleOffColor{};
	QColor circleOnColor{};
	// ±³¾°
	QColor backgroundOffColor{};
	QColor backgroundOnColor{};
	// text
	int spaceText{}; // ÎÄ×Ö¾àÀë»¬¿éµÄ¾àÀë
	int textFontSize{};
	bool fontBold{};
	QString offText{};
	QString onText{};
	QColor offTextColor{};
	QColor onTextColor{};
};
