/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/

#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <QMainWindow>

//=================================================================================================
namespace Ui {
	class SettingsWindow;
}

//=================================================================================================
class SettingsWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit SettingsWindow(QWidget *parent = nullptr);
	virtual ~SettingsWindow();

private:
	Ui::SettingsWindow						*ui;

public slots:
	void OnLoadSettings();
	void OnSaveSettings();
	void OnCancel();

	void OnBgColorChange();
	void OnLineColorChange();
	void OnCellColorChange();
};

//=================================================================================================

#endif

