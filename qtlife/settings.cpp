/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/

#include <QAction>
#include "ui_Settings.h"
#include "settings.h"
#include "commands.h"
#include "config.h"
#include "strings.h"
#include "fieldscene.h"

//-------------------------------------------------------------------------------------------------
SettingsWindow::SettingsWindow(QWidget *parent)
	:QMainWindow(parent)
	,ui(new Ui::SettingsWindow)
{
	ui->setupUi(this);
}

//-------------------------------------------------------------------------------------------------
SettingsWindow::~SettingsWindow()
{
	delete ui;
}

//-------------------------------------------------------------------------------------------------
