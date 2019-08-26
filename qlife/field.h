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

class DynModel;

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

    virtual void fromModel(DynModel& model);
    virtual bool addCell(int i, int j);
    virtual void clearCells();

    void setBackgroundColor(QColor color);
    void setCellColor(QColor color);
    void setBorderColor(QColor color);

    virtual bool update();

protected:
    virtual bool createBorders();
};

//=================================================================================================

#endif // FIELD_H