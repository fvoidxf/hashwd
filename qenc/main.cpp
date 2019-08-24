/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/

#include "mainwindow.h"
#include <QApplication>
#include <boost/shared_ptr.hpp>
#include "log.h"

boost::shared_ptr<Log> _log(new Log("qenc_%N.log", Log::DevFile));

//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    _log->init();
    _log->write("Инициализация приложения...");
    QApplication a(argc, argv);
    _log->write("Создание виджета...");
    MainWindow w;
    _log->write("Показ виджета...");
    w.show();
    _log->write("Завершение приложения...");
    return a.exec();
}

//-------------------------------------------------------------------------------------------------
