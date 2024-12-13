#include "uvmaterialcircularprogress.hpp"

#include <QFontDatabase>
#include <QPainter>
#include <QPainterPath>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QDebug>
#include <QTimer>

#include "uvmaterialcircularprogress_internal.hpp"
#include "uvmaterialcircularprogress_p.hpp"
#include "uvmaterialshared/uvmaterialstyle.hpp"

/*!
 *  \class CUVMaterialCircularProgressPrivate
 *  \internal
 */
CUVMaterialCircularProgressPrivate::CUVMaterialCircularProgressPrivate(CUVMaterialCircularProgress* q, QObject* parent): QObject(parent), q_ptr(q) {
}

CUVMaterialCircularProgressPrivate::~CUVMaterialCircularProgressPrivate() = default;

void CUVMaterialCircularProgressPrivate::init() {
	Q_Q(CUVMaterialCircularProgress);

	QFontDatabase::addApplicationFont(":/fonts/segoe_slboot_EX");
	QFontDatabase::addApplicationFont(":/fonts/segoen_slboot_EX");

	delegate = new CUVMaterialCircularProgressDelegate(q);
	progressType = Material::DeterminateProgress;
	penWidth = 6.25;
	size = 64;
	useThemeColors = true;
	showValue = true;
	timer = new QTimer(q);
	connect(timer, &QTimer::timeout, this, &CUVMaterialCircularProgressPrivate::_updateAnimation);

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

void CUVMaterialCircularProgressPrivate::_updateAnimation() {
	Q_Q(CUVMaterialCircularProgress);

	switch (progressType) {
		case Material::DiscontinuousLoading: {
			if (++currentIndex1 >= endIndex1) {
				currentIndex1 = startIndex1;
			}
			break;
		}
		case Material::ContinuousLoading: {
			if (++currentIndex2 > endIndex2) {
				currentIndex2 = startIndex2;
			}
		}
		default: break;
	}
	q->update();
}

void CUVMaterialCircularProgressPrivate::drawIndeterminate(QPainter& painter, QPen& pen) {
	Q_Q(CUVMaterialCircularProgress);

	painter.save();

	QVector<qreal> pattern;
	pattern << delegate->dashLength() * size / 50 << 30.0 * size / 50; // NOLINT
	pen.setDashOffset(delegate->dashOffset() * size / 50);
	pen.setDashPattern(pattern);
	painter.setPen(pen);
	painter.drawEllipse(QPoint(0, 0), size / 2, size / 2);

	painter.restore();
}

void CUVMaterialCircularProgressPrivate::drawDeterminate(QPainter& painter, const QPen& pen) {
	Q_Q(CUVMaterialCircularProgress);

	painter.save();

	painter.setPen(pen);
	const qreal x = static_cast<qreal>(q->width() - size) / 2;
	const qreal y = static_cast<qreal>(q->height() - size) / 2;
	const qreal a = -static_cast<qreal>(360) * (q->value() - q->minimum()) / (q->maximum() - q->minimum());
	QPainterPath path;
	path.arcMoveTo(x, y, size, size, 0);
	path.arcTo(x, y, size, size, 0, a);
	painter.drawPath(path);

	painter.restore();
}

void CUVMaterialCircularProgressPrivate::drawDiscontinuous(QPainter& painter, const QPen& pen) {
	Q_Q(CUVMaterialCircularProgress);

	painter.save();

	painter.setPen(pen);
	QFont font("Segoe Boot Semilight");
	font.setPixelSize(80);
	painter.setFont(font);
	const QFontMetrics fm(font);
	const int textX = (q->width() - fm.horizontalAdvance(QChar(currentIndex1))) / 2;
	const int textY = (q->height() + fm.height()) / 2 - fm.ascent() / 4;
	painter.drawText(textX, textY, QChar(currentIndex1));

	painter.restore();
}

void CUVMaterialCircularProgressPrivate::drawContinuous(QPainter& painter, const QPen& pen) {
	Q_Q(CUVMaterialCircularProgress);

	painter.save();

	painter.setPen(pen);
	QFont font("Segoe Boot Semilight");
	font.setPixelSize(80);
	painter.setFont(font);
	const QFontMetrics fm(font);
	const int textX = (q->width() - fm.horizontalAdvance(QChar(currentIndex2))) / 2;
	const int textY = (q->height() + fm.height()) / 2 - fm.ascent() / 4;
	painter.drawText(textX, textY, QChar(currentIndex2));

	painter.restore();
}

void CUVMaterialCircularProgressPrivate::drawValue(QPainter& painter, QPen& pen) {
	Q_Q(CUVMaterialCircularProgress);

	painter.save();

	painter.resetTransform();
	pen.setCapStyle(Qt::FlatCap);
	pen.setColor(Qt::black);
	pen.setWidthF(1.0);
	painter.setPen(pen);
	const QString curValue = QString("%1").arg(qMax(0, q->value() * 100 / (q->maximum() - q->minimum())));
	QFont font = painter.font();
	font.setPointSize(10);
	painter.setFont(font);
	const QFontMetrics fm(painter.font());
	const int textX = (q->width() - fm.horizontalAdvance(curValue)) / 2;
	const int textY = (q->height() + fm.height()) / 2 - fm.descent(); // 考虑到文本基线偏移
	painter.drawText(textX, textY, curValue);

	painter.restore();
}

/*!
 *  \class CUVMaterialCircularProgress
 */
CUVMaterialCircularProgress::CUVMaterialCircularProgress(QWidget* parent)
: QProgressBar(parent), d_ptr(new CUVMaterialCircularProgressPrivate(this)) {
	d_func()->init();

	this->setFixedSize(200, 200);
}

CUVMaterialCircularProgress::~CUVMaterialCircularProgress() = default;

void CUVMaterialCircularProgress::setProgressType(const Material::ProgressType type) {
	Q_D(CUVMaterialCircularProgress);

	switch (type) {
		case Material::DiscontinuousLoading:
		case Material::ContinuousLoading: {
			d->timer->start(20);
			break;
		}
		default: {
			d->timer->stop();
			break;
		}
	}

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

QSize CUVMaterialCircularProgress::sizeHint() const {
	Q_D(const CUVMaterialCircularProgress);

	const qreal s = d->size + d->penWidth + 8;
	return { static_cast<int>(s), static_cast<int>(s) };
}

void CUVMaterialCircularProgress::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	Q_D(CUVMaterialCircularProgress);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.save();

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

	switch (d->progressType) {
		case Material::IndeterminateProgress: {
			d->drawIndeterminate(painter, pen);
			break;
		}
		case Material::DeterminateProgress: {
			d->drawDeterminate(painter, pen);
			break;
		}
		case Material::DiscontinuousLoading: {
			d->drawDiscontinuous(painter, pen);
			break;
		}
		case Material::ContinuousLoading: {
			d->drawContinuous(painter, pen);
			break;
		}
		default: break;
	}

	if (d->showValue) {
		d->drawValue(painter, pen);
	}

	painter.restore();
}
