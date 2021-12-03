// TankView.h : CTankView 类的接口
//


#pragma once

class CUI;
class CWall;
class CMyTank1;
class CMyTank2;
class CEnemy;
class CLifeLogo;
class CTankView : public CView
{

	enum ObjType{enEnemy, enBullet, enExplosion};

protected: // 仅从序列化创建
	CTankView();
	DECLARE_DYNCREATE(CTankView)

	// 属性
public:
	CTankDoc* GetDocument() const;

	// 操作
public:

	// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 实现
public:
	virtual ~CTankView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//内存DC
	CDC*        MemeoryDC;
	//设备DC
	CClientDC*  ClientDC;
	//内存位图
	CBitmap*    MemeoryBitmap;


protected:
	//初始化游戏
	BOOL InitGame();
	//结束游戏
	void StopGame();
	//碰撞检测
	BOOL CollisionDetectionForTank(int x, int y, int TANK_WIDTH, int TANK_HEIGHT, int d);
	int CollisionDetectionForBullet(int x, int y, int d);
	//刷新游戏的帧画面
	void UpdateFrame(CDC* MemDC);

	CDC m_cacheDC;//缓冲DC
	CBitmap m_cacheCBitmap;//缓冲位图
	int y = 0;

	//AI模块
	void AI();

	//获得键的状态1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000) ? 1 : 0;
	}



	//坦克对象
	CMyTank1*  Player1;
	CMyTank2*  Player2;

	//墙的对象
	CWall* Wall;

	//UI对象
	CUI* UI;

	CObList    m_ObjList[15];

	//记录受到子弹碰撞的地图块位置
	int MapBlockRecordY;
	int MapBlockRecordX;


	int PlayerScoreNum = 0;
	int Player1_Life = 3;//Player1生命数
	int Player1_Flag = 0;//升级坦克用
	int Player2_Life = 3;//坦克生命数
	int Player2_Flag = 0;//升级坦克用

	int IsStarted = 0;//开始flag
	int IsGameOver = 0;//结束flag
	int IsDrawStage = 0;//关卡动画结束了吗
	int n = 0;
	int y1 = 0;
	int EnemyPosition = 1;//使用EnemyPosition的值确定生成敌人的位置
	int PlayerNum = 2;//玩家数量
	int EnemyNum = 20;//记录敌人的数量，初始值为1
	int StageNum = 1;
	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void GenerateEnemy();//生成敌人
	int LenthToCollision(CPoint PositionNow, int direction);//离障碍路的距离计算，传入值为当前位置和计算的方向，返回值为距离
	int WhereToGo(CEnemy* pEnemy);

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // TankView.cpp 中的调试版本
inline CTankDoc* CTankView::GetDocument() const
{
	return reinterpret_cast<CTankDoc*>(m_pDocument);
}
#endif