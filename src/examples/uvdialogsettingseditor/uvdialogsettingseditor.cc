#include "uvdialogsettingseditor.hpp"

CUVDialogSettingsEditor::CUVDialogSettingsEditor(QWidget* parent): QWidget(parent), m_pdialog(new CUVMaterialDialog) {
	createCtrl();
	customLayout();
	initConnection();
}

CUVDialogSettingsEditor::~CUVDialogSettingsEditor() = default;

void CUVDialogSettingsEditor::createCtrl() {
	m_pBtnShowDialog = new QPushButton(tr("Show Dialog"), this);

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");
	m_pdialog->setParent(m_pcanvas);

	m_pdialogWidget = new QWidget(this);
	m_pdialogWidget->setMinimumHeight(300);

	m_pCloseButton = new CUVMaterialFlatButton("Close");
	m_pCloseButton->setFixedWidth(150);

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;
	m_pVLayDialog = new QVBoxLayout;
	m_pVLayDialogWidget = new QVBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	m_pdialogWidget->setLayout(m_pVLayDialogWidget);
	m_pdialog->setWindowLayout(m_pVLayDialog);
	this->setLayout(m_pVLayCenter);
}

void CUVDialogSettingsEditor::customLayout() const {
	m_pVLayCenter->addWidget(m_pBtnShowDialog);
	m_pVLayCenter->addWidget(m_pcanvas);

	m_pVLayDialogWidget->addWidget(m_pCloseButton);
	m_pVLayDialogWidget->setAlignment(m_pCloseButton, Qt::AlignBottom | Qt::AlignCenter);

	m_pVLayDialog->addWidget(m_pdialogWidget);
}

void CUVDialogSettingsEditor::initConnection() const {
	connect(m_pBtnShowDialog, &QPushButton::clicked, m_pdialog, &CUVMaterialDialog::showDialog);
	connect(m_pCloseButton, &CUVMaterialFlatButton::clicked, m_pdialog, &CUVMaterialDialog::hideDialog);
}
