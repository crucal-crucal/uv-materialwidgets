#pragma once

#include <QObject>
#include <QPixmap>
#include <QPoint>

class CUVMaterialMenu;
class CUVMaterialMenuStyle;

class CUVMaterialMenuPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialMenuPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialMenu)

	Q_PROPERTY(int pAnimationImagePosY READ getAnimationImagePosY WRITE setAnimationImagePosY NOTIFY onAnimationImagePosYChanged)

public:
	explicit CUVMaterialMenuPrivate(CUVMaterialMenu* q, QObject* parent = nullptr);
	~CUVMaterialMenuPrivate() override;

	void setAnimationImagePosY(int pos);
	[[nodiscard]] int getAnimationImagePosY() const;

signals:
	void onAnimationImagePosYChanged();

protected:
	CUVMaterialMenu* const q_ptr{ nullptr };

private:
	int _pAnimationImagePosY{};
	QPixmap _animationPix;
	bool _isCloseAnimation{ false };
	QPoint _mousePressPoint;
	CUVMaterialMenuStyle* _menuStyle{ nullptr };
};
