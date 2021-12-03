#include "StdAfx.h"
#include "MyTank1.h"
#include "resource.h"
#include "Wall.h"

CImageList CMyTank1::m_Images[11];

CMyTank1::~CMyTank1(void)
{
}
CMyTank1::CMyTank1(void)
{
	m_nWait = 0;
	m_ptPos.x = 168;
	m_ptPos.y = 395;
	appear1 = 0;
	number1 = 0;
	time = 0;
	direction = 0;//0->初始状态, 1->Up, 2->Down, 3->RIGHT, 4->Left
}


BOOL CMyTank1::LoadImage()
{
	CGameObject::LoadImage(m_Images[0], IDB_MYPLAYERUP1, RGB(0, 0, 0), MyPlayer1_WIDTH, MyPlayer1_HEIGHT, 1);//用来在初始状态显示坦克
	CGameObject::LoadImage(m_Images[1], IDB_MYPLAYERUP1, RGB(0, 0, 0), MyPlayer1_WIDTH, MyPlayer1_HEIGHT, 1);
	CGameObject::LoadImage(m_Images[2], IDB_MYPLAYERDOWN1, RGB(0, 0, 0), MyPlayer1_WIDTH, MyPlayer1_HEIGHT, 1);
	CGameObject::LoadImage(m_Images[3], IDB_MYPLAYERRIGHT1, RGB(0, 0, 0), MyPlayer1_HEIGHT, MyPlayer1_WIDTH, 1);
	CGameObject::LoadImage(m_Images[4], IDB_MYPLAYERLEFT1, RGB(0, 0, 0), MyPlayer1_HEIGHT, MyPlayer1_WIDTH, 1);
	CGameObject::LoadImage(m_Images[5], IDB_CREATETANK, RGB(0, 0, 0), 30, 30, 32);
	CGameObject::LoadImage(m_Images[6], IDB_PROTECTIVECOVER, RGB(0, 0, 0), 30, 30, 2);
	return 0;
}

BOOL CMyTank1::Draw(CDC* pDC,BOOL bPause)
{
	//m_nWait++;
	if(m_nWait > 1)
		m_nWait=0;
    time++;

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
	}

	//划定坦克活动区域
	if(m_ptPos.x >= GAME_WIDTH - MyPlayer1_WIDTH)
		m_ptPos.x = GAME_WIDTH - MyPlayer1_WIDTH;

	if(m_ptPos.x <= 0)
		m_ptPos.x = 0;

	if(m_ptPos.y <= 0)
		m_ptPos.y = 0;

	if(m_ptPos.y >= GAME_HEIGHT - MyPlayer1_HEIGHT)
		m_ptPos.y = GAME_HEIGHT - MyPlayer1_HEIGHT;


	if (Is_JustCreated){
		if (ProcessForCreate == 32){
			return Is_JustCreated = FALSE;
		}
		//步进后用新位置绘制图像
		m_Images[5].Draw(pDC, ProcessForCreate, CPoint(m_ptPos.x - 2, m_ptPos.y - 2), ILD_TRANSPARENT);
		ProcessForCreate++;
		return Is_JustCreated = TRUE;
	}
	m_Images[direction].Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	if (time > 30 && time < 120 && ShieldFlag == 1)
	{
		//到图片尾部时将Process置为0，使图片反复播放
		if (ProcessForProtect == 2)
		{
			ProcessForProtect = 0;
		}
		//用新位置绘制图像
		m_Images[6].Draw(pDC, ProcessForProtect, CPoint(m_ptPos.x - 2, m_ptPos.y - 2), ILD_TRANSPARENT);
		ProcessForProtect++;
	}
	return TRUE;
}
