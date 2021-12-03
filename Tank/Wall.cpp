#include "stdafx.h"
#include "Wall.h"
#include "Resource.h"

CImageList CWall::m_Images[10];

CWall::CWall()
{
}


CWall::~CWall()
{
}

//读取地图，将地图读取到数组里
void CWall::LoadMap(int StageNum) {
	FILE *fp;
	errno_t err;
	char path[20];
	sprintf_s(path, 20, "../Map/map%d.txt",  StageNum);
	err = fopen_s(&fp, path, "r");//打开文件成功返回0，失败返回非0，比fopen安全
	//char msgbuf[100];
	//sprintf_s(msgbuf, "map[%d][%d] is %d\n", , map[i][j]);
	//OutputDebugString(msgbuf);
	int i, j;
	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++)
			fscanf_s(fp, "%d", &map[i][j]);
	}
	fclose(fp);
	StartTime++;
}

BOOL CWall::LoadImage()
{
	//加载墙的位图，因为在地图数组map中，0表示该位置没有地图块，1-5表示字符串类型，所以m_Images[]从1开始计数
	CGameObject::LoadImage(m_Images[1], IDB_WALLFOREST, RGB(0, 0, 0), MapBlock_Length, MapBlock_Length, 1);
	CGameObject::LoadImage(m_Images[2], IDB_WALLICE, RGB(0, 0, 0), MapBlock_Length, MapBlock_Length, 1);
	CGameObject::LoadImage(m_Images[3], IDB_WALLWATER, RGB(0, 0, 0), MapBlock_Length, MapBlock_Length, 1);
	CGameObject::LoadImage(m_Images[4], IDB_WALLFIRM, RGB(0, 0, 0), MapBlock_Length, MapBlock_Length, 1);
	CGameObject::LoadImage(m_Images[5], IDB_WALLBLOCK, RGB(0, 0, 0), MapBlock_Length, MapBlock_Length, 1);
	CGameObject::LoadImage(m_Images[6], IDB_WALLHOME_6, RGB(0, 0, 0), MapBlock_Length, MapBlock_Length, 1);
	CGameObject::LoadImage(m_Images[7], IDB_WALLHOME_7, RGB(0, 0, 0), MapBlock_Length, MapBlock_Length, 1);
	CGameObject::LoadImage(m_Images[8], IDB_WALLHOME_8, RGB(0, 0, 0), MapBlock_Length, MapBlock_Length, 1);
	CGameObject::LoadImage(m_Images[9], IDB_WALLHOME_9, RGB(0, 0, 0), MapBlock_Length, MapBlock_Length, 1);
	return 0;
}

//绘制除草地之外的地图
BOOL CWall::Draw(CDC* pDC, BOOL bPause) {
	int i, j;
	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			//char msgbuf[100];
			//sprintf_s(msgbuf, "map[%d][%d] is %d\n", i, j, map[i][j]);
			//OutputDebugString(msgbuf);
			if (map[i][j] && map[i][j] != 1) {
				m_Images[map[i][j]].Draw(pDC, 0, CPoint(j * 16 + 38, i * 16 + 15), ILD_TRANSPARENT);
			}
		}
	}
	return 0;
}

//绘制草地
BOOL CWall::DrawForest(CDC* pDC, BOOL bPause) {
	int i, j;
	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			if (map[i][j] == 1) {
				m_Images[map[i][j]].Draw(pDC, 0, CPoint(j * 16 + 38, i * 16 + 15), ILD_TRANSPARENT);
			}
		}
	}
	return 0;
}