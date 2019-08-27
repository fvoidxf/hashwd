/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#ifndef __CELLITEM_H__
#define __CELLITEM_H__

#include <QGraphicsItem>

//=================================================================================================
class CellItem : public QGraphicsItem
{
public:
    CellItem(int i, int j, QGraphicsItem *parent = nullptr);
    virtual ~CellItem();

    virtual QRectF boundingRect()const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)override;

protected:
    int m_i;
    int m_j;
};

//=================================================================================================

#endif // __CELLITEM_H__