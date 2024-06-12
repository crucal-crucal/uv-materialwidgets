#include "uvmaterialtextfield.hpp"

#include <QDebug>
#include <QPainter>
#include <QtWidgets/QApplication>

#include "uvmaterialtextfield_internal.hpp"
#include "uvmaterialtextfield_p.hpp"
#include "uvshared/uvmaterialstyle.hpp"

/*!
 *  \class CUVMaterialTextFieldPrivate
 *  \internal
 */
CUVMaterialTextFieldPrivate::CUVMaterialTextFieldPrivate(CUVMaterialTextField* q): q_ptr(q) {
}

CUVMaterialTextFieldPrivate::~CUVMaterialTextFieldPrivate() = default;

void CUVMaterialTextFieldPrivate::init() {
	Q_Q(CUVMaterialTextField);

	stateMachine = new CUVMaterialTextFieldStateMachine(q);
	label = nullptr;
	labelFontSize = 9.5;
	showLabel = false;
	showInputLine = true;
	useThemeColors = true;

	q->setFrame(false);
	q->setStyle(&CUVMaterialStyle::instance());
	q->setAttribute(Qt::WA_Hover);
	q->setMouseTracking(true);
	q->setTextMargins(0, 2, 0, 4);

	q->setFont(QFont("Roboto", 11, QFont::Normal));

	stateMachine->start();
	QCoreApplication::processEvents();
}

/*!
 *  \class CUVMaterialTextField
 */
CUVMaterialTextField::CUVMaterialTextField(QWidget* parent)
: QLineEdit(parent), d_ptr(new CUVMaterialTextFieldPrivate(this)) {
	d_func()->init();
}

CUVMaterialTextField::~CUVMaterialTextField() = default;

void CUVMaterialTextField::setUseThemeColors(const bool value) {
	Q_D(CUVMaterialTextField);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	d->stateMachine->setupProperties();
}

bool CUVMaterialTextField::useThemeColors() const {
	Q_D(const CUVMaterialTextField);

	return d->useThemeColors;
}

void CUVMaterialTextField::setShowLabel(const bool value) {
	Q_D(CUVMaterialTextField);

	if (d->showLabel == value) {
		return;
	}

	d->showLabel = value;

	if (!d->label && value) {
		d->label = new CUVMaterialTextFieldLabel(this);
		d->stateMachine->setLabel(d->label);
	}

	if (value) {
		setContentsMargins(0, 23, 0, 0);
	} else {
		setContentsMargins(0, 0, 0, 0);
	}
}

bool CUVMaterialTextField::hasLabel() const {
	Q_D(const CUVMaterialTextField);

	return d->showLabel;
}

void CUVMaterialTextField::setLabelFontSize(const qreal size) {
	Q_D(CUVMaterialTextField);

	d->labelFontSize = size;

	if (d->label) {
		QFont font(d->label->font());
		font.setPointSizeF(size);
		d->label->setFont(font);
		d->label->update();
	}
}

qreal CUVMaterialTextField::labelFontSize() const {
	Q_D(const CUVMaterialTextField);

	return d->labelFontSize;
}

void CUVMaterialTextField::setLabel(const QString& label) {
	Q_D(CUVMaterialTextField);

	d->labelString = label;
	setShowLabel(true);
	d->label->update();
}

QString CUVMaterialTextField::label() const {
	Q_D(const CUVMaterialTextField);

	return d->labelString;
}

void CUVMaterialTextField::setTextColor(const QColor& color) {
	Q_D(CUVMaterialTextField);

	d->textColor = color;
	setStyleSheet(QString("QLineEdit { color: %1; }").arg(color.name()));

	MATERIAL_DISABLE_THEME_COLORS
	d->stateMachine->setupProperties();
}

QColor CUVMaterialTextField::textColor() const {
	Q_D(const CUVMaterialTextField);

	if (d->useThemeColors || !d->textColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("text");
	} else {
		return d->textColor;
	}
}

void CUVMaterialTextField::setLabelColor(const QColor& color) {
	Q_D(CUVMaterialTextField);

	d->labelColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	d->stateMachine->setupProperties();
}

QColor CUVMaterialTextField::labelColor() const {
	Q_D(const CUVMaterialTextField);

	if (d->useThemeColors || !d->labelColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("accent3");
	} else {
		return d->labelColor;
	}
}

void CUVMaterialTextField::setInkColor(const QColor& color) {
	Q_D(CUVMaterialTextField);

	d->inkColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	d->stateMachine->setupProperties();
}

QColor CUVMaterialTextField::inkColor() const {
	Q_D(const CUVMaterialTextField);

	if (d->useThemeColors || !d->inkColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("primary1");
	} else {
		return d->inkColor;
	}
}

void CUVMaterialTextField::setInputLineColor(const QColor& color) {
	Q_D(CUVMaterialTextField);

	d->inputLineColor = color;

	MATERIAL_DISABLE_THEME_COLORS
	d->stateMachine->setupProperties();
}

QColor CUVMaterialTextField::inputLineColor() const {
	Q_D(const CUVMaterialTextField);

	if (d->useThemeColors || !d->inputLineColor.isValid()) {
		return CUVMaterialStyle::instance().themeColor("border");
	} else {
		return d->inputLineColor;
	}
}

void CUVMaterialTextField::setShowInputLine(const bool value) {
	Q_D(CUVMaterialTextField);

	if (d->showInputLine == value) {
		return;
	}

	d->showInputLine = value;
	update();
}

bool CUVMaterialTextField::hasInputLine() const {
	Q_D(const CUVMaterialTextField);

	return d->showInputLine;
}

CUVMaterialTextField::CUVMaterialTextField(CUVMaterialTextFieldPrivate& d, QWidget* parent)
: QLineEdit(parent), d_ptr(&d) {
	d_func()->init();
}

bool CUVMaterialTextField::event(QEvent* event) {
	Q_D(CUVMaterialTextField);

	switch (event->type()) {
		case QEvent::Resize:
		case QEvent::Move: {
			if (d->label) {
				d->label->setGeometry(rect());
			}
		}
		default:
			break;
	}
	return QLineEdit::event(event);
}

void CUVMaterialTextField::paintEvent(QPaintEvent* event) {
	Q_D(CUVMaterialTextField);

	QLineEdit::paintEvent(event);

	QPainter painter(this);

	const qreal progress = d->stateMachine->progress();

	if (text().isEmpty() && progress < 1) {
		painter.setOpacity(1 - progress);
		painter.fillRect(rect(), parentWidget()->palette().color(backgroundRole()));
	}

	const int y = height() - 1;
	const int wd = width() - 5;

	if (d->showInputLine) {
		QPen pen;
		pen.setWidth(1);
		pen.setColor(inputLineColor());

		if (!isEnabled())
			pen.setStyle(Qt::DashLine);

		painter.setPen(pen);
		painter.setOpacity(1);
		painter.drawLine(QLineF(2.5, y, wd, y));

		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(inkColor());

		if (progress > 0) {
			painter.setPen(Qt::NoPen);
			painter.setBrush(brush);
			const int w = static_cast<int>(1 - progress) * wd / 2;
			painter.drawRect(w + 2.5, height() - 2, wd - w * 2, 2); // NOLINT
		}
	}
}
