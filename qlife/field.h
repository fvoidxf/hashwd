/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/

#ifndef FIELD_H
#define FIELD_H

#include <QColor>
#include <QList>

class QGraphicsScene;
class QGraphicsItem;
class QSize;
class Cell;

//=================================================================================================
class Field
{
protected:
    int w,h;
    QGraphicsScene *scene;
    QGraphicsItem *main;
    QColor bgcolor;
    QColor cellcolor;
    QColor bordercolor;
    QList<QGraphicsItem*> borders;
    QList<Cell*> cells;

public:
    Field(int width, int height);
    virtual ~Field();

    void setScene(QGraphicsScene* s);

    QSize fieldSize()const;
    QSize cellSize()const;

    virtual bool addCell(int i, int j);
    virtual bool isAlive(int i, int j)const;
    virtual bool removeCell(int i, int j);

    void setBackgroundColor(QColor color);
    void setCellColor(QColor color);
    void setBorderColor(QColor color);

    virtual bool update();
    virtual bool run();

protected:
    virtual bool createBorders();
};

//=================================================================================================

#endif // FIELD_H
