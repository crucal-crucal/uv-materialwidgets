#pragma once

#include <QComboBox>

class CUVMaterialComboBoxPrivate;

#ifdef CUVMATERIALCOMBOBOX_LIB
#define CUVMATERIALCOMBOBOX_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALCOMBOBOX_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALCOMBOBOX_EXPORT CUVMaterialComboBox final : public QComboBox {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialComboBox)
	Q_DECLARE_PRIVATE(CUVMaterialComboBox)

	Q_PROPERTY(int BorderRadius READ getBorderRadius WRITE setBorderRadius NOTIFY onBorderRadiusChanged)

public:
	explicit CUVMaterialComboBox(QWidget* parent = nullptr);
	~CUVMaterialComboBox() override;

	void setBorderRadius(int borderRadius);
	[[nodiscard]] int getBorderRadius() const;

	void setNomalColor(const QColor& color);
	[[nodiscard]] QColor getNomalColor() const;

	void setMouseHoverColor(const QColor& color);
	[[nodiscard]] QColor getMouseHoverColor() const;

	void setMouseSelectedColor(const QColor& color);
	[[nodiscard]] QColor getMouseSelectedColor() const;

	void setBorderColor(const QColor& color);
	[[nodiscard]] QColor getBorderColor() const;

signals:
	void onBorderRadiusChanged();

protected:
	QScopedPointer<CUVMaterialComboBoxPrivate> d_ptr{ nullptr };

	void showPopup() override;
	void hidePopup() override;
};
