#pragma once
#include "gameobject.h"

class CExplosion :public CGameObject
{
public:
	CExplosion(int x,int y, int type);
	~CExplosion(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+EXPLOSION_WIDTH,m_ptPos.y+EXPLOSION_WIDTH));
	}
private:
	//ը����ͼƬ�б�
	static CImageList m_Images[2];
	//ͼ�������Ĳ�������
	int   Process = 0;
	//��ը���ͣ�1->̹�˱�ը��2->�ӵ���ը
	int Type;
public:
	static const int  EXPLOSION_WIDTH = 64;
};
