#include "uvmaterialprogress.hpp"

#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QDebug>

#include "uvmaterialprogress_internal.hpp"
#include "uvmaterialprogress_p.hpp"
#include "uvmaterialshared/uvmaterialstyle.hpp"

/*!
 *  \class CUVMaterialProgressPrivate
 *  \internal
 */
CUVMaterialProgressPrivate::CUVMaterialProgressPrivate(CUVMaterialProgress* q): q_ptr(q) {
}

CUVMaterialProgressPrivate::~CUVMaterialProgressPrivate() = default;

void CUVMaterialProgressPrivate::init() {
	Q_Q(CUVMaterialProgress);

	delegate = new CUVMaterialProgressDelegate(q);
	progressType = Material::DeterminateProgress;
	useThemeColors = true;

	const auto animation = new QPropertyAnimation(q);
	animation->setPropertyName("offset");
	animation->setTargetObject(delegate);
	animation->setStartValue(0);
	animation->setEndValue(1);
	animation->setDuration(1000);

	animation->setLoopCount(-1);

	animation->start();
}

/*!
 *  \class CUVMaterialProgress
 */
CUVMaterialProgress::CUVMaterialProgress(QWidget* parent)
: QProgressBar(parent), d_ptr(new CUVMaterialProgressPrivate(this)) {
	d_func()->init();
}

CUVMaterialProgress::~CUVMaterialProgress() = default;

void CUVMaterialProgress::setProgressType(const Material::ProgressType type) {
	Q_D(CUVMaterialProgress);

	d->progressType = type;
	update();
}

Material::ProgressType CUVMaterialProgress::progressType() const {
	Q_D(const CUVMaterialProgress);

	return d->progressType;
}

void CUVMaterialProgress::setUseThemeColors(const bool state) {
	Q_D(CUVMaterialProgress);

	if (d->useThemeColors == state) {
		return;
	}

	d->useThemeColors = state;
	update();
}

bool CUVMaterialProgress::useThemeColors() const {
	Q_D(const CUVMaterialProgress);

	return d->useThemeColors;
}

void CUVMaterialProgress::setProgressColor(const QColor& color) {
	Q_D(CUVMaterialProgress);

	d->progressColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialProgress::progressColor() const {
	Q_D(const CUVMaterialProgress);

	if (d->useThemeColors || !d->progressColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("primary1");
	} else {
		return d->progressColor;
	}
}

void CUVMaterialProgress::setBackgroundColor(const QColor& color) {
	Q_D(CUVMaterialProgress);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	update();
}

QColor CUVMaterialProgress::backgroundColor() const {
	Q_D(const CUVMaterialProgress);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("border");
	} else {
		return d->backgroundColor;
	}
}

void CUVMaterialProgress::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event)

	Q_D(CUVMaterialProgress);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(isEnabled() ? backgroundColor()
		               : CUVMaterialStyle::instance().themeColor("disabled"));
	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);

	QPainterPath path;
	path.addRoundedRect(0, 0, width(), height(), 5, 5);
	painter.setClipPath(path);

	painter.drawRect(0, 0, width(), height());

	if (isEnabled()) {
		brush.setColor(progressColor());
		painter.setBrush(brush);

		if (Material::IndeterminateProgress == d->progressType) {
			painter.drawRect(d->delegate->offset() * width() * 2 - width(), 0, width(), height()); // NOLINT
		} else {
			const qreal p = static_cast<qreal>(width()) * (value() - minimum()) / (maximum() - minimum());
			painter.drawRect(0, 0, p, height()); // NOLINT
		}
	}

	QPen pen(Qt::black);
	pen.setWidth(1);
	painter.setPen(pen);
	const QString curValue = QString("%1%").arg(qMax(0, value() * 100 / (maximum() - minimum())));
	// 设置字体
	QFont font = painter.font();
	font.setPointSize(10); // 可根据需求调整字号
	painter.setFont(font);

	// 获取文本尺寸
	QFontMetrics fm(painter.font());
	int textWidth = fm.horizontalAdvance(curValue);
	int textHeight = fm.height();

	// 计算文本绘制位置（居中）
	int textX = (width() - textWidth) / 2;
	int textY = (height() + textHeight) / 2 - fm.descent(); // 考虑到文本基线偏移

	// 绘制文本
	painter.drawText(textX, textY, curValue);
}
