// TankView.cpp : CTankView ���ʵ��
//

#include "stdafx.h"
#include "Tank.h"
#include "resource.h"
#include <mmsystem.h>
#include <ctime>//��ʼ��������������õ�time����

#include "TankDoc.h"
#include "TankView.h"
#include "MyTank1.h"
#include "MyTank2.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Wall.h"
#include "UI.h"
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTankView

IMPLEMENT_DYNCREATE(CTankView, CView)

BEGIN_MESSAGE_MAP(CTankView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CTankView ����/����
CTankView::CTankView() :Player1(NULL)
{
	// TODO: �ڴ˴���ӹ������

}

CTankView::~CTankView()
{
}

BOOL CTankView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTankView ����
void CTankView::OnDraw(CDC* /*pDC*/)
{
	//���ű�������
	//PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_ASYNC | SND_RESOURCE | SND_NODEFAULT | SND_LOOP);
	CTankDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

// CTankView ��ӡ

BOOL CTankView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTankView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTankView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CTankView ���

#ifdef _DEBUG
void CTankView::AssertValid() const
{
	CView::AssertValid();
}

void CTankView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTankDoc* CTankView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTankDoc)));
	return (CTankDoc*)m_pDocument;
}
#endif //_DEBUG

// CTankView ��Ϣ�������
void CTankView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
	InitGame();
}
BOOL CTankView::InitGame()
{
	a = 5;
	CRect rc;
	GetClientRect(rc);

	//�������������
	srand((unsigned)time(NULL));

	//�����豸DC
	ClientDC = new CClientDC(this);

	//�����ڴ�DC
	MemeoryDC = new CDC;
	MemeoryDC->CreateCompatibleDC(ClientDC);

	//�����ڴ�λͼ
	MemeoryBitmap = new CBitmap;
	MemeoryBitmap->CreateCompatibleBitmap(ClientDC, GAME_WIDTH, GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
	MemeoryDC->SelectObject(MemeoryBitmap);

	CMyTank1::LoadImage();
	CMyTank2::LoadImage();
	CEnemy::LoadImage();
	CBullet::LoadImage();
	CExplosion::LoadImage();
	CWall::LoadImage();
	CUI::LoadImage();

	//����UI����
	UI = new CUI;
	UI->Process = 0;

	//����ǽ����
	Wall = new CWall;
	Wall->LoadMap(StageNum);
	MapBlockRecordY = 26;
	MapBlockRecordX = 26;

	//��������(̹��)
	Player1 = new CMyTank1;
	if(PlayerNum == 2)
		Player2 = new CMyTank2;
	EnemyNum = 20;
	Player1_Life = 3;


	//ˢ�´��ڵļ�ʱ��
	/*1�Ǽ�ʱ����ʶ��30��ʱ��������λ�Ǻ��룻
	������������һ���ص�������������������������Ҫ��������Ĵ��룬
	����Խ����趨ΪNULL��Ҳ����ʹ��ϵͳĬ�ϵĻص�������ϵͳĬ���ϵ���onTime������*/
	SetTimer(1, 30, NULL);

	return TRUE;
}
void CTankView::StopGame()
{
	delete Wall;
	delete Player1;
	if (PlayerNum == 2)
		delete Player2;
	delete MemeoryDC;
	delete ClientDC;
	delete MemeoryBitmap;
}
//����̹�˵���ײ���ģ��
BOOL CTankView::CollisionDetectionForTank(int x, int y, int TANK_WIDTH, int TANK_HEIGHT, int d) {
	//0���յأ�1���ݵ� 2������ 3���� 4����ǽ 5����ǽ 6���ϼ�
	//ÿһ����ײ��ˮƽ�涼���м�����һ����������ײ���,ʹ̹���ܲ��ŵ�ͼ���ȥ
	//��Ϊ̹�˱ȵ�ͼ���������̹���м�ҲҪ����ײ���
	//�ȼ��̹�˼��ϲ�����᲻����ײ��������false
	//��Ϊ������˸�������Ҫ���Ǹ�����ɵ�λ��ƫ�Ƽ��ϣ�38��15��
	if (d == 0 || d == 1) {
		if (y - Tank_Speed < 15
			|| (Wall->map[(y - Tank_Speed - 15) / MapBlock_Length][(x + 1 - 38) / MapBlock_Length] >= 3
			&& Wall->map[(y - Tank_Speed - 15) / MapBlock_Length][(x + 1 - 38) / MapBlock_Length] <= 9)
			|| (Wall->map[(y - Tank_Speed - 15) / MapBlock_Length][(x + TANK_WIDTH / 2 - 38) / MapBlock_Length] >= 3
			&& Wall->map[(y - Tank_Speed - 15) / MapBlock_Length][(x + TANK_WIDTH / 2 - 38) / MapBlock_Length] <= 9)
			|| (Wall->map[(y - Tank_Speed - 15) / MapBlock_Length][(x + TANK_WIDTH - 1 - 38) / MapBlock_Length] >= 3
			&& Wall->map[(y - Tank_Speed - 15) / MapBlock_Length][(x + TANK_WIDTH - 1 - 38) / MapBlock_Length] <= 9)) return false;
	}
	else if (d == 2) {
		if (y + Tank_Speed > 405
			|| (Wall->map[(y + TANK_HEIGHT + Tank_Speed - 15) / MapBlock_Length][(x + 1 - 38) / MapBlock_Length] >= 3
			&& Wall->map[(y + TANK_HEIGHT + Tank_Speed - 15) / MapBlock_Length][(x + 1 - 38) / MapBlock_Length] <= 9)
			|| (Wall->map[(y + TANK_HEIGHT + Tank_Speed - 15) / MapBlock_Length][(x + TANK_WIDTH / 2 - 38) / MapBlock_Length] >= 3
			&& Wall->map[(y + TANK_HEIGHT + Tank_Speed - 15) / MapBlock_Length][(x + TANK_WIDTH / 2 - 38) / MapBlock_Length] <= 9)
			|| (Wall->map[(y + TANK_HEIGHT + Tank_Speed - 15) / MapBlock_Length][(x + TANK_WIDTH - 1 - 38) / MapBlock_Length] >= 3
			&& Wall->map[(y + TANK_HEIGHT + Tank_Speed - 15) / MapBlock_Length][(x + TANK_WIDTH - 1 - 38) / MapBlock_Length] <= 9)) return false;
	}
	else if (d == 3) {
		if (x + Tank_Speed > 428
			|| (Wall->map[(y + 1 - 15) / MapBlock_Length][(x + TANK_WIDTH + Tank_Speed - 38) / MapBlock_Length] >= 3
			&& Wall->map[(y + 1 - 15) / MapBlock_Length][(x + TANK_WIDTH + Tank_Speed - 38) / MapBlock_Length] <= 9)
			|| (Wall->map[(y + TANK_HEIGHT / 2 - 15) / MapBlock_Length][(x + TANK_WIDTH + Tank_Speed - 38) / MapBlock_Length] >= 3
			&& Wall->map[(y + TANK_HEIGHT / 2 - 15) / MapBlock_Length][(x + TANK_WIDTH + Tank_Speed - 38) / MapBlock_Length] <= 9)
			|| (Wall->map[(y + TANK_HEIGHT - 1 - 15) / MapBlock_Length][(x + TANK_WIDTH + Tank_Speed - 38) / MapBlock_Length] >= 3
			&& Wall->map[(y + TANK_HEIGHT - 1 - 15) / MapBlock_Length][(x + TANK_WIDTH + Tank_Speed - 38) / MapBlock_Length] <= 9)) return false;
	}
	else if (d == 4) {
		if (x - Tank_Speed < 38
			|| (Wall->map[(y + 1 - 15) / MapBlock_Length][(x - Tank_Speed - 38) / MapBlock_Length] >= 3
			&& Wall->map[(y + 1 - 15) / MapBlock_Length][(x - Tank_Speed - 38) / MapBlock_Length] <= 9)
			|| (Wall->map[(y + TANK_HEIGHT / 2 - 15) / MapBlock_Length][(x - Tank_Speed - 38) / MapBlock_Length] >= 3
			&& Wall->map[(y + TANK_HEIGHT / 2 - 15) / MapBlock_Length][(x - Tank_Speed - 38) / MapBlock_Length] <= 9)
			|| (Wall->map[(y + TANK_HEIGHT - 1 - 15) / MapBlock_Length][(x - Tank_Speed - 38) / MapBlock_Length] >= 3
			&& Wall->map[(y + TANK_HEIGHT - 1 - 15) / MapBlock_Length][(x - Tank_Speed - 38) / MapBlock_Length] <= 9)) return false;
	}
	return true;
}
//�����ӵ�����ײ���ģ��
BOOL CTankView::CollisionDetectionForBullet(int x, int y, int d) {
	//0���յأ�1���ݵ� 2������ 3���� 4����ǽ 5����ǽ 6���ϼ�
	//ÿһ����ײ��ˮƽ�����1��7����λ�õ���ײ���,ʹ�ӵ��ܲ��ŵ�ͼ���ȥ
	//��⵽��ײ���ײ���ĵ�ͼ����������
	//�ӵ�����ײû���ȼ��ϲ�������Ϊ�˱����ɽ��ţ�����
	if (d == 0 || d == 1){
		if (y < 15
			|| (Wall->map[(y - 15) / MapBlock_Length][((x - 38) + 1) / MapBlock_Length] >= 4
			&& Wall->map[(y - 15) / MapBlock_Length][((x - 38) + 1) / MapBlock_Length] <= 9)){
			MapBlockRecordY = (y - 15) / MapBlock_Length;
			MapBlockRecordX = ((x - 38) + 1) / MapBlock_Length;
			return false;
		}
		else if (y < 15
			|| (Wall->map[(y - 15) / MapBlock_Length][((x - 38) + Bullet_Length - 1) / MapBlock_Length] >= 4
			&& Wall->map[(y - 15) / MapBlock_Length][((x - 38) + Bullet_Length - 1) / MapBlock_Length] <= 9)){
			MapBlockRecordY = (y - 15) / MapBlock_Length;
			MapBlockRecordX = ((x - 38) + Bullet_Length - 1) / MapBlock_Length;
			return false;
		}
	}
	else if (d == 2){
		if (y > 418
			|| (Wall->map[((y - 15) + Bullet_Length) / MapBlock_Length][((x - 38) + 1) / MapBlock_Length] >= 4
			&& Wall->map[((y - 15) + Bullet_Length) / MapBlock_Length][((x - 38) + 1) / MapBlock_Length] <= 9)){
			MapBlockRecordY = ((y - 15) + Bullet_Length) / MapBlock_Length;
			MapBlockRecordX = ((x - 38) + 1) / MapBlock_Length;
			return false;
		}
		else if (y > 418
			|| (Wall->map[((y - 15) + Bullet_Length) / MapBlock_Length][((x - 38) + Bullet_Length - 1) / MapBlock_Length] >= 4
			&& Wall->map[((y - 15) + Bullet_Length) / MapBlock_Length][((x - 38) + Bullet_Length - 1) / MapBlock_Length] <= 9)){
			MapBlockRecordY = ((y - 15) + Bullet_Length) / MapBlock_Length;
			MapBlockRecordX = ((x - 38) + Bullet_Length - 1) / MapBlock_Length;
			return false;
		}
	}
	else if (d == 3){
		if (x > 441
			|| (Wall->map[((y - 15) + 1) / MapBlock_Length][((x - 38) + Bullet_Length) / MapBlock_Length] >= 4
			&& Wall->map[((y - 15) + 1) / MapBlock_Length][((x - 38) + Bullet_Length) / MapBlock_Length] <= 9)){
			MapBlockRecordY = ((y - 15) + 1) / MapBlock_Length;
			MapBlockRecordX = ((x - 38) + Bullet_Length) / MapBlock_Length;
			return false;
		}
		else if (x > 441
			|| (Wall->map[((y - 15) + Bullet_Length - 1) / MapBlock_Length][((x - 38) + Bullet_Length) / MapBlock_Length] >= 4
			&& Wall->map[((y - 15) + Bullet_Length - 1) / MapBlock_Length][((x - 38) + Bullet_Length) / MapBlock_Length] <= 9)){
			MapBlockRecordY = ((y - 15) + Bullet_Length - 1) / MapBlock_Length;
			MapBlockRecordX = ((x - 38) + Bullet_Length) / MapBlock_Length;
			return false;
		}
	}
	else if (d == 4){
		if (x < 38
			|| (Wall->map[((y - 15) + 1) / MapBlock_Length][(x - 38) / MapBlock_Length] >= 4
			&& Wall->map[((y - 15) + 1) / MapBlock_Length][(x - 38) / MapBlock_Length] <= 9)){
			MapBlockRecordY = ((y - 15) + 1) / MapBlock_Length;
			MapBlockRecordX = (x - 38) / MapBlock_Length;
			return false;
		}
		else if (x < 38
			|| (Wall->map[((y - 15) + Bullet_Length - 1) / MapBlock_Length][(x - 38) / MapBlock_Length] >= 4
			&& Wall->map[((y - 15) + Bullet_Length - 1) / MapBlock_Length][(x - 38) / MapBlock_Length] <= 9)){
			MapBlockRecordY = ((y - 15) + Bullet_Length - 1) / MapBlock_Length;
			MapBlockRecordX = (x - 38) / MapBlock_Length;
			return false;
		}
	}
	return true;
}
//���ϰ�·�ľ�����㣬����ֵΪ��ǰλ�ã�����ֵΪ����
int CTankView::LenthToCollision(CPoint PositionNow, int direction) {
	int i;
	if (direction == 1) {//������
		for (i = PositionNow.y; i >= 15; --i) {
			//26��30Ϊ�з�̹�˵Ŀ�͸ߣ������ò������ô�Ҳû��Ҫ��
			if (!CollisionDetectionForTank(PositionNow.x, i, 26, 30, 1))
				return PositionNow.y - i;
		}
		return i - PositionNow.y;
	}
	else if (direction == 2) {//������
		for (i = PositionNow.y; i <= 446; ++i) {
			if (!CollisionDetectionForTank(PositionNow.x, i, 26, 30, 2))
				return i - PositionNow.y;
		}
		return i - PositionNow.y;
	}
	else if (direction == 3) {//������
		for (i = PositionNow.x; i <= 476; ++i) {
			if (!CollisionDetectionForTank(i, PositionNow.y, 26, 30, 3))
				return i - PositionNow.x; 
		}
		return i - PositionNow.x;
	}
	else if (direction == 4) {//������
		for (i = PositionNow.x; i >= 20; --i) {
			if (!CollisionDetectionForTank(i, PositionNow.y, 26, 30, 4)) {
				return PositionNow.x - i;
			}	
		}
		return PositionNow.x - i;
	}
}
void CTankView::GenerateEnemy() {
	if (EnemyPosition == 1) {
		if (((rand() % 51) + 50) > 90)
			m_ObjList[enEnemy].AddTail(new CEnemy(38, 17, 1));
		else m_ObjList[enEnemy].AddTail(new CEnemy(38, 17, 0));
		EnemyPosition = 2;
	}
	else if (EnemyPosition == 2) {
		if (((rand() % 51) + 50) > 90)
			m_ObjList[enEnemy].AddTail(new CEnemy(233, 17, 1));
		else m_ObjList[enEnemy].AddTail(new CEnemy(233, 17, 0));
		EnemyPosition = 3;
	}
	else if (EnemyPosition == 3) {
		if (((rand() % 51) + 50) > 90)
			m_ObjList[enEnemy].AddTail(new CEnemy(426, 17, 1));
		else m_ObjList[enEnemy].AddTail(new CEnemy(233, 17, 0));
		EnemyPosition = 1;
	}
}
//����ѡ����ô��
int CTankView::WhereToGo(CEnemy* pEnemy){
	int direction = (rand() % 4) + 1;
	int len = LenthToCollision(CPoint(pEnemy->m_ptPos.x, pEnemy->m_ptPos.y), direction);
	if (len >= 5) {
		return direction;
	}
	else WhereToGo(pEnemy);
}
void CTankView::UpdateFrame(CDC* MemDC)
{
	//���ƿ�ʼ����
	if (IsStarted == 0) {
		CRect rect;
		GetClientRect(&rect);
		UI->DrawStartUI(MemDC, IDB_STARTUI, rect);
	}
	//���س����������
	if (GetKey(VK_RETURN) == 1)
		IsStarted = 1;
	if (IsStarted == 1 && IsDrawStage == 1){
		
		CPaintDC dc(this);//���ڻ����ļ�������
		CRect rect;
		CDC *cDC = this->GetDC();//��õ�ǰ���ڵ�DC
		GetClientRect(&rect);//��ô��ڵĳߴ�
		CDC m_bgcDC;//������ʾ�豸����
		m_bgcDC.CreateCompatibleDC(NULL);//��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
		CBitmap m_bgBitmap;// ����λͼ����
		m_bgBitmap.LoadBitmap(IDB_BITMAP1);
		m_bgcDC.SelectObject(&m_bgBitmap);
		//��ȡ���ڴ�С  
		GetClientRect(&rect);
		//��������DC  
		m_cacheDC.CreateCompatibleDC(NULL);
		m_cacheCBitmap.CreateCompatibleBitmap(cDC, rect.Width(), rect.Height());
		m_cacheDC.SelectObject(&m_cacheCBitmap);
		MemDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_bgcDC, 0, y, SRCCOPY);//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ

		//�ڻ�����ͼ��,ʹ��������Ч  
		ValidateRect(&rect);
		//��ͼ��ɺ������ 
		//�ͷŻ���DC  
		m_cacheDC.DeleteDC();
		//�ͷŶ���  
		m_cacheCBitmap.DeleteObject();
		//�ͷŴ���DC  
		ReleaseDC(cDC);

		//����̹������ֵ
		UI->DrawTankLife(MemeoryDC, FALSE, Player1_Life);
		//���Ƶ�������
		UI->DrawEnemyNum(MemeoryDC, FALSE, EnemyNum);
		//���Ƴ�ɭ��֮��ĵ�ͼ
		if (Wall != NULL){
			Wall->Draw(MemeoryDC, FALSE);
		}

		//����Player1̹��
		if (Player1 != NULL){
			if (IsStarted == 1 && Player1_Life != 0){
				Player1->Draw(MemeoryDC, FALSE);
			}
		}
		else{
			if (Player1_Life != 0){
				Player1 = new CMyTank1;
				Player1->Draw(MemeoryDC, FALSE);
			}
			else{
				Player1 = new CMyTank1;
			}
		}

		//����Player2̹��
		if (PlayerNum == 2) {
			if (Player2 != NULL) {
				if (IsStarted == 1) {
					Player2->Draw(MemeoryDC, FALSE);
				}
				if (Wall->map[0][12] == 0) {
					//IsGameOver = 1;
					CString str = _T("Game Over!\nPlayer1 win!!!");
					MemDC->SetBkMode(TRANSPARENT);
					MemDC->SetTextAlign(TA_CENTER);
					MemDC->SetTextColor(RGB(0, 0, 0));
					MemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
				}
			}
			else {
				if (Player2_Life == 0) {
					//IsGameOver = 1;
				}
				else {
					Player2 = new CMyTank2;
					Player2->Draw(MemeoryDC, FALSE);
				}
			}
		}

		//���� ��������ը���з�̹�ˡ��ӵ�
		if (IsStarted == 1){
			for (int i = 0; i < 15; i++){
				POSITION pos1, pos2;
				for (pos1 = m_ObjList[i].GetHeadPosition(); (pos2 = pos1) != NULL;){
					CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext(pos1);
					if (!pObj->Draw(MemDC, FALSE)){
						m_ObjList[i].RemoveAt(pos2);
						delete pObj;
					}
				}
			}
		}

		//����ɭ�֣����ں��棬��ʹ�ݵ���ǰ��Ķ����Ϸ�����
		if (Wall != NULL){
			if (IsStarted == 1){
				Wall->DrawForest(MemeoryDC, FALSE);
			}
		}

		//����GameOver
		if (Wall->map[24][12] == 0 || Wall->map[24][13] == 0
			|| Wall->map[25][12] == 0 || Wall->map[25][13] == 0
			|| Player1_Life == 0){
			IsGameOver = 1;
			UI->DrawGameOver(MemeoryDC, FALSE, y1);
			y1 += 1;
		}
	}
	if (StageNum != 0 && UI->Process != 59 && IsStarted == 1) {
		UI->DrawStage(MemeoryDC, FALSE, StageNum);
		if (UI->Process == 58) {
			IsDrawStage = 1;
			//���ƽ��������ɵ���
			GenerateEnemy();
			GenerateEnemy();
			GenerateEnemy();
		}
	}
	//�����ڴ�DC���豸DC
	ClientDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, MemeoryDC, 0, 0, SRCCOPY);
}
void CTankView::AI()
{
	if (Player1 != NULL && IsDrawStage == 1){
		if (Player1 == NULL)
			return;
		if (!IsGameOver){
			//�ƶ�Player1
			if ((GetKey(VK_UP) || GetKey(VK_DOWN)) && Player1->ProcessForCreate == 32){
				if (GetKey(VK_UP)){
					Player1->direction = 1;
					if (CollisionDetectionForTank(Player1->m_ptPos.x, Player1->m_ptPos.y, Player1->MyPlayer1_WIDTH, Player1->MyPlayer1_HEIGHT, Player1->direction)){
						Player1->m_ptPos.y -= Tank_Speed;
					}
				}

				if (GetKey(VK_DOWN)){
					Player1->direction = 2;
					if (CollisionDetectionForTank(Player1->m_ptPos.x, Player1->m_ptPos.y, Player1->MyPlayer1_WIDTH, Player1->MyPlayer1_HEIGHT, Player1->direction)){
						Player1->m_ptPos.y += Tank_Speed;
					}
				}
			}
			else if ((GetKey(VK_RIGHT) || GetKey(VK_LEFT)) && Player1->ProcessForCreate == 32){
				if (GetKey(VK_RIGHT)){
					Player1->direction = 3;
					if (CollisionDetectionForTank(Player1->m_ptPos.x, Player1->m_ptPos.y, Player1->MyPlayer1_WIDTH, Player1->MyPlayer1_HEIGHT, Player1->direction)){
						Player1->m_ptPos.x += Tank_Speed;
					}
				}
				if (GetKey(VK_LEFT)){
					Player1->direction = 4;
					if (CollisionDetectionForTank(Player1->m_ptPos.x, Player1->m_ptPos.y, Player1->MyPlayer1_WIDTH, Player1->MyPlayer1_HEIGHT, Player1->direction)){
						Player1->m_ptPos.x -= Tank_Speed;
					}
				}
			}
			//�ƶ�Player2
			/*::GetKeyState(VK_SHIFT) > 0 û����
			::GetKeyState(VK_SHIFT) < 0������*/
			if (PlayerNum == 2) {
				if (::GetKeyState(87) < 0) {
					//87-->W
					Player2->direction = 1;
					if (CollisionDetectionForTank(Player2->m_ptPos.x, Player2->m_ptPos.y, Player2->Enemy_WIDTH, Player2->Enemy_HEIGHT, Player2->direction)) {
						Player2->m_ptPos.y -= Tank_Speed;
					}
					else {
						char msgbuf[100];
						sprintf_s(msgbuf, "������%d��%d\n", Player2->m_ptPos.x, Player2->m_ptPos.y);
						OutputDebugString(msgbuf);
					}
				}
				if (::GetKeyState(83) < 0) {
					//83-->S
					Player2->direction = 2;
					if (CollisionDetectionForTank(Player2->m_ptPos.x, Player2->m_ptPos.y, Player2->Enemy_WIDTH, Player2->Enemy_HEIGHT, Player2->direction)) {
						Player2->m_ptPos.y += Tank_Speed;
					}
					else {
						char msgbuf[100];
						sprintf_s(msgbuf, "������%d��%d\n", Player2->m_ptPos.x, Player2->m_ptPos.y);
						OutputDebugString(msgbuf);
					}
				}
				if (::GetKeyState(68) < 0) {
					//68-->D
					Player2->direction = 3;
					if (CollisionDetectionForTank(Player2->m_ptPos.x, Player2->m_ptPos.y, Player2->Enemy_WIDTH, Player2->Enemy_HEIGHT, Player2->direction)) {
						Player2->m_ptPos.x += Tank_Speed;
					}
					else {
						char msgbuf[100];
						sprintf_s(msgbuf, "������%d��%d\n", Player2->m_ptPos.x, Player2->m_ptPos.y);
						OutputDebugString(msgbuf);
					}
				}
				if (::GetKeyState(65) < 0) {
					//65-->A
					Player2->direction = 4;
					if (CollisionDetectionForTank(Player2->m_ptPos.x, Player2->m_ptPos.y, Player2->Enemy_WIDTH, Player2->Enemy_HEIGHT, Player2->direction)) {
						Player2->m_ptPos.x -= Tank_Speed;
					}
					else {
						char msgbuf[100];
						sprintf_s(msgbuf, "������%d��%d\n", Player2->m_ptPos.x, Player2->m_ptPos.y);
						OutputDebugString(msgbuf);
					}
				}
			}
		}

		//Enemy���Ѱ·
		POSITION mPos17 = NULL, mPos18 = NULL;
		for (mPos17 = m_ObjList[enEnemy].GetHeadPosition(); (mPos18 = mPos17) != NULL;){
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(mPos17);
			if (pEnemy->IsRouteDone == 0 || pEnemy->IsRouteDone == 2 
				|| !CollisionDetectionForTank(pEnemy->m_ptPos.x, pEnemy->m_ptPos.y, pEnemy->Enemy_WIDTH, pEnemy->Enemy_HEIGHT, pEnemy->direction)
				|| ((rand() % 51) + 50) > 98 ) {
				pEnemy->direction = WhereToGo(pEnemy);
				pEnemy->len = LenthToCollision(CPoint(pEnemy->m_ptPos.x, pEnemy->m_ptPos.y), pEnemy->direction);
				pEnemy->IsRouteDone = 1;
			}
			if (pEnemy->ProcessForCreate == 32){
				if (pEnemy->len > 0) {
					if (CollisionDetectionForTank(pEnemy->m_ptPos.x, pEnemy->m_ptPos.y, pEnemy->Enemy_WIDTH, pEnemy->Enemy_HEIGHT, pEnemy->direction)) {
						pEnemy->direction = pEnemy->direction;
						if (pEnemy->direction == 1)
							pEnemy->m_ptPos.y -= pEnemy->speed;
						else if (pEnemy->direction == 2)
							pEnemy->m_ptPos.y += pEnemy->speed;
						else if (pEnemy->direction == 3)
							pEnemy->m_ptPos.x += pEnemy->speed;
						else if (pEnemy->direction == 4)
							pEnemy->m_ptPos.x -= pEnemy->speed;
						pEnemy->len -= pEnemy->speed;
					}
				}
				else pEnemy->IsRouteDone = 2;
			}
			//Enemy������ӵ�
			if (((rand() % 500) + 500) > 993 && pEnemy->ProcessForCreate == 32) {
				if (pEnemy->direction == 0 || pEnemy->direction == 1)
					m_ObjList[enBullet].AddTail(new CBullet(pEnemy->m_ptPos.x + 13, pEnemy->m_ptPos.y - 1, 1, pEnemy->direction, 1));
				if (pEnemy->direction == 2)
					m_ObjList[enBullet].AddTail(new CBullet(pEnemy->m_ptPos.x + 10, pEnemy->m_ptPos.y + 21, 1, pEnemy->direction, 1));
				if (pEnemy->direction == 3)
					m_ObjList[enBullet].AddTail(new CBullet(pEnemy->m_ptPos.x + 21, pEnemy->m_ptPos.y + 10, 1, pEnemy->direction, 1));
				if (pEnemy->direction == 4)
					m_ObjList[enBullet].AddTail(new CBullet(pEnemy->m_ptPos.x - 3, pEnemy->m_ptPos.y + 10, 1, pEnemy->direction, 1));
			}
		}

		CRect Player1_Rect = Player1->GetRect();//��ȡPlayer1�ľ���

		//�ӵ�ը����ǽ
		POSITION mPos19 = NULL, mPos20 = NULL;
		for (mPos19 = m_ObjList[enBullet].GetHeadPosition(); (mPos20 = mPos19) != NULL;){
			CBullet* pBullet = (CBullet*)m_ObjList[enBullet].GetNext(mPos19);
			if (!CollisionDetectionForBullet(pBullet->m_ptPos.x, pBullet->m_ptPos.y, pBullet->direction)){
				if (Wall->map[MapBlockRecordY][MapBlockRecordX] >= 6 && Wall->map[MapBlockRecordY][MapBlockRecordX] <= 9){
					Wall->map[24][12] = 0;
					Wall->map[24][13] = 0;
					Wall->map[25][12] = 0;
					Wall->map[25][13] = 0;
					//��ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 32, pBullet->m_ptPos.y - 32, 0));
					//ɾ������
					m_ObjList[enBullet].RemoveAt(mPos20);
					delete pBullet;
				}
				else {
					//С��ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 12, pBullet->m_ptPos.y - 12, 1));
					//ɾ������
					m_ObjList[enBullet].RemoveAt(mPos20);
					delete pBullet;
					//�����ǽ
					if (Wall->map[MapBlockRecordY][MapBlockRecordX] == 5)
						Wall->map[MapBlockRecordY][MapBlockRecordX] = 0;
				}
			}
		}

		//�ӵ�ը��Player2
		if (PlayerNum == 2) {
			POSITION mPos1 = NULL, mPos2 = NULL;
			for (mPos1 = m_ObjList[enBullet].GetHeadPosition(); (mPos2 = mPos1) != NULL;){
				CBullet* pBullet = (CBullet*)m_ObjList[enBullet].GetNext(mPos1);
				CRect Bullet_Rect = pBullet->GetRect();//��ȡ�ӵ��ľ���
				CRect Player2_Rect = Player2->GetRect();//��ȡPlayer2�ľ���
				//������������Ƿ��ཻ
				CRect tmpRect;
				if (tmpRect.IntersectRect(&Bullet_Rect, Player2_Rect)){
					//��ӱ�ըЧ��
					//�ӵ���С��ը
 					m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 12, pBullet->m_ptPos.y - 12, 1));
					//̹���ٴ�ը
					m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 32, pBullet->m_ptPos.y - 32, 0));

					//ɾ���ӵ�
					m_ObjList[enBullet].RemoveAt(mPos2);
					delete pBullet;

					//����Player2����ֵ
					Player2_Life -= 1;
				}
				break;
			}
		}

		//�ӵ�ը��Player1
		POSITION mPos15 = NULL, mPos16 = NULL;
		for (mPos15 = m_ObjList[enBullet].GetHeadPosition(); (mPos16 = mPos15) != NULL;){
			CBullet* pBullet = (CBullet*)m_ObjList[enBullet].GetNext(mPos15);
			if (pBullet->from_flag == 1) {
				CRect Bullet_Rect = pBullet->GetRect();//��ȡ�ӵ��ľ���
			    //������������Ƿ��ཻ
				CRect tmpRect;
				if (tmpRect.IntersectRect(&Bullet_Rect, Player1_Rect) && Player1->time == 120) {
					//��ӱ�ըЧ��
					//�ӵ���С��ը
					m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 12, pBullet->m_ptPos.y - 12, 1));
					//̹���ٴ�ը
					m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 32, pBullet->m_ptPos.y - 32, 0));

					//ɾ���ӵ�
					m_ObjList[enBullet].RemoveAt(mPos16);
					delete pBullet;

					//����Player1����ֵ,��ɾ��Player1ʵ��
					//Ҫ����Player1����ֵ��Ϊ��������Ȼ��������ֵʱ�����
					if (Player1_Life > 0) {
						Player1_Life -= 1;
						delete Player1;
						Player1 = NULL;
						break;
					}
				}
			}
		}
		//�ӵ�ը���ӵ�
		//��Ϊ��ͬһ��List������Ƕ��ѭ���������ӵ���ײ�Ļ���ͬʱɾ�������ӵ���������Ҫ�����ˢ��һ��ѭ��������ֵ����Ȼ��Խ��
		POSITION mPos27 = NULL, mPos28 = NULL;
		for (mPos27 = m_ObjList[enBullet].GetHeadPosition(); (mPos28 = mPos27) != NULL;) {
			CBullet* pBullet1 = (CBullet*)m_ObjList[enBullet].GetNext(mPos27);
			CRect Bullet1_Rect = pBullet1->GetRect();//��ȡ�ӵ��ľ���
			POSITION mPos25 = NULL, mPos26 = NULL;
			for (mPos25 = m_ObjList[enBullet].GetHeadPosition(); (mPos26 = mPos25) != NULL;) {
				CBullet* pBullet2 = (CBullet*)m_ObjList[enBullet].GetNext(mPos25);
				CRect Bullet2_Rect = pBullet2->GetRect();
				//������������Ƿ��ཻ
				CRect tmpRect;
				if (tmpRect.IntersectRect(&Bullet1_Rect, Bullet2_Rect)
					&& (pBullet1->from_flag != pBullet2->from_flag)) {
					//ɾ���ӵ�
					m_ObjList[enBullet].RemoveAt(mPos28);
					delete pBullet1;
					m_ObjList[enBullet].RemoveAt(mPos26);
					delete pBullet2;
					mPos27 = m_ObjList[enBullet].GetHeadPosition();
				}
			}
		}
		//�ӵ�ը��Enemy
		POSITION mPos21 = NULL, mPos22 = NULL;
		for (mPos21 = m_ObjList[enBullet].GetHeadPosition(); (mPos22 = mPos21) != NULL;) {
			CBullet* pBullet = (CBullet*)m_ObjList[enBullet].GetNext(mPos21);//���ص�ǰλ�õ����ݣ�֮��λ�ú���һλ
			if (pBullet->from_flag == 0) {
				CRect Bullet_Rect = pBullet->GetRect();//��ȡ�ӵ��ľ���
				POSITION mPos23 = NULL, mPos24 = NULL;
				for (mPos23 = m_ObjList[enEnemy].GetHeadPosition(); (mPos24 = mPos23) != NULL;) {
					CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(mPos23);
					CRect Enemy_Rect = pEnemy->GetRect();
					//������������Ƿ��ཻ
					CRect tmpRect;
					if (tmpRect.IntersectRect(&Bullet_Rect, Enemy_Rect)) {
						//��ӱ�ըЧ��
						//�ӵ���С��ը
						m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 12, pBullet->m_ptPos.y - 12, 1));
						//�����ٴ�ը
						m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 32, pBullet->m_ptPos.y - 32, 0));
						//ɾ���ӵ�
						m_ObjList[enBullet].RemoveAt(mPos22);
						delete pBullet; 
						mPos21 = m_ObjList[enBullet].GetHeadPosition();
						mPos22 = mPos21;
						//ɾ�����˲���������һ������,����������һ,��������Ϊ0ʱ������һ��
						m_ObjList[enEnemy].RemoveAt(mPos24);
						delete pEnemy;
						GenerateEnemy();
						EnemyNum--;
						if (EnemyNum == 0) {
							EnemyNum = 20;
							m_ObjList[enBullet].RemoveAll();
							m_ObjList[enEnemy].RemoveAll();
							StageNum++;
							if (StageNum == 3)
								StageNum = 1;
							delete Player1;
							Player1 = NULL;
							Wall->LoadMap(StageNum);
							MapBlockRecordY = 26;
							MapBlockRecordX = 26;
							Player1_Life = 3;
							IsDrawStage = 0;
							UI->Process = 0;
							break;
						}
						break;
						break;
					}
				}
			}
			break;
		}
	}
}
void CTankView::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent){
	case 1:
		//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
		UpdateFrame(MemeoryDC);
		//IsStartedΪ1ʱ��ʼ��Ϸ
		if (IsStarted == 1){
			AI();
		}
		break;
	}
	CView::OnTimer(nIDEvent);
}
void CTankView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!IsGameOver){
		switch (nChar) {
		case VK_SPACE:
			if (Player1 != NULL && Player1->ProcessForCreate == 32){
				CPoint pt = Player1->GetPoint();
				if (Player1_Flag == 0){
					//Ϊ��ʹ�ӵ�һ��ʼ�����ʱ����̹����ײ����Ҫ�Բ�ͬ��������ӵ���λ�ý��е���
					if (Player1->direction == 0 || Player1->direction == 1)
						m_ObjList[enBullet].AddTail(new CBullet(pt.x + 10, pt.y - 3, 1, Player1->direction, 0));
					if (Player1->direction == 2)
						m_ObjList[enBullet].AddTail(new CBullet(pt.x + 10, pt.y + 21, 1, Player1->direction, 0));
					if (Player1->direction == 3)
						m_ObjList[enBullet].AddTail(new CBullet(pt.x + 21, pt.y + 10, 1, Player1->direction, 0));
					if (Player1->direction == 4)
						m_ObjList[enBullet].AddTail(new CBullet(pt.x - 3, pt.y + 10, 1, Player1->direction, 0));
				}
			}
			break;
		case 70:
			if (PlayerNum == 2)
				if (Player2 != NULL && Player2->Fired()){
					CPoint pt2 = Player2->GetPoint();
					if (Player2_Flag == 0){
						if (Player2->direction == 0 || Player2->direction == 1)
							m_ObjList[enBullet].AddTail(new CBullet(pt2.x + 13, pt2.y - 1, 1, Player2->direction, 1));
						if (Player2->direction == 2)
							m_ObjList[enBullet].AddTail(new CBullet(pt2.x + 10, pt2.y + 21, 1, Player2->direction, 1));
						if (Player2->direction == 3)
							m_ObjList[enBullet].AddTail(new CBullet(pt2.x + 21, pt2.y + 10, 1, Player2->direction, 1));
						if (Player2->direction == 4)
							m_ObjList[enBullet].AddTail(new CBullet(pt2.x - 3, pt2.y + 10, 1, Player2->direction, 1));
					}
				}
			break;
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

}