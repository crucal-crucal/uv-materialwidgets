#pragma once

#include "uvmaterialflatbutton/uvmaterialflatbutton.hpp"

class CUVMaterialRaisedButtonPrivate;

#ifdef CUVMATERIALRAISEDBUTTON_LIB
#define CUVMATERIALRAISEDBUTTON_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALRAISEDBUTTON_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALRAISEDBUTTON_EXPORT CUVMaterialRaisedButton : public CUVMaterialFlatButton {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialRaisedButton)
	Q_DECLARE_PRIVATE(CUVMaterialRaisedButton)

public:
	explicit CUVMaterialRaisedButton(QWidget* parent = nullptr);
	explicit CUVMaterialRaisedButton(const QString& text, QWidget* parent = nullptr);
	~CUVMaterialRaisedButton() override;

protected:
	explicit CUVMaterialRaisedButton(CUVMaterialRaisedButtonPrivate& d, QWidget* parent = nullptr);

	bool event(QEvent* event) override;
};
