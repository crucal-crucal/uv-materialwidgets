#pragma once

#include <QObject>

class QPropertyAnimation;
class CUVMaterialScrollBar;

class CUVMaterialScrollBarPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialScrollBarPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialScrollBar)

	Q_PROPERTY(int pTargetMaximum READ getTargetMaximum WRITE setTargetMaximum NOTIFY targetMaximumChanged)

public:
	explicit CUVMaterialScrollBarPrivate(CUVMaterialScrollBar* q, QObject* parent = nullptr);
	~CUVMaterialScrollBarPrivate() override;

	Q_SLOT void onRangeChanged(int min, int max);

	void setTargetMaximum(int targetMaximum);
	[[nodiscard]] int getTargetMaximum() const;

signals:
	void targetMaximumChanged();

protected:
	CUVMaterialScrollBar* const q_ptr{ nullptr };

private:
	bool _pIsAnimation{};
	int _pTargetMaximum{};
	QPropertyAnimation* _slideSmoothAnimation{ nullptr };
	int _scrollValue{ 0 };
	int _lastHorizontalDeltaAngle{ -120 };
	int _lastVerticalDeltaAngle{ -120 };

	void _scroll(int value);
	[[nodiscard]] int _pixelPosToRangeValue(int pos) const;
};
