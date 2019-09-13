/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	try
	{
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
