#pragma once

#include <QtWidgets/QWidget>

class QStackedLayout;
class CUVMaterialDialog;
class CUVMaterialDialogWindow;

class CUVMaterialDialogProxy final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialDialogProxy)

	Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

	enum TransparencyMode {
		Transparent,
		SemiTransparent,
		Opaque,
	};

public:
	explicit CUVMaterialDialogProxy(CUVMaterialDialogWindow* source, QStackedLayout* layout, CUVMaterialDialog* dialog, QWidget* parent = nullptr);
	~CUVMaterialDialogProxy() override;

	void setOpacity(qreal opacity);
	[[nodiscard]] inline qreal opacity() const;

public slots:
	void makeOpaque();
	void makeTransparent();

	[[nodiscard]] QSize sizeHint() const override;

protected:
	bool event(QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	CUVMaterialDialogWindow* const m_source{ nullptr };
	QStackedLayout* const m_layout{ nullptr };
	CUVMaterialDialog* const m_dialog{ nullptr };
	qreal m_opacity{};
	TransparencyMode m_mode{};
};

inline qreal CUVMaterialDialogProxy::opacity() const {
	return m_opacity;
}

class CUVMaterialDialogWindow final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialDialogWindow)

	Q_PROPERTY(int offset WRITE setOffset READ offset)

public:
	explicit CUVMaterialDialogWindow(CUVMaterialDialog* dialog, QWidget* parent = nullptr);
	~CUVMaterialDialogWindow() override;

	void setOffset(int offset) const;
	[[nodiscard]] int offset() const;

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	CUVMaterialDialog* const m_dialog{ nullptr };
};
