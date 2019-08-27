/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/

#include <stdexcept>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QLine>
#include "cell.h"
#include "field.h"
#include "dynmodel.h"
#include "fieldscene.h"
#include "workarea.h"
#include "config.h"

//-------------------------------------------------------------------------------------------------
Field::Field(int width, int height)
    :w(width)
    ,h(height)
    ,scene(nullptr)
    ,main(nullptr)
    ,workarea(nullptr)
{

}

//-------------------------------------------------------------------------------------------------
Field::~Field()
{

}

//-------------------------------------------------------------------------------------------------
/*bool Field::createBorders()
{
    if(!scene)
        return false;

    if(borders.isEmpty())
    {
        for(auto i = 0; i < w; i++)
        {
            QLine line(i*W_STEP, 0, i*W_STEP, M_H);
            QGraphicsItem* item = scene->addLine(line, QPen(bordercolor));
            borders.push_back(item);
        }
        for(auto i = 0; i < h; i++)
        {
            QLine line(0, i*H_STEP, M_W, i*H_STEP);
            QGraphicsItem* item = scene->addLine(line,QPen(bordercolor));
            borders.push_back(item);
        }
    }
    return true;
}*/

//-------------------------------------------------------------------------------------------------
void Field::setScene(FieldScene *s)
{
    scene = s;
}

//-------------------------------------------------------------------------------------------------
QSize Field::cellSize() const
{
    return QSize( Config::instance()->cellWidth() , Config::instance()->cellHeight() );
}

//-------------------------------------------------------------------------------------------------
QSize Field::fieldSize() const
{
    return QSize( Config::instance()->fieldWidth() , Config::instance()->fieldHeight() );
}

//-------------------------------------------------------------------------------------------------
bool Field::addCell(int i, int j)
{
    if(!scene)
        return false;
    QRectF rect(i*cellSize().width(),j*cellSize().height(),cellSize().width(), cellSize().height());
    QBrush brush(cellcolor, Qt::BrushStyle::SolidPattern);
    QPen pen(bordercolor);

    Cell *cell = new Cell(cellSize().width(), cellSize().height());

    QGraphicsItem* pGrItem = scene->addRect(rect,pen, brush);
    cell->assign(pGrItem,i,j);
    cells.push_back(cell);
    return true;
}

//-------------------------------------------------------------------------------------------------
void Field::setBackgroundColor(QColor color)
{
    bgcolor = color;
}

//-------------------------------------------------------------------------------------------------
void Field::setCellColor(QColor color)
{
    cellcolor = color;
}

//-------------------------------------------------------------------------------------------------
void Field::setBorderColor(QColor color)
{
    bordercolor = color;
}

//-------------------------------------------------------------------------------------------------
bool Field::update()
{
    if(!scene)
        return false;
    /*if(!main)
    {
        QRectF rc(0, 0, fieldSize().width(), fieldSize().height());
        QBrush brush(bgcolor);
        QPen pen(bordercolor);
        main = reinterpret_cast<QGraphicsItem*>( scene->addRect(rc, pen, brush) );
    }
    else
    {
        QGraphicsRectItem* grRect = dynamic_cast<QGraphicsRectItem*>(main);
        QPen pen(bordercolor);
        grRect->setPen(pen);
        QBrush brush(bgcolor);
        grRect->setBrush(brush);
    }*/
    //if(borders.isEmpty())
    //    createBorders();
    //else
    //{
    //    for(QGraphicsItem* item : borders)
    //    {
    //        QGraphicsLineItem* lineItem = dynamic_cast<QGraphicsLineItem*>(item);
    //       lineItem->setPen(QPen(bordercolor));
    //    }
    //}
}

//-------------------------------------------------------------------------------------------------
void Field::clearCells()
{
    for(Cell* c: cells){
        scene->removeItem(c->item);
        delete c;
    }
    cells.clear();
}

//-------------------------------------------------------------------------------------------------
void Field::fromModel(DynModel &model)
{
    for(auto i = 0; i < w; i++)
    {
        for(auto j = 0; j < h; j++)
        {
            if(model(i,j) == 1)
                addCell(i,j);
        }
    }
}

//-------------------------------------------------------------------------------------------------
bool Field::init()
{
    workarea = new Workarea(QRectF(0,0, Config::instance()->fieldWidth() , Config::instance()->fieldHeight() ), Config::instance()->columns(), Config::instance()->rows() );
    scene->addItem(workarea);
    return true;
}

//-------------------------------------------------------------------------------------------------
