#pragma once
#include <QWidget>

class TrainWidget : public QWidget {
	Q_OBJECT

public:
	TrainWidget(QWidget * parent = Q_NULLPTR);
	~TrainWidget();

	virtual void closeEvent(QCloseEvent *ev);

signals:
	void closeWidget();
};
