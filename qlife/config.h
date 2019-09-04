/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <QColor>


//=================================================================================================
class Config
{
public:
	enum WorkMode
	{
		UndefinedMode = 0,			//Неопределенный
		GameMode,					//Режим игры
		EditMode,					//Режим редактирования
	};

protected:
	int m_screenWidth;
	int m_screenHeight;
	int m_fieldWidth;
	int m_fieldHeight;
	int m_columns;
	int m_rows;
	int m_thread_timeout_ms;
	QColor m_bgAreaColor;
	QColor m_brdColor;
	QColor m_cellColor;

	int m_randomN_CNT;
	int m_randomM_CNT;
	int m_randomN_POS;
	int m_randomM_POS;

	int m_majVer;
	int m_midVer;
	int m_minVer;

	qreal m_cellScale;

	WorkMode m_workMode;

	unsigned long m_threadTerminateMsTimeout;

public:
	virtual ~Config(){}

	static Config* instance();

private:
	Config();
	static Config* m_self;

public:
	int screenWidth()const { return m_screenWidth; }
	int screenHeight()const { return m_screenHeight; }
	int columns()const { return m_columns*m_cellScale; }
	int rows()const { return m_rows*m_cellScale; }
	int fieldWidth()const { return m_fieldWidth; }
	int fieldHeight()const { return m_fieldHeight; }
	int cellWidth()const { return m_fieldWidth / columns(); }
	int cellHeight()const { return m_fieldHeight / rows(); }
	int threadTimeoutMs()const { return m_thread_timeout_ms; }

	QColor areaBackgroundColor()const { return m_bgAreaColor; }
	QColor borderColor()const { return m_brdColor; }
	QColor cellColor()const { return m_cellColor; }

	int randomStartN()const { return m_randomN_POS; }
	int randomStartM()const { return m_randomM_POS; }
	int randomCountN()const { return m_randomN_CNT; }
	int randomCountM()const { return m_randomM_CNT; }

	qreal cellScaleFactor()const { return m_cellScale; }

	WorkMode currentMode()const { return m_workMode; }
	void setGameMode() { m_workMode = GameMode; }
	void setEditMode() { m_workMode = EditMode; }

	void scenePosToIndex(QPointF pos, int& i, int& j);

	int minVer()const { return m_minVer; }
	int midVer()const { return m_midVer; }
	int majVer()const { return m_majVer; }

	QString version()const;

	unsigned long threadTerminateTimeoutMs()const { return m_threadTerminateMsTimeout; }
};

//=================================================================================================

#endif // __CONFIG_H__
