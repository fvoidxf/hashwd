/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/
#include <QThread>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"
#include "dynmodel.h"

#define FIELD_N 20
#define FIELD_M 20

//-------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,scene(nullptr)
{
    ui->setupUi(this);
}

//-------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//-------------------------------------------------------------------------------------------------
void init_scenario_01(DynModel& model)
{
    model(0,0) = 1;
    model(0,1) = 1;
    model(0,2) = 1;

    model(1,0) = 1;
    model(1,2) = 1;
    model(1,3) = 1;

    model(2,1) = 1;
    model(2,2) = 1;
    model(3,2) = 1;

    model(0,5) = 1;
    model(1,5) = 1;
}

//-------------------------------------------------------------------------------------------------
void life_step(DynModel& model)
{
    for(auto i = 1; i < FIELD_N - 1; i++)
    {
        for(auto j = 1; j < FIELD_N - 1; j++)
        {
            int alive_cnt = 0;
            if(model(i-1, j-1))
                ++alive_cnt;
            if(model(i, j-1))
                ++alive_cnt;
            if(model(i+1,j-1))
                ++alive_cnt;

            if(model(i-1, j))
                ++alive_cnt;
            if(model(i+1, j))
                ++alive_cnt;

            if(model(i-1, j+1))
                ++alive_cnt;
            if(model(i, j+1))
                ++alive_cnt;
            if(model(i+1, j+1))
                ++alive_cnt;

            if(model(i,j)==0)
            {
                if(alive_cnt == 3)
                {
                    model(i,j) = 1;
                    continue;
                }
            }

            if(model(i,j)==1)
            {
                if((alive_cnt == 2) || (alive_cnt==3))
                {
                    model(i,j) = 1;
                    continue;
                }
            }

            model(i,j) = 0;
        }
    }
}

//-------------------------------------------------------------------------------------------------
bool MainWindow::init()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    field.reset(new Field(FIELD_N, FIELD_M));
    field->setScene(scene);
    field->setBackgroundColor(QColor(255,0,0));
    field->setCellColor(QColor(0,255,128));
    field->setBorderColor(Qt::yellow);
    field->setBackgroundColor(Qt::green);
    field->setCellColor(Qt::blue);
    field->update();

    DynModel *pM = new DynModel(FIELD_N,FIELD_M);
    pM->allocate();
    pM->clear();
    init_scenario_01(*pM);
    field->fromModel(*pM);
    int st = 47;
    while(--st){
        field->clearCells();
        life_step(*pM);
        field->fromModel(*pM);
        field->update();
    }
    pM->free();
    delete pM;

    return true;
}

//-------------------------------------------------------------------------------------------------
