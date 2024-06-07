#include "uvmaterialwaitingwidget.hpp"

#include <algorithm>
#include <cmath>
#include <QPainter>
#include <QTimer>

CUVMaterialWatingWidget::CUVMaterialWatingWidget(QWidget* parent, const bool centerOnParent, const bool disableParentWhenSpinning)
: QWidget(parent), m_centerOnParent(centerOnParent), m_disableParentWhenSpinning(disableParentWhenSpinning) {
	initialize();
}

CUVMaterialWatingWidget::CUVMaterialWatingWidget(const Qt::WindowModality modality, QWidget* parent, const bool centerOnParent,
                                                 const bool disableParentWhenSpinning)
: QWidget(parent, Qt::Dialog | Qt::FramelessWindowHint), m_centerOnParent(centerOnParent), m_disableParentWhenSpinning(disableParentWhenSpinning) {
	initialize();

	setWindowModality(modality);
	setAttribute(Qt::WA_TranslucentBackground);
}

void CUVMaterialWatingWidget::initialize() {
	m_color = Qt::black;
	m_fontSize = 12;
	m_textColor = Qt::black;
	m_roundness = 100.0;
	m_minimumTrailOpacity = 3.14159265358979323846;
	m_trailFadePercentage = 80.0;
	m_revolutionsPerSecond = 1.57079632679489661923;
	m_numberOfLines = 20;
	m_lineLength = 10;
	m_lineWidth = 2;
	m_innerRadius = 10;
	m_currentCounter = 0;
	m_isSpinning = false;
	m_textPosition = TextPosition::Bottom;

	m_timer = new QTimer(this);
	connect(m_timer, &QTimer::timeout, this, &CUVMaterialWatingWidget::rotate);
	updateSize();
	updateTimer();
	hide();
}

void CUVMaterialWatingWidget::paintEvent(QPaintEvent*) {
	updatePosition();
	QPainter painter(this);
	painter.fillRect(this->rect(), Qt::transparent);
	painter.setRenderHint(QPainter::Antialiasing, true);

	if (m_currentCounter >= m_numberOfLines) {
		m_currentCounter = 0;
	}

	const int centerX = width() / 2;
	int centerY;
	if (m_textPosition == TextPosition::Bottom) {
		centerY = (height() - m_textHeight - 10) / 2;
	} else { // TextPosition::Top
		centerY = (height() + m_textHeight + 20) / 2;
	}

	painter.setPen(Qt::NoPen);
	for (int i = 0; i < m_numberOfLines; ++i) {
		painter.save();
		painter.translate(centerX, centerY);
		const qreal rotateAngle = static_cast<qreal>(360 * i) / static_cast<qreal>(m_numberOfLines);
		painter.rotate(rotateAngle);
		painter.translate(m_innerRadius, 0);
		const int distance = lineCountDistanceFromPrimary(i, m_currentCounter, m_numberOfLines);
		QColor color = currentLineColor(distance, m_numberOfLines, m_trailFadePercentage, m_minimumTrailOpacity, m_color);
		painter.setBrush(color);
		painter.drawRoundedRect(QRect(0, -m_lineWidth / 2, m_lineLength, m_lineWidth), m_roundness, m_roundness, Qt::RelativeSize);
		painter.restore();
	}

	// draw text
	if (!m_text.isEmpty()) {
		QFont font = painter.font();
		font.setPointSize(m_fontSize);
		painter.setFont(font);
		painter.setPen(m_textColor);

		const int x = (width() - m_textWidth) / 2;
		int y;
		if (m_textPosition == TextPosition::Bottom) {
			y = height() - 10;
		} else { // TextPosition::Top
			y = 10 + m_textHeight;
		}

		painter.drawText(x, y, m_text);
	}
}

void CUVMaterialWatingWidget::start() {
	updatePosition();
	m_isSpinning = true;
	show();

	if (parentWidget() && m_disableParentWhenSpinning) {
		parentWidget()->setEnabled(false);
	}

	if (!m_timer->isActive()) {
		m_timer->start();
		m_currentCounter = 0;
	}
}

void CUVMaterialWatingWidget::stop() {
	m_isSpinning = false;
	hide();

	if (parentWidget() && m_disableParentWhenSpinning) {
		parentWidget()->setEnabled(true);
	}

	if (m_timer->isActive()) {
		m_timer->stop();
		m_currentCounter = 0;
	}
}

void CUVMaterialWatingWidget::setNumberOfLines(const int lines) {
	m_numberOfLines = lines;
	m_currentCounter = 0;
	updateTimer();
}

