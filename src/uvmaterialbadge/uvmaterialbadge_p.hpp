#pragma once

#include <QIcon>
#include <QSize>
#include <QtGlobal>

class CUVMaterialBadge;

class CUVMaterialBadgePrivate {
	Q_DISABLE_COPY(CUVMaterialBadgePrivate)
	Q_DECLARE_PUBLIC(CUVMaterialBadge)

public:
	explicit CUVMaterialBadgePrivate(CUVMaterialBadge* q);
	~CUVMaterialBadgePrivate();

	void init();

	CUVMaterialBadge* const q_ptr{ nullptr };
	QString text{};
	QColor textColor{};
	QColor backgroundColor{};
	QSize size{};
	QIcon icon{};
	qreal x{};
	qreal y{};
	int padding{};
	bool useThemeColors{};
};
