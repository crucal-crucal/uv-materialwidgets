#pragma once

#include <QObject>

class CUVMessageBar;
class CUVAwesomeButton;
class QPainter;

class CUVMessageBarPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMessageBarPrivate)
	Q_DECLARE_PUBLIC(CUVMessageBar)

public:
	explicit CUVMessageBarPrivate(CUVMessageBar* q, QObject* parent = nullptr);
	~CUVMessageBarPrivate() override;

	void init();
	void messageBarStartAnimation(int displayMsec);
	void messageBarFinishAnimation();
	void messageBarEventAnimation();
	void updateActiveMap(bool isActive);

	/**
	 * 初始坐标计算
	 * @param startX 起始 x, &
	 * @param startY 起始 y, &
	 * @param endX 结束 x, &
	 * @param endY 结束 y, &
	 */
	void calculatePos(int& startX, int& startY, int& endX, int& endY);
	[[nodiscard]] int calculateMinimumHeightTotal(bool isJudgeIndex = false);

	void drawMessage(QPainter* painter, const QColor& backgroundColor, const QColor& iconColor,
	                 const QString& iconText, const QColor& textColor, int iconPixelSize,
	                 int iconX, const QColor& penColor = Qt::white);
	void drawSuccess(QPainter* painter);
	void drawError(QPainter* painter);
	void drawWarning(QPainter* painter);
	void drawInfo(QPainter* painter);

	static void showMessageBar(const UVMessageBarType::PositionPolicy& positionPolicy, const UVMessageBarType::MessageMode& messageMode,
						   const QString& title, const QString& message, int displayMsec, QWidget* parent = nullptr);

public slots:
	void onCloseButtonClicked();
	void onOtherMessageBarClosed(UVMessageBarType::PositionPolicy positionPolicy, int barIndex);

signals:
	void messageBarClosed(UVMessageBarType::PositionPolicy positionPolicy, int messageBarIndex);

public:
	CUVMessageBar* const q_ptr{ nullptr };
	int borderRadius{};
	QString title{};
	QString text{};
	UVMessageBarType::PositionPolicy policy{};
	UVMessageBarType::MessageMode messageMode{};

	// 位置数据
	int leftPadding{};
	int titleLeftSpacing{};
	int textLeftSpacing{};
	int closeButtonLeftRightMargin{};
	int closeButtonWidth{};
	int messageBarHorizontalMargin{};
	int messageBarVerticalBottomMargin{};
	int messageBarVerticalTopMargin{};
	int messageBarSpacing{};
	int shadowBorderWidth{};

	// 逻辑数据
	int messageBarIndex{};
	bool isMessageBarStartAnimationFinished{};
	bool isMessageBarEventAnimationInStartAnimation{};
	bool isCloseAnimationStart{};
	bool isNormalDisplay{};
	bool isMessageBarEventAnimationStart{};
	CUVAwesomeButton* closeButton{ nullptr };
	static QMap<UVMessageBarType::PositionPolicy, QList<CUVMessageBar*>*> messageBarActiveMap;
};
