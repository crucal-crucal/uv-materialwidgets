#pragma once

#include <QColor>
#include <QObject>

#include "uvmaterialmessagebar/uvdef.hpp"

using namespace UVIconType;

class CUVMaterialAwesomeButton;

class CUVMaterialAwesomeButtonPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialAwesomeButtonPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialAwesomeButton)

public:
	explicit CUVMaterialAwesomeButtonPrivate(CUVMaterialAwesomeButton* q, QObject* parent = nullptr);
	~CUVMaterialAwesomeButtonPrivate() override;

	void init();

public:
	CUVMaterialAwesomeButton* const q_ptr{ nullptr };

	int borderRaius{ 0 };
	CUVIconType iconType{};
	QColor lightHoverColor{};
	QColor darkHoverColor{};
	QColor lightIconColor{};
	QColor darkIconColor{};
	bool isSelected{};
};
