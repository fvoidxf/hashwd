#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,scene(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::init()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    field.reset(new Field(20, 20));
    field->setScene(scene);
    field->draw();
    field->addCell(2,2);
    return true;
}
