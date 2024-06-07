#pragma once

#include "uvmaterialraisedbutton/uvmaterialraisedbutton.hpp"

class CUVMaterialFloatingActionButtonPrivate;

#ifdef CUVMATERIALFAB_LIB
#define CUVMATERIALFAB_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALFAB_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALFAB_EXPORT CUVMaterialFloatingActionButton final : public CUVMaterialRaisedButton {
	Q_OBJECT

public:
	explicit CUVMaterialFloatingActionButton(const QIcon& icon, QWidget* parent = nullptr);
	~CUVMaterialFloatingActionButton() override;

	[[nodiscard]] QSize sizeHint() const override;

	void setMini(bool state);
	[[nodiscard]] bool isMini() const;

	void setCorner(Qt::Corner corner);
	[[nodiscard]] Qt::Corner corner() const;

	void setOffset(int x, int y);
	[[nodiscard]] QSize offset() const;

	void setXOffset(int x);
	[[nodiscard]] int xOffset() const;

	void setYOffset(int y);
	[[nodiscard]] int yOffset() const;

protected:
	bool event(QEvent* event) override;
	bool eventFilter(QObject* watched, QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

	void updateClipPath() override;

private:
	Q_DISABLE_COPY(CUVMaterialFloatingActionButton)
	Q_DECLARE_PRIVATE(CUVMaterialFloatingActionButton)
};
