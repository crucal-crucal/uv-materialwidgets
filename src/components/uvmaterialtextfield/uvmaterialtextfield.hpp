#pragma once

#include <QColor>
#include <QtWidgets/QLineEdit>

class CUVMaterialTextFieldPrivate;

#ifdef CUVMATERIALTEXTFIELD_LIB
#define CUVMATERIALTEXTFIELD_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALTEXTFIELD_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALTEXTFIELD_EXPORT CUVMaterialTextField : public QLineEdit {
	Q_OBJECT

	Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
	Q_PROPERTY(QColor inkColor WRITE setInkColor READ inkColor)
	Q_PROPERTY(QColor inputLineColor WRITE setInputLineColor READ inputLineColor)

public:
	explicit CUVMaterialTextField(QWidget* parent = nullptr);
	~CUVMaterialTextField() override;

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setShowLabel(bool value);
	[[nodiscard]] bool hasLabel() const;

	void setLabelFontSize(qreal size);
	[[nodiscard]] qreal labelFontSize() const;

	void setLabel(const QString& label);
	[[nodiscard]] QString label() const;

	void setTextColor(const QColor& color);
	[[nodiscard]] QColor textColor() const;

	void setLabelColor(const QColor& color);
	[[nodiscard]] QColor labelColor() const;

	void setInkColor(const QColor& color);
	[[nodiscard]] QColor inkColor() const;

	void setInputLineColor(const QColor& color);
	[[nodiscard]] QColor inputLineColor() const;

	void setShowInputLine(bool value);
	[[nodiscard]] bool hasInputLine() const;

protected:
	explicit CUVMaterialTextField(CUVMaterialTextFieldPrivate& d, QWidget* parent = nullptr);

	bool event(QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVMaterialTextFieldPrivate> d_ptr{ nullptr };

private:
	Q_DISABLE_COPY(CUVMaterialTextField)
	Q_DECLARE_PRIVATE(CUVMaterialTextField)
};
