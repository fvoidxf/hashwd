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

	QPalette pltBg = ui->labelBackground->palette();
	QPalette pltLine = ui->labelLine->palette();
	QPalette pltCell = ui->labelCell->palette();

	pltBg.setColor(QPalette::Background, Config::instance()->areaBackgroundColor());
	pltLine.setColor(QPalette::Background, Config::instance()->borderColor());
	pltCell.setColor(QPalette::Background, Config::instance()->cellColor());

	ui->labelBackground->setPalette(pltBg);
	ui->labelLine->setPalette(pltLine);
	ui->labelCell->setPalette(pltCell);

	connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(OnCancel()));
	connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(OnLoadSettings()));
	connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(OnSaveSettings()));

	connect(ui->areaClrButton, SIGNAL(clicked()), this, SLOT(OnBgColorChange()));
	connect(ui->lineClrButton, SIGNAL(clicked()), this, SLOT(OnLineColorChange()));
	connect(ui->cellClrButton, SIGNAL(clicked()), this, SLOT(OnCellColorChange()));

	QString strCol = QString("%1").arg(Config::instance()->columns());
	ui->lineEditColumns->setText(strCol);

	QString strRow = QString("%1").arg(Config::instance()->rows());
	ui->lineEditRows->setText(strRow);

	QString strWidth = QString("%1").arg(Config::instance()->fieldWidth());
	ui->lineEditWidth->setText(strWidth);

	QString strHeight = QString("%1").arg(Config::instance()->fieldHeight());
	ui->lineEditHeight->setText(strHeight);
}

//-------------------------------------------------------------------------------------------------
SettingsWindow::~SettingsWindow()
{
	delete ui;
}

//-------------------------------------------------------------------------------------------------
void SettingsWindow::OnLoadSettings()
{
	QString strCol = QString("%1").arg(Config::instance()->columns());
	QString strRow = QString("%1").arg(Config::instance()->rows());
	QString strWid = QString("%1").arg(Config::instance()->fieldWidth());
	QString strHeig = QString("%1").arg(Config::instance()->fieldHeight());

	ui->lineEditColumns->setText(strCol);
	ui->lineEditRows->setText(strRow);
	ui->lineEditWidth->setText(strWid);
	ui->lineEditHeight->setText(strHeig);

	statusBar()->showMessage("Настройки загружены...", 5000);
	Config::instance()->readSettings();
}

//-------------------------------------------------------------------------------------------------
void SettingsWindow::OnSaveSettings()
{
	QString strCol = ui->lineEditColumns->text();
	QString strRow = ui->lineEditRows->text();
	QString strWid = ui->lineEditWidth->text();
	QString strHeig = ui->lineEditHeight->text();

	Config::instance()->setColumns(strCol.toInt());
	Config::instance()->setRows(strRow.toInt());
	Config::instance()->setFieldWidth(strWid.toInt());
	Config::instance()->setFieldHeight(strHeig.toInt());

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
	Config::instance()->setBackgroundColor(clr);
}

//-------------------------------------------------------------------------------------------------
void SettingsWindow::OnLineColorChange()
{
	QColor clr = QColorDialog::getColor();
	QPalette plt = ui->labelLine->palette();
	plt.setColor(QPalette::Background, clr);
	ui->labelLine->setPalette(plt);
	Config::instance()->setLineColor(clr);
}

//-------------------------------------------------------------------------------------------------
void SettingsWindow::OnCellColorChange()
{
	QColor clr = QColorDialog::getColor();
	QPalette plt = ui->labelCell->palette();
	plt.setColor(QPalette::Background, clr);
	ui->labelCell->setPalette(plt);
	Config::instance()->setCellColor(clr);
}

//-------------------------------------------------------------------------------------------------