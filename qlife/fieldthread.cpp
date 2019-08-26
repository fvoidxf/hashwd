/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/
#include "fieldthread.h"

#ifndef FIELD_N
    #define FIELD_N 20
#endif

#ifndef FIELD_M
    #define FIELD_M 20
#endif

#ifndef THREAD_TM
    #define THREAD_TM 260
#endif

//-------------------------------------------------------------------------------------------------
FieldThread::FieldThread(QSharedPointer<Field> pField, QObject *parent)
    :QThread(parent)
    ,field(pField)
    ,model(new DynModel(FIELD_N,FIELD_M))
{
    model->allocate();
    model->clear();
    modelInit();
}

//-------------------------------------------------------------------------------------------------
FieldThread::~FieldThread()
{

}

//-------------------------------------------------------------------------------------------------
void FieldThread::run()
{
    while(true)
    {
        emit clearCells();
        modelStep();
        for(auto i = 0; i < FIELD_N; i++)
        {
            for(auto j = 0; j < FIELD_M; j++)
            {
                if(model->item(i,j) == 1)
                    emit addCell(i,j);
            }
        }
        QThread::msleep(THREAD_TM);
    }
}

//-------------------------------------------------------------------------------------------------
void FieldThread::modelStep()
{
    for(auto i = 1; i < FIELD_N - 1; i++)
    {
        for(auto j = 1; j < FIELD_N - 1; j++)
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
