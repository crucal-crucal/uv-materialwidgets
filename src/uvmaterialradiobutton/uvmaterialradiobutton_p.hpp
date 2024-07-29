#pragma once

#include "uvmaterialshared/uvmaterialcheckable_p.hpp"

class CUVMaterialRadioButton;

class CUVMaterialRadioButtonPrivate : public CUVMaterialCheckablePrivate {
	Q_DISABLE_COPY(CUVMaterialRadioButtonPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialRadioButton) // NOLINT

public:
	explicit CUVMaterialRadioButtonPrivate(CUVMaterialRadioButton* q);
	~CUVMaterialRadioButtonPrivate();

	void init();
};
