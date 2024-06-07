#include "uvscrollbarsettingseditor.hpp"

CUVScrollBarSettingsEditor::CUVScrollBarSettingsEditor(QWidget* parent)
: QWidget(parent), m_pVerticalScrollBar(new CUVMaterialScrollBar), m_pHorizontalScrollBar(new CUVMaterialScrollBar) {
	createCtrl();
	customLayout();
	initData();
}

CUVScrollBarSettingsEditor::~CUVScrollBarSettingsEditor() = default;

void CUVScrollBarSettingsEditor::createCtrl() {
	m_pTextEdit = new QTextEdit(this);
	m_pTextEdit->setMaximumHeight(400);

	m_pcancas = new QWidget(this);
	m_pcancas->setStyleSheet("background-color: rgb(255, 255, 255);");

	m_pVLayBottom = new QVBoxLayout;
	m_pVLayCenter = new QVBoxLayout;

	m_pcancas->setLayout(m_pVLayBottom);
	this->setLayout(m_pVLayCenter);
}

void CUVScrollBarSettingsEditor::customLayout() const {
	m_pVLayBottom->addWidget(m_pTextEdit);
	m_pVLayBottom->setAlignment(m_pTextEdit, Qt::AlignHCenter);

	m_pVLayCenter->addWidget(m_pcancas);
}

void CUVScrollBarSettingsEditor::initData() const {
	QString str{};
	for (int i = 0; i < 100; i++) {
		str += QString("this is test %1,this is test %2,this is test %3,this is test %4\n").arg(i).arg(i+1).arg(i+2).arg(i+3);
	}
	m_pTextEdit->setText(str);
	m_pTextEdit->update();
	m_pTextEdit->setLineWrapMode(QTextEdit::NoWrap);
	m_pTextEdit->setVerticalScrollBar(m_pVerticalScrollBar);
	m_pTextEdit->setHorizontalScrollBar(m_pHorizontalScrollBar);
}
