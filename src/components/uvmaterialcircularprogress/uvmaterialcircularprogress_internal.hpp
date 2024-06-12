#pragma once

#include <QObject>

#include "uvmaterialcircularprogress.hpp"

class CUVMaterialCircularProgressDelegate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialCircularProgressDelegate)

	Q_PROPERTY(qreal dashOffset WRITE setDashOffset READ dashOffset)
	Q_PROPERTY(qreal dashLength WRITE setDashLength READ dashLength)
	Q_PROPERTY(int angle WRITE setAngle READ angle)

public:
	explicit CUVMaterialCircularProgressDelegate(CUVMaterialCircularProgress* parent);
	~CUVMaterialCircularProgressDelegate() override;

	void setDashOffset(qreal offset);
	[[nodiscard]] qreal dashOffset() const;

	void setDashLength(qreal length);
	[[nodiscard]] qreal dashLength() const;

	void setAngle(int angle);
	[[nodiscard]] int angle() const;

private:
	CUVMaterialCircularProgress* const m_progress{ nullptr };
	qreal m_dashOffset{};
	qreal m_dashLength{};
	int m_angle{};
};
