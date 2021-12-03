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
		//sprintf_s(msgbuf, "Player1����:%d, %d\n", m_ptPos.x, m_ptPos.y);
		//OutputDebugString(msgbuf);
		return CRect(m_ptPos, CPoint(m_ptPos.x + Enemy_WIDTH, m_ptPos.y + Enemy_HEIGHT));
	}

	static const int Enemy_WIDTH = 26;//̹�˵Ŀ�
	static const int Enemy_HEIGHT = 30;//̹�˵ĳ�

	
	int direction = 0;//̹�˷���
	int ProcessForCreate = 0;//ͼ�������Ĳ�������
	int IsRouteDone = 0;//�����߹�����·������,0Ϊ�մ�����1Ϊ�����ߣ�2Ϊ������
	int len = 1;//���˵�����ѡ·���ĳ���
	int speed = 2;//���˵��ٶ�
	int level;//�з�̹�˵ĵȼ�

private:

	static CImageList m_Images[20];

	BOOL Is_JustCreated = TRUE;//�궨̹���Ƿ�ոձ�����


};
