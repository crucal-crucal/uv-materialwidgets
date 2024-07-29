#include "uvmaterialcircularprogress_internal.hpp"

/*!
 *  \class CUVMaterialCircularProgressDelegate
 *  \internal
 */
CUVMaterialCircularProgressDelegate::CUVMaterialCircularProgressDelegate(CUVMaterialCircularProgress* parent)
: QObject(parent), m_progress(parent), m_dashOffset(0), m_dashLength(89), m_angle(0) {
	Q_ASSERT(parent);
}

CUVMaterialCircularProgressDelegate::~CUVMaterialCircularProgressDelegate() = default;

void CUVMaterialCircularProgressDelegate::setDashOffset(const qreal offset) {
	m_dashOffset = offset;
	m_progress->update();
}

qreal CUVMaterialCircularProgressDelegate::dashOffset() const {
	return m_dashOffset;
}

void CUVMaterialCircularProgressDelegate::setDashLength(const qreal length) {
	m_dashLength = length;
	m_progress->update();
}

qreal CUVMaterialCircularProgressDelegate::dashLength() const {
	return m_dashLength;
}

void CUVMaterialCircularProgressDelegate::setAngle(const int angle) {
	m_angle = angle;
	m_progress->update();
}

int CUVMaterialCircularProgressDelegate::angle() const {
	return m_angle;
}
