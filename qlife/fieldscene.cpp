/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#include "dynmodel.h"
#include "workarea.h"
#include "fieldscene.h"
#include "cellitem.h"
#include "config.h"

//-------------------------------------------------------------------------------------------------
FieldScene::FieldScene(QObject *parent)
    :QGraphicsScene (parent)
	,m_area(nullptr)
{

}

//-------------------------------------------------------------------------------------------------
FieldScene::FieldScene(const QRectF &sceneRect, QObject *parent)
	:QGraphicsScene(sceneRect, parent)
	,m_area(nullptr)
{

}

//-------------------------------------------------------------------------------------------------
FieldScene::FieldScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
	:QGraphicsScene(x, y, width, height, parent)
	,m_area(nullptr)
{

}

//-------------------------------------------------------------------------------------------------
FieldScene::~FieldScene()
{

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
	m_cells.push_back(pCell);

	return true;
}

//-------------------------------------------------------------------------------------------------
void FieldScene::clearCells()
{
	for (CellItem* c : m_cells)
	{
		removeItem(c);
		delete c;
	}
	m_cells.clear();
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
