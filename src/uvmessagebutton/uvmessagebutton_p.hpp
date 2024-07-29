#pragma once

#include "uvmessagebar/uvdef.hpp"

class CUVMessageButton;

class CUVMessageButtonPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMessageButtonPrivate)
	Q_DECLARE_PUBLIC(CUVMessageButton)

public:
	explicit CUVMessageButtonPrivate(CUVMessageButton* q, QObject* parent = nullptr);
	~CUVMessageButtonPrivate() override;

	void init();

	CUVMessageButton* const q_ptr{ nullptr };
	int borderRadius{};
	QString title{};
	QString text{};
	int displayMsec{};
	UVMessageBarType::MessageMode messageMode{};
	UVMessageBarType::PositionPolicy policy{};

	int shadowBorderWidth{};
	int penBorderWidth{};
};
