#include "cell.h"

Cell::Cell(int width, int height)
    :w(width)
    ,h(height)
{

}

Cell::~Cell()
{

}

int Cell::width() const
{
    return w;
}

int Cell::height() const
{
    return h;
}
