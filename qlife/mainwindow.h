/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

class FieldThread;
class FieldScene;
class Workarea;

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
    Ui::MainWindow *m_ui;
    FieldScene *m_scene;
    FieldThread *m_thread;
	Workarea *m_area;

public:
    bool init();

public slots:
    void OnClearCells();
	void OnDataReady();
};

//=================================================================================================

#endif // __MAINWINDOW_H__
