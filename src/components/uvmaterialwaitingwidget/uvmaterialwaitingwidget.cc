#include "uvmaterialwaitingwidget.hpp"

#include <algorithm>
#include <cmath>
#include <QPainter>
#include <QTimer>

#include "uvmaterialwaitingwidget_p.hpp"

/*!
 *  \CUVMaterialTabsPrivate
 *  \internal
 */
CUVMaterialWatingWidgetPrivate::CUVMaterialWatingWidgetPrivate(CUVMaterialWatingWidget* q): q_ptr(q) {
}

CUVMaterialWatingWidgetPrivate::~CUVMaterialWatingWidgetPrivate() = default;

void CUVMaterialWatingWidgetPrivate::rotate() {
	Q_Q(CUVMaterialWatingWidget);

	++currentCounter;
	if (currentCounter >= numberOfLines) {
		currentCounter = 0;
	}
	q->update();
}

int CUVMaterialWatingWidgetPrivate::lineCountDistanceFromPrimary(const int current, const int primary, const int totalNrOfLines) {
	int distance = primary - current;
	if (distance < 0) {
		distance += totalNrOfLines;
	}
	return distance;
}

QColor CUVMaterialWatingWidgetPrivate::currentLineColor(const int distance, const int totalNrOfLines, const qreal trailFadePerc,
                                                        const qreal minOpacity, QColor color) {
	if (distance == 0) {
		return color;
	}
	const qreal minAlphaF = minOpacity / 100.0;
	if (const int distanceThreshold = static_cast<int>(ceil((totalNrOfLines - 1) * trailFadePerc / 100.0)); distance > distanceThreshold) {
		color.setAlphaF(minAlphaF);
	} else {
		const qreal alphaDiff = color.alphaF() - minAlphaF;
		const qreal gradient = alphaDiff / static_cast<qreal>(distanceThreshold + 1);
		qreal resultAlpha = color.alphaF() - gradient * distance;

		// If alpha is out of bounds, clip it.
		resultAlpha = std::min(1.0, std::max(0.0, resultAlpha));
		color.setAlphaF(resultAlpha);
	}
	return color;
}

void CUVMaterialWatingWidgetPrivate::initialize() {
	Q_Q(CUVMaterialWatingWidget);

	color = Qt::black;
	fontSize = 12;
	textColor = Qt::black;
	roundness = 100.0;
	minimumTrailOpacity = 3.14159265358979323846;
	trailFadePercentage = 80.0;
	revolutionsPerSecond = 1.57079632679489661923;
	numberOfLines = 20;
	lineLength = 10;
	lineWidth = 2;
	innerRadius = 10;
	currentCounter = 0;
	isSpinning = false;
	textPosition = CUVMaterialWatingWidget::Bottom;

	timer = new QTimer(q);
	QObject::connect(timer, &QTimer::timeout, this, &CUVMaterialWatingWidgetPrivate::rotate);
	updateSize();
	updateTimer();
	q->hide();
}

void CUVMaterialWatingWidgetPrivate::updateSize() {
	Q_Q(CUVMaterialWatingWidget);

	QFont font;
	font.setPointSize(fontSize);
	const QFontMetrics metrics(font);
	textHeight = metrics.height();
	textWidth = metrics.horizontalAdvance(text);
	const int spinnerSize = (innerRadius + lineLength) * 2;
	const int width = std::max(spinnerSize, textWidth + 20); // 确保窗口宽度足够
	const int height = spinnerSize + textHeight + 20;        // 增加文本高度和10像素间距
	q->setFixedSize(width, height);
}

void CUVMaterialWatingWidgetPrivate::updateTimer() const {
	timer->setInterval(1000 / (numberOfLines * revolutionsPerSecond)); // NOLINT
}

void CUVMaterialWatingWidgetPrivate::updatePosition() {
	Q_Q(CUVMaterialWatingWidget);

	if (q->parentWidget() && centerOnParent) {
		q->move(q->parentWidget()->width() / 2 - q->width() / 2, q->parentWidget()->height() / 2 - q->height() / 2);
	}
}

