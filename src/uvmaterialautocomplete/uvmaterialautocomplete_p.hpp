#pragma once

#include "uvmaterialtextfield/uvmaterialtextfield_p.hpp"

class QWidget;
class QVBoxLayout;
class QtMaterialAutoCompleteOverlay;
class CUVMaterialAutoCompleteStateMachine;

class CUVMaterialAutoCompletePrivate final : public CUVMaterialTextFieldPrivate {
	Q_DISABLE_COPY(CUVMaterialAutoCompletePrivate)
	Q_DECLARE_PUBLIC(CUVMaterialAutoComplete) // NOLINT

public:
	explicit CUVMaterialAutoCompletePrivate(CUVMaterialAutoComplete* q);
	~CUVMaterialAutoCompletePrivate() override;

	void init(); // NOLINT

	QWidget* menu{ nullptr };
	QWidget* frame{ nullptr };
	CUVMaterialAutoCompleteStateMachine* stateMachine{ nullptr };
	QVBoxLayout* menuLayout{ nullptr };
	QStringList dataSource{ nullptr };
	int maxWidth{};
};