void CUVMaterialWatingWidget::setLineLength(const int length) {
	m_lineLength = length;
	updateSize();
}

void CUVMaterialWatingWidget::setLineWidth(const int width) {
	m_lineWidth = width;
	updateSize();
}

void CUVMaterialWatingWidget::setInnerRadius(const int radius) {
	m_innerRadius = radius;
	updateSize();
}

void CUVMaterialWatingWidget::setText(const QString& text) {
	m_text = text;
	updateSize();
}

void CUVMaterialWatingWidget::setTextColor(const QColor& color) {
	m_textColor = color;
}

void CUVMaterialWatingWidget::setFontSize(const int size) {
	m_fontSize = size;
	updateSize();
}

void CUVMaterialWatingWidget::setTextPosition(const TextPosition& position) {
	m_textPosition = position;
}

QColor CUVMaterialWatingWidget::color() {
	return m_color;
}

qreal CUVMaterialWatingWidget::roundness() const {
	return m_roundness;
}

qreal CUVMaterialWatingWidget::minimumTrailOpacity() const {
	return m_minimumTrailOpacity;
}

qreal CUVMaterialWatingWidget::trailFadePercentage() const {
	return m_trailFadePercentage;
}

qreal CUVMaterialWatingWidget::revolutionsPersSecond() const {
	return m_revolutionsPerSecond;
}

int CUVMaterialWatingWidget::numberOfLines() const {
	return m_numberOfLines;
}

int CUVMaterialWatingWidget::lineLength() const {
	return m_lineLength;
}

int CUVMaterialWatingWidget::lineWidth() const {
	return m_lineWidth;
}

int CUVMaterialWatingWidget::innerRadius() const {
	return m_innerRadius;
}

QString CUVMaterialWatingWidget::text() const {
	return m_text;
}

QColor CUVMaterialWatingWidget::textColor() const {
	return m_textColor;
}

int CUVMaterialWatingWidget::fontSize() const {
	return m_fontSize;
}

bool CUVMaterialWatingWidget::isSpinning() const {
	return m_isSpinning;
}

CUVMaterialWatingWidget::TextPosition CUVMaterialWatingWidget::textPosition() const {
	return m_textPosition;
}

void CUVMaterialWatingWidget::setRoundness(const qreal roundness) {
	m_roundness = std::max(0.0, std::min(100.0, roundness));
}

void CUVMaterialWatingWidget::setColor(const QColor& color) {
	m_color = color;
}

void CUVMaterialWatingWidget::setRevolutionsPerSecond(const qreal revolutionsPerSecond) {
	m_revolutionsPerSecond = revolutionsPerSecond;
	updateTimer();
}

void CUVMaterialWatingWidget::setTrailFadePercentage(const qreal trail) {
	m_trailFadePercentage = trail;
}

void CUVMaterialWatingWidget::setMinimumTrailOpacity(const qreal minimumTrailOpacity) {
	m_minimumTrailOpacity = minimumTrailOpacity;
}

void CUVMaterialWatingWidget::rotate() {
	++m_currentCounter;
	if (m_currentCounter >= m_numberOfLines) {
		m_currentCounter = 0;
	}
	update();
}

void CUVMaterialWatingWidget::updateSize() {
	QFont font;
	font.setPointSize(m_fontSize);
	const QFontMetrics metrics(font);
	m_textHeight = metrics.height();
	m_textWidth = metrics.horizontalAdvance(m_text);
	const int spinnerSize = (m_innerRadius + m_lineLength) * 2;
	const int width = std::max(spinnerSize, m_textWidth + 20); // 确保窗口宽度足够
	const int height = spinnerSize + m_textHeight + 20;        // 增加文本高度和10像素间距
	setFixedSize(width, height);
}

void CUVMaterialWatingWidget::updateTimer() const {
	m_timer->setInterval(1000 / (m_numberOfLines * m_revolutionsPerSecond)); // NOLINT
}

void CUVMaterialWatingWidget::updatePosition() {
	if (parentWidget() && m_centerOnParent) {
		move(parentWidget()->width() / 2 - width() / 2, parentWidget()->height() / 2 - height() / 2);
	}
}

int CUVMaterialWatingWidget::lineCountDistanceFromPrimary(const int current, const int primary, const int totalNrOfLines) {
	int distance = primary - current;
	if (distance < 0) {
		distance += totalNrOfLines;
	}
	return distance;
}

QColor CUVMaterialWatingWidget::currentLineColor(const int distance, const int totalNrOfLines, const qreal trailFadePerc,
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
