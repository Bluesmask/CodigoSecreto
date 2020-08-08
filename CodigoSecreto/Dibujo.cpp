#include "stdafx.h"
#include "CodigoSecreto.h"
#include "Dibujo.h"

IMPLEMENT_DYNAMIC(CDibujo, CStatic)

CDibujo::CDibujo(int pos,int nopos)
:m_pos(pos),m_npos(nopos)
{
	m_bmpos=LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_POS));
	m_bmnopos=LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_NOPOS));
}

CDibujo::~CDibujo()
{
}

BEGIN_MESSAGE_MAP(CDibujo, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CDibujo::OnPaint()
{
	CPaintDC dc(this);
	CDC cc;

	cc.CreateCompatibleDC(&dc);
	cc.SelectObject(m_bmnopos);
	for(int i=0;i<m_npos;i++)
		dc.BitBlt(i*16,0,16,16,&cc,0,0,SRCCOPY);
	cc.SelectObject(m_bmpos);
	for(int i=0;i<m_pos;i++)
		dc.BitBlt((i+m_npos)*16,0,16,16,&cc,0,0,SRCCOPY);
}
