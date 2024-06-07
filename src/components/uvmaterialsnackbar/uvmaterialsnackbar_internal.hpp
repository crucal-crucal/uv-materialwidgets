#pragma once

#include <QStateMachine>
#include <QTimer>

#include "uvmaterialsnackbar.hpp"

class CUVMaterialSnackbar;

class CUVMaterialSnackbarStateMachine final : public QStateMachine {
	Q_OBJECT

	Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
	explicit CUVMaterialSnackbarStateMachine(CUVMaterialSnackbar* parent, const CUVMaterialSnackbar::SnackBarPosition& position);
	~CUVMaterialSnackbarStateMachine() override;

	void setOffset(qreal offset);
	[[nodiscard]] inline qreal offset() const;

	void setPosition(CUVMaterialSnackbar::SnackBarPosition position);
	[[nodiscard]] inline CUVMaterialSnackbar::SnackBarPosition position() const;

public slots:
	void progress();
	void setStateProperty();

protected slots:
	void snackbarShown();

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	Q_DISABLE_COPY(CUVMaterialSnackbarStateMachine)

	CUVMaterialSnackbar* const m_snackbar{ nullptr };
	CUVMaterialSnackbar::SnackBarPosition m_position{ CUVMaterialSnackbar::BOTTOM };
	QState* m_hiddenState{ nullptr };
	QState* m_visibleState{ nullptr };
	QState* m_finalState{ nullptr };
	QTimer m_timer{};
	qreal m_offset{};
};

inline qreal CUVMaterialSnackbarStateMachine::offset() const {
	return m_offset;
}

inline CUVMaterialSnackbar::SnackBarPosition CUVMaterialSnackbarStateMachine::position() const {
	return m_position;
}
