// TankDoc.cpp : CTankDoc ���ʵ��
//

#include "stdafx.h"
#include "Tank.h"

#include "TankDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTankDoc

IMPLEMENT_DYNCREATE(CTankDoc, CDocument)

BEGIN_MESSAGE_MAP(CTankDoc, CDocument)
END_MESSAGE_MAP()


// CTankDoc ����/����

CTankDoc::CTankDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CTankDoc::~CTankDoc()
{
}

BOOL CTankDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CTankDoc ���л�

void CTankDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CTankDoc ���

#ifdef _DEBUG
void CTankDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTankDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTankDoc ����
