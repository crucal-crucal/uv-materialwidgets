#pragma once

#include <QAbstractScrollArea>
#include <QScrollBar>

class CUVScrollBarPrivate;

class CUVScrollBar final : public QScrollBar {
	Q_OBJECT
	Q_DISABLE_COPY(CUVScrollBar)
	Q_DECLARE_PRIVATE(CUVScrollBar)

	Q_PROPERTY(bool pIsAnimation READ getIsAnimation WRITE setIsAnimation NOTIFY isAnimationChanged)

public:
	explicit CUVScrollBar(QWidget* parent = nullptr);
	explicit CUVScrollBar(Qt::Orientation orientation, QWidget* parent = nullptr);
	explicit CUVScrollBar(QScrollBar* originScrollBar, QAbstractScrollArea* parent = nullptr);
	~CUVScrollBar() override;

	void setIsAnimation(bool isAnimation);
	[[nodiscard]] bool getIsAnimation() const;

signals:
	void isAnimationChanged();
	void rangeAnimationFinished();

protected:
	QScopedPointer<CUVScrollBarPrivate> d_ptr{ nullptr };

	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;
	bool event(QEvent* event) override;
	bool eventFilter(QObject* watched, QEvent* event) override;
};
