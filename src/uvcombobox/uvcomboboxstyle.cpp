#include "uvcomboboxstyle.hpp"

#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>
#include <QWidget>

CUVComboBoxStyle::CUVComboBoxStyle(QStyle* style): QProxyStyle(style) {
	_pExpandIconRotate = 0;
	_pExpandMarkWidth = 0;
	normalColor = qRgb(25, 25, 25);
	mouseHoverColor = qRgb(42, 42, 42);
	mouseSelectedColor = qRgb(42, 42, 42);
	borderColor = qRgb(75, 75, 77);
	selectedMarkColor = QColor(0x4C, 0xA0, 0xE0);
	itemHoverColor = QColor(0x40, 0x40, 0x40);
	expansionIndicatorColor = QColor(0x4C, 0xA0, 0xE0);
	unselectedMarkColor = Qt::gray;
}

CUVComboBoxStyle::~CUVComboBoxStyle() = default;

void CUVComboBoxStyle::drawPrimitive(const PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const {
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

void CUVComboBoxStyle::drawControl(const ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const {
	switch (element) {
		case QStyle::CE_ComboBoxLabel: {
			return;
		}
		case QStyle::CE_ShapedFrame: {
			// container区域
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
			// 覆盖高亮
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
						// 选中且鼠标悬停时
						painter->setBrush(mouseHoverColor);
						painter->drawPath(path);
					} else {
						// 选中但鼠标未悬停
						painter->setBrush(mouseSelectedColor);
						painter->drawPath(path);
					}
					painter->save();
					painter->setPen(QPen(selectedMarkColor, 2)); // 设置画笔颜色和宽度
				} else {
					if (option->state & QStyle::State_MouseOver) {
						// 未选中但鼠标悬停时
						painter->setBrush(itemHoverColor);
						painter->drawPath(path);
					}
					painter->save();
					painter->setPen(QPen(unselectedMarkColor, 2)); // 设置未选中的图标颜色和宽度
				}

				// 计算勾选图标的绘制区域
				const int checkSize = static_cast<int>(qMin(optionRect.width(), optionRect.height()) * 0.5); // 图标大小为项目高度的一半
				const auto checkRect = QRect(optionRect.x() + 5,
											 optionRect.y() + (optionRect.height() - checkSize) / 2,
											 checkSize,
											 checkSize);
				// 绘制勾选图标
				QPainterPath checkPath;
				checkPath.moveTo(checkRect.left() + checkRect.width() * 0.2, checkRect.top() + checkRect.height() * 0.5);
				checkPath.lineTo(checkRect.left() + checkRect.width() * 0.4, checkRect.bottom() - checkRect.height() * 0.25);
				checkPath.lineTo(checkRect.right() - checkRect.width() * 0.2, checkRect.top() + checkRect.height() * 0.3);
				painter->drawPath(checkPath);
				painter->restore();
				// 文字绘制
				painter->setPen(Qt::white);
				painter->drawText(QRect(option->rect.x() + 25, option->rect.y(), option->rect.width() - 25, option->rect.height()), Qt::AlignVCenter, vopt->text);
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

void CUVComboBoxStyle::drawComplexControl(const ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget) const {
	switch (control) {
		case QStyle::CC_ComboBox: {
			// 主体显示绘制
			if (const auto copt = qstyleoption_cast<const QStyleOptionComboBox*>(option)) {
				painter->save();
				painter->setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
				// 背景绘制
				painter->setPen(borderColor);
				painter->setBrush(copt->state.testFlag(QStyle::State_MouseOver) ? mouseHoverColor : normalColor);
				QRect comboBoxRect = copt->rect;
				comboBoxRect.adjust(_shadowBorderWidth, 1, -_shadowBorderWidth, -1);
				painter->drawRoundedRect(comboBoxRect, 3, 3);
				// 文字绘制
				const QRect textRect = subControlRect(QStyle::CC_ComboBox, copt, QStyle::SC_ScrollBarSubLine, widget);
				painter->setPen(Qt::white);
				painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, copt->currentText);
				// 展开指示器绘制
				painter->setPen(Qt::NoPen);
				painter->setBrush(expansionIndicatorColor);
				painter->drawRoundedRect(QRectF(comboBoxRect.center().x() - _pExpandMarkWidth, comboBoxRect.height() - 3, _pExpandMarkWidth * 2, 3), 2, 2);
				// 展开图标绘制
				if (const QRect expandIconRect = subControlRect(QStyle::CC_ComboBox, copt, QStyle::SC_ScrollBarAddPage, widget); expandIconRect.isValid()) {
					const int size = qMin(expandIconRect.width(), expandIconRect.height()) - 15;
					const int xOffset = (expandIconRect.width() - size) / 2;
					const int yOffset = (expandIconRect.height() - size) / 2;
					const QRect squareRect(expandIconRect.x() + xOffset, expandIconRect.y() + yOffset, size, size);
					// 绘制图标
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

QRect CUVComboBoxStyle::subControlRect(const ComplexControl cc, const QStyleOptionComplex* opt, const SubControl sc, const QWidget* widget) const {
	switch (cc) {
		case QStyle::CC_ComboBox: {
			switch (sc) {
				case QStyle::SC_ScrollBarSubLine: {
					// 文字区域
					QRect textRect = QProxyStyle::subControlRect(cc, opt, sc, widget);
					textRect.setLeft(16);
					textRect.setRight(textRect.right() - 15);
					return textRect;
				}
				case QStyle::SC_ScrollBarAddPage: {
					// 展开图标区域
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

QSize CUVComboBoxStyle::sizeFromContents(const ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const {
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

void CUVComboBoxStyle::setExpandIconRotate(const qreal ExpandIconRotate) {
	_pExpandIconRotate = ExpandIconRotate;
	emit onExpandIconRotateChanged();
}

qreal CUVComboBoxStyle::getExpandIconRotate() const {
	return _pExpandIconRotate;
}

void CUVComboBoxStyle::setExpandMarkWidth(const qreal ExpandMarkWidth) {
	_pExpandMarkWidth = ExpandMarkWidth;
	emit onExpandMarkWidthChanged();
}

qreal CUVComboBoxStyle::getExpandMarkWidth() const {
	return _pExpandMarkWidth;
}
