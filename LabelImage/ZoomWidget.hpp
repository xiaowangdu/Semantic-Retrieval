#pragma once
#include <QSpinBox>

class ZoomWidget : public QSpinBox {
	Q_OBJECT

public:
	ZoomWidget(int value = 100, QWidget * parent = Q_NULLPTR);
	~ZoomWidget();

	QSize minimumSizeHint() const;
private:
	
};
