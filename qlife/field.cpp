#include <QGraphicsScene>
#include <QLine>
#include "field.h"

#define M_H 238
#define M_W 380

#define W_STEP 20
#define H_STEP 12

Field::Field(int width, int height)
    :w(width)
    ,h(height)
    ,scene(nullptr)
{

}

Field::~Field()
{

}

bool Field::draw()
{
    if(!scene)
        return false;
    for(auto i = 0; i < w; i++)
    {
        QSharedPointer<QLine> pLine(new QLine(i*W_STEP, 0, i*W_STEP, M_H));
        scene->addLine(*pLine);
    }
    for(auto i = 0; i < h; i++)
    {
        QSharedPointer<QLine> pLine(new QLine(0, i*H_STEP, M_W, i*H_STEP));
        scene->addLine(*pLine);
    }
    return true;
}

void Field::setScene(QGraphicsScene *s)
{
    scene = s;
}

QSize Field::cellSize() const
{
    return QSize(W_STEP, H_STEP);
}

bool Field::addCell(int i, int j)
{
    QRectF rect(i*cellSize().width(),j*cellSize().height(),cellSize().width(), cellSize().height());
    QBrush brush(Qt::blue, Qt::BrushStyle::SolidPattern);
    QPen pen(Qt::red);
    scene->addRect(rect,pen, brush);
    return true;
}
