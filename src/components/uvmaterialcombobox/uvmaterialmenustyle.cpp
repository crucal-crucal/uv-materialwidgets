#include "uvmaterialmenustyle.hpp"

#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>

#include "uvmaterialmenu.hpp"

CUVMaterialMenuStyle::CUVMaterialMenuStyle(QStyle* style): QProxyStyle(style) {
	_pMenuItemHeight = 32;
	_windowLinearGradient = new QLinearGradient(0, 0, 100, 100);
}

CUVMaterialMenuStyle::~CUVMaterialMenuStyle() = default;

void CUVMaterialMenuStyle::drawPrimitive(const PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const {
	switch (element) {
		case QStyle::PE_PanelMenu: {
			// ��������Ӱ
			painter->save();
			painter->setRenderHint(QPainter::Antialiasing);
			QPainterPath path;
			path.setFillRule(Qt::WindingFill);
			auto color = QColor(0x9C, 0x9B, 0x9E);
			for (int i = 0; i < _shadowBorderWidth; i++) {
				QPainterPath painter_path;
				painter_path.setFillRule(Qt::WindingFill);
				painter_path.addRoundedRect(_shadowBorderWidth - i, _shadowBorderWidth - i, option->rect.width() - (_shadowBorderWidth - i) * 2,
				                            option->rect.height() - (_shadowBorderWidth - i) * 2, 6 + i, 6 + i);
				const int alpha = 5 * (_shadowBorderWidth - i + 1);
				color.setAlpha(alpha > 255 ? 255 : alpha);
				painter->setPen(color);
				painter->drawPath(painter_path);
			}
			painter->restore();
			// ��������
			const QRect foregroundRect(_shadowBorderWidth, _shadowBorderWidth, option->rect.width() - 2 * _shadowBorderWidth, option->rect.height() - 2 * _shadowBorderWidth);
			painter->setPen(QColor(0x52, 0x50, 0x52));
			_windowLinearGradient->setFinalStop(foregroundRect.bottomRight());
			painter->setBrush(*_windowLinearGradient);
			painter->drawRoundedRect(foregroundRect, 6, 6);
			painter->restore();
			return;
		}
		case QStyle::PE_FrameMenu: {
			return;
		}
		default: {
			break;
		}
	}
	QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void CUVMaterialMenuStyle::drawControl(const ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const {
	switch (element) {
		case QStyle::CE_MenuItem: {
			// ���ݻ��� ��������
			if (const auto mopt = qstyleoption_cast<const QStyleOptionMenuItem*>(option)) {
				if (mopt->menuItemType == QStyleOptionMenuItem::Separator) {
					const QRect separatorRect = mopt->rect;
					painter->save();
					painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
					painter->setPen(Qt::NoPen);
					painter->setBrush(QColor(0xB3, 0xB3, 0xB3));
					painter->drawRoundedRect(QRectF(separatorRect.x() + separatorRect.width() * 0.055, separatorRect.center().y(), separatorRect.width() - separatorRect.width() * 0.11, 1.5), 1, 1);
					painter->restore();
					return;
				} else {
					const QRect menuRect = mopt->rect;
					const qreal contentPadding = menuRect.width() * 0.055;
					const qreal textLeftSpacing = menuRect.width() * 0.082;
					painter->save();
					painter->setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
					// ����Ч��
					if (mopt->state.testFlag(QStyle::State_Enabled) && (mopt->state.testFlag(QStyle::State_MouseOver) || mopt->state.testFlag(QStyle::State_Selected))) {
						QRect hoverRect = menuRect;
						hoverRect.adjust(0, 2, 0, -2);
						painter->setPen(Qt::NoPen);
						painter->setBrush(QColor(0x46, 0x46, 0x46));
						painter->drawRoundedRect(hoverRect, 5, 5);
					}
					// Icon����
					const QIcon menuIcon = mopt->icon;
					// check����
					if (mopt->menuHasCheckableItems) {
						// painter->save();
						// painter->setPen(!mopt->state.testFlag(QStyle::State_Enabled) ? Qt::gray : Qt::white);
						// QFont iconFont = QFont("ElaAwesome");
						// iconFont.setPixelSize(_pMenuItemHeight * 0.57);
						// painter->setFont(iconFont);
						// painter->drawText(QRectF(menuRect.x() + contentPadding, menuRect.y(), _iconWidth, menuRect.height()), Qt::AlignCenter, mopt->checked ? QChar((unsigned short) ElaIconType::Check) : QChar((unsigned short) ElaIconType::None));
						// painter->restore();
					} else {
						if (!menuIcon.isNull()) {
							painter->drawPixmap(QRect(menuRect.x() + contentPadding, menuRect.center().y() - _iconWidth / 2, _iconWidth, _iconWidth), // NOLINT
							                    menuIcon.pixmap(_iconWidth, _iconWidth));
						} else {
							if (const auto menu = dynamic_cast<const CUVMaterialMenu*>(widget)) {
								if (const QAction* action = menu->actionAt(menuRect.center())) {
									if (const QString iconText = action->property("CUVIconType").toString(); !iconText.isEmpty()) {
										painter->save();
										painter->setPen(!mopt->state.testFlag(QStyle::State_Enabled) ? Qt::gray : Qt::white);
										painter->drawText(QRectF(menuRect.x() + contentPadding, menuRect.y(), _iconWidth, menuRect.height()), Qt::AlignCenter, iconText);
										painter->restore();
									}
								}
							}
						}
					}
					// ���ֺͿ�ݼ�����
					if (!mopt->text.isEmpty()) {
						QStringList textList = mopt->text.split("\t");
						painter->setPen(!mopt->state.testFlag(QStyle::State_Enabled) ? Qt::gray : Qt::white);

						painter->drawText(QRectF(menuRect.x() + (_isAnyoneItemHasIcon ? contentPadding + textLeftSpacing : 0) + _iconWidth, menuRect.y(), menuRect.width(), menuRect.height()), Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine, textList[0]);
						if (textList.count() > 1) {
							painter->drawText(QRectF(menuRect.x() + contentPadding + _iconWidth + textLeftSpacing, menuRect.y(), menuRect.width() - (contentPadding * 2 + _iconWidth + textLeftSpacing), menuRect.height()), Qt::AlignRight | Qt::AlignVCenter | Qt::TextSingleLine, textList[1]);
						}
					}
					// չ��ͼ��
					if (mopt->menuItemType == QStyleOptionMenuItem::SubMenu) {
						painter->save();
						painter->setPen(!mopt->state.testFlag(QStyle::State_Enabled) ? Qt::gray : Qt::white);
						// QFont iconFont = QFont("ElaAwesome");
						// iconFont.setPixelSize(18);
						// painter->setFont(iconFont);
						// painter->drawText(QRect(menuRect.right() - 25, menuRect.y(), 25, menuRect.height()), Qt::AlignVCenter, QChar((unsigned short) ElaIconType::AngleRight));
						painter->drawPixmap(QRect(menuRect.right() - 25, menuRect.y(), 25, menuRect.height()), QPixmap());
						painter->restore();
					}
					painter->restore();
				}
			}

			return;
		}
		case QStyle::CE_MenuEmptyArea: {
			return;
		}
		default: {
			break;
		}
	}
	QProxyStyle::drawControl(element, option, painter, widget);
}

int CUVMaterialMenuStyle::pixelMetric(const PixelMetric metric, const QStyleOption* option, const QWidget* widget) const {
	switch (metric) {
		case QStyle::PM_SmallIconSize: {
			//ͼ����
			return _iconWidth;
		}
		case QStyle::PM_MenuPanelWidth: {
			//��Χ�������
			return _shadowBorderWidth * 1.5; // NOLINT
		}
		default: {
			break;
		}
	}
	return QProxyStyle::pixelMetric(metric, option, widget);
}

QSize CUVMaterialMenuStyle::sizeFromContents(const ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const {
	switch (type) {
		case QStyle::CT_MenuItem: {
			if (const auto mopt = qstyleoption_cast<const QStyleOptionMenuItem*>(option)) {
				if (mopt->menuItemType == QStyleOptionMenuItem::Separator) {
					break;
				}
				const QSize menuItemSize = QProxyStyle::sizeFromContents(type, option, size, widget);
				const auto menu = dynamic_cast<const CUVMaterialMenu*>(widget);
				if (menu->isHasIcon() || mopt->menuHasCheckableItems) {
					_isAnyoneItemHasIcon = true;
				}
				if (menu->isHasChildMenu()) {
					return { menuItemSize.width() + 20, _pMenuItemHeight };
				} else {
					return { menuItemSize.width(), _pMenuItemHeight };
				}
			}
		}
		default: {
			break;
		}
	}
	return QProxyStyle::sizeFromContents(type, option, size, widget);
}

void CUVMaterialMenuStyle::setMenuItemHeight(const int height) {
	_pMenuItemHeight = height;
	emit onMenuItemHeightChanged();
}

int CUVMaterialMenuStyle::getMenuItemHeight() const {
	return _pMenuItemHeight;
}
