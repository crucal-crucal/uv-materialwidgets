#pragma once

#include <QComboBox>

class CUVMultiSelectComboBoxPrivate;

#ifdef CUVMULTISELECTCOMBOBOX_LIB
#define CUVMULTISELECTCOMBOBOX_EXPORT Q_DECL_EXPORT
#else
#define CUVMULTISELECTCOMBOBOX_EXPORT Q_DECL_IMPORT
#endif
class CUVMultiSelectComboBox : public QComboBox {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMultiSelectComboBox)
	Q_DECLARE_PRIVATE(CUVMultiSelectComboBox)
	Q_PROPERTY(int pBorderRadius READ getBorderRadius WRITE setBorderRadius NOTIFY pborderRadiusChanged)

public:
	explicit CUVMultiSelectComboBox(QWidget* parent = nullptr);
	~CUVMultiSelectComboBox() override;

	void setCurrentSelection(const QString& selection);
	void setCurrentSelection(const QStringList& selection);
	void setCurrentSelection(int index);
	void setCurrentSelection(const QList<int>& selectionIndex);
	[[nodiscard]] QStringList getCurrentSelection() const;
	[[nodiscard]] QList<int> getCurrentSelectionIndex() const;
	void setBorderRadius(int radius);
	[[nodiscard]] int getBorderRadius() const;

signals:
	void itemSelectionChanged(const QVector<bool>& itemSelection);
	void currentTextListChanged(const QStringList& selectedTextList);
	void pborderRadiusChanged();

protected:
	const QScopedPointer<CUVMultiSelectComboBoxPrivate> d_ptr{ nullptr };

	void paintEvent(QPaintEvent* event) override;
	void showPopup() override;
	void hidePopup() override;
};
