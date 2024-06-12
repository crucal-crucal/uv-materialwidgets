#pragma once

#include <QStateMachine>
#include "uvmaterialautocomplete.hpp"

class CUVMaterialAutoCompleteStateMachine final : public QStateMachine {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialAutoCompleteStateMachine)

public:
	explicit CUVMaterialAutoCompleteStateMachine(QWidget* menu);
	~CUVMaterialAutoCompleteStateMachine() override;

signals:
	void shouldOpen();
	void shouldClose();
	void shouldFade();

private:
	QWidget* const m_menu;
	QState* const m_closedState;
	QState* const m_openState;
	QState* const m_closingState;
};
