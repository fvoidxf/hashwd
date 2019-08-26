/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#ifndef __FIELDVIEW_H__
#define __FIELDVIEW_H__

#include <QGraphicsView>

class QGraphicsScene;
class Workarea;

//=================================================================================================
class FieldView : public QGraphicsView
{
    Q_OBJECT

public:
    FieldView(QWidget *parent = nullptr);
    FieldView(QGraphicsScene *scene, QWidget *parent = nullptr);
    virtual ~FieldView();

    void setWorkarea(Workarea *_area){area = _area;}

protected:
    Workarea* area;
    virtual void resizeEvent(QResizeEvent *event)override;
};

//=================================================================================================

#endif // __FIELDVIEW_H__
