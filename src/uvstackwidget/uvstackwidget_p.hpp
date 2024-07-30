#pragma once

#include <QObject>

class CUVStackWidget;
class QPropertyAnimation;

class CUVStackWidgetPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVStackWidgetPrivate)
	Q_DECLARE_PUBLIC(CUVStackWidget)

public:
	explicit CUVStackWidgetPrivate(CUVStackWidget* q, QObject* parent = nullptr);
	~CUVStackWidgetPrivate() override;

	CUVStackWidget* const q_ptr{ nullptr };

private slots:
	void onValueChanged(const QVariant& value);

private:
	int m_offset{};
	int m_curIndex{};
	int m_lastIndex{};
	int m_duration{};
	CUVStackWidget::MoveDirection m_moveDirection{};
	QPropertyAnimation* m_pMoveAnimation{ nullptr };
	QList<QWidget*> m_WidgetList{};

	void moveAnimationStart();
	void setWidgetsVisible() const;
};
