#pragma once

#include "uvshared/uvmaterialcheckable_p.hpp"

class CUVMaterialCheckBox;

class CUVMaterialCheckBoxPrivate : public CUVMaterialCheckablePrivate {
	Q_DISABLE_COPY(CUVMaterialCheckBoxPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialCheckBox) // NOLINT

public:
	explicit CUVMaterialCheckBoxPrivate(CUVMaterialCheckBox* q);
	~CUVMaterialCheckBoxPrivate();

	void init();
};