/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
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
class FieldScene;
class Workarea;

//=================================================================================================
class Field
{
protected:
    int w,h;
    FieldScene *scene;
    QGraphicsItem *main;
    QColor bgcolor;
    QColor cellcolor;
    QColor bordercolor;
    Workarea* workarea;
    //QList<QGraphicsItem*> borders;
    QList<Cell*> cells;

public:
    Field(int width, int height);
    virtual ~Field();

    void setScene(FieldScene* s);

    QSize fieldSize()const;
    QSize cellSize()const;

    virtual void fromModel(DynModel& model);
    virtual bool addCell(int i, int j);
    virtual void clearCells();

    void setBackgroundColor(QColor color);
    void setCellColor(QColor color);
    void setBorderColor(QColor color);

    virtual bool update();
    virtual bool init();

    Workarea* getWorkarea(){return workarea;}

	int width()const { return w; }
	int height()const { return h; }

protected:
    //virtual bool createBorders();
};

//=================================================================================================

#endif // FIELD_H
