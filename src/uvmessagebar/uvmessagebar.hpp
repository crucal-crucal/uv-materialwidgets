#pragma once

#include <QWidget>

#include "uvdef.hpp"

class CUVMessageBarPrivate;

class CUVMESSAGEBAR_EXPORT CUVMessageBar final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMessageBar)
	Q_DECLARE_PRIVATE(CUVMessageBar)

public:
	explicit CUVMessageBar(const UVMessageBarType::PositionPolicy& policy, const UVMessageBarType::MessageMode& messageMode,
	                       const QString& title, const QString& message, int displayMsec, QWidget* parent = nullptr);
	~CUVMessageBar() override;

	/**
	 * success notification
	 * @param title 标题
	 * @param message 消息
	 * @param displayMsec 显示时间, 默认2000ms
	 * @param positionPolicy 显示位置, 默认右上角
	 * @param parent 父窗口
	 */
	static void success(const QString& title, const QString& message, int displayMsec = 2000,
	                    const UVMessageBarType::PositionPolicy& positionPolicy = UVMessageBarType::TopRight, QWidget* parent = nullptr);

	/**
	 * waring notification
	 * @param title 标题
	 * @param message 消息
	 * @param displayMsec 显示时间, 默认2000ms
	 * @param positionPolicy 显示位置, 默认左上角
	 * @param parent 父窗口
	 */
	static void warning(const QString& title, const QString& message, int displayMsec = 2000,
	                    const UVMessageBarType::PositionPolicy& positionPolicy = UVMessageBarType::TopLeft, QWidget* parent = nullptr);

	/**
	 * infomation notification
	 * @param title 标题
	 * @param message 消息
	 * @param displayMsec 显示时间, 默认2000ms
	 * @param positionPolicy 显示位置, 默认左下角
	 * @param parent 父窗口
	 */
	static void infomation(const QString& title, const QString& message, int displayMsec = 2000,
	                       const UVMessageBarType::PositionPolicy& positionPolicy = UVMessageBarType::BottomLeft, QWidget* parent = nullptr);

	/**
	 * error notification
	 * @param title 标题
	 * @param message 消息
	 * @param displayMsec 显示时间, 默认2000ms
	 * @param positionPolicy 显示位置, 默认右下角
	 * @param parent 父窗口
	 */
	static void error(const QString& title, const QString& message, int displayMsec = 2000,
	                  const UVMessageBarType::PositionPolicy& positionPolicy = UVMessageBarType::BottomRight, QWidget* parent = nullptr);

protected:
	void paintEvent(QPaintEvent* event) override;
	bool eventFilter(QObject* watched, QEvent* event) override;
	const QScopedPointer<CUVMessageBarPrivate> d_ptr{ nullptr };
};
