#pragma once
#include "GameObject.h"
#include "Resource.h"

class CMyTank1 :public CGameObject
{
public:
	CMyTank1(void);
	~CMyTank1(void);

	BOOL Draw(CDC* pDC,BOOL bPause);
	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + MyPlayer1_WIDTH, m_ptPos.y + MyPlayer1_HEIGHT));
	}

	static const int MyPlayer1_WIDTH = 26;//坦克的宽
	static const int MyPlayer1_HEIGHT = 26;//坦克的长
	BOOL Is_JustCreated = TRUE;//标定坦克是否刚刚被创建
	int direction = 0;//坦克方向
    int ShieldFlag = 1;//坦克刚生成时的护盾
	int ProcessForCreate = 0;//生成图像索引的步进计数
	int ProcessForProtect = 0;//护盾图像索引的步进计数
	int m_nWait;//发射延时
	int time;
	int appear1;
	int number1;

private:
	static CImageList m_Images[11];
};
