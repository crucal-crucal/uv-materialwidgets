#pragma once

#include <QPushButton>

#include "uvmaterialmessagebar/uvdef.hpp"

#ifdef CUVMATERIALMESSAGEBUTTON_LIB
#define CUVMATERIALMESSAGEBUTTON_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALMESSAGEBUTTON_EXPORT Q_DECL_IMPORT
#endif

class CUVMaterialMessageButtonPrivate;

/**
 * @brief 点击即可调用对应的消息提示框
 */
class CUVMATERIALMESSAGEBUTTON_EXPORT CUVMaterialMessageButton final : public QPushButton {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialMessageButton)
	Q_DECLARE_PRIVATE(CUVMaterialMessageButton)

	Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius NOTIFY borderRadiusChanged)
	Q_PROPERTY(QString barTitle READ barTitle WRITE setBarTitle NOTIFY barTitleChanged)
	Q_PROPERTY(QString barText READ barText WRITE setBarText NOTIFY barTextChanged)
	Q_PROPERTY(int displayMsec READ displayMsec WRITE setDisplayMsec NOTIFY displayMsecChanged)
	Q_PROPERTY(UVMessageBarType::MessageMode messageMode READ messageMode WRITE setMessageMode NOTIFY messageModeChanged)
	Q_PROPERTY(UVMessageBarType::PositionPolicy positionPolicy READ positionPolicy WRITE setPositionPolicy NOTIFY positionPolicyChanged)

public:
	explicit CUVMaterialMessageButton(QWidget* parent = nullptr);
	explicit CUVMaterialMessageButton(const QString& text, QWidget* parent = nullptr);
	explicit CUVMaterialMessageButton(const QString& text, const UVMessageBarType::MessageMode& messageMode, QWidget* parent = nullptr);
	~CUVMaterialMessageButton() override;

	void setBorderRadius(int radius);
	[[nodiscard]] int borderRadius() const;

	void setBarTitle(const QString& title);
	[[nodiscard]] QString barTitle() const;

	void setBarText(const QString& text);
	[[nodiscard]] QString barText() const;

	void setDisplayMsec(int msec);
	[[nodiscard]] int displayMsec() const;

	void setMessageMode(const UVMessageBarType::MessageMode& messageMode);
	[[nodiscard]] UVMessageBarType::MessageMode messageMode() const;

	void setPositionPolicy(const UVMessageBarType::PositionPolicy& positionPolicy);
	[[nodiscard]] UVMessageBarType::PositionPolicy positionPolicy() const;

signals:
	void borderRadiusChanged(int radius);
	void barTitleChanged(const QString& title);
	void barTextChanged(const QString& text);
	void displayMsecChanged(int msec);
	void messageModeChanged(const UVMessageBarType::MessageMode& messageMode);
	void positionPolicyChanged(const UVMessageBarType::PositionPolicy& positionPolicy);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	const QScopedPointer<CUVMaterialMessageButtonPrivate> d_ptr{ nullptr };
};
