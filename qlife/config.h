/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#ifndef __CONFIG_H__
#define __CONFIG_H__

//=================================================================================================
class Config
{
protected:
	int m_screenWidth;
	int m_screenHeight;
	int m_fieldWidth;
	int m_fieldHeight;
	int m_columns;
	int m_rows;
	int m_thread_timeout_ms;

public:
	virtual ~Config(){}

	static Config* instance();

private:
	Config();
	static Config* m_self;

public:
	int screenWidth()const { return m_screenWidth; }
	int screenHeight()const { return m_screenHeight; }
	int columns()const { return m_columns; }
	int rows()const { return m_rows; }
	int fieldWidth()const { return m_fieldWidth; }
	int fieldHeight()const { return m_fieldHeight; }
	int cellWidth()const { return m_fieldWidth / m_columns; }
	int cellHeight()const { return m_fieldHeight / m_rows; }
	int threadTimeoutMs()const { return m_thread_timeout_ms; }
};

//=================================================================================================

#endif // __CONFIG_H__
