#pragma once

#include <QColor>
#include <QObject>

class CUVMaterialSnackbar;
class CUVMaterialSnackbarStateMachine;

class CUVMaterialSnackbarPrivate {
	Q_DISABLE_COPY(CUVMaterialSnackbarPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialSnackbar)

public:
	explicit CUVMaterialSnackbarPrivate(CUVMaterialSnackbar* q);
	~CUVMaterialSnackbarPrivate();

	void init(const CUVMaterialSnackbar::SnackBarPosition& postion);

	CUVMaterialSnackbar* const q_ptr{ nullptr };
	CUVMaterialSnackbarStateMachine* stateMachine{ nullptr };
	QColor backgroundColor{};
	QColor textColor{};
	qreal bgOpacity{};
	QList<QString> messages{};
	int duration{};
	int boxWidth{};
	bool clickDismiss{};
	bool useThemeColors{};
};
