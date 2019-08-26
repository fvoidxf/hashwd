/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

//-------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

//-------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//-------------------------------------------------------------------------------------------------
