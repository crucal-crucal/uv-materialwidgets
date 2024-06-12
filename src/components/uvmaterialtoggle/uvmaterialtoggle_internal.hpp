#pragma once

#include "uvshared/uvmaterialrippleoverlay.hpp"

class CUVMaterialToggle;
class CUVMaterialToggleThumb;
class CUVMaterialToggleTrack;

class CUVMaterialToggleRippleOverlay final : public CUVMaterialRippleOverlay {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialToggleRippleOverlay)

public:
	CUVMaterialToggleRippleOverlay(CUVMaterialToggleThumb* thumb, CUVMaterialToggleTrack* track, CUVMaterialToggle* parent);
	~CUVMaterialToggleRippleOverlay() override;

protected slots:
	void addToggleRipple();

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;
	[[nodiscard]] QRect overlayGeometry() const override;

private:
	CUVMaterialToggle* const m_toggle;
	CUVMaterialToggleThumb* const m_thumb;
	CUVMaterialToggleTrack* const m_track;
};

class CUVMaterialToggleThumb final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialToggleThumb)

	Q_PROPERTY(qreal shift WRITE setShift READ shift)
	Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)

public:
	explicit CUVMaterialToggleThumb(CUVMaterialToggle* parent);
	~CUVMaterialToggleThumb() override;

	void setShift(qreal shift);
	[[nodiscard]] inline qreal shift() const;

	[[nodiscard]] inline qreal offset() const;

	inline void setThumbColor(const QColor& color);
	[[nodiscard]] inline QColor thumbColor() const;

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	void updateOffset();

	CUVMaterialToggle* const m_toggle{ nullptr };
	QColor m_thumbColor{};
	qreal m_shift{};
	qreal m_offset{};
};

inline qreal CUVMaterialToggleThumb::shift() const {
	return m_shift;
}

inline qreal CUVMaterialToggleThumb::offset() const {
	return m_offset;
}

inline void CUVMaterialToggleThumb::setThumbColor(const QColor& color) {
	m_thumbColor = color;
	update();
}

inline QColor CUVMaterialToggleThumb::thumbColor() const {
	return m_thumbColor;
}

class CUVMaterialToggleTrack final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialToggleTrack)

	Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)

public:
	explicit CUVMaterialToggleTrack(CUVMaterialToggle* parent);
	~CUVMaterialToggleTrack() override;

	void setTrackColor(const QColor& color);
	[[nodiscard]] inline QColor trackColor() const;

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	CUVMaterialToggle* const m_toggle{ nullptr };
	QColor m_trackColor{};
};

inline QColor CUVMaterialToggleTrack::trackColor() const {
	return m_trackColor;
}
