#include "uvstackwidgetsettingseditor.hpp"

#include <QButtonGroup>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

#include "uvstackwidget/uvstackwidget.hpp"

CUVStackWidgetSettingsEditor::CUVStackWidgetSettingsEditor(QWidget* parent) : QWidget(parent) {
	createCtrl();
	customLayout();
	initConnection();
	initData();
}

CUVStackWidgetSettingsEditor::~CUVStackWidgetSettingsEditor() = default;

void CUVStackWidgetSettingsEditor::createCtrl() {
	m_pLbMoveDirection = new QLabel(tr("Move Direction"), this);
	m_pCbMoveDirection = new QComboBox(this);

	m_pStackWidget = new CUVStackWidget(this);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(m_pStackWidget->sizePolicy().hasHeightForWidth());
	m_pStackWidget->setSizePolicy(sizePolicy);

	m_pButtonGroup = new QButtonGroup(this);

	m_pMoveDirectionHLayout = new QHBoxLayout;
	m_pBtnHLayout = new QHBoxLayout;
	m_pLayout = new QVBoxLayout;

	this->setLayout(m_pLayout);
}

void CUVStackWidgetSettingsEditor::customLayout() const {
	m_pMoveDirectionHLayout->addWidget(m_pLbMoveDirection);
	m_pMoveDirectionHLayout->addWidget(m_pCbMoveDirection);
	m_pMoveDirectionHLayout->addStretch();

	m_pLayout->addLayout(m_pMoveDirectionHLayout);
	m_pLayout->addLayout(m_pBtnHLayout);
	m_pLayout->addWidget(m_pStackWidget);
}

void CUVStackWidgetSettingsEditor::initConnection() {
	connect(m_pButtonGroup, &QButtonGroup::idClicked, m_pStackWidget, &CUVStackWidget::setCurrentIndex);
	connect(m_pCbMoveDirection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVStackWidgetSettingsEditor::updateWidget);
}

void CUVStackWidgetSettingsEditor::initData() {
	m_pCbMoveDirection->addItem(tr("Horizontal"));
	m_pCbMoveDirection->addItem(tr("Vertical"));

	QList<QColor> colorList{};
	colorList << Qt::red << Qt::green << Qt::blue << Qt::gray << Qt::cyan << Qt::magenta;

	QList<QPushButton*> buttonList{};
	for (int i = 0; i < colorList.size(); i++) {
		const QString text = QString("Widget %1").arg(i);
		const auto button = new QPushButton(text, this);
		button->setCheckable(true);
		buttonList << button;
	}

	for (int i = 0; i < buttonList.size(); ++i) {
		const auto label = new QLabel(m_pStackWidget);
		label->setStyleSheet(QString("background-color: %1; color: #ffffff").arg(colorList.at(i).name(QColor::HexRgb)));
		label->setText(QString("Widget %1").arg(i));
		label->setAlignment(Qt::AlignCenter);
		m_pButtonGroup->addButton(buttonList.at(i), m_pStackWidget->addWidget(label));
	}

	for (const auto& btn: buttonList) {
		m_pBtnHLayout->addWidget(btn);
	}
}

void CUVStackWidgetSettingsEditor::updateWidget() const {
	switch (m_pCbMoveDirection->currentIndex()) {
		case 0: {
			m_pStackWidget->setMoveDirection(CUVStackWidget::Horizontal);
			break;
		}
		case 1: {
			m_pStackWidget->setMoveDirection(CUVStackWidget::Vertical);
			break;
		}
		default: break;
	}
}
