#include "uvmaterialtabs_internal.hpp"

#include <QDebug>
#include <QEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLayoutItem>

#include "uvmaterialtabs.hpp"

/*!
 *  \class CUVMaterialTabsInkBar
 *  \internal
 */
CUVMaterialTabsInkBar::CUVMaterialTabsInkBar(CUVMaterialTabs* parent)
: CUVMaterialOverlayWidget(parent), m_tabs(parent), m_animation(new QPropertyAnimation(parent)), m_tween(0) {
	Q_ASSERT(parent);

	m_animation->setPropertyName("tweenValue");
	m_animation->setEasingCurve(QEasingCurve::OutCirc);
	m_animation->setTargetObject(this);
	m_animation->setDuration(700);

	m_tabs->installEventFilter(this);

	setAttribute(Qt::WA_TransparentForMouseEvents);
	setAttribute(Qt::WA_NoSystemBackground);
}

CUVMaterialTabsInkBar::~CUVMaterialTabsInkBar() = default;

void CUVMaterialTabsInkBar::refreshGeometry() {
	if (const QLayoutItem* item = m_tabs->layout()->itemAt(m_tabs->currentIndex())) {
		const QRect r(item->geometry());
		const qreal s = 1 - m_tween;

		if (QAbstractAnimation::Running != m_animation->state()) {
			m_geometry = QRect(r.left(), r.bottom() - 1, r.width(), 2);
		} else {
			const qreal left = m_previousGeometry.left() * s + r.left() * m_tween;
			const qreal width = m_previousGeometry.width() * s + r.width() * m_tween;
			m_geometry = QRect(left, r.bottom() - 1, width, 2); // NOLINT
		}
		m_tabs->update();
	}
}

void CUVMaterialTabsInkBar::animate() {
	raise();

	m_previousGeometry = m_geometry;

	m_animation->stop();
	m_animation->setStartValue(0);
	m_animation->setEndValue(1);
	m_animation->start();
}

bool CUVMaterialTabsInkBar::eventFilter(QObject* watched, QEvent* event) {
	switch (event->type()) {
		case QEvent::Move:
		case QEvent::Resize: {
			refreshGeometry();
			break;
		}
		default: break;
	}
	return CUVMaterialOverlayWidget::eventFilter(watched, event);
}

void CUVMaterialTabsInkBar::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	QPainter painter(this);

	painter.setOpacity(1);
	painter.fillRect(m_geometry, m_tabs->inkColor());
}

/*!
 *  \class CUVMaterialTab
 *  \internal
 */
CUVMaterialTab::CUVMaterialTab(CUVMaterialTabs* parent)
: CUVMaterialFlatButton(parent),
  m_tabs(parent),
  m_active(false) {
	Q_ASSERT(parent);

	setMinimumHeight(50);

	QFont f(font());
	f.setStyleName("Normal");
	setFont(f);

	setCornerRadius(0);
	setRole(Material::Primary);
	setBackgroundMode(Qt::OpaqueMode);
	setBaseOpacity(0.25);

	connect(this, &CUVMaterialTab::clicked, this, &CUVMaterialTab::activateTab);
}

CUVMaterialTab::~CUVMaterialTab() = default;

QSize CUVMaterialTab::sizeHint() const {
	if (icon().isNull()) {
		return CUVMaterialFlatButton::sizeHint();
	} else {
		return { 40, iconSize().height() + 46 };
	}
}

void CUVMaterialTab::activateTab() {
	m_tabs->setCurrentTab(this);
}

void CUVMaterialTab::paintForeground(QPainter* painter) {
	painter->setPen(foregroundColor());

	if (!icon().isNull()) {
		painter->translate(0, 12);
	}

	const QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));
	const QSize base(size() - textSize);

	const QRect textGeometry(QPoint(base.width(), base.height()) / 2, textSize);

	painter->drawText(textGeometry, Qt::AlignCenter, text());

	if (!icon().isNull()) {
		const QSize& size = iconSize();
		const QRect iconRect(QPoint((width() - size.width()) / 2, 0), size);

		QPixmap pixmap = icon().pixmap(iconSize());
		QPainter icon(&pixmap);
		icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
		icon.fillRect(pixmap.rect(), painter->pen().color());
		painter->drawPixmap(iconRect, pixmap);
	}

	if (!m_active) {
		if (!icon().isNull()) {
			painter->translate(0, -12);
		}
		QBrush overlay;
		overlay.setStyle(Qt::SolidPattern);
		overlay.setColor(backgroundColor());
		painter->setOpacity(0.36);
		painter->fillRect(rect(), overlay);
	}
}
