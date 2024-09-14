#include "uvcomboboxview.hpp"

#include <QMouseEvent>

CUVComboBoxView::CUVComboBoxView(QWidget* parent): QListView(parent) {
}

CUVComboBoxView::~CUVComboBoxView() = default;

void CUVComboBoxView::mousePressEvent(QMouseEvent* event) {
	QModelIndex index = indexAt(event->pos());
	if (index.isValid()) {
		emit itemPressed(index);
	}
	event->ignore();
}
