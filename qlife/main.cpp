/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/

#include "mainwindow.h"
#include <QApplication>

//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //w.init();

    return a.exec();
}

//-------------------------------------------------------------------------------------------------
