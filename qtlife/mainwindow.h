#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class FieldScene;

//=================================================================================================
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow							*ui;

	QMenu									*m_fileMenu;
	QMenu									*m_gameMenu;
	QMenu									*m_helpMenu;

	QAction									*m_exitAction;
	QAction									*m_changeModeAction;
	QAction									*m_aboutAction;



	void									_update();

public slots:
	void									OnExit();
	void									OnChangeMode();
	void									OnUpdateStatusMsg(const QString& msg);
	void									OnAbout();
};

//=================================================================================================

#endif // MAINWINDOW_H
