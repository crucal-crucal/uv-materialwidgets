#pragma once

#include <QColor>
#include <QtGlobal>

class CUVMaterialTextField;
class CUVMaterialTextFieldStateMachine;
class CUVMaterialTextFieldLabel;

class CUVMaterialTextFieldPrivate {
	Q_DISABLE_COPY(CUVMaterialTextFieldPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialTextField)

public:
	explicit CUVMaterialTextFieldPrivate(CUVMaterialTextField* q);
	virtual ~CUVMaterialTextFieldPrivate();

	void init(); // NOLINT

	CUVMaterialTextField* const q_ptr{ nullptr };
	CUVMaterialTextFieldStateMachine* stateMachine{ nullptr };
	CUVMaterialTextFieldLabel* label{ nullptr };
	QColor textColor{};
	QColor labelColor{};
	QColor inkColor{};
	QColor inputLineColor{};
	QString labelString{};
	qreal labelFontSize{};
	bool showLabel{};
	bool showInputLine{};
	bool useThemeColors{};
};