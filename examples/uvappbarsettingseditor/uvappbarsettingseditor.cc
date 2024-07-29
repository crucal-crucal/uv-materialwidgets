#include "uvappbarsettingseditor.hpp"

#include <QColorDialog>

#include "mainwidget.hpp"
#include "uvmaterialshared/uvmaterialtheme.hpp"
#include "uvmaterialappbar/uvmaterialappbar.hpp"

CUVAppBarSettingsEditor::CUVAppBarSettingsEditor(QWidget* parent) : QWidget(parent), m_pMaterialAppBar(new CUVMaterialAppBar) {
	createCtrl();
	customLayout();
	setUpForm();
	initConnection();
}

CUVAppBarSettingsEditor::~CUVAppBarSettingsEditor() = default;

void CUVAppBarSettingsEditor::createCtrl() {
	m_pLbuseThemeColor = new QLabel(this);
	m_pLbuseThemeColor->setText(tr("Use theme colors"));

	m_pCbuseThemeColor = new QCheckBox(this);

	m_pLbBackgroundColor = new QLabel(this);
	m_pLbBackgroundColor->setText(tr("Background color"));

	m_pLeBackgroundColor = new QLineEdit(this);
	m_pTbBackgroundColor = new QToolButton(this);
	m_pTbBackgroundColor->setObjectName("backgroundColorToolButton");
	m_pTbBackgroundColor->setText("...");

	m_pLbAppBarText = new QLabel(this);
	m_pLbAppBarText->setText(tr("AppBar"));
	m_pLbAppBarText->setAttribute(Qt::WA_TranslucentBackground);
	m_pLbAppBarText->setForegroundRole(QPalette::WindowText);
	m_pLbAppBarText->setContentsMargins(6, 0, 0, 0);

	QPalette palette = m_pLbAppBarText->palette();
	palette.setColor(m_pLbAppBarText->foregroundRole(), Qt::white);
	m_pLbAppBarText->setPalette(palette);

	m_pMaterialIconButton = new CUVMaterialIconButton(CUVMaterialTheme::icon("navigation", "menu"));
	m_pMaterialIconButton->setIconSize(QSize(24, 24));
	m_pMaterialIconButton->setColor(Qt::white);
	m_pMaterialIconButton->setFixedWidth(42);

	m_pVLayCenter = new QVBoxLayout;
	m_pHLayuseThemeColor = new QHBoxLayout;
	m_pHLayuseBackgroundColor = new QHBoxLayout;

	m_pcanvas = new QWidget;
	m_pcanvas->setStyleSheet("QWidget { background: white; }");

	m_pVLayBottom = new QVBoxLayout;
	m_pcanvas->setLayout(m_pVLayBottom);

	this->setLayout(m_pVLayCenter);
}

void CUVAppBarSettingsEditor::customLayout() const {
	m_pHLayuseThemeColor->addWidget(m_pLbuseThemeColor);
	m_pHLayuseThemeColor->addWidget(m_pCbuseThemeColor);
	m_pHLayuseThemeColor->addStretch();

	m_pHLayuseBackgroundColor->addWidget(m_pLbBackgroundColor);
	m_pHLayuseBackgroundColor->addWidget(m_pLeBackgroundColor);
	m_pHLayuseBackgroundColor->addWidget(m_pTbBackgroundColor);
	m_pHLayuseBackgroundColor->addStretch();

	m_pMaterialAppBar->appBarLayout()->addWidget(m_pMaterialIconButton);
	m_pMaterialAppBar->appBarLayout()->addWidget(m_pLbAppBarText);
	m_pMaterialAppBar->appBarLayout()->addStretch(1);

	m_pVLayBottom->addWidget(m_pMaterialAppBar);
	m_pVLayBottom->addStretch(1);

	m_pVLayCenter->addLayout(m_pHLayuseThemeColor);
	m_pVLayCenter->addLayout(m_pHLayuseBackgroundColor);
	m_pVLayCenter->addWidget(m_pcanvas);
	m_pVLayCenter->setContentsMargins(20, 20, 20, 20);
}

void CUVAppBarSettingsEditor::initConnection() {
	connect(m_pCbuseThemeColor, &QCheckBox::toggled, this, &CUVAppBarSettingsEditor::updateWidget);
	connect(m_pTbBackgroundColor, &QToolButton::clicked, this, &CUVAppBarSettingsEditor::selectColor);
}

void CUVAppBarSettingsEditor::setUpForm() const {
	m_pCbuseThemeColor->setChecked(m_pMaterialAppBar->useThemeColors());
}

void CUVAppBarSettingsEditor::updateWidget() const {
	m_pMaterialAppBar->setUseThemeColors(m_pCbuseThemeColor->isChecked());
}

void CUVAppBarSettingsEditor::selectColor() {
	if (QColorDialog dialog(this); dialog.exec()) {
		const QColor color = dialog.selectedColor();
		if ("backgroundColorToolButton" == sender()->objectName()) {
			m_pMaterialAppBar->setBackgroundColor(color);
			m_pLeBackgroundColor->setText(color.name(QColor::HexRgb));
		}
	}
	setUpForm();
}
