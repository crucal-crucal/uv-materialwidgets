#pragma once

#include "uvmaterialtextfield/uvmaterialtextfield.hpp"

class CUVMaterialAutoCompletePrivate;

#ifdef CUVMATERIALAUTOCOMPLETE_LIB
#define CUVMATERIALAUTOCOMPLETE_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALAUTOCOMPLETE_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALAUTOCOMPLETE_EXPORT CUVMaterialAutoComplete final : public CUVMaterialTextField {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialAutoComplete)
	Q_DECLARE_PRIVATE(CUVMaterialAutoComplete)

public:
	explicit CUVMaterialAutoComplete(QWidget* parent = nullptr);
	~CUVMaterialAutoComplete() override;

	void setDataSource(const QStringList& data);

signals:
	void itemSelected(QString);

protected slots:
	void updateResults(const QString& text);

protected:
	bool event(QEvent* event) override;
	bool eventFilter(QObject* watched, QEvent* event) override;
};
