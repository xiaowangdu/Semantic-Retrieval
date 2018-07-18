#include "ShrinkImageView.hpp"
#include <QDebug>
#include <QResizeEvent>
#include <QHeaderView>

ShrinkImageView::ShrinkImageView(QWidget * parent) 
	: QTableWidget(parent) 
{
	horizontalHeader()->setVisible(false);
	verticalHeader()->setVisible(false);

	setSelectionMode(QAbstractItemView::NoSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
}

ShrinkImageView::~ShrinkImageView() 
{
	
}

void ShrinkImageView::resizeEvent(QResizeEvent *event)
{
	horizontalHeader()->setDefaultSectionSize((event->size().width())/columnCount());
	verticalHeader()->setDefaultSectionSize((event->size().height())/rowCount());
}