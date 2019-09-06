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
	for (auto i = 1; i < Config::instance()->columns() - 1; i++)
	{
		for (auto j = 1; j < Config::instance()->rows() - 1; j++)
		{
			int alive_cnt = 0;
			if (model->item(i - 1, j - 1))
				++alive_cnt;
			if (model->item(i, j - 1))
				++alive_cnt;
			if (model->item(i + 1, j - 1))
				++alive_cnt;

			if (model->item(i - 1, j))
				++alive_cnt;
			if (model->item(i + 1, j))
				++alive_cnt;

			if (model->item(i - 1, j + 1))
				++alive_cnt;
			if (model->item(i, j + 1))
				++alive_cnt;
			if (model->item(i + 1, j + 1))
				++alive_cnt;

			if (model->item(i, j) == 0)
			{
				if (alive_cnt == 3)
				{
					model->item(i, j) = 1;
					continue;
				}
			}

			if (model->item(i, j) == 1)
			{
				if ((alive_cnt == 2) || (alive_cnt == 3))
				{
					model->item(i, j) = 1;
					continue;
				}
			}

			model->item(i, j) = 0;
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
		QThread::msleep(300);
		QMutexLocker lock(m_model->mutex());
		step(m_model);
		emit ModelUpdated();
	}
}

//-------------------------------------------------------------------------------------------------
