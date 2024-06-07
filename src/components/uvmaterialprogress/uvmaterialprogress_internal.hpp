#pragma once

#include "uvmaterialprogress.hpp"

class CUVMaterialProgressDelegate final : public QObject {
	Q_OBJECT

	Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
	explicit CUVMaterialProgressDelegate(CUVMaterialProgress* parent);
	~CUVMaterialProgressDelegate() override;

	void setOffset(qreal offset);
	[[nodiscard]] qreal offset() const;

private:
	Q_DISABLE_COPY(CUVMaterialProgressDelegate)

	CUVMaterialProgress* const m_progress{ nullptr };
	qreal m_offset{};
};
