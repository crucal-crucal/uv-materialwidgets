#pragma once

#include <QPainter>
#include <QtGlobal>

class CUVSwitchButton;

class CUVSwitchButtonPrivate final : public QObject {
	Q_OBJECT

	Q_DISABLE_COPY(CUVSwitchButtonPrivate)
	Q_DECLARE_PUBLIC(CUVSwitchButton)

public:
	explicit CUVSwitchButtonPrivate(CUVSwitchButton* q);
	~CUVSwitchButtonPrivate() override;

public slots:
	void updateValue();

public:
	void init();
	void drawBackGround(QPainter* painter) const;
	void drawSlider(QPainter* painter) const;
	void drawText(QPainter* painter) const;
	[[nodiscard]] int getTextWidth() const;
	[[nodiscard]] QRect getBackgroundRect() const;
	[[nodiscard]] QPainterPath getBackgroundPath(const QRect& rect) const;
	[[nodiscard]] QRect getSliderRect() const;
	[[nodiscard]] QRect getTextRect(const CUVSwitchButton::TextPosition& position, bool isChecked) const;
	[[nodiscard]] std::pair<int, int> getEndXandStep(const CUVSwitchButton::TextPosition& position) const;

	CUVSwitchButton* const q_ptr{ nullptr };

	int spaceSlider{}; // �������߽����
	int radius{};      // Բ�ǽǶ�
	int spaceText{};   // ���־��뻬��ľ���

	bool checked{};    // �Ƿ�ѡ��
	bool showText{};   // �Ƿ���ʾ����
	bool animation{};  // �Ƿ�ʹ�ö���

	QColor bgColorOn{};      // ��ʱ��ı���ɫ
	QColor bgColorOff{};     // �ر�ʱ��ı���ɫ
	QColor sliderColorOn{};  // ��ʱ�򻬿���ɫ
	QColor sliderColorOff{}; // �ر�ʱ�򻬿���ɫ
	QColor textColorOn{};    // ��ʱ��������ɫ
	QColor textColorOff{};   // �ر�ʱ��������ɫ

	QString textOn{};  // ��ʱ�������
	QString textOff{}; // �ر�ʱ�������
	int fontSize{};    // ���ִ�С
	bool fontBold{};   // �����Ƿ�Ӵ�

	QTimer* timer{ nullptr }; // ������ʱ��
	int step{};               // ��������
	int startX{};             // ���鿪ʼX������
	int endX{};               // �������X������

	CUVSwitchButton::TextPosition textPostion{}; // ����λ��
};
