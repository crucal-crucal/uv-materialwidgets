#pragma once

#include <QAbstractScrollArea>
#include <QObject>
#include <QScrollBar>

class QTimer;
class QPropertyAnimation;
class CUVScrollBar;

class CUVScrollBarPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVScrollBarPrivate)
	Q_DECLARE_PUBLIC(CUVScrollBar)

	Q_PROPERTY(int pTargetMaximum READ getTargetMaximum WRITE setTargetMaximum NOTIFY targetMaximumChanged)

public:
	explicit CUVScrollBarPrivate(CUVScrollBar* q, QObject* parent = nullptr);
	~CUVScrollBarPrivate() override;

	Q_SLOT void onRangeChanged(int min, int max);

	void setTargetMaximum(int targetMaximum);
	[[nodiscard]] int getTargetMaximum() const;

signals:
	void targetMaximumChanged();

protected:
	CUVScrollBar* const q_ptr{ nullptr };

private:
	QScrollBar* _originScrollBar{ nullptr };
	QAbstractScrollArea* _originScrollArea{ nullptr };
	QTimer* _expandTimer{ nullptr };
	QPropertyAnimation* _slideSmoothAnimation{ nullptr };
	bool _isExpand{ false };
	bool _pIsAnimation{};
	int _pTargetMaximum{};
	int _scrollValue{ -1 };
	int _lastHorizontalDeltaAngle{ -120 };
	int _lastVerticalDeltaAngle{ -120 };

	void _scroll(Qt::KeyboardModifiers modifiers, int value);
	[[nodiscard]] int _pixelPosToRangeValue(int pos) const;

	void _initAllConfig();
	static void _handleScrollBarValueChanged(QScrollBar* scrollBar, int value);
	void _handleScrollBarRangeChanged(int min, int max);
	void _handleScrollBarGeometry();
};
