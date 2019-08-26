/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/
#include <QThread>
#include "fieldthread.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"
#include "dynmodel.h"
#include "fieldscene.h"
#include "fieldview.h"

#ifndef FIELD_N
    #define FIELD_N 20
#endif

#ifndef FIELD_M
    #define FIELD_M 20
#endif

#define WINDOW_WIDTH	640
#define WINDOW_HEIGHT	480

//-------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,scene(nullptr)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setCentralWidget(ui->graphicsView);
    field.reset(new Field(FIELD_N, FIELD_M));
    thread = new FieldThread(field, this);
    connect(thread, SIGNAL(clearCells()), this, SLOT(OnClearCells()));
    connect(thread, SIGNAL(addCell(int,int)), this, SLOT(OnAddCell(int,int)));
}

//-------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    thread->setStopFlag();
    thread->wait();
    delete ui;
}

//-------------------------------------------------------------------------------------------------
bool MainWindow::init()
{
    scene = new FieldScene(this);
    ui->graphicsView->setScene(scene);

    field->setScene(scene);
    field->init();
    ui->graphicsView->setWorkarea(field->getWorkarea());
    field->setBackgroundColor(QColor(255,0,0));
    field->setCellColor(QColor(0,255,128));
    field->setBorderColor(Qt::yellow);
    field->setBackgroundColor(Qt::green);
    field->setCellColor(Qt::blue);
    field->update();

    DynModel *pM = new DynModel(FIELD_N,FIELD_M);
    pM->allocate();
    pM->clear();

    thread->start();

    return true;
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnClearCells()
{
    field->clearCells();
    field->update();
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnAddCell(int i, int j)
{
#ifdef _DEBUG
    _CrtMemState _memState;
    _CrtMemCheckpoint(&_memState);
    //_CrtDumpMemoryLeaks();
#endif
    //Дичайшие утечки, которые дают оба метода
    field->addCell(i,j);
    field->update();
#ifdef _DEBUG
    _CrtMemDumpAllObjectsSince(&_memState);

#endif
}

//-------------------------------------------------------------------------------------------------
