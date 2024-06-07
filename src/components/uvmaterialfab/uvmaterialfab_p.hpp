#pragma once

#include "uvmaterialraisedbutton/uvmaterialraisedbutton_p.hpp"

class CUVMaterialFloatingActionButton;

class CUVMaterialFloatingActionButtonPrivate : public CUVMaterialRaisedButtonPrivate {
	Q_DISABLE_COPY(CUVMaterialFloatingActionButtonPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialFloatingActionButton) // NOLINT

public:
	enum {
		DefaultDiameter = 56,
		MiniDiameter    = 40
	};

	enum {
		DefaultIconSize = 24,
		MiniIconSize    = 18
	};

	explicit CUVMaterialFloatingActionButtonPrivate(CUVMaterialFloatingActionButton* q);
	~CUVMaterialFloatingActionButtonPrivate();

	void init();
	[[nodiscard]] QRect fabGeometry() const;
	void setupProperties() const;

	[[nodiscard]] inline int diameter() const;
	[[nodiscard]] inline int iconSize() const;

	Qt::Corner corner{};
	bool mini{};
	int offsX{};
	int offsY{};
};

inline int CUVMaterialFloatingActionButtonPrivate::diameter() const {
	return mini ? MiniDiameter : DefaultDiameter;
}

inline int CUVMaterialFloatingActionButtonPrivate::iconSize() const {
	return mini ? MiniIconSize : DefaultIconSize;
}
