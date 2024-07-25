#include "uvmaterialcomboboxstyle.hpp"

#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>
#include <QWidget>

CUVMaterialComboBoxStyle::CUVMaterialComboBoxStyle(QStyle* style): QProxyStyle(style) {
	_pExpandIconRotate = 0;
	_pExpandMarkWidth = 0;
	normalColor = qRgb(25, 25, 25);
	mouseHoverColor = qRgb(42, 42, 42);
	mouseSelectedColor = qRgb(42, 42, 42);
	borderColor = qRgb(75, 75, 77);
}

CUVMaterialComboBoxStyle::~CUVMaterialComboBoxStyle() = default;

void CUVMaterialComboBoxStyle::drawPrimitive(const PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const {
	switch (element) {
		case QStyle::PE_Widget: {
			return;
		}
		default: {
			break;
		}
	}
	QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void CUVMaterialComboBoxStyle::drawControl(const ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const {
	switch (element) {
		case QStyle::CE_ComboBoxLabel: {
			return;
		}
		case QStyle::CE_ShapedFrame: {
			// container����
			if (widget->objectName() == "CUVComboBoxContainer") {
				const QRect viewRect = option->rect;
				painter->save();
				painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
				QPainterPath path;
				path.setFillRule(Qt::WindingFill);
				auto color = QColor(0x9C, 0x9B, 0x9E);
				for (int i = 0; i < _shadowBorderWidth; i++) {
					QPainterPath painter_path;
					painter_path.setFillRule(Qt::WindingFill);
					painter_path.addRoundedRect(_shadowBorderWidth - i, _shadowBorderWidth - i, viewRect.width() - (_shadowBorderWidth - i) * 2,
					                            viewRect.height() - (_shadowBorderWidth - i) * 2, 6 + i, 6 + i);
					const int alpha = 5 * (_shadowBorderWidth - i + 1);
					color.setAlpha(alpha > 255 ? 255 : alpha);
					painter->setPen(color);
					painter->drawPath(painter_path);
				}
				const QRect foregroundRect(viewRect.x() + _shadowBorderWidth, viewRect.y(), viewRect.width() - 2 * _shadowBorderWidth, viewRect.height() - _shadowBorderWidth);
				painter->setPen(QColor(0x52, 0x50, 0x52));
				painter->setBrush(normalColor);
				painter->drawRoundedRect(foregroundRect, 3, 3);
				painter->restore();
			}
			return;
		}
		case QStyle::CE_ItemViewItem: {
			// ���Ǹ���
			if (const auto vopt = qstyleoption_cast<const QStyleOptionViewItem*>(option)) {
				constexpr int margin = 2;
				painter->save();
				painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
				painter->setPen(Qt::NoPen);
				QPainterPath path;
				QRect optionRect = option->rect;
				optionRect.adjust(margin, margin, -margin, -margin);
				path.addRoundedRect(optionRect, 5, 5);
				if (option->state & QStyle::State_Selected) {
					if (option->state & QStyle::State_MouseOver) {
						// ѡ��ʱ����
						painter->setBrush(mouseHoverColor);
						painter->drawPath(path);
					} else {
						// ѡ��
						painter->setBrush(mouseSelectedColor);
						painter->drawPath(path);
					}
					// ѡ��Mark
					painter->setPen(Qt::NoPen);
					painter->setBrush(QColor(0x4C, 0xA0, 0xE0));
					painter->drawRoundedRect(QRectF(optionRect.x() + 3, optionRect.y() + optionRect.height() * 0.2, 3, optionRect.height() - +optionRect.height() * 0.4), 2, 2);
				} else {
					if (option->state & QStyle::State_MouseOver) {
						// ����ʱ��ɫ
						painter->setBrush(QColor(0x40, 0x40, 0x40));
						painter->drawPath(path);
					}
				}
				// ���ֻ���
				painter->setPen(Qt::white);
				painter->drawText(QRect(option->rect.x() + 15, option->rect.y(), option->rect.width() - 15, option->rect.height()), Qt::AlignVCenter, vopt->text);
				painter->restore();
			}
			return;
		}
		default: {
			break;
		}
	}
	QProxyStyle::drawControl(element, option, painter, widget);
}

void CUVMaterialComboBoxStyle::drawComplexControl(const ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget) const {
	switch (control) {
		case QStyle::CC_ComboBox: {
			// ������ʾ����
			if (const auto copt = qstyleoption_cast<const QStyleOptionComboBox*>(option)) {
				painter->save();
				painter->setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
				// ��������
				painter->setPen(borderColor);
				painter->setBrush(copt->state.testFlag(QStyle::State_MouseOver) ? mouseHoverColor : normalColor);
				QRect comboBoxRect = copt->rect;
				comboBoxRect.adjust(_shadowBorderWidth, 1, -_shadowBorderWidth, -1);
				painter->drawRoundedRect(comboBoxRect, 3, 3);
				// ���ֻ���
				const QRect textRect = subControlRect(QStyle::CC_ComboBox, copt, QStyle::SC_ScrollBarSubLine, widget);
				painter->setPen(Qt::white);
				painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, copt->currentText);
				// չ��ָʾ������
				painter->setPen(Qt::NoPen);
				painter->setBrush(QColor(0x4C, 0xA0, 0xE0));
				painter->drawRoundedRect(QRectF(comboBoxRect.center().x() - _pExpandMarkWidth, comboBoxRect.height() - 3, _pExpandMarkWidth * 2, 3), 2, 2);
				// չ��ͼ�����
				if (const QRect expandIconRect = subControlRect(QStyle::CC_ComboBox, copt, QStyle::SC_ScrollBarAddPage, widget); expandIconRect.isValid()) {
					const int size = qMin(expandIconRect.width(), expandIconRect.height()) - 15;
					const int xOffset = (expandIconRect.width() - size) / 2;
					const int yOffset = (expandIconRect.height() - size) / 2;
					const QRect squareRect(expandIconRect.x() + xOffset, expandIconRect.y() + yOffset, size, size);
					// ����ͼ��
					const QPixmap scaledPixmap = QPixmap(":/icons/icons/combo/combobox_down_arrow.png").scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
					painter->setPen(Qt::white);
					painter->translate(squareRect.x() + static_cast<qreal>(size) / 2, squareRect.y() + static_cast<qreal>(size) / 2);
					painter->rotate(_pExpandIconRotate);
					painter->translate(-squareRect.x() - static_cast<qreal>(size) / 2, -squareRect.y() - static_cast<qreal>(size) / 2);
					painter->drawPixmap(squareRect, scaledPixmap);
					painter->restore();
				}
			}
			return;
		}
		default: {
			break;
		}
	}

	QProxyStyle::drawComplexControl(control, option, painter, widget);
}

QRect CUVMaterialComboBoxStyle::subControlRect(const ComplexControl cc, const QStyleOptionComplex* opt, const SubControl sc, const QWidget* widget) const {
	switch (cc) {
		case QStyle::CC_ComboBox: {
			switch (sc) {
				case QStyle::SC_ScrollBarSubLine: {
					// ��������
					QRect textRect = QProxyStyle::subControlRect(cc, opt, sc, widget);
					textRect.setLeft(16);
					textRect.setRight(textRect.right() - 15);
					return textRect;
				}
				case QStyle::SC_ScrollBarAddPage: {
					// չ��ͼ������
					QRect expandIconRect = QProxyStyle::subControlRect(cc, opt, sc, widget);
					expandIconRect.setLeft(expandIconRect.left() - 30);
					return expandIconRect;
				}
				default: {
					break;
				}
			}
			break;
		}
		default: {
			break;
		}
	}

	return QProxyStyle::subControlRect(cc, opt, sc, widget);
}

QSize CUVMaterialComboBoxStyle::sizeFromContents(const ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const {
	switch (type) {
		case QStyle::CT_ItemViewItem: {
			QSize itemSize = QProxyStyle::sizeFromContents(type, option, size, widget);
			itemSize.setHeight(35);
			return itemSize;
		}
		case QStyle::CT_ComboBox: {
			QSize comboBoxSize = QProxyStyle::sizeFromContents(type, option, size, widget);
			comboBoxSize.setWidth(comboBoxSize.width() + 26);
			return comboBoxSize;
		}
		default: {
			break;
		}
	}
	return QProxyStyle::sizeFromContents(type, option, size, widget);
}

void CUVMaterialComboBoxStyle::setExpandIconRotate(const qreal ExpandIconRotate) {
	_pExpandIconRotate = ExpandIconRotate;
	emit onExpandIconRotateChanged();
}

qreal CUVMaterialComboBoxStyle::getExpandIconRotate() const {
	return _pExpandIconRotate;
}

void CUVMaterialComboBoxStyle::setExpandMarkWidth(const qreal ExpandMarkWidth) {
	_pExpandMarkWidth = ExpandMarkWidth;
	emit onExpandMarkWidthChanged();
}

qreal CUVMaterialComboBoxStyle::getExpandMarkWidth() const {
	return _pExpandMarkWidth;
}
