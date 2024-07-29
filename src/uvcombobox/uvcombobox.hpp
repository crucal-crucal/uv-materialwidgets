#pragma once

#include <QComboBox>

class CUVComboBoxPrivate;

#ifdef CUVCOMBOBOX_LIB
#define CUVCOMBOBOX_EXPORT Q_DECL_EXPORT
#else
#define CUVCOMBOBOX_EXPORT Q_DECL_IMPORT
#endif

class CUVCOMBOBOX_EXPORT CUVComboBox final : public QComboBox {
	Q_OBJECT
	Q_DISABLE_COPY(CUVComboBox)
	Q_DECLARE_PRIVATE(CUVComboBox)

	Q_PROPERTY(int BorderRadius READ getBorderRadius WRITE setBorderRadius NOTIFY onBorderRadiusChanged)

public:
	explicit CUVComboBox(QWidget* parent = nullptr);
	~CUVComboBox() override;

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

	void setSelectedMarkColor(const QColor& color);
	[[nodiscard]] QColor getSelectedMarkColor() const;

	void setItemHoverColor(const QColor& color);
	[[nodiscard]] QColor getItemHoverColor() const;

	void setExpansionIndicatorColor(const QColor& color);
	[[nodiscard]] QColor getExpansionIndicatorColor() const;

signals:
	void onBorderRadiusChanged();

protected:
	QScopedPointer<CUVComboBoxPrivate> d_ptr{ nullptr };

	void showPopup() override;
	void hidePopup() override;
};
