/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMutexLocker>
#include "dynmodel.h"
#include "fieldscene.h"
#include "cellitem.h"
#include "config.h"
#include "commands.h"

//-------------------------------------------------------------------------------------------------
FieldScene::FieldScene(QObject *parent)
	:QGraphicsScene(parent)
	, m_model(nullptr)
{
	m_model = new TSModel(Config::instance()->columns(), Config::instance()->rows());
	Config::instance()->game()->setModel(m_model);

	connect(Config::instance()->game(), SIGNAL(ModelUpdated()), this, SLOT(OnModelUpdated()));

	initializeCells();
}

//-------------------------------------------------------------------------------------------------
FieldScene::FieldScene(const QRectF &sceneRect, QObject *parent)
	:QGraphicsScene(sceneRect, parent)
	, m_model(nullptr)
{
	m_model = new TSModel(Config::instance()->columns(), Config::instance()->rows());
	Config::instance()->game()->setModel(m_model);

	connect(Config::instance()->game(), SIGNAL(ModelUpdated()), this, SLOT(OnModelUpdated()));

	initializeCells();
}

//-------------------------------------------------------------------------------------------------
FieldScene::FieldScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
	:QGraphicsScene(x, y, width, height, parent)
	, m_model(nullptr)
{
	m_model = new TSModel(Config::instance()->columns(), Config::instance()->rows());
	Config::instance()->game()->setModel(m_model);

	connect(Config::instance()->game(), SIGNAL(ModelUpdated()), this, SLOT(OnModelUpdated()));

	initializeCells();
}

//-------------------------------------------------------------------------------------------------
FieldScene::~FieldScene()
{
	if (m_model)
		delete m_model;
}

//-------------------------------------------------------------------------------------------------
void FieldScene::fromModel(TSModel& model)
{
	for (auto i = 0; i < Config::instance()->columns(); i++)
	{
		for (auto j = 0; j < Config::instance()->rows(); j++)
		{
			if (model.item(i, j) == 1)
				addCell(i, j);
			else
				removeCell(i, j);
		}
	}
}

//-------------------------------------------------------------------------------------------------
bool FieldScene::addCell(int i, int j)
{
	const int Index = Config::instance()->index(i, j);
	m_cells[Index]->setEnabled();
	return true;
}

//-------------------------------------------------------------------------------------------------
bool FieldScene::removeCell(int i, int j)
{
	QGraphicsItem* pRemoveItem = nullptr;
	for(CellItem* pCell : m_cells)
	{
		if (pCell->i() == i)
		{
			if (pCell->j() == j)
			{
				pCell->setEnabled(false);
				return true;
			}
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
void FieldScene::clearCells()
{
	for (CellItem* c : m_cells)
	{
		if (c->isEnabled())
		{
			QMutexLocker lock(m_model->mutex());
			m_model->item(c->i(), c->j()) = 0;
			c->setEnabled(false);
		}
	}
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
			int i = 0, j = 0;
			Config::instance()->scenePosToIndex(pos, i, j);

			const int Index = Config::instance()->index(i, j);

			if (m_cells[Index]->isEnabled())
			{
				std::auto_ptr<ICommand> pRemove(ICommand::createCellCmd(ICommand::RemoveCell, i, j));
				dynamic_cast<RemoveCellCommand*>(pRemove.get())->setScene(this);
				dynamic_cast<RemoveCellCommand*>(pRemove.get())->setModel(this->model());
				pRemove->exec();
			}
			else
			{
				std::auto_ptr<ICommand> pAdd(ICommand::createCellCmd(ICommand::AddCell, i, j));
				dynamic_cast<AddCellCommand*>(pAdd.get())->setScene(this);
				dynamic_cast<AddCellCommand*>(pAdd.get())->setModel(this->model());
				pAdd->exec();
			}

			/*QList<QGraphicsItem*> _items = items(pos, Qt::ContainsItemShape);
			QGraphicsItem* pSelectedItem = nullptr;

			for (QGraphicsItem* pItem : _items)
			{
				if (dynamic_cast<CellItem*>(pItem) != nullptr)
				{
					pSelectedItem = pItem;
					continue;
				}
			}

			if (pSelectedItem)
			{
				//Founded item
				std::auto_ptr<ICommand> pRemove(ICommand::createCellCmd(ICommand::RemoveCell, i, j));
				dynamic_cast<RemoveCellCommand*>(pRemove.get())->setScene(this);
				dynamic_cast<RemoveCellCommand*>(pRemove.get())->setModel(this->model());
				pRemove->exec();
			}
			else
			{
				//Not founded item
				std::auto_ptr<ICommand> pAdd(ICommand::createCellCmd(ICommand::AddCell, i, j));
				dynamic_cast<AddCellCommand*>(pAdd.get())->setScene(this);
				dynamic_cast<AddCellCommand*>(pAdd.get())->setModel(this->model());
				pAdd->exec();
			}*/
		}
		QGraphicsScene::mousePressEvent(event);
	}
}

//-------------------------------------------------------------------------------------------------
void FieldScene::OnModelUpdated()
{
	QMutexLocker lock(m_model->mutex());
	fromModel(*m_model);
}

//-------------------------------------------------------------------------------------------------
bool FieldScene::initializeCells()
{
	try
	{
		for (auto i = 0; i < Config::instance()->columns(); i++)
		{
			for (auto j = 0; j < Config::instance()->rows(); j++)
			{
				CellItem* pC = new CellItem(i, j);
				pC->setBackgroundColor(Config::instance()->areaBackgroundColor());
				pC->setBorderColor(Config::instance()->borderColor());
				m_cells.push_back(pC);
				addItem(pC);
			}
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
