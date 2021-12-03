#include "StdAfx.h"
#include "Enemy.h"
#include "resource.h"
#include "Wall.h"

CImageList CEnemy::m_Images[20];

CEnemy::~CEnemy(void)
{
}
CEnemy::CEnemy(int x, int y, int lv)
{
	m_ptPos.x = x;
	m_ptPos.y = y;
	level = lv;
	direction = 2;//0->初始状态, 1->Up, 2->Down, 3->RIGHT, 4->Left
}

BOOL CEnemy::LoadImage()
{
	CGameObject::LoadImage(m_Images[0], IDB_ENEMY1UP, RGB(0, 0, 0), Enemy_WIDTH, Enemy_HEIGHT, 1);//用来在初始状态显示坦克
	CGameObject::LoadImage(m_Images[1], IDB_ENEMY1UP, RGB(0, 0, 0), Enemy_WIDTH, Enemy_HEIGHT, 1);
	CGameObject::LoadImage(m_Images[2], IDB_ENEMY1DOWN, RGB(0, 0, 0), Enemy_WIDTH, Enemy_HEIGHT, 1);
	CGameObject::LoadImage(m_Images[3], IDB_ENEMY1RIGHT, RGB(0, 0, 0), Enemy_HEIGHT, Enemy_WIDTH, 1);
	CGameObject::LoadImage(m_Images[4], IDB_ENEMY1LEFT, RGB(0, 0, 0), Enemy_HEIGHT, Enemy_WIDTH, 1);
	CGameObject::LoadImage(m_Images[5], IDB_CREATETANK, RGB(0, 0, 0), 30, 30, 32);
	CGameObject::LoadImage(m_Images[6], IDB_ENEMY2UP, RGB(0, 0, 0), Enemy_WIDTH, Enemy_HEIGHT, 1);
	CGameObject::LoadImage(m_Images[7], IDB_ENEMY2DOWN, RGB(0, 0, 0), Enemy_WIDTH, Enemy_HEIGHT, 1);
	CGameObject::LoadImage(m_Images[8], IDB_ENEMY2RIGHT, RGB(0, 0, 0), Enemy_HEIGHT, Enemy_WIDTH, 1);
	CGameObject::LoadImage(m_Images[9], IDB_ENEMY2LEFT, RGB(0, 0, 0), Enemy_HEIGHT, Enemy_WIDTH, 1);
	return 0;
}

BOOL CEnemy::Draw(CDC* pDC, BOOL bPause)
{

	//划定坦克活动区域
	if (m_ptPos.x >= GAME_WIDTH - Enemy_WIDTH)
		m_ptPos.x = GAME_WIDTH - Enemy_WIDTH;
	if (m_ptPos.x <= 0)
		m_ptPos.x = 0;

	if (m_ptPos.y <= 0)
		m_ptPos.y = 0;

	if (m_ptPos.y >= GAME_HEIGHT - Enemy_HEIGHT)
		m_ptPos.y = GAME_HEIGHT - Enemy_HEIGHT;

	if (Is_JustCreated){
		////只有6张图片
		if (ProcessForCreate == 32){

			//ProcessForCreate = 0;
			Is_JustCreated = FALSE;
		}
		else{
			//用新位置绘制图像
			m_Images[5].Draw(pDC, ProcessForCreate, CPoint(m_ptPos.x - 2, m_ptPos.y - 2), ILD_TRANSPARENT);
			ProcessForCreate++;
			return Is_JustCreated = TRUE;
		}
	}
	if (level == 0)
		m_Images[direction].Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	else if (level == 1)
		m_Images[direction + 5].Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}