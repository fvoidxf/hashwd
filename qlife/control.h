/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#ifndef __CONTROL_H__
#define __CONTROL_H__

class DynModel;
class FieldThread;

//=================================================================================================
class Control
{
public:
	Control();
	virtual ~Control();

protected:
	DynModel				*m_model;
	FieldThread				*m_thread;
};

//=================================================================================================

#endif // __CONTROL_H__
