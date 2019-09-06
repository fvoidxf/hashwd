/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#ifndef __CELLITEM_H__
#define __CELLITEM_H__

#include <QGraphicsItem>

//=================================================================================================
class CellItem : public QGraphicsItem
{
public:
	CellItem(int i, int j, QGraphicsItem *parent = nullptr);
	virtual ~CellItem();

	virtual QRectF boundingRect()const override;
	virtual void paint(QPainter *painter,
		const QStyleOptionGraphicsItem *option,
		QWidget *widget)override;

	void setBackgroundColor(QColor color);
	void setBorderColor(QColor color);

	void setEnabled(bool bEnabled = true);

	int i()const { return m_i; }
	int j()const { return m_j; }

	bool isEnabled()const { return m_enabled; }

protected:
	int m_i;
	int m_j;
	bool m_enabled;

	QColor m_bgColor;
	QColor m_brdColor;
};

//=================================================================================================

#endif // __CELLITEM_H__
