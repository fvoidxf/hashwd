/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/

#include "game.h"
#include "dynmodel.h"
#include "config.h"
#include "fieldscene.h"

//-------------------------------------------------------------------------------------------------
Game::Game(QObject *parent)
	:QThread(parent)
	,m_model(nullptr)
	,m_running(false)
{

}

//-------------------------------------------------------------------------------------------------
Game::~Game()
{

}

//-------------------------------------------------------------------------------------------------
bool Game::step(TSModel *model)
{
	for (auto i = 0; i < Config::instance()->columns(); i++)
	{
		for (auto j = 0; j < Config::instance()->rows(); j++)
		{
			int alive_cnt = 0;
			if (i && j && model->item(i - 1, j - 1))
				++alive_cnt;
			if (j && model->item(i, j - 1))
				++alive_cnt;
			if ( (i < Config::instance()->columns() - 1) &&  j && model->item(i + 1, j - 1))
				++alive_cnt;

			if (i && model->item(i - 1, j))
				++alive_cnt;
			if ((i < Config::instance()->columns() - 1) && model->item(i + 1, j))
				++alive_cnt;

			if ( (j < Config::instance()->rows() - 1) && i && model->item(i - 1, j + 1))
				++alive_cnt;
			if ((j < Config::instance()->rows() - 1) && model->item(i, j + 1))
				++alive_cnt;
			if ((j < Config::instance()->rows() - 1) && (i < Config::instance()->columns() - 1) && model->item(i + 1, j + 1))
				++alive_cnt;

			if (model->item(i, j) == 0)
			{
				//dead cell
				if (alive_cnt == 3)
					model->item(i, j) = 1;
				continue;
			}
			else
			{
				//live cell
				if ((alive_cnt == 2) || (alive_cnt == 3))
					continue;
				model->item(i, j) = 0;
			}
		}
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
void Game::run()
{
	m_running = true;

	while (m_running)
	{
		QThread::msleep(40);
		QMutexLocker lock(m_model->mutex());
		step(m_model);
		CompCont::incIndex();
		Config::instance()->sticker()->add(m_model);
		emit ModelUpdated();
	}
}

//-------------------------------------------------------------------------------------------------
