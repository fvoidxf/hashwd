/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#include <QResizeEvent>
#include "workarea.h"
#include "fieldview.h"

//-------------------------------------------------------------------------------------------------
FieldView::FieldView(QWidget *parent)
	:QGraphicsView(parent)
{

}

//-------------------------------------------------------------------------------------------------
FieldView::FieldView(QGraphicsScene *scene, QWidget *parent)
	:QGraphicsView(scene, parent)
{

}

//-------------------------------------------------------------------------------------------------
FieldView::~FieldView()
{

}

//-------------------------------------------------------------------------------------------------
void FieldView::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	if (area && event)
	{
		qreal w = event->size().width();
		qreal h = event->size().height();
		//area->setSize(w,h);
	}
}

//-------------------------------------------------------------------------------------------------
