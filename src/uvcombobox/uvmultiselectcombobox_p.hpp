#pragma once

class CUVComboBoxStyle;
class CUVComboBoxView;
class CUVMultiSelectComboBox;

class CUVMultiSelectComboBoxPrivate final : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(CUVMultiSelectComboBoxPrivate)
	Q_DECLARE_PUBLIC(CUVMultiSelectComboBox)
	Q_PROPERTY(qreal pExpandIconRotate MEMBER _pExpandIconRotate NOTIFY pExpandIconRotateChanged)
	Q_PROPERTY(qreal pExpandMarkWidth MEMBER _pExpandMarkWidth NOTIFY pExpandMarkWidthChanged)

public:
	explicit CUVMultiSelectComboBoxPrivate(CUVMultiSelectComboBox* q, QObject* parent = nullptr);
	~CUVMultiSelectComboBoxPrivate() override;
	Q_SLOT void onItemPressed(const QModelIndex& index);

	void setExpandIconRotate(qreal _expandIconRotate);
	[[nodiscard]] qreal expandIconRotate() const;

	void setExpandMarkWidth(qreal _expandMarkWidth);
	[[nodiscard]] qreal expandMarkWidth() const;

signals:
	void pExpandIconRotateChanged(qreal);
	void pExpandMarkWidthChanged(qreal);

protected:
	CUVMultiSelectComboBox* const q_ptr{ nullptr };

private:
	int _pBorderRadius{};
	qreal _pExpandIconRotate{};
	qreal _pExpandMarkWidth{};

	CUVComboBoxStyle* _comboBoxStyle{ nullptr };
	CUVComboBoxView* _comboBoxView{ nullptr };
	QVector<bool> _itemSelection{};
	bool _isFirstPopup{ false };
	bool _isAllowHidePopup{ false };
	QString _currentText{};
	QStringList _selectedTextList{};

	void _refreshCurrentIndexs();
	void _adjustSelectedVector();
};

inline void CUVMultiSelectComboBoxPrivate::setExpandIconRotate(const qreal _expandIconRotate) {
	_pExpandIconRotate = _expandIconRotate;
	Q_EMIT pExpandIconRotateChanged(_expandIconRotate);
}

inline qreal CUVMultiSelectComboBoxPrivate::expandIconRotate() const {
	return _pExpandIconRotate;
}

inline void CUVMultiSelectComboBoxPrivate::setExpandMarkWidth(const qreal _expandMarkWidth) {
	_pExpandMarkWidth = _expandMarkWidth;
	Q_EMIT pExpandMarkWidthChanged(_expandMarkWidth);
}

inline qreal CUVMultiSelectComboBoxPrivate::expandMarkWidth() const {
	return _pExpandMarkWidth;
}
