/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/

#include <QAction>
#include <QColorDialog>
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

	connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(OnCancel()));
	connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(OnLoadSettings()));
	connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(OnSaveSettings()));

	connect(ui->areaClrButton, SIGNAL(clicked()), this, SLOT(OnBgColorChange()));
}

//-------------------------------------------------------------------------------------------------
SettingsWindow::~SettingsWindow()
{
	delete ui;
}

//-------------------------------------------------------------------------------------------------
void SettingsWindow::OnLoadSettings()
{
	statusBar()->showMessage("Настройки загружены...", 5000);
	Config::instance()->readSettings();
}

//-------------------------------------------------------------------------------------------------
void SettingsWindow::OnSaveSettings()
{
	statusBar()->showMessage("Настройки сохранены...", 5000);
	Config::instance()->writeSettings();
}

//-------------------------------------------------------------------------------------------------
void SettingsWindow::OnCancel()
{
	this->setVisible(false);
}

//-------------------------------------------------------------------------------------------------
void SettingsWindow::OnBgColorChange()
{
	QColor clr = QColorDialog::getColor();
	QPalette plt = ui->labelBackground->palette();
	plt.setColor(QPalette::Background, clr);
	ui->labelBackground->setPalette(plt);
}

//-------------------------------------------------------------------------------------------------
void SettingsWindow::OnLineColorChange()
{

}

//-------------------------------------------------------------------------------------------------
void SettingsWindow::OnCellColorChange()
{
	
}

//-------------------------------------------------------------------------------------------------
