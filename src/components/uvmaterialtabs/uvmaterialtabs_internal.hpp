#pragma once

#include "uvmaterialflatbutton/uvmaterialflatbutton.hpp"
#include "uvshared/uvmaterialoverlaywidget.hpp"

class QPropertyAnimation;
class CUVMaterialTabs;

class CUVMaterialTabsInkBar final : public CUVMaterialOverlayWidget {
	Q_OBJECT

	Q_PROPERTY(qreal tweenValue WRITE setTweenValue READ tweenValue)

public:
	explicit CUVMaterialTabsInkBar(CUVMaterialTabs* parent);
	~CUVMaterialTabsInkBar() override;

	inline void setTweenValue(qreal value);
	[[nodiscard]] inline qreal tweenValue() const;

	void refreshGeometry();
	void animate();

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	Q_DISABLE_COPY(CUVMaterialTabsInkBar)

	CUVMaterialTabs* const m_tabs{ nullptr };
	QPropertyAnimation* const m_animation{ nullptr };
	QRect m_geometry{};
	QRect m_previousGeometry{};
	qreal m_tween{};
};

inline void CUVMaterialTabsInkBar::setTweenValue(const qreal value) {
	m_tween = value;
	refreshGeometry();
}

inline qreal CUVMaterialTabsInkBar::tweenValue() const {
	return m_tween;
}

class CUVMaterialTab final : public CUVMaterialFlatButton {
	Q_OBJECT

public:
	explicit CUVMaterialTab(CUVMaterialTabs* parent);
	~CUVMaterialTab() override;

	inline void setActive(bool state);
	[[nodiscard]] inline bool isActive() const;

	[[nodiscard]] QSize sizeHint() const override;

protected slots:
	void activateTab();

protected:
	void paintForeground(QPainter* painter) override;

private:
	Q_DISABLE_COPY(CUVMaterialTab)

	CUVMaterialTabs* const m_tabs{ nullptr };
	bool m_active{};
};

inline void CUVMaterialTab::setActive(const bool state) {
	m_active = state;
	update();
}

inline bool CUVMaterialTab::isActive() const {
	return m_active;
}
