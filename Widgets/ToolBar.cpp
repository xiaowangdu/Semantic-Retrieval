#include "ToolBar.hpp"
#include <QLayout>

ToolBar::ToolBar(const QString &title, QWidget * parent) : QToolBar(title, parent) {
	QLayout *ly = layout();
	QMargins m(0, 0, 0, 0);
	ly->setSpacing(0);
	ly->setContentsMargins(m);
	setContentsMargins(m);
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
}

ToolBar::~ToolBar() {
	
}
