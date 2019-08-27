/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#ifndef __WORKAREA_H__
#define __WORKAREA_H__

#include <QGraphicsItem>

//=================================================================================================
class Workarea : public QGraphicsItem
{
public:
    Workarea(const QRectF& areasize, int N, int M, QGraphicsItem *parent = nullptr);
    virtual ~Workarea();

    virtual QRectF boundingRect()const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)override;

    virtual void setSize(qreal w, qreal h);

	int width()const { return m_n; }
	int height()const { return m_m; }

protected:
    QRectF m_rect;
    const int m_n;
    const int m_m;
};

//=================================================================================================

#endif // __WORKAREA_H__
