#include "TrainWidget.hpp"

TrainWidget::TrainWidget(QWidget * parent) : QWidget(parent) {
	
}

TrainWidget::~TrainWidget() {
	
}

void TrainWidget::closeEvent(QCloseEvent *ev)
{
	QWidget::closeEvent(ev);
}
