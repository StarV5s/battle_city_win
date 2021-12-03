// TankDoc.cpp : CTankDoc 类的实现
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


// CTankDoc 构造/析构

CTankDoc::CTankDoc()
{
	// TODO: 在此添加一次性构造代码

}

CTankDoc::~CTankDoc()
{
}

BOOL CTankDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CTankDoc 序列化

void CTankDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CTankDoc 诊断

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


// CTankDoc 命令
