/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#include <QPainter>
#include "cellitem.h"
#include "config.h"

//-------------------------------------------------------------------------------------------------
CellItem::CellItem(int i, int j, QGraphicsItem* parent)
    :QGraphicsItem (parent)
    ,m_i(i)
    ,m_j(j)
{

}

//-------------------------------------------------------------------------------------------------
CellItem::~CellItem()
{

}

//-------------------------------------------------------------------------------------------------
QRectF CellItem::boundingRect()const
{
    return QRectF(0,0, Config::instance()->cellWidth(), Config::instance()->cellHeight() );
}

//-------------------------------------------------------------------------------------------------
void CellItem::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
	QRect rc( m_i*Config::instance()->cellWidth(), m_j*Config::instance()->cellHeight(),
		      Config::instance()->cellWidth(), Config::instance()->cellHeight() );
	painter->drawRect(rc);
}

//-------------------------------------------------------------------------------------------------
