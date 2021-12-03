#pragma once
#include "GameObject.h"
#include "resource.h"

class CUI :
	public CGameObject
{
public:
	CUI();
	~CUI();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x, m_ptPos.y));
	}

	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL DrawStartUI(CDC* pDC, UINT bmpID, CRect DestRect);
	BOOL DrawGameOver(CDC* pDC, BOOL bPause, int i);
	BOOL DrawTankLife(CDC* pDC, BOOL bPause, int Life);
	BOOL DrawEnemyNum(CDC* pDC, BOOL bPause, int n);
	BOOL DrawStage(CDC* pDC, BOOL bPause, int n);
	static BOOL LoadImage();
	int Process = 0;//图像索引的步进计数

private:
	static CImageList m_Images[10];

};

