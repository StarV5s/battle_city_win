#pragma once
#include "GameObject.h"
#include "Resource.h"

class CMyTank2 :public CGameObject
{
public:
	CMyTank2(void);
	~CMyTank2(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		//char msgbuf[100];
		//sprintf_s(msgbuf, "Player2矩形:%d, %d\n", m_ptPos.x, m_ptPos.y);
		//OutputDebugString(msgbuf);
		return CRect(m_ptPos, CPoint(m_ptPos.x + TANK_WIDTH, m_ptPos.y + TANK_HEIGHT));
	}

	static const int Enemy_WIDTH = 26;//坦克的宽
	static const int Enemy_HEIGHT = 30;//坦克的长

	//坦克方向
	int direction = 0;
	//是否可以开火发射导弹
	BOOL Fired();

	int    ShieldFlag = 0;
	int    ShieldFlag1 = 0;
	int    RFlag = 0;

private:

	static CImageList m_Images[5];
	static CImageList p_Images;
	int    m_nWait;//发射延时
	int time;
	int appear1;
	int number1;

};
