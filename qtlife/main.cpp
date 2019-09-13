/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/

#include "mainwindow.h"
#include <QApplication>
#include "config.h"

int main(int argc, char *argv[])
{
	try
	{
		Config::instance()->readSettings();

		QApplication a(argc, argv);
		MainWindow w;
		w.show();

		return a.exec();
	}
	catch (...)
	{
		return -1;
	}
	return 0;
}
