#pragma once
#include "GameObject.h"
#include "Resource.h"

class CEnemy :public CGameObject
{
public:
	CEnemy(int x, int y, int lv);
	~CEnemy(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		//char msgbuf[100];
		//sprintf_s(msgbuf, "Player1矩形:%d, %d\n", m_ptPos.x, m_ptPos.y);
		//OutputDebugString(msgbuf);
		return CRect(m_ptPos, CPoint(m_ptPos.x + Enemy_WIDTH, m_ptPos.y + Enemy_HEIGHT));
	}

	static const int Enemy_WIDTH = 26;//坦克的宽
	static const int Enemy_HEIGHT = 30;//坦克的长

	
	int direction = 0;//坦克方向
	int ProcessForCreate = 0;//图像索引的步进计数
	int IsRouteDone = 0;//敌人走过单次路径了吗,0为刚创建，1为还在走，2为走完了
	int len = 1;//敌人单次所选路径的长度
	int speed = 2;//敌人的速度
	int level;//敌方坦克的等级

private:

	static CImageList m_Images[20];

	BOOL Is_JustCreated = TRUE;//标定坦克是否刚刚被创建


};
