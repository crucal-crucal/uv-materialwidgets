#pragma once

#include "uvshared/uvmaterialoverlaywidget.hpp"

class QLayout;
class CUVMaterialDialogPrivate;

#ifdef CUVMATERIALDIALOG_LIB
#define CUVMATERIALDIALOG_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALDIALOG_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALDIALOG_EXPORT CUVMaterialDialog final : public CUVMaterialOverlayWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialDialog)
	Q_DECLARE_PRIVATE(CUVMaterialDialog)

public:
	explicit CUVMaterialDialog(QWidget* parent = nullptr);
	~CUVMaterialDialog() override;

	[[nodiscard]] QLayout* windowLayout() const;
	void setWindowLayout(QLayout* layout);

public slots:
	void showDialog();
	void hideDialog();

protected:
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVMaterialDialogPrivate> d_ptr{ nullptr };
};
