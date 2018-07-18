#include "ZoomWidget.hpp"

ZoomWidget::ZoomWidget(int value, QWidget * parent) : QSpinBox(parent) 
{
	setButtonSymbols(QAbstractSpinBox::NoButtons);
	setRange(1, 500);
	setSuffix(" %");
	setValue(value);
	setToolTip("Zoom Level");
	setStatusTip(toolTip());
	setAlignment(Qt::AlignCenter);
}

ZoomWidget::~ZoomWidget() {
	
}

QSize ZoomWidget::minimumSizeHint() const
{
	int height = QSpinBox::minimumSizeHint().height();
	QFontMetrics fm = QFontMetrics(font());
	int width = fm.width(maximum());
	return QSize(width, height);
}