#pragma once

#include <QChar>
#include <QColor>
#include <QIcon>
#include <QImage>
#include <QPixmap>
#include <QtGlobal>

#include "uvshared/uvmaterialtheme.hpp"

class CUVMaterialAvatar;

class CUVMaterialAvatarPrivate {
	Q_DISABLE_COPY(CUVMaterialAvatarPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialAvatar)

public:
	explicit CUVMaterialAvatarPrivate(CUVMaterialAvatar* q);
	~CUVMaterialAvatarPrivate();

	void init();

	CUVMaterialAvatar* const q_ptr{ nullptr };
	int size{};
	Material::AvatarType type{};
	QChar letter{};
	QImage image{};
	QIcon icon{};
	QPixmap pixmap{};
	bool useThemeColors{};
	QColor textColor{};
	QColor backgroundColor{};
};
