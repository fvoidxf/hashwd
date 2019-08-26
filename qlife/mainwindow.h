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
class FieldThread;

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
    FieldThread *thread;

public:
    bool init();

public slots:
    void OnClearCells();
    void OnAddCell(int i, int j);
};

//=================================================================================================

#endif // __MAINWINDOW_H__