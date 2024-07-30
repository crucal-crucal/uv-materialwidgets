#pragma once

#include <QWidget>

#ifdef CUVSTACKWIDGET_LIB
#define CUVSTACKWIDGET_EXPORT Q_DECL_EXPORT
#else
#define CUVSTACKWIDGET_EXPORT Q_DECL_IMPORT
#endif

class CUVStackWidgetPrivate;

class CUVSTACKWIDGET_EXPORT CUVStackWidget final : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(CUVStackWidget)
	Q_DECLARE_PRIVATE(CUVStackWidget)

public:
	enum MoveDirection {
		Horizontal = 0, // 横向移动
		Vertical   = 1  // 纵向移动
	};

	explicit CUVStackWidget(QWidget* parent = nullptr);
	~CUVStackWidget() override;

	[[nodiscard]] int count() const;
	[[nodiscard]] int currentIndex() const;
	[[nodiscard]] int indexOf(QWidget* widget) const;
	[[nodiscard]] QWidget* currentWidget() const;
	[[nodiscard]] QWidget* widget(int index) const;

	int addWidget(QWidget* widget);
	int insertWidget(int index, QWidget* widget);

	void removeWidget(QWidget* widget);
	void removeWidget(int index);
	void setDuration(int duration);
	void setMoveDirection(const MoveDirection& move_direction);

public slots:
	void setCurrentIndex(int index);
	void setCurrentWidget(QWidget* widget);

signals:
	void currentChanged(int index);
	void widgetRemoved(int index);

protected:
	void resizeEvent(QResizeEvent* event) override;

	QScopedPointer<CUVStackWidgetPrivate> d_ptr{ nullptr };
};
