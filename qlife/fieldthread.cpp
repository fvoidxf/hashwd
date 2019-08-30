/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/
#include "fieldthread.h"
#include "config.h"

//-------------------------------------------------------------------------------------------------
FieldThread::FieldThread(QObject *parent)
    :QThread(parent)
    ,m_model( nullptr )
    ,m_isRunning(true)
	,m_stepCount(GetInfiniteSteps())
	,m_mutex(nullptr)
{

}

//-------------------------------------------------------------------------------------------------
FieldThread::~FieldThread()
{

}

//-------------------------------------------------------------------------------------------------
void FieldThread::randomModel(int start_i, int start_j, int i_cnt, int j_cnt)
{
	if (!m_model)
		return;
	for (auto i = start_i; i < (start_i + i_cnt); i++)
	{
		for (auto j = start_j; j < (start_j + j_cnt); j++)
		{
			m_model->item(i, j) = randomBool();
		}
	}
}

//-------------------------------------------------------------------------------------------------
void FieldThread::setStopFlag()
{
    m_isRunning = false;
}

//-------------------------------------------------------------------------------------------------
unsigned char FieldThread::randomBool()
{
    return rand() % 2;
}

//-------------------------------------------------------------------------------------------------
void FieldThread::run()
{
	if (!m_mutex)
		return;

    while(m_isRunning && m_stepCount)
    {
        emit clearCells();
		QMutexLocker lock(m_mutex);
        modelStep();
		lock.unlock();
		emit dataReady();
        QThread::msleep( Config::instance()->threadTimeoutMs() );
		if (m_stepCount != GetInfiniteSteps())
			--m_stepCount;
    }
}

//-------------------------------------------------------------------------------------------------
void FieldThread::modelStep()
{
	if (!m_model)
		return;

    for(auto i = 1; i < Config::instance()->columns() - 1; i++)
    {
        for(auto j = 1; j < Config::instance()->rows() - 1; j++)
        {
            int alive_cnt = 0;
            if(m_model->item(i-1, j-1))
                ++alive_cnt;
            if(m_model->item(i, j-1))
                ++alive_cnt;
            if(m_model->item(i+1,j-1))
                ++alive_cnt;

            if(m_model->item(i-1, j))
                ++alive_cnt;
            if(m_model->item(i+1, j))
                ++alive_cnt;

            if(m_model->item(i-1, j+1))
                ++alive_cnt;
            if(m_model->item(i, j+1))
                ++alive_cnt;
            if(m_model->item(i+1, j+1))
                ++alive_cnt;

            if(m_model->item(i,j)==0)
            {
                if(alive_cnt == 3)
                {
					m_model->item(i,j) = 1;
                    continue;
                }
            }

            if(m_model->item(i,j)==1)
            {
                if((alive_cnt == 2) || (alive_cnt==3))
                {
					m_model->item(i,j) = 1;
                    continue;
                }
            }

			m_model->item(i,j) = 0;
        }
    }
}

//-------------------------------------------------------------------------------------------------
void FieldThread::clearModel()
{
	if (!m_mutex)
		return;
	QMutexLocker lock(m_mutex);
	if (!m_model)
		return;
	m_model->clear();
}

//-------------------------------------------------------------------------------------------------
