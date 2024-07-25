#pragma once


#include <QMenu>
#include <QWidget>

class CUVMaterialMenuPrivate;

class CUVMaterialMenu final : public QMenu {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialMenu)
	Q_DECLARE_PRIVATE(CUVMaterialMenu)

public:
	explicit CUVMaterialMenu(QWidget* parent = nullptr);
	explicit CUVMaterialMenu(const QString& title, QWidget* parent = nullptr);
	~CUVMaterialMenu() override;

	void setMenuItemHeight(int menuItemHeight);
	[[nodiscard]] int getMenuItemHeight() const;


	QAction* addMenu(QMenu* menu);
	CUVMaterialMenu* addMenu(const QString& title);
	CUVMaterialMenu* addMenu(const QIcon& icon, const QString& title);

	[[nodiscard]] bool isHasChildMenu() const;
	[[nodiscard]] bool isHasIcon() const;

signals:
	void menuShow();

protected:
	QScopedPointer<CUVMaterialMenuPrivate> d_ptr{ nullptr };

	void showEvent(QShowEvent* event) override;;
	void paintEvent(QPaintEvent* event) override;
};
