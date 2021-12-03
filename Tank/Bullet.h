#pragma once//避免重定义
#include "gameobject.h"

class CBullet :
	public CGameObject
{
public:
	CBullet(int x, int y, int n, int d, int from);
	~CBullet(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	int direction;//控制子弹射出的方向
	int from_flag;//定义子弹是从哪里出来的，0是自己坦克，1是敌人

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x + 6, m_ptPos.y + 8));
	}
private:
	static CImageList m_Images[5];
	int m_n;//控制子弹的类型
};
