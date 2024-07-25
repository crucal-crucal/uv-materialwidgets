#pragma once

#include <QObject>

class CUVMaterialComboBox;
class CUVMaterialComboBoxStyle;

class CUVMaterialComboBoxPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialComboBoxPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialComboBox)

public:
	explicit CUVMaterialComboBoxPrivate(CUVMaterialComboBox* q, QObject* parent = nullptr);
	~CUVMaterialComboBoxPrivate() override;

protected:
	CUVMaterialComboBox* const q_ptr{ nullptr };

private:
	int _pBorderRadius{};
	CUVMaterialComboBoxStyle* _comboBoxStyle{ nullptr };
	bool _isAllowHidePopup{ false };
};