/*!
 *  \CUVMaterialWatingWidget
 */
CUVMaterialWatingWidget::CUVMaterialWatingWidget(QWidget* parent, const bool centerOnParent, const bool disableParentWhenSpinning)
: QWidget(parent), d_ptr(new CUVMaterialWatingWidgetPrivate(this)) {
	d_func()->initialize();
	d_ptr->centerOnParent = centerOnParent;
	d_ptr->disableParentWhenSpinning = disableParentWhenSpinning;
}

CUVMaterialWatingWidget::CUVMaterialWatingWidget(const Qt::WindowModality modality, QWidget* parent, const bool centerOnParent,
                                                 const bool disableParentWhenSpinning)
: QWidget(parent, Qt::Dialog | Qt::FramelessWindowHint), d_ptr(new CUVMaterialWatingWidgetPrivate(this)) {
	d_func()->initialize();
	d_ptr->centerOnParent = centerOnParent;
	d_ptr->disableParentWhenSpinning = disableParentWhenSpinning;

	setWindowModality(modality);
	setAttribute(Qt::WA_TranslucentBackground);
}

CUVMaterialWatingWidget::~CUVMaterialWatingWidget() = default;

void CUVMaterialWatingWidget::paintEvent(QPaintEvent*) {
	Q_D(CUVMaterialWatingWidget);

	d->updatePosition();
	QPainter painter(this);
	painter.fillRect(this->rect(), Qt::transparent);
	painter.setRenderHint(QPainter::Antialiasing, true);

	if (d->currentCounter >= d->numberOfLines) {
		d->currentCounter = 0;
	}

	const int centerX = width() / 2;
	int centerY;
	if (d->textPosition == TextPosition::Bottom) {
		centerY = (height() - d->textHeight - 10) / 2;
	} else { // TextPosition::Top
		centerY = (height() + d->textHeight + 20) / 2;
	}

	painter.setPen(Qt::NoPen);
	for (int i = 0; i < d->numberOfLines; ++i) {
		painter.save();
		painter.translate(centerX, centerY);
		const qreal rotateAngle = static_cast<qreal>(360 * i) / static_cast<qreal>(d->numberOfLines);
		painter.rotate(rotateAngle);
		painter.translate(d->innerRadius, 0);
		const int distance = CUVMaterialWatingWidgetPrivate::lineCountDistanceFromPrimary(i, d->currentCounter, d->numberOfLines);
		QColor color = CUVMaterialWatingWidgetPrivate::currentLineColor(distance, d->numberOfLines, d->trailFadePercentage,
		                                                                d->minimumTrailOpacity, d->color);
		painter.setBrush(color);
		painter.drawRoundedRect(QRect(0, -d->lineWidth / 2, d->lineLength, d->lineWidth), d->roundness, d->roundness, Qt::RelativeSize);
		painter.restore();
	}

	// draw text
	if (!d->text.isEmpty()) {
		QFont font = painter.font();
		font.setPointSize(d->fontSize);
		painter.setFont(font);
		painter.setPen(d->textColor);

		const int x = (width() - d->textWidth) / 2;
		int y;
		if (d->textPosition == TextPosition::Bottom) {
			y = height() - 10;
		} else { // TextPosition::Top
			y = 10 + d->textHeight;
		}

		painter.drawText(x, y, d->text);
	}
}

void CUVMaterialWatingWidget::start() {
	Q_D(CUVMaterialWatingWidget);

	d->updatePosition();
	d->isSpinning = true;
	show();

	if (parentWidget() && d->disableParentWhenSpinning) {
		parentWidget()->setEnabled(false);
	}

	if (!d->timer->isActive()) {
		d->timer->start();
		d->currentCounter = 0;
	}
}

void CUVMaterialWatingWidget::stop() {
	Q_D(CUVMaterialWatingWidget);

	d->isSpinning = false;
	hide();

	if (parentWidget() && d->disableParentWhenSpinning) {
		parentWidget()->setEnabled(true);
	}

	if (d->timer->isActive()) {
		d->timer->stop();
		d->currentCounter = 0;
	}
}

