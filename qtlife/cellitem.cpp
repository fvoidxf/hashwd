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
	:QGraphicsItem(parent)
	, m_i(i)
	, m_j(j)
	, m_enabled(false)
{

}

//-------------------------------------------------------------------------------------------------
CellItem::~CellItem()
{

}

//-------------------------------------------------------------------------------------------------
QRectF CellItem::boundingRect()const
{
	return QRectF(Config::instance()->cellWidth()*m_i,
		Config::instance()->cellHeight()*m_j,
		Config::instance()->cellWidth(),
		Config::instance()->cellHeight());
}

//-------------------------------------------------------------------------------------------------
void CellItem::paint(QPainter *painter,
	const QStyleOptionGraphicsItem *option,
	QWidget *widget)
{
	QRect rc(m_i*Config::instance()->cellWidth(), m_j*Config::instance()->cellHeight(),
		Config::instance()->cellWidth(), Config::instance()->cellHeight());

	painter->setBrush(QBrush(m_bgColor));
	painter->setPen(m_brdColor);

	painter->drawRect(rc);
}

//-------------------------------------------------------------------------------------------------
void CellItem::setBackgroundColor(QColor color)
{
	m_bgColor = color;
	update();
}

//-------------------------------------------------------------------------------------------------
void CellItem::setBorderColor(QColor color)
{
	m_brdColor = color;
	update();
}

//-------------------------------------------------------------------------------------------------
void CellItem::setEnabled(bool bEnabled)
{
	m_enabled = bEnabled;
	if (bEnabled)
		setBackgroundColor(Config::instance()->cellColor());
	else
		setBackgroundColor(Config::instance()->areaBackgroundColor());
}

//-------------------------------------------------------------------------------------------------
