#pragma once

#include <QtWidgets/QWidget>

#include "uvshared/uvmaterialtheme.hpp"

class CUVMaterialAvatarPrivate;

#ifdef CUVMATERIALAVATAR_LIB
#define CUVMATERIALAVATAR_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALAVATAR_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALAVATAR_EXPORT CUVMaterialAvatar final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialAvatar)
	Q_DECLARE_PRIVATE(CUVMaterialAvatar)

public:
	explicit CUVMaterialAvatar(QWidget* parent = nullptr);
	explicit CUVMaterialAvatar(const QIcon& icon, QWidget* parent = nullptr);
	explicit CUVMaterialAvatar(const QChar& letter, QWidget* parent = nullptr);
	explicit CUVMaterialAvatar(const QImage& image, QWidget* parent = nullptr);
	~CUVMaterialAvatar() override;

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setTextColor(const QColor& color);
	[[nodiscard]] QColor textColor() const;

	void setBackgroundColor(const QColor& color);
	[[nodiscard]] QColor backgroundColor() const;

	[[nodiscard]] QSize sizeHint() const override;

	void setSize(int size);
	[[nodiscard]] int Size() const;

	void setLetter(const QChar& letter);
	void setImage(const QImage& image);
	void setIcon(const QIcon& icon);

	[[nodiscard]] Material::AvatarType type() const;

protected:
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVMaterialAvatarPrivate> d_ptr{ nullptr };
};
