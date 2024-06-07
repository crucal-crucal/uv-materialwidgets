#pragma once

#include <QStateMachine>
#include "uvmaterialscrollbar.hpp"

#ifdef CUVMATERIALSCROLLBAR_LIB
#define CUVMATERIALSCROLLBAR_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALSCROLLBAR_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALSCROLLBAR_EXPORT CUVMaterialScrollBarStateMachine final : public QStateMachine {
	Q_OBJECT

	Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
	explicit CUVMaterialScrollBarStateMachine(CUVMaterialScrollBar* parent);
	~CUVMaterialScrollBarStateMachine() override;

	void setOpacity(qreal opacity);
	[[nodiscard]] qreal opacity() const;

private:
	Q_DISABLE_COPY(CUVMaterialScrollBarStateMachine)

	CUVMaterialScrollBar* const m_scrollBar{ nullptr };
	QState* const m_focusState{ nullptr };
	QState* const m_blurState{ nullptr };
	qreal m_opacity{};
};
