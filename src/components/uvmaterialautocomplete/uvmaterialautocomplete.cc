#include "uvmaterialautocomplete.hpp"

#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QVBoxLayout>

#include "uvmaterialautocomplete_internal.hpp"
#include "uvmaterialautocomplete_p.hpp"
#include "uvmaterialflatbutton/uvmaterialflatbutton.hpp"

/*!
 *  \class CUVMaterialAutoCompletePrivate
 */
CUVMaterialAutoCompletePrivate::CUVMaterialAutoCompletePrivate(CUVMaterialAutoComplete* q): CUVMaterialTextFieldPrivate(q) {
}

/*!
 *  \internal
 */
CUVMaterialAutoCompletePrivate::~CUVMaterialAutoCompletePrivate() = default;

/*!
 *  \internal
 */
void CUVMaterialAutoCompletePrivate::init() {
	Q_Q(CUVMaterialAutoComplete);

	menu = new QWidget;
	frame = new QWidget;
	stateMachine = new CUVMaterialAutoCompleteStateMachine(menu);
	menuLayout = new QVBoxLayout;
	maxWidth = 0;

	menu->setParent(q->parentWidget());
	frame->setParent(q->parentWidget());

	menu->installEventFilter(q);
	frame->installEventFilter(q);

	auto* effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(11);
	effect->setColor(QColor(0, 0, 0, 50));
	effect->setOffset(0, 3);

	frame->setGraphicsEffect(effect);
	frame->setVisible(false);

	menu->setLayout(menuLayout);
	menu->setVisible(false);

	menuLayout->setContentsMargins(0, 0, 0, 0);
	menuLayout->setSpacing(0);

	QObject::connect(q, &CUVMaterialAutoComplete::textEdited, q, &CUVMaterialAutoComplete::updateResults);

	stateMachine->start();
}

/*!
 *  \class CUVMaterialAutoComplete
 */
CUVMaterialAutoComplete::CUVMaterialAutoComplete(QWidget* parent): CUVMaterialTextField(*new CUVMaterialAutoCompletePrivate(this), parent) {
	d_func()->init();
}

CUVMaterialAutoComplete::~CUVMaterialAutoComplete() = default;

void CUVMaterialAutoComplete::setDataSource(const QStringList& data) {
	Q_D(CUVMaterialAutoComplete);

	d->dataSource = data;
	update();
}

void CUVMaterialAutoComplete::updateResults(const QString& text) {
	Q_D(CUVMaterialAutoComplete);

	QStringList results;

	if (const QString trimmed(text.trimmed()); !trimmed.isEmpty()) {
		const QString lookup(trimmed.toLower());
		for (auto& i : d->dataSource) {
			if (i.toLower().indexOf(lookup) != -1) {
				results.push_back(i);
			}
		}
	}

	const int diff = results.length() - d->menuLayout->count();
	const QFont font("Roboto", 12, QFont::Normal);

	if (diff > 0) {
		for (int c = 0; c < diff; c++) {
			auto* item = new CUVMaterialFlatButton;
			item->setFont(font);
			item->setTextAlignment(Qt::AlignLeft);
			item->setCornerRadius(0);
			item->setHaloVisible(false);
			item->setFixedHeight(50);
			item->setOverlayStyle(Material::TintedOverlay);
			d->menuLayout->addWidget(item);
			item->installEventFilter(this);
		}
	} else if (diff < 0) {
		for (int c = 0; c < -diff; c++) {
			if (const auto widget = d->menuLayout->itemAt(0)->widget()) {
				d->menuLayout->removeWidget(widget);
				delete widget;
			}
		}
	}

	const auto fm = new QFontMetrics(font);
	d->maxWidth = 0;

	for (int i = 0; i < results.count(); ++i) {
		QWidget* widget = d->menuLayout->itemAt(i)->widget();
		if (const auto item = dynamic_cast<CUVMaterialFlatButton*>(widget)) {
			const QString& curtext = results.at(i);
			QRect rect = fm->boundingRect(curtext);
			d->maxWidth = qMax(d->maxWidth, rect.width());
			item->setText(curtext);
		}
	}

	if (!results.count()) {
		emit d->stateMachine->shouldClose();
	} else {
		emit d->stateMachine->shouldOpen();
	}

	d->menu->setFixedHeight(results.length() * 50);
	d->menu->setFixedWidth(qMax(d->maxWidth + 24, width()));
	d->menu->update();
}

bool CUVMaterialAutoComplete::CUVMaterialAutoComplete::event(QEvent* event) {
	Q_D(CUVMaterialAutoComplete);

	switch (event->type()) {
		case QEvent::Move:
		case QEvent::Resize: {
			d->menu->move(pos() + QPoint(0, height() + 6));
			break;
		}
		case QEvent::ParentChange: {
			if (const auto widget = dynamic_cast<QWidget*>(parent())) {
				d->menu->setParent(widget);
				d->frame->setParent(widget);
			}
			break;
		}
		default:
			break;
	}
	return CUVMaterialTextField::event(event);
}

bool CUVMaterialAutoComplete::eventFilter(QObject* watched, QEvent* event) {
	Q_D(CUVMaterialAutoComplete);

	if (d->frame == watched) {
		switch (event->type()) {
			case QEvent::Paint: {
				QPainter painter(d->frame);
				painter.fillRect(d->frame->rect(), Qt::white);
				break;
			}
			default: break;
		}
	} else if (d->menu == watched) {
		switch (event->type()) {
			case QEvent::Resize:
			case QEvent::Move: {
				d->frame->setGeometry(d->menu->geometry());
				break;
			}
			case QEvent::Show: {
				d->frame->show();
				d->menu->raise();
				break;
			}
			case QEvent::Hide: {
				d->frame->hide();
				break;
			}
			default: break;
		}
	} else {
		switch (event->type()) {
			case QEvent::MouseButtonPress: {
				emit d->stateMachine->shouldFade();
				if (const auto widget = dynamic_cast<CUVMaterialFlatButton*>(watched)) {
					const QString text(widget->text());
					setText(text);
					emit itemSelected(text);
				}
				break;
			}
			default: break;
		}
	}
	return CUVMaterialTextField::eventFilter(watched, event);
}
