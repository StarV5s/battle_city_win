#include "StdAfx.h"
#include "MyTank2.h"
#include "resource.h"
#include "Wall.h"

CImageList CMyTank2::m_Images[5];
CImageList CMyTank2::p_Images;

CMyTank2::~CMyTank2(void)
{
}
CMyTank2::CMyTank2(void)
{
	m_nWait = 0;
	m_ptPos.x = 165;
	m_ptPos.y = 20;
	appear1 = 0;
	number1 = 0;
	time = 0;
	direction = 2;//0->初始状态, 1->Up, 2->Down, 3->RIGHT, 4->Left
}

BOOL CMyTank2::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;

}




BOOL CMyTank2::LoadImage()
{
	CGameObject::LoadImage(m_Images[0], IDB_ENEMY1UP, RGB(0, 0, 0), Enemy_WIDTH, Enemy_HEIGHT, 1);//用来在初始状态显示坦克
	CGameObject::LoadImage(m_Images[1], IDB_ENEMY1UP, RGB(0, 0, 0), Enemy_WIDTH, Enemy_HEIGHT, 1);
	CGameObject::LoadImage(m_Images[2], IDB_ENEMY1DOWN, RGB(0, 0, 0), Enemy_WIDTH, Enemy_HEIGHT, 1);
	CGameObject::LoadImage(m_Images[3], IDB_ENEMY1RIGHT, RGB(0, 0, 0), Enemy_HEIGHT, Enemy_WIDTH, 1);
	CGameObject::LoadImage(m_Images[4], IDB_ENEMY1LEFT, RGB(0, 0, 0), Enemy_HEIGHT, Enemy_WIDTH, 1);
	CGameObject::LoadImage(m_Images[5], IDB_CREATETANK, RGB(0, 0, 0), 30, 30, 32);
	//CGameObject::LoadImage(m_Images[0], IDB_TANKUP2, RGB(0, 0, 0), 26, 26, 1);//用来在初始状态显示坦克
	//CGameObject::LoadImage(m_Images[1], IDB_TANKUP2, RGB(0, 0, 0), 26, 26, 1);
	//CGameObject::LoadImage(m_Images[2], IDB_TANKDOWN2, RGB(0, 0, 0), 26, 26, 1);
	//CGameObject::LoadImage(m_Images[3], IDB_TANKRIGHT2, RGB(0, 0, 0), 26, 26, 1);
	//CGameObject::LoadImage(m_Images[4], IDB_TANKLEFT2, RGB(0, 0, 0), 26, 26, 1);
	return 0;
}

BOOL CMyTank2::Draw(CDC* pDC, BOOL bPause)
{
	//m_nWait++;
	if (m_nWait>3)
		m_nWait = 0;
	time++;
	if (ShieldFlag == 1)
	{
		p_Images.Draw(pDC, 0, CPoint(m_ptPos.x - 18, m_ptPos.y - 22), ILD_TRANSPARENT);
		if (time % 3 == 0)
			appear1++;
	}
	if (appear1 == 4)
	{
		number1++;
		appear1 = 0;
	}
	if (number1 == 12)
	{
		appear1 = 0;
		number1 = 0;
		ShieldFlag = 0;
		ShieldFlag1 = 0;
		RFlag = 0;
	}

	//划定坦克活动区域
	if (m_ptPos.x >= GAME_WIDTH - TANK_WIDTH)
		m_ptPos.x = GAME_WIDTH - TANK_WIDTH;
	if (m_ptPos.x <= 0)
		m_ptPos.x = 0;

	if (m_ptPos.y <= 0)
		m_ptPos.y = 0;

	if (m_ptPos.y >= GAME_HEIGHT - TANK_HEIGHT)
		m_ptPos.y = GAME_HEIGHT - TANK_HEIGHT;
	//char msgbuf[100];
	//sprintf_s(msgbuf, "Tank's position is (%d,%d)\n", m_ptPos.x, m_ptPos.y);
	//OutputDebugString(msgbuf);

	//if (m_Images[direction] == NULL){
	//	sprintf_s(msgbuf, "m_Images[%d] == NULL\n", direction);
	//	OutputDebugString(msgbuf);
	//}
	//	
	//if (pDC == NULL)
	//	OutputDebugString("pDC == NULL\n");

	m_Images[direction].Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);


	return TRUE;
}