#include "uvwatingwidgetsettingseditor.hpp"

#include <QColorDialog>

CUVWatingWidgetSettingsEditor::CUVWatingWidgetSettingsEditor(QWidget* parent): QWidget(parent), m_pWating(new CUVWatingWidget) {
	createCtrl();
	customLayout();
	initData();
	setupForm();
	initConnection();
}

CUVWatingWidgetSettingsEditor::~CUVWatingWidgetSettingsEditor() = default;

void CUVWatingWidgetSettingsEditor::createCtrl() {
	m_pLbTextPosition = new QLabel(tr("Text Position:"), this);
	m_pLbTextPosition->setFixedWidth(m_nLabelWidth);
	m_pCbTextPosition = new QComboBox(this);

	m_pLbText = new QLabel(tr("Text:"), this);
	m_pLbText->setFixedWidth(m_nLabelWidth);
	m_pLeText = new QLineEdit(this);

	m_pLbTextColor = new QLabel(tr("Text Color:"), this);
	m_pLbTextColor->setFixedWidth(m_nLabelWidth);
	m_pLeTextColor = new QLineEdit(this);
	m_pTbTextColor = new QToolButton(this);
	m_pTbTextColor->setText("...");
	m_pTbTextColor->setObjectName("TbTextColor");

	m_pLbColor = new QLabel(tr("Color:"), this);
	m_pLbColor->setFixedWidth(m_nLabelWidth);
	m_pLeColor = new QLineEdit(this);
	m_pTbColor = new QToolButton(this);
	m_pTbColor->setText("...");
	m_pTbColor->setObjectName("TbColor");

	m_pLbRoundness = new QLabel(tr("Roundness:"), this);
	m_pLbRoundness->setFixedWidth(m_nLabelWidth);
	m_pDSpinRoundness = new QDoubleSpinBox(this);

	m_pLbOpacity = new QLabel(tr("Opacity:"), this);
	m_pLbOpacity->setFixedWidth(m_nLabelWidth);
	m_pDSpinOpacity = new QDoubleSpinBox(this);

	m_pLbFadePerc = new QLabel(tr("Fade Percent:"), this);
	m_pLbFadePerc->setFixedWidth(m_nLabelWidth);
	m_pDSpinFadePerc = new QDoubleSpinBox(this);

	m_pLbLines = new QLabel(tr("Lines:"), this);
	m_pLbLines->setFixedWidth(m_nLabelWidth);
	m_pSpinLines = new QSpinBox(this);

	m_pLbLineLength = new QLabel(tr("Line Length:"), this);
	m_pLbLineLength->setFixedWidth(m_nLabelWidth);
	m_pSpinLineLength = new QSpinBox(this);

	m_pLbLineWidth = new QLabel(tr("Line Width:"), this);
	m_pLbLineWidth->setFixedWidth(m_nLabelWidth);
	m_pSpinLineWidth = new QSpinBox(this);

	m_pLbInnerRadius = new QLabel(tr("Inner Radius:"), this);
	m_pLbInnerRadius->setFixedWidth(m_nLabelWidth);
	m_pSpinInnerRadius = new QSpinBox(this);

	m_pLbRev = new QLabel(tr("Rev/S:"), this);
	m_pLbRev->setFixedWidth(m_nLabelWidth);
	m_pDSpinRev = new QDoubleSpinBox(this);

	m_pBtnStart = new QPushButton(this);
	m_pBtnStart->setText("Start");

	m_pBtnStop = new QPushButton(this);
	m_pBtnStop->setText("Stop");

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color:rgb(255,255,255);");
	m_pWating->setParent(m_pcanvas);

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pHLayTextPosition = new QHBoxLayout;
	m_pHLayText = new QHBoxLayout;
	m_pHLayTextColor = new QHBoxLayout;
	m_pHLayColor = new QHBoxLayout;
	m_pHLayRoundness = new QHBoxLayout;
	m_pHLayOpacity = new QHBoxLayout;
	m_pHLayFadePerc = new QHBoxLayout;
	m_pHLayLines = new QHBoxLayout;
	m_pHLayLineLength = new QHBoxLayout;
	m_pHLayLineWidth = new QHBoxLayout;
	m_pHLayInnerRadius = new QHBoxLayout;
	m_pHLayRev = new QHBoxLayout;
	m_pHLayBtn = new QHBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVWatingWidgetSettingsEditor::customLayout() const {
	m_pHLayTextPosition->addWidget(m_pLbTextPosition);
	m_pHLayTextPosition->addWidget(m_pCbTextPosition);
	m_pHLayTextPosition->addStretch();

	m_pHLayText->addWidget(m_pLbText);
	m_pHLayText->addWidget(m_pLeText);
	m_pHLayText->addStretch();

	m_pHLayTextColor->addWidget(m_pLbTextColor);
	m_pHLayTextColor->addWidget(m_pLeTextColor);
	m_pHLayTextColor->addWidget(m_pTbTextColor);
	m_pHLayTextColor->addStretch();

	m_pHLayColor->addWidget(m_pLbColor);
	m_pHLayColor->addWidget(m_pLeColor);
	m_pHLayColor->addWidget(m_pTbColor);
	m_pHLayColor->addStretch();

	m_pHLayRoundness->addWidget(m_pLbRoundness);
	m_pHLayRoundness->addWidget(m_pDSpinRoundness);
	m_pHLayRoundness->addStretch();

	m_pHLayOpacity->addWidget(m_pLbOpacity);
	m_pHLayOpacity->addWidget(m_pDSpinOpacity);
	m_pHLayOpacity->addStretch();

	m_pHLayFadePerc->addWidget(m_pLbFadePerc);
	m_pHLayFadePerc->addWidget(m_pDSpinFadePerc);
	m_pHLayFadePerc->addStretch();

	m_pHLayLines->addWidget(m_pLbLines);
	m_pHLayLines->addWidget(m_pSpinLines);
	m_pHLayLines->addStretch();

	m_pHLayLineLength->addWidget(m_pLbLineLength);
	m_pHLayLineLength->addWidget(m_pSpinLineLength);
	m_pHLayLineLength->addStretch();

	m_pHLayLineWidth->addWidget(m_pLbLineWidth);
	m_pHLayLineWidth->addWidget(m_pSpinLineWidth);
	m_pHLayLineWidth->addStretch();

	m_pHLayInnerRadius->addWidget(m_pLbInnerRadius);
	m_pHLayInnerRadius->addWidget(m_pSpinInnerRadius);
	m_pHLayInnerRadius->addStretch();

	m_pHLayRev->addWidget(m_pLbRev);
	m_pHLayRev->addWidget(m_pDSpinRev);
	m_pHLayRev->addStretch();

	m_pHLayBtn->addWidget(m_pBtnStart);
	m_pHLayBtn->addWidget(m_pBtnStop);

	m_pVLayBottom->addWidget(m_pWating);
	m_pVLayBottom->setAlignment(m_pWating, Qt::AlignHCenter);

	m_pVLayCenter->addLayout(m_pHLayTextPosition);
	m_pVLayCenter->addLayout(m_pHLayText);
	m_pVLayCenter->addLayout(m_pHLayTextColor);
	m_pVLayCenter->addLayout(m_pHLayColor);
	m_pVLayCenter->addLayout(m_pHLayRoundness);
	m_pVLayCenter->addLayout(m_pHLayOpacity);
	m_pVLayCenter->addLayout(m_pHLayFadePerc);
	m_pVLayCenter->addLayout(m_pHLayLines);
	m_pVLayCenter->addLayout(m_pHLayLineLength);
	m_pVLayCenter->addLayout(m_pHLayLineWidth);
	m_pVLayCenter->addLayout(m_pHLayInnerRadius);
	m_pVLayCenter->addLayout(m_pHLayRev);
	m_pVLayCenter->addLayout(m_pHLayBtn);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVWatingWidgetSettingsEditor::initData() const {
	m_pCbTextPosition->addItem("Bottom");
	m_pCbTextPosition->addItem("Top");

	m_pWating->setText("test");
}

void CUVWatingWidgetSettingsEditor::initConnection() {
	connect(m_pCbTextPosition, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CUVWatingWidgetSettingsEditor::updateWidget);
	connect(m_pLeText, &QLineEdit::textChanged, this, &CUVWatingWidgetSettingsEditor::updateWidget);
	connect(m_pDSpinRoundness, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CUVWatingWidgetSettingsEditor::updateWidget);
	connect(m_pDSpinOpacity, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CUVWatingWidgetSettingsEditor::updateWidget);
	connect(m_pDSpinFadePerc, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CUVWatingWidgetSettingsEditor::updateWidget);
	connect(m_pSpinLines, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVWatingWidgetSettingsEditor::updateWidget);
	connect(m_pSpinLineLength, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVWatingWidgetSettingsEditor::updateWidget);
	connect(m_pSpinLineWidth, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVWatingWidgetSettingsEditor::updateWidget);
	connect(m_pSpinInnerRadius, QOverload<int>::of(&QSpinBox::valueChanged), this, &CUVWatingWidgetSettingsEditor::updateWidget);
	connect(m_pDSpinRev, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CUVWatingWidgetSettingsEditor::updateWidget);
	connect(m_pTbColor, &QToolButton::clicked, this, &CUVWatingWidgetSettingsEditor::selectColor);
	connect(m_pTbTextColor, &QToolButton::clicked, this, &CUVWatingWidgetSettingsEditor::selectColor);
	connect(m_pBtnStart, &QPushButton::clicked, m_pWating, &CUVWatingWidget::start);
	connect(m_pBtnStop, &QPushButton::clicked, m_pWating, &CUVWatingWidget::stop);
}

void CUVWatingWidgetSettingsEditor::setupForm() const {
	switch (m_pWating->textPosition()) {
		case CUVWatingWidget::Bottom: {
			m_pCbTextPosition->setCurrentIndex(0);
			break;
		}
		case CUVWatingWidget::Top: {
			m_pCbTextPosition->setCurrentIndex(1);
			break;
		}
		default: break;
	}

	m_pLeText->setText(m_pWating->text());
	m_pLeTextColor->setText(m_pWating->textColor().name(QColor::HexRgb));
	m_pLeColor->setText(m_pWating->color().name(QColor::HexRgb));
	m_pDSpinRoundness->setValue(m_pWating->roundness());
	m_pDSpinOpacity->setValue(m_pWating->minimumTrailOpacity());
	m_pDSpinFadePerc->setValue(m_pWating->trailFadePercentage());
	m_pSpinLines->setValue(m_pWating->numberOfLines());
	m_pSpinLineLength->setValue(m_pWating->lineLength());
	m_pSpinLineWidth->setValue(m_pWating->lineWidth());
	m_pSpinInnerRadius->setValue(m_pWating->innerRadius());
	m_pDSpinRev->setValue(m_pWating->revolutionsPersSecond());
}

void CUVWatingWidgetSettingsEditor::updateWidget() const {
	switch (m_pCbTextPosition->currentIndex()) {
		case 0: {
			m_pWating->setTextPosition(CUVWatingWidget::Bottom);
			break;
		}
		case 1: {
			m_pWating->setTextPosition(CUVWatingWidget::Top);
			break;
		}
		default: break;
	}

	m_pWating->setText(m_pLeText->text());
	m_pWating->setRoundness(m_pDSpinRoundness->value());
	m_pWating->setMinimumTrailOpacity(m_pDSpinOpacity->value());
	m_pWating->setTrailFadePercentage(m_pDSpinFadePerc->value());
	m_pWating->setNumberOfLines(m_pSpinLines->value());
	m_pWating->setLineLength(m_pSpinLineLength->value());
	m_pWating->setLineWidth(m_pSpinLineWidth->value());
	m_pWating->setInnerRadius(m_pSpinInnerRadius->value());
	m_pWating->setRevolutionsPerSecond(m_pDSpinRev->value());
}

void CUVWatingWidgetSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if (const QString senderName = sender()->objectName(); "TbColor" == senderName) {
			m_pWating->setColor(color);
			m_pLeColor->setText(color.name(QColor::HexRgb));
		} else if ("TbTextColor" == senderName) {
			m_pWating->setTextColor(color);
			m_pLeTextColor->setText(color.name(QColor::HexRgb));
		}
	}
	setupForm();
}
