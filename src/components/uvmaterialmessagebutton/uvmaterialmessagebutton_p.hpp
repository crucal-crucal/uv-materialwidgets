#pragma once

#include "uvmaterialmessagebar/uvdef.hpp"

class CUVMaterialMessageButton;

class CUVMaterialMessageButtonPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMaterialMessageButtonPrivate)
	Q_DECLARE_PUBLIC(CUVMaterialMessageButton)

public:
	explicit CUVMaterialMessageButtonPrivate(CUVMaterialMessageButton* q, QObject* parent = nullptr);
	~CUVMaterialMessageButtonPrivate() override;

	void init();

	CUVMaterialMessageButton* const q_ptr{ nullptr };
	int borderRadius{};
	QString title{};
	QString text{};
	int displayMsec{};
	UVMessageBarType::MessageMode messageMode{};
	UVMessageBarType::PositionPolicy policy{};

	int shadowBorderWidth{};
	int penBorderWidth{};
};
