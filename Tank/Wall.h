#pragma once
#include "GameObject.h"
#include "Resource.h"

class CWall :
	public CGameObject
{
public:
	CWall();
	~CWall();
	//��ȡ��ͼ������
	void LoadMap(int StageNum);
	static BOOL LoadImage();
	BOOL Draw(CDC* pDC, BOOL bPause);//���Ƴ��ݵ�֮��ĵ�ͼ
	BOOL DrawForest(CDC* pDC, BOOL bPause);//���Ʋݵ�

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + MapBlock_Length, m_ptPos.y + MapBlock_Length));
	}

	int map[26][26];//���������ͼ

protected:
	static CImageList m_Images[10];
	
	int StartTime = 0;//�궨��Ϸ��ʼ���
};
