// TankDoc.h : CTankDoc ��Ľӿ�
//


#pragma once


class CTankDoc : public CDocument
{
protected: // �������л�����
	CTankDoc();
	DECLARE_DYNCREATE(CTankDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CTankDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


