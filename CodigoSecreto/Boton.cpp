#include "stdafx.h"
#include "CodigoSecreto.h"
#include "Boton.h"

IMPLEMENT_DYNAMIC(CBoton,CButton)

CBoton::CBoton()
:m_color(0)
{
}

CBoton::~CBoton()
{
}

BEGIN_MESSAGE_MAP(CBoton, CButton)
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_ENABLE()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(WM_CHECADO,&CBoton::OnCheck)
	ON_BN_CLICKED(WM_BORRAR,&CBoton::OnBorrar)
	ON_WM_MBUTTONDOWN()
END_MESSAGE_MAP()

void CBoton::OnRButtonUp(UINT nFlags,CPoint point)
{
	NMHDR hdr;

	hdr.code=NM_RCLICK;
	hdr.hwndFrom=GetSafeHwnd();
	hdr.idFrom=GetDlgCtrlID();
	GetParent()->SendMessage(WM_NOTIFY,(WPARAM)hdr.idFrom,(LPARAM)&hdr);
}

BOOL CBoton::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL ret=CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);

	ret=m_check.Create(L"",BS_AUTOCHECKBOX | WS_VISIBLE,CRect(10,2,50,52),this,WM_CHECADO);
	if(ret)
		ret=m_borrar.Create(L"",BS_PUSHBUTTON| WS_VISIBLE,CRect(100,12,123,35),this,WM_BORRAR);
	if(ret)
		m_borrar.SetWindowTextW(L"X");
	return ret;
}

bool CBoton::Marcada()
{
	return m_check.GetCheck();
}

void CBoton::Marcar(bool v)
{
	m_check.SetCheck(v);
}

void CBoton::OnPaint()
{
	CButton::OnPaint();
}

void CBoton::OnEnable(BOOL bEnable)
{
	CButton::OnEnable(bEnable);
	if(!bEnable)
	{
		m_check.ShowWindow(SW_HIDE);
		m_borrar.ShowWindow(SW_HIDE);
	}
}

void CBoton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *dc=CDC::FromHandle(lpDrawItemStruct->hDC);
	CString strText;

	GetWindowText(strText);
	dc->SelectObject(GetStockObject(NULL_BRUSH));
	dc->Rectangle(CRect(lpDrawItemStruct->rcItem));
	dc->SetTextColor(m_color);
	dc->DrawText(strText, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	return;
}

void CBoton::OnCheck()
{
	GetParent()->SendMessage(WM_CHECADO,GetDlgCtrlID(),0);
}

void CBoton::OnBorrar()
{
	GetParent()->SendMessage(WM_BORRAR,GetDlgCtrlID(),0);
}

void CBoton::OnMButtonDown(UINT nFlags,CPoint point)
{
	GetParent()->SendMessage(WM_MCLICK,GetDlgCtrlID(),0);
}

void CBoton::Color(COLORREF c)
{
	m_color=c;
	Invalidate();
}