#pragma once

#include <QIcon>
#include <QtWidgets/QWidget>

#include "uvmaterialshared/uvmaterialtheme.hpp"

class CUVMaterialTabsPrivate;
class CUVMaterialTab;

#ifdef CUVMATERIALTABS_LIB
#define CUVMATERIALTABS_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALTABS_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALTABS_EXPORT CUVMaterialTabs final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialTabs)
	Q_DECLARE_PRIVATE(CUVMaterialTabs)

public:
	explicit CUVMaterialTabs(QWidget* parent = nullptr);
	~CUVMaterialTabs() override;

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setHaloVisible(bool value);
	[[nodiscard]] bool isHaloVisible() const;

	void setRippleStyle(Material::RippleStyle style);
	[[nodiscard]] Material::RippleStyle rippleStyle() const;

	void setInkColor(const QColor& color);
	[[nodiscard]] QColor inkColor() const;

	void setBackgroundColor(const QColor& color);
	[[nodiscard]] QColor backgroundColor() const;

	void setTextColor(const QColor& color);
	[[nodiscard]] QColor textColor() const;

	void addTab(const QString& text, const QIcon& icon = QIcon());

	void setCurrentTab(CUVMaterialTab* tab);
	void setCurrentTab(int index);

	[[nodiscard]] int currentIndex() const;

signals:
	void currentChanged(int);

protected:
	void setTabActive(int index, bool active = true);
	void updateTabs();

	const QScopedPointer<CUVMaterialTabsPrivate> d_ptr{ nullptr };
};
