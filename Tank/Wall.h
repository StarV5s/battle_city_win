#pragma once
#include "GameObject.h"
#include "Resource.h"

class CWall :
	public CGameObject
{
public:
	CWall();
	~CWall();
	//读取地图块数据
	void LoadMap(int StageNum);
	static BOOL LoadImage();
	BOOL Draw(CDC* pDC, BOOL bPause);//绘制除草地之外的地图
	BOOL DrawForest(CDC* pDC, BOOL bPause);//绘制草地

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + MapBlock_Length, m_ptPos.y + MapBlock_Length));
	}

	int map[26][26];//用来储存地图

protected:
	static CImageList m_Images[10];
	
	int StartTime = 0;//标定游戏开始与否
};
