#pragma once

#include <QPushButton>

#include "uvmaterialmessagebar/uvdef.hpp"

#ifdef CUVMATERIALAWESOMEBUTTON_LIB
#define CUVMATERIALAWESOMEBUTTON_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALAWESOMEBUTTON_EXPORT Q_DECL_IMPORT
#endif

using namespace UVIconType;

class CUVMaterialAwesomeButtonPrivate;

/**
 * 使用 Awesome 绘制的图标按钮
 */
class CUVMATERIALAWESOMEBUTTON_EXPORT CUVMaterialAwesomeButton final : public QPushButton {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialAwesomeButton)
	Q_DECLARE_PRIVATE(CUVMaterialAwesomeButton)

	Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius NOTIFY borderRadiusChanged)
	Q_PROPERTY(QColor lightHoverColor READ lightHoverColor WRITE setLightHoverColor NOTIFY lightHoverColorChanged)
	Q_PROPERTY(QColor darkHoverColor READ darkHoverColor WRITE setDarkHoverColor NOTIFY darkHoverColorChanged)
	Q_PROPERTY(QColor lightIconColor READ lightIconColor WRITE setLightIconColor NOTIFY lightIconColorChanged)
	Q_PROPERTY(QColor darkIconColor READ darkIconColor WRITE setDarkIconColor NOTIFY darkIconColorChanged)
	Q_PROPERTY(bool isSelected READ isSelected WRITE setIsSelected NOTIFY isSelectedChanged)

public:
	explicit CUVMaterialAwesomeButton(const CUVIconType& iconType, QWidget* parent = nullptr);
	explicit CUVMaterialAwesomeButton(const CUVIconType& iconType, int pixelSize, QWidget* parent = nullptr);
	explicit CUVMaterialAwesomeButton(const CUVIconType& iconType, int pixelSize, int fixedWidth, int fixedHeight, QWidget* parent = nullptr);
	~CUVMaterialAwesomeButton() override;

	void setIconType(const CUVIconType& iconType);
	[[nodiscard]] CUVIconType iconType() const;

	void setBorderRadius(int radius);
	[[nodiscard]] int borderRadius() const;

	void setLightHoverColor(const QColor& color);
	[[nodiscard]] QColor lightHoverColor() const;

	void setDarkHoverColor(const QColor& color);
	[[nodiscard]] QColor darkHoverColor() const;

	void setLightIconColor(const QColor& color);
	[[nodiscard]] QColor lightIconColor() const;

	void setDarkIconColor(const QColor& color);
	[[nodiscard]] QColor darkIconColor() const;

	void setIsSelected(bool isSelected);
	[[nodiscard]] bool isSelected() const;

signals:
	void borderRadiusChanged(int radius);
	void lightHoverColorChanged(const QColor& color);
	void darkHoverColorChanged(const QColor& color);
	void lightIconColorChanged(const QColor& color);
	void darkIconColorChanged(const QColor& color);
	void isSelectedChanged(bool isSelected);

protected:
	void paintEvent(QPaintEvent* event) override;
	const QScopedPointer<CUVMaterialAwesomeButtonPrivate> d_ptr{ nullptr };
};
