#include "StdAfx.h"
#include "Explosion.h"
#include "resource.h"

CImageList CExplosion::m_Images[2];

CExplosion::CExplosion(int x, int y, int type) :CGameObject(x, y), Type(type)
{
}

CExplosion::~CExplosion(void)
{
}
BOOL CExplosion::Draw(CDC* pDC,BOOL bPause)
{
	//只有6张图片
	if (Process == 6)
	{
		Process = 0;
		return FALSE;
	}

	//用新位置绘制图像
	m_Images[Type].Draw(pDC, Process, m_ptPos, ILD_TRANSPARENT);
	Process++;
	return TRUE;

}

BOOL CExplosion::LoadImage()
{
	CGameObject::LoadImage(m_Images[0], IDB_TANKEXPLOSION, RGB(0, 0, 0), 64, 64, 6);
	CGameObject::LoadImage(m_Images[1], IDB_BULLETEXPLOSION, RGB(0, 0, 0), 32, 32, 6);
	return 0;
}