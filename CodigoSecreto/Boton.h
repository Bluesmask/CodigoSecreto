#pragma once

#define WM_CHECADO WM_USER+1080
#define WM_BORRAR WM_USER+1081
#define WM_MCLICK WM_USER+1082

class CBoton : public CButton
{
	DECLARE_DYNAMIC(CBoton)
public:
	CBoton();
	virtual ~CBoton();
	bool Marcada();
	void Marcar(bool v);
	void Color(COLORREF c);
	virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
protected:
	DECLARE_MESSAGE_MAP()
	CButton m_check,m_borrar;
	COLORREF m_color;
	afx_msg void OnRButtonUp(UINT nFlags,CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnCheck();
	afx_msg void OnBorrar();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	afx_msg void OnMButtonDown(UINT nFlags,CPoint point);
};


