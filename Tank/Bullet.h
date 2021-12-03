#pragma once//�����ض���
#include "gameobject.h"

class CBullet :
	public CGameObject
{
public:
	CBullet(int x, int y, int n, int d, int from);
	~CBullet(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	int direction;//�����ӵ�����ķ���
	int from_flag;//�����ӵ��Ǵ���������ģ�0���Լ�̹�ˣ�1�ǵ���

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x + 6, m_ptPos.y + 8));
	}
private:
	static CImageList m_Images[5];
	int m_n;//�����ӵ�������
};
