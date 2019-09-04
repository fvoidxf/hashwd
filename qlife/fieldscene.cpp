/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMutexLocker>
#include "dynmodel.h"
#include "workarea.h"
#include "fieldscene.h"
#include "cellitem.h"
#include "config.h"
#include "fieldthread.h"

//-------------------------------------------------------------------------------------------------
FieldScene::FieldScene(QObject *parent)
    :QGraphicsScene (parent)
	,m_area(nullptr)
	,m_thread(nullptr)
{

}

//-------------------------------------------------------------------------------------------------
FieldScene::FieldScene(const QRectF &sceneRect, QObject *parent)
	:QGraphicsScene(sceneRect, parent)
	,m_area(nullptr)
	,m_thread(nullptr)
{

}

//-------------------------------------------------------------------------------------------------
FieldScene::FieldScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
	:QGraphicsScene(x, y, width, height, parent)
	,m_area(nullptr)
	,m_thread(nullptr)
{

}

//-------------------------------------------------------------------------------------------------
FieldScene::~FieldScene()
{

}

//-------------------------------------------------------------------------------------------------
void FieldScene::setThread(FieldThread* thread)
{
	m_thread = thread;
}

//-------------------------------------------------------------------------------------------------
void FieldScene::fromModel(DynModel& model)
{
	for (auto i = 0; i < Config::instance()->columns(); i++)
	{
		for (auto j = 0; j < Config::instance()->rows(); j++)
		{
			if (model.item(i, j) == 1)
				addCell(i, j);
		}
	}
}

//-------------------------------------------------------------------------------------------------
bool FieldScene::addCell(int i, int j)
{
	CellItem *pCell = new CellItem(i, j);
	pCell->setBackgroundColor( Config::instance()->cellColor() );
	pCell->setBorderColor( Config::instance()->borderColor() );
	addItem(pCell);
	if (m_thread)
	{
		QMutexLocker lock(m_thread->getMutex());
		m_thread->getData()->item(i, j) = 1;
	}
	m_cells.push_back(pCell);

	return true;
}

//-------------------------------------------------------------------------------------------------
void FieldScene::clearCells()
{
	/*for (CellItem* c : m_cells)
	{
		if (m_thread)
		{
			QMutexLocker lock(m_thread->getMutex());
			m_thread->getData()->item(c->i(), c->j()) = 0;
		}
		removeItem(c);
		delete c;
	}
	m_cells.clear();*/
}

//-------------------------------------------------------------------------------------------------
bool FieldScene::init()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
void FieldScene::addArea(Workarea *area)
{
	m_area = area;
	addItem(area);
}

//-------------------------------------------------------------------------------------------------
void FieldScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (Config::instance()->currentMode() == Config::GameMode)
		QGraphicsScene::mousePressEvent(event);
	else if (Config::instance()->currentMode() == Config::EditMode)
	{
		if (Qt::LeftButton & event->button())
		{
			QPointF pos = event->scenePos();
			qDebug() << "scene pos: " << pos.x() << " " << pos.y();
			QList<QGraphicsItem*> _items = items(pos, Qt::ContainsItemShape);
			QGraphicsItem* pRM = nullptr;
			for (QGraphicsItem* itm : _items)
			{
				if (dynamic_cast<CellItem*>(itm) != nullptr)
				{
					qDebug() << "founded cell!";
					pRM = itm;
					continue;
				}
			}
			if (pRM)
			{
				removeItem(pRM);
				delete pRM;
			}
			else
			{
				int i = 0;
				int j = 0;
				Config::instance()->scenePosToIndex(pos, i, j);
				addCell(i, j);
			}
			if (_items.empty())
				qDebug() << "No cells founded!";
		}
		QGraphicsScene::mousePressEvent(event);
	}
}

//-------------------------------------------------------------------------------------------------