void CUVMaterialWatingWidget::setNumberOfLines(const int lines) {
	Q_D(CUVMaterialWatingWidget);

	d->numberOfLines = lines;
	d->currentCounter = 0;
	d->updateTimer();
}

void CUVMaterialWatingWidget::setLineLength(const int length) {
	Q_D(CUVMaterialWatingWidget);

	d->lineLength = length;
	d->updateSize();
}

void CUVMaterialWatingWidget::setLineWidth(const int width) {
	Q_D(CUVMaterialWatingWidget);

	d->lineWidth = width;
	d->updateSize();
}

void CUVMaterialWatingWidget::setInnerRadius(const int radius) {
	Q_D(CUVMaterialWatingWidget);

	d->innerRadius = radius;
	d->updateSize();
}

void CUVMaterialWatingWidget::setText(const QString& text) {
	Q_D(CUVMaterialWatingWidget);

	d->text = text;
	d->updateSize();
}

void CUVMaterialWatingWidget::setTextColor(const QColor& color) {
	Q_D(CUVMaterialWatingWidget);

	d->textColor = color;
}

void CUVMaterialWatingWidget::setFontSize(const int size) {
	Q_D(CUVMaterialWatingWidget);

	d->fontSize = size;
	d->updateSize();
}

void CUVMaterialWatingWidget::setTextPosition(const TextPosition& position) {
	Q_D(CUVMaterialWatingWidget);

	d->textPosition = position;
}

QColor CUVMaterialWatingWidget::color() {
	Q_D(CUVMaterialWatingWidget);

	return d->color;
}

qreal CUVMaterialWatingWidget::roundness() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->roundness;
}

qreal CUVMaterialWatingWidget::minimumTrailOpacity() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->minimumTrailOpacity;
}

qreal CUVMaterialWatingWidget::trailFadePercentage() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->trailFadePercentage;
}

qreal CUVMaterialWatingWidget::revolutionsPersSecond() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->revolutionsPerSecond;
}

int CUVMaterialWatingWidget::numberOfLines() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->numberOfLines;
}

int CUVMaterialWatingWidget::lineLength() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->lineLength;
}

int CUVMaterialWatingWidget::lineWidth() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->lineWidth;
}

int CUVMaterialWatingWidget::innerRadius() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->innerRadius;
}

QString CUVMaterialWatingWidget::text() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->text;
}

QColor CUVMaterialWatingWidget::textColor() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->textColor;
}

int CUVMaterialWatingWidget::fontSize() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->fontSize;
}

bool CUVMaterialWatingWidget::isSpinning() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->isSpinning;
}

CUVMaterialWatingWidget::TextPosition CUVMaterialWatingWidget::textPosition() const {
	Q_D(const CUVMaterialWatingWidget);

	return d->textPosition;
}

void CUVMaterialWatingWidget::setRoundness(const qreal roundness) {
	Q_D(CUVMaterialWatingWidget);

	d->roundness = std::max(0.0, std::min(100.0, roundness));
}

void CUVMaterialWatingWidget::setColor(const QColor& color) {
	Q_D(CUVMaterialWatingWidget);

	d->color = color;
}

void CUVMaterialWatingWidget::setRevolutionsPerSecond(const qreal revolutionsPerSecond) {
	Q_D(CUVMaterialWatingWidget);

	d->revolutionsPerSecond = revolutionsPerSecond;
	d->updateTimer();
}

void CUVMaterialWatingWidget::setTrailFadePercentage(const qreal trail) {
	Q_D(CUVMaterialWatingWidget);

	d->trailFadePercentage = trail;
}

void CUVMaterialWatingWidget::setMinimumTrailOpacity(const qreal minimumTrailOpacity) {
	Q_D(CUVMaterialWatingWidget);

	d->minimumTrailOpacity = minimumTrailOpacity;
}
