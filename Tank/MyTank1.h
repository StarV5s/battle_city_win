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

	static const int MyPlayer1_WIDTH = 26;//̹�˵Ŀ�
	static const int MyPlayer1_HEIGHT = 26;//̹�˵ĳ�
	BOOL Is_JustCreated = TRUE;//�궨̹���Ƿ�ոձ�����
	int direction = 0;//̹�˷���
    int ShieldFlag = 1;//̹�˸�����ʱ�Ļ���
	int ProcessForCreate = 0;//����ͼ�������Ĳ�������
	int ProcessForProtect = 0;//����ͼ�������Ĳ�������
	int m_nWait;//������ʱ
	int time;
	int appear1;
	int number1;

private:
	static CImageList m_Images[11];
};
