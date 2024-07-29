#include "uvmaterialprogress_internal.hpp"

/*!
 *  \class CUVMaterialProgressDelegate
 *  \internal
 */
CUVMaterialProgressDelegate::CUVMaterialProgressDelegate(CUVMaterialProgress* parent)
: QObject(parent), m_progress(parent), m_offset(0) {
	Q_ASSERT(parent);
}

CUVMaterialProgressDelegate::~CUVMaterialProgressDelegate() = default;

void CUVMaterialProgressDelegate::setOffset(const qreal offset) {
	m_offset = offset;
	m_progress->update();
}

qreal CUVMaterialProgressDelegate::offset() const {
	return m_offset;
}
