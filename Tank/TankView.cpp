// TankView.cpp : CTankView 类的实现
//

#include "stdafx.h"
#include "Tank.h"
#include "resource.h"
#include <mmsystem.h>
#include <ctime>//初始化随机数种子里用到time函数

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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CTankView 构造/析构
CTankView::CTankView() :Player1(NULL)
{
	// TODO: 在此处添加构造代码

}

CTankView::~CTankView()
{
}

BOOL CTankView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTankView 绘制
void CTankView::OnDraw(CDC* /*pDC*/)
{
	//播放背景音乐
	//PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_ASYNC | SND_RESOURCE | SND_NODEFAULT | SND_LOOP);
	CTankDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

// CTankView 打印

BOOL CTankView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTankView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTankView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CTankView 诊断

#ifdef _DEBUG
void CTankView::AssertValid() const
{
	CView::AssertValid();
}

void CTankView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTankDoc* CTankView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTankDoc)));
	return (CTankDoc*)m_pDocument;
}
#endif //_DEBUG

// CTankView 消息处理程序
void CTankView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
	InitGame();
}
BOOL CTankView::InitGame()
{
	a = 5;
	CRect rc;
	GetClientRect(rc);

	//产生随机数种子
	srand((unsigned)time(NULL));

	//建立设备DC
	ClientDC = new CClientDC(this);

	//建立内存DC
	MemeoryDC = new CDC;
	MemeoryDC->CreateCompatibleDC(ClientDC);

	//建立内存位图
	MemeoryBitmap = new CBitmap;
	MemeoryBitmap->CreateCompatibleBitmap(ClientDC, GAME_WIDTH, GAME_HEIGHT);

	//将位图选入内存DC
	MemeoryDC->SelectObject(MemeoryBitmap);

	CMyTank1::LoadImage();
	CMyTank2::LoadImage();
	CEnemy::LoadImage();
	CBullet::LoadImage();
	CExplosion::LoadImage();
	CWall::LoadImage();
	CUI::LoadImage();

	//生成UI对象
	UI = new CUI;
	UI->Process = 0;

	//生成墙对象
	Wall = new CWall;
	Wall->LoadMap(StageNum);
	MapBlockRecordY = 26;
	MapBlockRecordX = 26;

	//产生主角(坦克)
	Player1 = new CMyTank1;
	if(PlayerNum == 2)
		Player2 = new CMyTank2;
	EnemyNum = 20;
	Player1_Life = 3;


	//刷新窗口的计时器
	/*1是计时器标识；30是时间间隔，单位是毫秒；
	第三个参数是一个回调函数，在这个函数里，放入你想要做的事情的代码，
	你可以将它设定为NULL，也就是使用系统默认的回调函数，系统默认认的是onTime函数。*/
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
//面向坦克的碰撞检测模块
BOOL CTankView::CollisionDetectionForTank(int x, int y, int TANK_WIDTH, int TANK_HEIGHT, int d) {
	//0：空地；1：草地 2：冰块 3：河 4：铁墙 5：土墙 6：老家
	//每一个碰撞的水平面都往中间缩了一个像素做碰撞检测,使坦克能擦着地图块过去
	//因为坦克比地图块宽，所以在坦克中间也要做碰撞检测
	//先检测坦克加上步长后会不会碰撞，如果会就false
	//因为外面加了个框，所以要把那个框造成的位置偏移加上（38，15）
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
//面向子弹的碰撞检测模块
BOOL CTankView::CollisionDetectionForBullet(int x, int y, int d) {
	//0：空地；1：草地 2：冰块 3：河 4：铁墙 5：土墙 6：老家
	//每一个碰撞的水平面加了1、7两个位置的碰撞检测,使子弹能擦着地图块过去
	//检测到碰撞后把撞到的地图块的坐标改了
	//子弹的碰撞没有先加上步长，是为了避免隔山打牛的情况
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
//离障碍路的距离计算，传入值为当前位置，返回值为距离
int CTankView::LenthToCollision(CPoint PositionNow, int direction) {
	int i;
	if (direction == 1) {//往上走
		for (i = PositionNow.y; i >= 15; --i) {
			//26和30为敌方坦克的宽和高，这里用参数不好传也没必要传
			if (!CollisionDetectionForTank(PositionNow.x, i, 26, 30, 1))
				return PositionNow.y - i;
		}
		return i - PositionNow.y;
	}
	else if (direction == 2) {//往下走
		for (i = PositionNow.y; i <= 446; ++i) {
			if (!CollisionDetectionForTank(PositionNow.x, i, 26, 30, 2))
				return i - PositionNow.y;
		}
		return i - PositionNow.y;
	}
	else if (direction == 3) {//往右走
		for (i = PositionNow.x; i <= 476; ++i) {
			if (!CollisionDetectionForTank(i, PositionNow.y, 26, 30, 3))
				return i - PositionNow.x; 
		}
		return i - PositionNow.x;
	}
	else if (direction == 4) {//往左走
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
//敌人选择怎么走
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
	//绘制开始界面
	if (IsStarted == 0) {
		CRect rect;
		GetClientRect(&rect);
		UI->DrawStartUI(MemDC, IDB_STARTUI, rect);
	}
	//按回车键绘制天空
	if (GetKey(VK_RETURN) == 1)
		IsStarted = 1;
	if (IsStarted == 1 && IsDrawStage == 1){
		
		CPaintDC dc(this);//用于绘制文件上下文
		CRect rect;
		CDC *cDC = this->GetDC();//获得当前窗口的DC
		GetClientRect(&rect);//获得窗口的尺寸
		CDC m_bgcDC;//定义显示设备对象
		m_bgcDC.CreateCompatibleDC(NULL);//建立与屏幕显示兼容的内存显示设备
		CBitmap m_bgBitmap;// 定义位图对象
		m_bgBitmap.LoadBitmap(IDB_BITMAP1);
		m_bgcDC.SelectObject(&m_bgBitmap);
		//获取窗口大小  
		GetClientRect(&rect);
		//创建缓冲DC  
		m_cacheDC.CreateCompatibleDC(NULL);
		m_cacheCBitmap.CreateCompatibleBitmap(cDC, rect.Width(), rect.Height());
		m_cacheDC.SelectObject(&m_cacheCBitmap);
		MemDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_bgcDC, 0, y, SRCCOPY);//将内存中的图拷贝到屏幕上进行显示

		//在绘制完图后,使窗口区有效  
		ValidateRect(&rect);
		//绘图完成后的清理 
		//释放缓冲DC  
		m_cacheDC.DeleteDC();
		//释放对象  
		m_cacheCBitmap.DeleteObject();
		//释放窗口DC  
		ReleaseDC(cDC);

		//绘制坦克生命值
		UI->DrawTankLife(MemeoryDC, FALSE, Player1_Life);
		//绘制敌人数量
		UI->DrawEnemyNum(MemeoryDC, FALSE, EnemyNum);
		//绘制除森林之外的地图
		if (Wall != NULL){
			Wall->Draw(MemeoryDC, FALSE);
		}

		//绘制Player1坦克
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

		//绘制Player2坦克
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

		//绘制 导弹、爆炸、敌方坦克、子弹
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

		//绘制森林，放在后面，能使草地在前面的对象上方绘制
		if (Wall != NULL){
			if (IsStarted == 1){
				Wall->DrawForest(MemeoryDC, FALSE);
			}
		}

		//绘制GameOver
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
			//绘制结束后生成敌人
			GenerateEnemy();
			GenerateEnemy();
			GenerateEnemy();
		}
	}
	//复制内存DC到设备DC
	ClientDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, MemeoryDC, 0, 0, SRCCOPY);
}
void CTankView::AI()
{
	if (Player1 != NULL && IsDrawStage == 1){
		if (Player1 == NULL)
			return;
		if (!IsGameOver){
			//移动Player1
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
			//移动Player2
			/*::GetKeyState(VK_SHIFT) > 0 没按下
			::GetKeyState(VK_SHIFT) < 0被按下*/
			if (PlayerNum == 2) {
				if (::GetKeyState(87) < 0) {
					//87-->W
					Player2->direction = 1;
					if (CollisionDetectionForTank(Player2->m_ptPos.x, Player2->m_ptPos.y, Player2->Enemy_WIDTH, Player2->Enemy_HEIGHT, Player2->direction)) {
						Player2->m_ptPos.y -= Tank_Speed;
					}
					else {
						char msgbuf[100];
						sprintf_s(msgbuf, "坐标是%d，%d\n", Player2->m_ptPos.x, Player2->m_ptPos.y);
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
						sprintf_s(msgbuf, "坐标是%d，%d\n", Player2->m_ptPos.x, Player2->m_ptPos.y);
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
						sprintf_s(msgbuf, "坐标是%d，%d\n", Player2->m_ptPos.x, Player2->m_ptPos.y);
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
						sprintf_s(msgbuf, "坐标是%d，%d\n", Player2->m_ptPos.x, Player2->m_ptPos.y);
						OutputDebugString(msgbuf);
					}
				}
			}
		}

		//Enemy随机寻路
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
			//Enemy随机发子弹
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

		CRect Player1_Rect = Player1->GetRect();//获取Player1的矩形

		//子弹炸掉土墙
		POSITION mPos19 = NULL, mPos20 = NULL;
		for (mPos19 = m_ObjList[enBullet].GetHeadPosition(); (mPos20 = mPos19) != NULL;){
			CBullet* pBullet = (CBullet*)m_ObjList[enBullet].GetNext(mPos19);
			if (!CollisionDetectionForBullet(pBullet->m_ptPos.x, pBullet->m_ptPos.y, pBullet->direction)){
				if (Wall->map[MapBlockRecordY][MapBlockRecordX] >= 6 && Wall->map[MapBlockRecordY][MapBlockRecordX] <= 9){
					Wall->map[24][12] = 0;
					Wall->map[24][13] = 0;
					Wall->map[25][12] = 0;
					Wall->map[25][13] = 0;
					//大爆炸效果
					m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 32, pBullet->m_ptPos.y - 32, 0));
					//删除导弹
					m_ObjList[enBullet].RemoveAt(mPos20);
					delete pBullet;
				}
				else {
					//小爆炸效果
					m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 12, pBullet->m_ptPos.y - 12, 1));
					//删除导弹
					m_ObjList[enBullet].RemoveAt(mPos20);
					delete pBullet;
					//清除土墙
					if (Wall->map[MapBlockRecordY][MapBlockRecordX] == 5)
						Wall->map[MapBlockRecordY][MapBlockRecordX] = 0;
				}
			}
		}

		//子弹炸掉Player2
		if (PlayerNum == 2) {
			POSITION mPos1 = NULL, mPos2 = NULL;
			for (mPos1 = m_ObjList[enBullet].GetHeadPosition(); (mPos2 = mPos1) != NULL;){
				CBullet* pBullet = (CBullet*)m_ObjList[enBullet].GetNext(mPos1);
				CRect Bullet_Rect = pBullet->GetRect();//获取子弹的矩形
				CRect Player2_Rect = Player2->GetRect();//获取Player2的矩形
				//检测两个矩形是否相交
				CRect tmpRect;
				if (tmpRect.IntersectRect(&Bullet_Rect, Player2_Rect)){
					//添加爆炸效果
					//子弹先小爆炸
 					m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 12, pBullet->m_ptPos.y - 12, 1));
					//坦克再大爆炸
					m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 32, pBullet->m_ptPos.y - 32, 0));

					//删除子弹
					m_ObjList[enBullet].RemoveAt(mPos2);
					delete pBullet;

					//减少Player2生命值
					Player2_Life -= 1;
				}
				break;
			}
		}

		//子弹炸掉Player1
		POSITION mPos15 = NULL, mPos16 = NULL;
		for (mPos15 = m_ObjList[enBullet].GetHeadPosition(); (mPos16 = mPos15) != NULL;){
			CBullet* pBullet = (CBullet*)m_ObjList[enBullet].GetNext(mPos15);
			if (pBullet->from_flag == 1) {
				CRect Bullet_Rect = pBullet->GetRect();//获取子弹的矩形
			    //检测两个矩形是否相交
				CRect tmpRect;
				if (tmpRect.IntersectRect(&Bullet_Rect, Player1_Rect) && Player1->time == 120) {
					//添加爆炸效果
					//子弹先小爆炸
					m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 12, pBullet->m_ptPos.y - 12, 1));
					//坦克再大爆炸
					m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 32, pBullet->m_ptPos.y - 32, 0));

					//删除子弹
					m_ObjList[enBullet].RemoveAt(mPos16);
					delete pBullet;

					//减少Player1生命值,并删除Player1实例
					//要避免Player1生命值变为负数，不然绘制生命值时会出错
					if (Player1_Life > 0) {
						Player1_Life -= 1;
						delete Player1;
						Player1 = NULL;
						break;
					}
				}
			}
		}
		//子弹炸掉子弹
		//因为对同一个List进行了嵌套循环，而且子弹相撞的话会同时删掉两个子弹，所以需要在最后刷新一下循环变量的值，不然会越界
		POSITION mPos27 = NULL, mPos28 = NULL;
		for (mPos27 = m_ObjList[enBullet].GetHeadPosition(); (mPos28 = mPos27) != NULL;) {
			CBullet* pBullet1 = (CBullet*)m_ObjList[enBullet].GetNext(mPos27);
			CRect Bullet1_Rect = pBullet1->GetRect();//获取子弹的矩形
			POSITION mPos25 = NULL, mPos26 = NULL;
			for (mPos25 = m_ObjList[enBullet].GetHeadPosition(); (mPos26 = mPos25) != NULL;) {
				CBullet* pBullet2 = (CBullet*)m_ObjList[enBullet].GetNext(mPos25);
				CRect Bullet2_Rect = pBullet2->GetRect();
				//检测两个矩形是否相交
				CRect tmpRect;
				if (tmpRect.IntersectRect(&Bullet1_Rect, Bullet2_Rect)
					&& (pBullet1->from_flag != pBullet2->from_flag)) {
					//删除子弹
					m_ObjList[enBullet].RemoveAt(mPos28);
					delete pBullet1;
					m_ObjList[enBullet].RemoveAt(mPos26);
					delete pBullet2;
					mPos27 = m_ObjList[enBullet].GetHeadPosition();
				}
			}
		}
		//子弹炸掉Enemy
		POSITION mPos21 = NULL, mPos22 = NULL;
		for (mPos21 = m_ObjList[enBullet].GetHeadPosition(); (mPos22 = mPos21) != NULL;) {
			CBullet* pBullet = (CBullet*)m_ObjList[enBullet].GetNext(mPos21);//返回当前位置的数据，之后位置后移一位
			if (pBullet->from_flag == 0) {
				CRect Bullet_Rect = pBullet->GetRect();//获取子弹的矩形
				POSITION mPos23 = NULL, mPos24 = NULL;
				for (mPos23 = m_ObjList[enEnemy].GetHeadPosition(); (mPos24 = mPos23) != NULL;) {
					CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(mPos23);
					CRect Enemy_Rect = pEnemy->GetRect();
					//检测两个矩形是否相交
					CRect tmpRect;
					if (tmpRect.IntersectRect(&Bullet_Rect, Enemy_Rect)) {
						//添加爆炸效果
						//子弹先小爆炸
						m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 12, pBullet->m_ptPos.y - 12, 1));
						//敌人再大爆炸
						m_ObjList[enExplosion].AddTail(new CExplosion(pBullet->m_ptPos.x - 32, pBullet->m_ptPos.y - 32, 0));
						//删除子弹
						m_ObjList[enBullet].RemoveAt(mPos22);
						delete pBullet; 
						mPos21 = m_ObjList[enBullet].GetHeadPosition();
						mPos22 = mPos21;
						//删除敌人并重新生成一个敌人,敌人数量减一,敌人数量为0时进入下一关
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
		//刷新游戏帧画面: 在内存DC上绘图
		UpdateFrame(MemeoryDC);
		//IsStarted为1时开始游戏
		if (IsStarted == 1){
			AI();
		}
		break;
	}
	CView::OnTimer(nIDEvent);
}
void CTankView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!IsGameOver){
		switch (nChar) {
		case VK_SPACE:
			if (Player1 != NULL && Player1->ProcessForCreate == 32){
				CPoint pt = Player1->GetPoint();
				if (Player1_Flag == 0){
					//为了使子弹一开始发射出时不与坦克相撞，需要对不同方向发射的子弹的位置进行调整
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