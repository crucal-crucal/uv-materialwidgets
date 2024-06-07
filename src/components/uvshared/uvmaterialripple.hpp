#pragma once

#include <QBrush>
#include <QParallelAnimationGroup>
#include <QPoint>
#include <QPropertyAnimation>

class CUVMaterialRippleOverlay;

#ifdef CUVMATERIALSHARED_LIB
#define CUVMATERIALSHARED_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALSHARED_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALSHARED_EXPORT CUVMaterialRipple final : public QParallelAnimationGroup {
	Q_OBJECT

	Q_PROPERTY(qreal radius WRITE setRadius READ radius)
	Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
	explicit CUVMaterialRipple(const QPoint& center, QObject* parent = nullptr);
	CUVMaterialRipple(const QPoint& center, CUVMaterialRippleOverlay* overlay, QObject* parent = nullptr);
	~CUVMaterialRipple() override;

	inline void setOverlay(CUVMaterialRippleOverlay* overlay);

	void setRadius(qreal radius);
	[[nodiscard]] inline qreal radius() const;

	void setOpacity(qreal opacity);
	[[nodiscard]] inline qreal opacity() const;

	void setColor(const QColor& color);
	[[nodiscard]] inline QColor color() const;

	void setBrush(const QBrush& brush);
	[[nodiscard]] inline QBrush brush() const;

	[[nodiscard]] inline QPoint center() const;

	[[nodiscard]] inline QPropertyAnimation* radiusAnimation() const;
	[[nodiscard]] inline QPropertyAnimation* opacityAnimation() const;

	inline void setOpacityStartValue(qreal value) const;
	inline void setOpacityEndValue(qreal value) const;
	inline void setRadiusStartValue(qreal value) const;
	inline void setRadiusEndValue(qreal value) const;
	inline void setDuration(int msecs) const;

protected slots:
	void destroy();

private:
	Q_DISABLE_COPY(CUVMaterialRipple)

	QPropertyAnimation* animate(const QByteArray& property, const QEasingCurve& easing = QEasingCurve::OutQuad, int duration = 800);

	void init();

	CUVMaterialRippleOverlay* m_overlay;
	QPropertyAnimation* const m_radiusAnimation;
	QPropertyAnimation* const m_opacityAnimation;
	qreal m_radius;
	qreal m_opacity;
	QPoint m_center;
	QBrush m_brush;
};

inline void CUVMaterialRipple::setOverlay(CUVMaterialRippleOverlay* overlay) {
	m_overlay = overlay;
}

inline qreal CUVMaterialRipple::radius() const {
	return m_radius;
}

inline qreal CUVMaterialRipple::opacity() const {
	return m_opacity;
}

inline QColor CUVMaterialRipple::color() const {
	return m_brush.color();
}

inline QBrush CUVMaterialRipple::brush() const {
	return m_brush;
}

inline QPoint CUVMaterialRipple::center() const {
	return m_center;
}

inline QPropertyAnimation* CUVMaterialRipple::radiusAnimation() const {
	return m_radiusAnimation;
}

inline QPropertyAnimation* CUVMaterialRipple::opacityAnimation() const {
	return m_opacityAnimation;
}

inline void CUVMaterialRipple::setOpacityStartValue(const qreal value) const {
	m_opacityAnimation->setStartValue(value);
}

inline void CUVMaterialRipple::setOpacityEndValue(const qreal value) const {
	m_opacityAnimation->setEndValue(value);
}

inline void CUVMaterialRipple::setRadiusStartValue(const qreal value) const {
	m_radiusAnimation->setStartValue(value);
}

inline void CUVMaterialRipple::setRadiusEndValue(const qreal value) const {
	m_radiusAnimation->setEndValue(value);
}

inline void CUVMaterialRipple::setDuration(const int msecs) const {
	m_radiusAnimation->setDuration(msecs);
	m_opacityAnimation->setDuration(msecs);
}
