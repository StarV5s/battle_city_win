#include "StdAfx.h"
#include "Bullet.h"
#include "resource.h"


CImageList CBullet::m_Images[5];


CBullet::CBullet(int x, int y, int n, int d, int from) :CGameObject(x, y), m_n(n), direction(d), from_flag(from)
{

}

CBullet::~CBullet(void)
{
}
BOOL CBullet::LoadImage()
{
	CGameObject::LoadImage(m_Images[0], IDB_BULLETUP, RGB(0, 0, 0), 6, 8, 1);
	CGameObject::LoadImage(m_Images[1], IDB_BULLETUP, RGB(0, 0, 0), 6, 8, 1);
	CGameObject::LoadImage(m_Images[2], IDB_BULLETDOWN, RGB(0, 0, 0), 6, 8, 1);
	CGameObject::LoadImage(m_Images[3], IDB_BULLETRIGHT, RGB(0, 0, 0), 8, 6, 1);
	CGameObject::LoadImage(m_Images[4], IDB_BULLETLEFT, RGB(0, 0, 0), 8, 6, 1);
	return 0;
}
BOOL CBullet::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause){
		//控制子弹的类型
		if (m_n == 1 || m_n == 2){
			//控制子弹射出的方向
			if (direction == 0 || direction == 1){
				m_ptPos.y = m_ptPos.y - Bullet_Speed;
			}
			else if (direction == 2){
				m_ptPos.y = m_ptPos.y + Bullet_Speed;
			}
			else if (direction == 3){
				m_ptPos.x = m_ptPos.x + Bullet_Speed;
			}
			else if (direction == 4){
				m_ptPos.x = m_ptPos.x - Bullet_Speed;
			}
		}
		else if (m_n == 3)
		{
			/*m_ptPos.y = m_ptPos.y - 20;
			m_ptPos.x = m_ptPos.x - 3;*/
			m_ptPos.y = m_ptPos.y - 20;
		}
		else if (m_n == 4)
		{
			m_ptPos.y = m_ptPos.y - 20;
			m_ptPos.x = m_ptPos.x + 3;
		}
	}


	//出游戏范围就不绘制了
	if (m_ptPos.x > GAME_WIDTH + Bullet_Length)
		return FALSE;
	if (m_ptPos.x < -Bullet_Length)
		return FALSE;
	if (m_ptPos.y > GAME_HEIGHT + Bullet_Length)
		return FALSE;
	if (m_ptPos.y < -Bullet_Length)
		return FALSE;

	m_Images[direction].Draw(pDC, 0, m_ptPos, ILD_NORMAL);

	return TRUE;
}