#ifndef CELL_H
#define CELL_H

class Cell
{
protected:
    int w,h;

public:
    Cell(int width, int height);
    virtual ~Cell();

    int width()const;
    int height()const;
};

#endif // CELL_H
