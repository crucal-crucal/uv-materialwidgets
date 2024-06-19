#pragma once

#include <QColor>
#include <QObject>

#include "uvdef.hpp"

using namespace UVIconType;

class CUVMaterialIconButton;

class CUVMaterialIconButtonPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialIconButtonPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialIconButton)

public:
	explicit CUVMaterialIconButtonPrivate(CUVMaterialIconButton* q, QObject* parent = nullptr);
	~CUVMaterialIconButtonPrivate() override;

	void init();

public:
	CUVMaterialIconButton* const q_ptr{ nullptr };

	int borderRaius{ 0 };
	CUVIconType iconType{};
	QColor lightHoverColor{};
	QColor darkHoverColor{};
	QColor lightIconColor{};
	QColor darkIconColor{};
	bool isSelected{};
};
