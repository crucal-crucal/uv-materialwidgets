#include "uvsnackbarsettingseditor.hpp"


CUVSnackBarSettingsEditor::CUVSnackBarSettingsEditor(QWidget* parent): QWidget(parent), m_pSnackBar(new CUVMaterialSnackbar(this)) {
	createCtrl();
	customLayout();
	initConnection();
}

CUVSnackBarSettingsEditor::~CUVSnackBarSettingsEditor() = default;

void CUVSnackBarSettingsEditor::createCtrl() {
	m_pBtnShowSnackBar = new QPushButton(this);
	m_pBtnShowSnackBar->setText(tr("Show Snackbar"));
	m_pBtnShowSnackBar->setFixedWidth(150);

	m_pcanvas = new QWidget(this);
	m_pcanvas->setStyleSheet("background-color: rgb(255, 255, 255);");

	m_pVLayCenter = new QVBoxLayout;
	m_pVLayBottom = new QVBoxLayout;

	m_pcanvas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVSnackBarSettingsEditor::customLayout() const {
	m_pVLayCenter->addWidget(m_pBtnShowSnackBar);
	m_pVLayCenter->addWidget(m_pcanvas);
}

void CUVSnackBarSettingsEditor::initConnection() {
	connect(m_pBtnShowSnackBar, &QPushButton::clicked, this, &CUVSnackBarSettingsEditor::showSnackbar);
}


void CUVSnackBarSettingsEditor::showSnackbar() const {
	m_pSnackBar->addMessage(tr("This is a snackbar message."));
}
