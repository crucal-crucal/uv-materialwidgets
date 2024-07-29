#include "uvautocompletesettingseditor.hpp"

#include <QDebug>

#include "uvmaterialautocomplete/uvmaterialautocomplete.hpp"

CUVAutoCompleteSettingsEditor::CUVAutoCompleteSettingsEditor(QWidget* parent)
: QWidget(parent), m_autocomplete(new CUVMaterialAutoComplete) {
	m_pVLayCenter = new QVBoxLayout;
	setLayout(m_pVLayCenter);

	m_pcanvas = new QWidget;
	m_pcanvas->setStyleSheet("QWidget { background: white; }");
	m_pVLayCenter->addWidget(m_pcanvas);

	m_pVLayCenter->setContentsMargins(20, 20, 20, 20);

	m_pVLayCanvas = new QVBoxLayout;
	m_pcanvas->setLayout(m_pVLayCanvas);

	const QStringList states = {
		"Alabama", "Alaska", "American Samoa", "Arizona", "Arkansas", "California", "Colorado", "Connecticut", "Delaware", "District of Columbia",
		"Florida", "Georgia", "Guam", "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland",
		"Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire", "New Jersey",
		"New Mexico", "New York", "North Carolina", "North Dakota", "Northern Marianas Islands", "Ohio", "Oklahoma", "Oregon", "Pennsylvania",
		"Puerto Rico", "Rhode Island", "South Carolina", "South Dakota", "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Virgin Islands",
		"Washington", "West Virginia", "Wisconsin", "Wyoming"
	};

	m_autocomplete->setDataSource(states);
	m_autocomplete->setLabel("this is test");

	m_pVLayCanvas->addSpacing(100);
	m_pVLayCanvas->addWidget(m_autocomplete);
	m_pVLayCanvas->addStretch();
	m_pVLayCanvas->setAlignment(m_autocomplete, Qt::AlignHCenter);
}

CUVAutoCompleteSettingsEditor::~CUVAutoCompleteSettingsEditor() = default;
