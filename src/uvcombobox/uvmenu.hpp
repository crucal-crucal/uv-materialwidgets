#pragma once

#include <QMenu>
#include <QWidget>

class CUVMenuPrivate;

class CUVMenu final : public QMenu {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMenu)
	Q_DECLARE_PRIVATE(CUVMenu)

public:
	explicit CUVMenu(QWidget* parent = nullptr);
	explicit CUVMenu(const QString& title, QWidget* parent = nullptr);
	~CUVMenu() override;

	void setMenuItemHeight(int menuItemHeight);
	[[nodiscard]] int getMenuItemHeight() const;


	QAction* addMenu(QMenu* menu);
	CUVMenu* addMenu(const QString& title);
	CUVMenu* addMenu(const QIcon& icon, const QString& title);

	[[nodiscard]] bool isHasChildMenu() const;
	[[nodiscard]] bool isHasIcon() const;

signals:
	void menuShow();

protected:
	QScopedPointer<CUVMenuPrivate> d_ptr{ nullptr };

	void showEvent(QShowEvent* event) override;;
	void paintEvent(QPaintEvent* event) override;
};
