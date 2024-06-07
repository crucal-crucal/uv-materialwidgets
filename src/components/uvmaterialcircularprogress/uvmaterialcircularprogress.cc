#include "uvmaterialcircularprogress.hpp"

#include <QPainter>
#include <QPainterPath>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

#include "uvmaterialcircularprogress_internal.hpp"
#include "uvmaterialcircularprogress_p.hpp"
#include "uvshared/uvmaterialstyle.hpp"

/*!
 *  \class CUVMaterialCircularProgressPrivate
 *  \internal
 */
CUVMaterialCircularProgressPrivate::CUVMaterialCircularProgressPrivate(CUVMaterialCircularProgress* q): q_ptr(q) {
}

CUVMaterialCircularProgressPrivate::~CUVMaterialCircularProgressPrivate() = default;

void CUVMaterialCircularProgressPrivate::init() {
	Q_Q(CUVMaterialCircularProgress);

	delegate = new CUVMaterialCircularProgressDelegate(q);
	progressType = Material::IndeterminateProgress;
	penWidth = 6.25;
	size = 64;
	useThemeColors = true;

	q->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

	const auto group = new QParallelAnimationGroup(q);
	group->setLoopCount(-1);

	auto animation = new QPropertyAnimation(q);
	animation->setPropertyName("dashLength");
	animation->setTargetObject(delegate);
	animation->setEasingCurve(QEasingCurve::InOutQuad);
	animation->setStartValue(0.1);
	animation->setKeyValueAt(0.15, 0.2);
	animation->setKeyValueAt(0.6, 20);
	animation->setKeyValueAt(0.7, 20);
	animation->setEndValue(20);
	animation->setDuration(2050);

	group->addAnimation(animation);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("dashOffset");
	animation->setTargetObject(delegate);
	animation->setEasingCurve(QEasingCurve::InOutSine);
	animation->setStartValue(0);
	animation->setKeyValueAt(0.15, 0);
	animation->setKeyValueAt(0.6, -7);
	animation->setKeyValueAt(0.7, -7);
	animation->setEndValue(-25);
	animation->setDuration(2050);

	group->addAnimation(animation);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("angle");
	animation->setTargetObject(delegate);
	animation->setStartValue(0);
	animation->setEndValue(719);
	animation->setDuration(2050);

	group->addAnimation(animation);

	group->start();
}

/*!
 *  \class CUVMaterialCircularProgress
 */
CUVMaterialCircularProgress::CUVMaterialCircularProgress(QWidget* parent)
: QProgressBar(parent), d_ptr(new CUVMaterialCircularProgressPrivate(this)) {
	d_func()->init();
}

CUVMaterialCircularProgress::~CUVMaterialCircularProgress() = default;

void CUVMaterialCircularProgress::setProgressType(const Material::ProgressType type) {
	Q_D(CUVMaterialCircularProgress);

	d->progressType = type;
	update();
}

Material::ProgressType CUVMaterialCircularProgress::progressType() const {
	Q_D(const CUVMaterialCircularProgress);

	return d->progressType;
}

void CUVMaterialCircularProgress::setUseThemeColors(const bool value) {
	Q_D(CUVMaterialCircularProgress);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	update();
}

bool CUVMaterialCircularProgress::useThemeColors() const {
	Q_D(const CUVMaterialCircularProgress);

	return d->useThemeColors;
}

void CUVMaterialCircularProgress::setLineWidth(const qreal width) {
	Q_D(CUVMaterialCircularProgress);

	d->penWidth = width;
	update();
	updateGeometry();
}

qreal CUVMaterialCircularProgress::lineWidth() const {
	Q_D(const CUVMaterialCircularProgress);

	return d->penWidth;
}

void CUVMaterialCircularProgress::setSize(const int size) {
	Q_D(CUVMaterialCircularProgress);

	d->size = size;
	update();
	updateGeometry();
}

int CUVMaterialCircularProgress::Size() const {
	Q_D(const CUVMaterialCircularProgress);

	return d->size;
}

void CUVMaterialCircularProgress::setColor(const QColor& color) {
	Q_D(CUVMaterialCircularProgress);

	d->color = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialCircularProgress::color() const {
	Q_D(const CUVMaterialCircularProgress);

	if (d->useThemeColors || !d->color.isValid()) {
		return CUVMaterialStyle::instance().themeColor("primary1");
	} else {
		return d->color;
	}
}

/*!
 *  \reimp
 */
QSize CUVMaterialCircularProgress::sizeHint() const {
	Q_D(const CUVMaterialCircularProgress);

	const qreal s = d->size + d->penWidth + 8;
	return { static_cast<int>(s), static_cast<int>(s) };
}

/*!
 *  \reimp
 */
void CUVMaterialCircularProgress::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	Q_D(CUVMaterialCircularProgress);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	if (!isEnabled()) {
		QPen pen;
		pen.setCapStyle(Qt::RoundCap);
		pen.setWidthF(d->penWidth);
		pen.setColor(CUVMaterialStyle::instance().themeColor("border"));
		painter.setPen(pen);
		painter.drawLine(rect().center() - QPointF(20, 20), rect().center() + QPointF(20, 20));
		painter.drawLine(rect().center() + QPointF(20, -20), rect().center() - QPointF(20, -20));
		return;
	}

	if (Material::IndeterminateProgress == d->progressType) {
		painter.translate(static_cast<qreal>(width()) / 2, static_cast<qreal>(height()) / 2);
		painter.rotate(d->delegate->angle());
	}

	QPen pen;
	pen.setCapStyle(Qt::RoundCap);
	pen.setWidthF(d->penWidth);
	pen.setColor(color());

	if (Material::IndeterminateProgress == d->progressType) {
		QVector<qreal> pattern;
		pattern << d->delegate->dashLength() * d->size / 50 << 30 * d->size / 50; // NOLINT

		pen.setDashOffset(d->delegate->dashOffset() * d->size / 50);
		pen.setDashPattern(pattern);

		painter.setPen(pen);

		painter.drawEllipse(QPoint(0, 0), d->size / 2, d->size / 2);
	} else {
		painter.setPen(pen);

		const qreal x = static_cast<qreal>(width() - d->size) / 2;
		const qreal y = static_cast<qreal>(height() - d->size) / 2;

		const qreal a = static_cast<qreal>(360) * (value() - minimum()) / (maximum() - minimum());

		QPainterPath path;
		path.arcMoveTo(x, y, d->size, d->size, 0);
		path.arcTo(x, y, d->size, d->size, 0, a);

		painter.drawPath(path);
	}
}
