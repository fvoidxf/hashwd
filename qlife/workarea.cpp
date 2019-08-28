/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "workarea.h"

//-------------------------------------------------------------------------------------------------
Workarea::Workarea(const QRectF& areasize, int N, int M, QGraphicsItem *parent)
    :QGraphicsItem (parent)
    ,m_rect(areasize)
    ,m_n(N)
    ,m_m(M)
{

}

//-------------------------------------------------------------------------------------------------
Workarea::~Workarea()
{

}

//-------------------------------------------------------------------------------------------------
QRectF Workarea::boundingRect() const
{
    return m_rect;
}

//-------------------------------------------------------------------------------------------------
void Workarea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setBrush( QBrush(m_bgColor) );
	painter->setPen( m_brdColor );

    painter->drawRect(m_rect);

    for(auto i = 0; i < m_n; i++)
    {
        qreal k = m_rect.width()/m_n;
        qreal x = i*k;
        QLineF line(x, 0, x, m_rect.height());
        painter->drawLine(line);
    }
    for(auto j = 0; j < m_m; j++)
    {
        qreal k = m_rect.height()/m_m;
        qreal y = j*k;
        QLineF line(0, y, m_rect.width(), y);
        painter->drawLine(line);
    }
}

//-------------------------------------------------------------------------------------------------
void Workarea::setSize(qreal w, qreal h)
{
    m_rect.setWidth(w);
    m_rect.setHeight(h);
}

//-------------------------------------------------------------------------------------------------
void Workarea::setBackgroundColor(QColor color)
{
	m_bgColor = color;
}

//-------------------------------------------------------------------------------------------------
void Workarea::setBorderColor(QColor color)
{
	m_brdColor = color;
}

//-------------------------------------------------------------------------------------------------
