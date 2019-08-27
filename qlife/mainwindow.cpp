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
#include "config.h"
#include "workarea.h"

//-------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,scene(nullptr)
	,area(nullptr)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setFixedSize( Config::instance()->screenWidth(), Config::instance()->screenHeight() );
    setCentralWidget(ui->graphicsView);
}

//-------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	if (thread) {
		thread->setStopFlag();
		thread->wait();
	}
    delete ui;
}

//-------------------------------------------------------------------------------------------------
bool MainWindow::init()
{
	//field.reset(new Field(Config::instance()->columns(), Config::instance()->rows()));
	thread = new FieldThread(this);

	connect(thread, SIGNAL(clearCells()), this, SLOT(OnClearCells()));
	connect(thread, SIGNAL(addCell(int,int)), this, SLOT(OnAddCell(int,int)));

    scene = new FieldScene(this);
    ui->graphicsView->setScene(scene);

	QRectF areasz(0, 0, Config::instance()->fieldWidth(), Config::instance()->fieldHeight());

	area = new Workarea(areasz, Config::instance()->columns(), Config::instance()->rows());
	scene->addItem(area);

    /*field->setScene(scene);
    field->init();
    ui->graphicsView->setWorkarea(field->getWorkarea());
    field->setBackgroundColor(QColor(255,0,0));
    field->setCellColor(QColor(0,255,128));
    field->setBorderColor(Qt::yellow);
    field->setBackgroundColor(Qt::green);
    field->setCellColor(Qt::blue);
    field->update();*/

    thread->start();

    return true;
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnClearCells()
{
    //field->clearCells();
    //field->update();
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
    //field->addCell(i,j);
    //field->update();
#ifdef _DEBUG
    _CrtMemDumpAllObjectsSince(&_memState);

#endif
}

//-------------------------------------------------------------------------------------------------
