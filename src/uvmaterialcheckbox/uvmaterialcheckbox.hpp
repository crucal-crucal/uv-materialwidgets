#pragma once

#include "uvmaterialshared/uvmaterialcheckable.hpp"

class CUVMaterialCheckBoxPrivate;

#ifdef CUVMATERIALCHECKBOX_LIB
#define CUVMATERIALCHECKBOX_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALCHECKBOX_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALCHECKBOX_EXPORT CUVMaterialCheckBox final : public CUVMaterialCheckable {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialCheckBox)
	Q_DECLARE_PRIVATE(CUVMaterialCheckBox)

public:
	explicit CUVMaterialCheckBox(QWidget* parent = nullptr);
	~CUVMaterialCheckBox() override;
};
