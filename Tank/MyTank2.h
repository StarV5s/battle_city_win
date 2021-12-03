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
		//sprintf_s(msgbuf, "Player2����:%d, %d\n", m_ptPos.x, m_ptPos.y);
		//OutputDebugString(msgbuf);
		return CRect(m_ptPos, CPoint(m_ptPos.x + TANK_WIDTH, m_ptPos.y + TANK_HEIGHT));
	}

	static const int Enemy_WIDTH = 26;//̹�˵Ŀ�
	static const int Enemy_HEIGHT = 30;//̹�˵ĳ�

	//̹�˷���
	int direction = 0;
	//�Ƿ���Կ����䵼��
	BOOL Fired();

	int    ShieldFlag = 0;
	int    ShieldFlag1 = 0;
	int    RFlag = 0;

private:

	static CImageList m_Images[5];
	static CImageList p_Images;
	int    m_nWait;//������ʱ
	int time;
	int appear1;
	int number1;

};
