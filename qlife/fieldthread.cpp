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
    ,model(new DynModel( Config::instance()->columns() , Config::instance()->rows() ))
    ,isRunning(true)
{
    time_t t;
    time(&t);
    srand( t );

    model->allocate();
    model->clear();
    randomModel( Config::instance()->columns() /4, Config::instance()->rows() /2 );
}

//-------------------------------------------------------------------------------------------------
FieldThread::~FieldThread()
{

}

//-------------------------------------------------------------------------------------------------
void FieldThread::randomModel(int N, int M)
{
    int limN = model->N() <= N ? model->N() : N;
    int limM = model->M() <= M ? model->M() : M;

    for(auto i = 0; i < limN; i++)
    {
        for(auto j = 0; j < limM; j++)
        {
            model->item(i,j) = randomBool();
        }
    }
}

//-------------------------------------------------------------------------------------------------
void FieldThread::setStopFlag()
{
    isRunning = false;
}

//-------------------------------------------------------------------------------------------------
unsigned char FieldThread::randomBool()
{
    return rand() % 2;
}

//-------------------------------------------------------------------------------------------------
void FieldThread::run()
{
    while(isRunning)
    {
        emit clearCells();
		QMutexLocker lock(&m_mutex);
        modelStep();
		lock.unlock();
		emit dataReady();
        QThread::msleep( Config::instance()->threadTimeoutMs() );
    }
}

//-------------------------------------------------------------------------------------------------
void FieldThread::modelStep()
{
    for(auto i = 1; i < Config::instance()->columns() - 1; i++)
    {
        for(auto j = 1; j < Config::instance()->rows() - 1; j++)
        {
            int alive_cnt = 0;
            if(model->item(i-1, j-1))
                ++alive_cnt;
            if(model->item(i, j-1))
                ++alive_cnt;
            if(model->item(i+1,j-1))
                ++alive_cnt;

            if(model->item(i-1, j))
                ++alive_cnt;
            if(model->item(i+1, j))
                ++alive_cnt;

            if(model->item(i-1, j+1))
                ++alive_cnt;
            if(model->item(i, j+1))
                ++alive_cnt;
            if(model->item(i+1, j+1))
                ++alive_cnt;

            if(model->item(i,j)==0)
            {
                if(alive_cnt == 3)
                {
                    model->item(i,j) = 1;
                    continue;
                }
            }

            if(model->item(i,j)==1)
            {
                if((alive_cnt == 2) || (alive_cnt==3))
                {
                    model->item(i,j) = 1;
                    continue;
                }
            }

            model->item(i,j) = 0;
        }
    }
}

//-------------------------------------------------------------------------------------------------
void FieldThread::modelInit()
{
    model->item(0,0) = 1;
    model->item(0,1) = 1;
    model->item(0,2) = 1;

    model->item(1,0) = 1;
    model->item(1,2) = 1;
    model->item(1,3) = 1;

    model->item(2,1) = 1;
    model->item(2,2) = 1;
    model->item(3,2) = 1;

    model->item(0,5) = 1;
    model->item(1,5) = 1;
}

//-------------------------------------------------------------------------------------------------
