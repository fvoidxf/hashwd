#ifndef FIELD_H
#define FIELD_H

class QGraphicsScene;
class QSize;

class Field
{
protected:
    int w,h;
    QGraphicsScene *scene;

public:
    Field(int width, int height);
    virtual ~Field();

    virtual bool draw();
    void setScene(QGraphicsScene* s);
    QSize cellSize()const;

    virtual bool addCell(int i, int j);
};

#endif // FIELD_H
