/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/

#ifndef __CELL_H__
#define __CELL_H__

class QGraphicsItem;
class Field;

//=================================================================================================
class Cell
{
    friend class Field;
protected:
    int w,h;
    int i,j;
    QGraphicsItem *item;

    void assign(QGraphicsItem* pItem, int _i, int _j);

public:
    Cell(int width, int height);
    virtual ~Cell();

    int width()const;
    int height()const;
};

//=================================================================================================

#endif // __CELL_H__
