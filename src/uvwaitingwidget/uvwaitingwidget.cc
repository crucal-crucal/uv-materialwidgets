#include "uvwaitingwidget.hpp"

#include <algorithm>
#include <cmath>
#include <QPainter>
#include <QTimer>

#include "uvwaitingwidget_p.hpp"

/*!
 *  \CUVWatingWidgetPrivate
 *  \internal
 */
CUVWatingWidgetPrivate::CUVWatingWidgetPrivate(CUVWatingWidget* q): q_ptr(q) {
}

CUVWatingWidgetPrivate::~CUVWatingWidgetPrivate() = default;

void CUVWatingWidgetPrivate::rotate() {
	Q_Q(CUVWatingWidget);

	++currentCounter;
	if (currentCounter >= numberOfLines) {
		currentCounter = 0;
	}
	q->update();
}

int CUVWatingWidgetPrivate::lineCountDistanceFromPrimary(const int current, const int primary, const int totalNrOfLines) {
	int distance = primary - current;
	if (distance < 0) {
		distance += totalNrOfLines;
	}
	return distance;
}

QColor CUVWatingWidgetPrivate::currentLineColor(const int distance, const int totalNrOfLines, const qreal trailFadePerc,
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

void CUVWatingWidgetPrivate::initialize() {
	Q_Q(CUVWatingWidget);

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
	textPosition = CUVWatingWidget::Bottom;

	timer = new QTimer(q);
	QObject::connect(timer, &QTimer::timeout, this, &CUVWatingWidgetPrivate::rotate);
	updateSize();
	updateTimer();
	q->hide();
}

void CUVWatingWidgetPrivate::updateSize() {
	Q_Q(CUVWatingWidget);

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

void CUVWatingWidgetPrivate::updateTimer() const {
	timer->setInterval(1000 / (numberOfLines * revolutionsPerSecond)); // NOLINT
}

void CUVWatingWidgetPrivate::updatePosition() {
	Q_Q(CUVWatingWidget);

	if (q->parentWidget() && centerOnParent) {
		q->move(q->parentWidget()->width() / 2 - q->width() / 2, q->parentWidget()->height() / 2 - q->height() / 2);
	}
}

/*!
 *  \CUVWatingWidget
 */
CUVWatingWidget::CUVWatingWidget(QWidget* parent, const bool centerOnParent, const bool disableParentWhenSpinning)
: QWidget(parent), d_ptr(new CUVWatingWidgetPrivate(this)) {
	d_func()->initialize();
	d_ptr->centerOnParent = centerOnParent;
	d_ptr->disableParentWhenSpinning = disableParentWhenSpinning;
}

CUVWatingWidget::CUVWatingWidget(const Qt::WindowModality modality, QWidget* parent, const bool centerOnParent,
                                 const bool disableParentWhenSpinning)
: QWidget(parent, Qt::Dialog | Qt::FramelessWindowHint), d_ptr(new CUVWatingWidgetPrivate(this)) {
	d_func()->initialize();
	d_ptr->centerOnParent = centerOnParent;
	d_ptr->disableParentWhenSpinning = disableParentWhenSpinning;

	setWindowModality(modality);
	setAttribute(Qt::WA_TranslucentBackground);
}

CUVWatingWidget::~CUVWatingWidget() = default;

void CUVWatingWidget::paintEvent(QPaintEvent*) {
	Q_D(CUVWatingWidget);

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
		const int distance = CUVWatingWidgetPrivate::lineCountDistanceFromPrimary(i, d->currentCounter, d->numberOfLines);
		QColor color = CUVWatingWidgetPrivate::currentLineColor(distance, d->numberOfLines, d->trailFadePercentage,
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

void CUVWatingWidget::start() {
	Q_D(CUVWatingWidget);

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

void CUVWatingWidget::stop() {
	Q_D(CUVWatingWidget);

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

void CUVWatingWidget::setNumberOfLines(const int lines) {
	Q_D(CUVWatingWidget);

	d->numberOfLines = lines;
	d->currentCounter = 0;
	d->updateTimer();
}

void CUVWatingWidget::setLineLength(const int length) {
	Q_D(CUVWatingWidget);

	d->lineLength = length;
	d->updateSize();
}

void CUVWatingWidget::setLineWidth(const int width) {
	Q_D(CUVWatingWidget);

	d->lineWidth = width;
	d->updateSize();
}

void CUVWatingWidget::setInnerRadius(const int radius) {
	Q_D(CUVWatingWidget);

	d->innerRadius = radius;
	d->updateSize();
}

void CUVWatingWidget::setText(const QString& text) {
	Q_D(CUVWatingWidget);

	d->text = text;
	d->updateSize();
}

void CUVWatingWidget::setTextColor(const QColor& color) {
	Q_D(CUVWatingWidget);

	d->textColor = color;
}

void CUVWatingWidget::setFontSize(const int size) {
	Q_D(CUVWatingWidget);

	d->fontSize = size;
	d->updateSize();
}

void CUVWatingWidget::setTextPosition(const TextPosition& position) {
	Q_D(CUVWatingWidget);

	d->textPosition = position;
}

QColor CUVWatingWidget::color() {
	Q_D(CUVWatingWidget);

	return d->color;
}

qreal CUVWatingWidget::roundness() const {
	Q_D(const CUVWatingWidget);

	return d->roundness;
}

qreal CUVWatingWidget::minimumTrailOpacity() const {
	Q_D(const CUVWatingWidget);

	return d->minimumTrailOpacity;
}

qreal CUVWatingWidget::trailFadePercentage() const {
	Q_D(const CUVWatingWidget);

	return d->trailFadePercentage;
}

qreal CUVWatingWidget::revolutionsPersSecond() const {
	Q_D(const CUVWatingWidget);

	return d->revolutionsPerSecond;
}

int CUVWatingWidget::numberOfLines() const {
	Q_D(const CUVWatingWidget);

	return d->numberOfLines;
}

int CUVWatingWidget::lineLength() const {
	Q_D(const CUVWatingWidget);

	return d->lineLength;
}

int CUVWatingWidget::lineWidth() const {
	Q_D(const CUVWatingWidget);

	return d->lineWidth;
}

int CUVWatingWidget::innerRadius() const {
	Q_D(const CUVWatingWidget);

	return d->innerRadius;
}

QString CUVWatingWidget::text() const {
	Q_D(const CUVWatingWidget);

	return d->text;
}

QColor CUVWatingWidget::textColor() const {
	Q_D(const CUVWatingWidget);

	return d->textColor;
}

int CUVWatingWidget::fontSize() const {
	Q_D(const CUVWatingWidget);

	return d->fontSize;
}

bool CUVWatingWidget::isSpinning() const {
	Q_D(const CUVWatingWidget);

	return d->isSpinning;
}

CUVWatingWidget::TextPosition CUVWatingWidget::textPosition() const {
	Q_D(const CUVWatingWidget);

	return d->textPosition;
}

void CUVWatingWidget::setRoundness(const qreal roundness) {
	Q_D(CUVWatingWidget);

	d->roundness = std::max(0.0, std::min(100.0, roundness));
}

void CUVWatingWidget::setColor(const QColor& color) {
	Q_D(CUVWatingWidget);

	d->color = color;
}

void CUVWatingWidget::setRevolutionsPerSecond(const qreal revolutionsPerSecond) {
	Q_D(CUVWatingWidget);

	d->revolutionsPerSecond = revolutionsPerSecond;
	d->updateTimer();
}

void CUVWatingWidget::setTrailFadePercentage(const qreal trail) {
	Q_D(CUVWatingWidget);

	d->trailFadePercentage = trail;
}

void CUVWatingWidget::setMinimumTrailOpacity(const qreal minimumTrailOpacity) {
	Q_D(CUVWatingWidget);

	d->minimumTrailOpacity = minimumTrailOpacity;
}
