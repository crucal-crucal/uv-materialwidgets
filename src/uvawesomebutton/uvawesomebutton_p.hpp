#pragma once

#include <QColor>
#include <QObject>

#include "uvmessagebar/uvdef.hpp"

using namespace UVIconType;

class CUVAwesomeButton;

class CUVAwesomeButtonPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVAwesomeButtonPrivate)
	Q_DECLARE_PUBLIC(CUVAwesomeButton)

public:
	explicit CUVAwesomeButtonPrivate(CUVAwesomeButton* q, QObject* parent = nullptr);
	~CUVAwesomeButtonPrivate() override;

	void init();

public:
	CUVAwesomeButton* const q_ptr{ nullptr };

	int borderRaius{ 0 };
	CUVIconType iconType{};
	QColor lightHoverColor{};
	QColor darkHoverColor{};
	QColor lightIconColor{};
	QColor darkIconColor{};
	bool isSelected{};
};
