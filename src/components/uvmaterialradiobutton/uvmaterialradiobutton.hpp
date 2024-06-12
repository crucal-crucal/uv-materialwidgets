#pragma once

#include "uvshared/uvmaterialcheckable.hpp"

class CUVMaterialRadioButtonPrivate;

#ifdef CUVMATERIALRADIOBUTTON_LIB
#define CUVMATERIALRADIOBUTTON_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALRADIOBUTTON_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALRADIOBUTTON_EXPORT CUVMaterialRadioButton final : public CUVMaterialCheckable {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialRadioButton)
	Q_DECLARE_PRIVATE(CUVMaterialRadioButton)

public:
	explicit CUVMaterialRadioButton(QWidget* parent = nullptr);
	~CUVMaterialRadioButton() override;

protected:
	void setupProperties() override;
};
