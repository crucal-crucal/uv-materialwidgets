#pragma once

#include <QListView>

class CUVComboBoxView final : public QListView {
	Q_OBJECT

public:
	explicit CUVComboBoxView(QWidget* parent = nullptr);
	~CUVComboBoxView() override;

signals:
	void itemPressed(const QModelIndex& index);

protected:
	void mousePressEvent(QMouseEvent* event) override;
};
