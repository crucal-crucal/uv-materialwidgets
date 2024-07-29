#pragma once

#include <QObject>
#include <QPixmap>
#include <QPoint>

class CUVMenu;
class CUVMenuStyle;

class CUVMenuPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMenuPrivate)
	Q_DECLARE_PUBLIC(CUVMenu)

	Q_PROPERTY(int pAnimationImagePosY READ getAnimationImagePosY WRITE setAnimationImagePosY NOTIFY onAnimationImagePosYChanged)

public:
	explicit CUVMenuPrivate(CUVMenu* q, QObject* parent = nullptr);
	~CUVMenuPrivate() override;

	void setAnimationImagePosY(int pos);
	[[nodiscard]] int getAnimationImagePosY() const;

signals:
	void onAnimationImagePosYChanged();

protected:
	CUVMenu* const q_ptr{ nullptr };

private:
	int _pAnimationImagePosY{};
	QPixmap _animationPix;
	bool _isCloseAnimation{ false };
	QPoint _mousePressPoint;
	CUVMenuStyle* _menuStyle{ nullptr };
};
