#pragma once

#include <QScrollBar>

class CUVMaterialScrollBarPrivate;

class CUVMaterialScrollBar final : public QScrollBar {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialScrollBar)
	Q_DECLARE_PRIVATE(CUVMaterialScrollBar)

	Q_PROPERTY(bool pIsAnimation READ getIsAnimation WRITE setIsAnimation NOTIFY isAnimationChanged)

public:
	explicit CUVMaterialScrollBar(QWidget* parent = nullptr);
	explicit CUVMaterialScrollBar(Qt::Orientation orientation, QWidget* parent = nullptr);
	~CUVMaterialScrollBar() override;

	void setIsAnimation(bool isAnimation);
	[[nodiscard]] bool getIsAnimation() const;

signals:
	void isAnimationChanged();

protected:
	QScopedPointer<CUVMaterialScrollBarPrivate> d_ptr{ nullptr };

	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;
};
