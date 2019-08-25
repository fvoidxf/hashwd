/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

class Field;

namespace Ui {
    class MainWindow;
}

//=================================================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QSharedPointer<Field> field;

public:
    bool init();
};

//=================================================================================================

#endif // __MAINWINDOW_H__
