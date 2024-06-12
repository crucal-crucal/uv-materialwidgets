#pragma once

#include <QStateMachine>

#include "uvshared/uvmaterialoverlaywidget.hpp"

class CUVMaterialDrawer;
class CUVMaterialDrawerWidget;

class CUVMaterialDrawerStateMachine final : public QStateMachine {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialDrawerStateMachine)

	Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
	explicit CUVMaterialDrawerStateMachine(CUVMaterialDrawerWidget* drawer,
	                                       CUVMaterialDrawer* parent);
	~CUVMaterialDrawerStateMachine() override;

	void setOpacity(qreal opacity);
	[[nodiscard]] inline qreal opacity() const;

	[[nodiscard]] bool isInClosedState() const;

	void updatePropertyAssignments();

signals:
	void signalOpen();
	void signalClose();

private:
	CUVMaterialDrawerWidget* const m_drawer{ nullptr };
	CUVMaterialDrawer* const m_main{ nullptr };
	QState* const m_openingState{ nullptr };
	QState* const m_openedState{ nullptr };
	QState* const m_closingState{ nullptr };
	QState* const m_closedState{ nullptr };
	qreal m_opacity{};
};

inline qreal CUVMaterialDrawerStateMachine::opacity() const {
	return m_opacity;
}

class CUVMaterialDrawerWidget final : public CUVMaterialOverlayWidget {
	Q_OBJECT

	Q_PROPERTY(int offset WRITE setOffset READ offset)

public:
	explicit CUVMaterialDrawerWidget(QWidget* parent = nullptr);
	~CUVMaterialDrawerWidget() override;

	void setOffset(int offset);
	[[nodiscard]] inline int offset() const;

protected:
	void paintEvent(QPaintEvent* event) override;

	[[nodiscard]] QRect overlayGeometry() const override;

private:
	int m_offset{};
};

inline int CUVMaterialDrawerWidget::offset() const {
	return m_offset;
}
