/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#ifndef __FIELDSCENE_H__
#define __FIELDSCENE_H__

#include <QGraphicsScene>

class Workarea;
class CellItem;
class DynModel;
class FieldThread;

//=================================================================================================
class FieldScene : public QGraphicsScene
{
    Q_OBJECT

public:
    FieldScene(QObject *parent = nullptr);
	FieldScene(const QRectF &sceneRect, QObject *parent = nullptr);
	FieldScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
	virtual ~FieldScene();

protected:
	Workarea *m_area;
	QVector<CellItem*> m_cells;
	FieldThread *m_thread;

	QColor m_cellColor;
	QColor m_borderColor;

public:
	virtual void fromModel(DynModel& model);
	virtual bool addCell(int i, int j);
	virtual void clearCells();

	virtual bool init();
	virtual void addArea(Workarea *area);

	void setDataThread(FieldThread* thread);

protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)override;

	void _internalRemoveCell(QGraphicsItem* pCell);
};

//=================================================================================================

#endif // __FIELDSCENE_H__
