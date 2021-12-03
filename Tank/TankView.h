// TankView.h : CTankView ��Ľӿ�
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

protected: // �������л�����
	CTankView();
	DECLARE_DYNCREATE(CTankView)

	// ����
public:
	CTankDoc* GetDocument() const;

	// ����
public:

	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// ʵ��
public:
	virtual ~CTankView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//�ڴ�DC
	CDC*        MemeoryDC;
	//�豸DC
	CClientDC*  ClientDC;
	//�ڴ�λͼ
	CBitmap*    MemeoryBitmap;


protected:
	//��ʼ����Ϸ
	BOOL InitGame();
	//������Ϸ
	void StopGame();
	//��ײ���
	BOOL CollisionDetectionForTank(int x, int y, int TANK_WIDTH, int TANK_HEIGHT, int d);
	int CollisionDetectionForBullet(int x, int y, int d);
	//ˢ����Ϸ��֡����
	void UpdateFrame(CDC* MemDC);

	CDC m_cacheDC;//����DC
	CBitmap m_cacheCBitmap;//����λͼ
	int y = 0;

	//AIģ��
	void AI();

	//��ü���״̬1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000) ? 1 : 0;
	}



	//̹�˶���
	CMyTank1*  Player1;
	CMyTank2*  Player2;

	//ǽ�Ķ���
	CWall* Wall;

	//UI����
	CUI* UI;

	CObList    m_ObjList[15];

	//��¼�ܵ��ӵ���ײ�ĵ�ͼ��λ��
	int MapBlockRecordY;
	int MapBlockRecordX;


	int PlayerScoreNum = 0;
	int Player1_Life = 3;//Player1������
	int Player1_Flag = 0;//����̹����
	int Player2_Life = 3;//̹��������
	int Player2_Flag = 0;//����̹����

	int IsStarted = 0;//��ʼflag
	int IsGameOver = 0;//����flag
	int IsDrawStage = 0;//�ؿ�������������
	int n = 0;
	int y1 = 0;
	int EnemyPosition = 1;//ʹ��EnemyPosition��ֵȷ�����ɵ��˵�λ��
	int PlayerNum = 2;//�������
	int EnemyNum = 20;//��¼���˵���������ʼֵΪ1
	int StageNum = 1;
	// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void GenerateEnemy();//���ɵ���
	int LenthToCollision(CPoint PositionNow, int direction);//���ϰ�·�ľ�����㣬����ֵΪ��ǰλ�úͼ���ķ��򣬷���ֵΪ����
	int WhereToGo(CEnemy* pEnemy);

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // TankView.cpp �еĵ��԰汾
inline CTankDoc* CTankView::GetDocument() const
{
	return reinterpret_cast<CTankDoc*>(m_pDocument);
}
#endif