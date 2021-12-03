#include "stdafx.h"
#include "UI.h"
#include "resource.h"

CImageList CUI::m_Images[10];
CUI::CUI()
{
}


CUI::~CUI()
{
}

BOOL CUI::LoadImage()
{
	CGameObject::LoadImage(m_Images[1], IDB_GAMEOVER, RGB(0, 0, 0), 254, 122, 2);
	CGameObject::LoadImage(m_Images[2], IDB_PLAYERLIFE0, RGB(255, 255, 255), 29, 34, 1);
	CGameObject::LoadImage(m_Images[3], IDB_PLAYERLIFE1, RGB(255, 255, 255), 29, 34, 1);
	CGameObject::LoadImage(m_Images[4], IDB_PLAYERLIFE2, RGB(255, 255, 255), 29, 34, 1);
	CGameObject::LoadImage(m_Images[5], IDB_PLAYERLIFE3, RGB(255, 255, 255), 29, 34, 1);
	CGameObject::LoadImage(m_Images[6], IDB_ENEMYNUM, RGB(255, 255, 255), 14, 14, 1);
	CGameObject::LoadImage(m_Images[7], IDB_STAGE1, RGB(255, 255, 255), 536, 446, 9);
	return 0;
}

BOOL CUI::Draw(CDC* pDC, BOOL bPause)
{
	return TRUE;
}
//���ƿ�ʼ����
BOOL CUI::DrawStartUI(CDC* pDC, UINT bmpID, CRect DestRect)
{
	CBitmap bmp;
	bmp.LoadBitmap(bmpID);//����ͼ

	BITMAP bitmap;//�������������Ϊ���Եõ�ͼƬ�Ŀ�͸ߣ����һ�仰��
	bmp.GetBitmap(&bitmap);

	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);//�����ڴ�dc
	dcMem.SelectObject(&bmp);//��ͼƬ���ص��ڴ�dc
	CBitmap* pbmpOld = dcMem.SelectObject(&bmp);
	pDC->StretchBlt(0, 0, 536, 446, &dcMem, 0, 0, 536, 446, SRCCOPY);  //���ڴ�dc�������ȫ�����Ƶ���ǰdc����
	return true;
}
//����GameOver
BOOL CUI::DrawGameOver(CDC* pDC, BOOL bPause, int i){
	if (i < 284)
		m_Images[1].Draw(pDC, 0, CPoint(119, 431 - i), ILD_TRANSPARENT);
	else m_Images[1].Draw(pDC, 0, CPoint(119, 431 - 284), ILD_TRANSPARENT);
	return 0;
}
//����̹������ֵ
BOOL CUI::DrawTankLife(CDC* pDC, BOOL bPause, int Life)
{

	m_Images[Life + 2].Draw(pDC, 0, CPoint(480, 250), ILD_TRANSPARENT);
	return TRUE;
}
//���Ƶ�������ֵ
BOOL CUI::DrawEnemyNum(CDC* pDC, BOOL bPause, int n)
{
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0)
			m_Images[6].Draw(pDC, 0, CPoint(480, 50 + i/2 * 17), ILD_TRANSPARENT);
		else m_Images[6].Draw(pDC, 0, CPoint(500, 50 + i/2 * 17), ILD_TRANSPARENT);
	}
	return TRUE;
//���ƹؿ�ͼ
}BOOL CUI::DrawStage(CDC* pDC, BOOL bPause, int n)
{
	//���ò������������ķ�ʽʵ�ֶ�ͼ
	if (Process >= 0 && Process < 8) {
		m_Images[7].Draw(pDC, Process, CPoint(0, 0), ILD_TRANSPARENT);
		Process++;
	}
	//��֮��ͣ�����һ֡
	else if (Process >= 8 && Process <= 50) {
		m_Images[7].Draw(pDC, 8, CPoint(0, 0), ILD_TRANSPARENT);
		Process++;
	}
	//�ٴ����һ֡���Ų���
	else if (Process > 50 && Process <= 59) {
		m_Images[7].Draw(pDC, 59 - Process, CPoint(0, 0), ILD_TRANSPARENT);
		Process++;
	}

	return TRUE;
}