#pragma once

#include "uvshared/uvmaterialoverlaywidget.hpp"

class CUVMaterialDrawerPrivate;
class CUVMaterialDrawerStateMachine;

#ifdef CUVMATERIALDRAWER_LIB
#define CUVMATERIALDRAWER_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALDRAWER_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALDRAWER_EXPORT CUVMaterialDrawer final : public CUVMaterialOverlayWidget {
	Q_OBJECT

public:
	explicit CUVMaterialDrawer(QWidget* parent = nullptr);
	~CUVMaterialDrawer() override;

	void setDrawerWidth(int width);
	[[nodiscard]] int drawerWidth() const;

	void setDrawerLayout(QLayout* layout);
	[[nodiscard]] QLayout* drawerLayout() const;

	void setClickOutsideToClose(bool state);
	[[nodiscard]] bool clickOutsideToClose() const;

	void setAutoRaise(bool state);
	[[nodiscard]] bool autoRaise() const;

	void setOverlayMode(bool value);
	[[nodiscard]] bool overlayMode() const;

public slots:
	void openDrawer();
	void closeDrawer();

protected:
	bool event(QEvent* event) override;
	bool eventFilter(QObject* watched, QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVMaterialDrawerPrivate> d_ptr{ nullptr };

private:
	Q_DISABLE_COPY(CUVMaterialDrawer)
	Q_DECLARE_PRIVATE(CUVMaterialDrawer)
};
