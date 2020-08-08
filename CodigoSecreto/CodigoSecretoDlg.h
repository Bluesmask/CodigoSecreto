#pragma once
#include "afxwin.h"
#include "Dibujo.h"
#include "Boton.h"

#define MAX_CODIGO 10

class CCodigoSecretoDlg: public CDialogEx
{
public:
	CCodigoSecretoDlg(CWnd* pParent = NULL);
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CODIGOSECRETO_DIALOG };
#endif
protected:
	int m_codigo[MAX_CODIGO],m_digitos,m_intentos,m_tam;
	int m_numero_actual[MAX_CODIGO];
	int m_numero_anterior[MAX_CODIGO];
	virtual void DoDataExchange(CDataExchange* pDX);
	void GenerarCodigo();
	void CambiarDigito(int pos,CBoton &b,int val=1);
	HICON m_hIcon;
	CButton m_comprobar;
	CString m_tiempo;
	CTime m_inicio;
	bool m_primero;
	CFont m_fuente;
	CList<void*,void*> m_lista;
	CBoton m_digito1,m_digito2,m_digito3,m_digito4,m_digito5,m_digito6;
	int m_posibles[10];
	bool m_saltar;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSalir();
	afx_msg void OnBnClickedDigito(UINT nID);
	afx_msg void OnBnRClickedDigito(NMHDR *pNotifyStruct,LRESULT *result);
	afx_msg void OnBnClickedComprobar();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedNuevaPartida();
	afx_msg void OnBnClickedVerCodigo();
	afx_msg LRESULT OnChecado(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnBorrar(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMClick(WPARAM wParam,LPARAM lParam);
public:
	afx_msg void OnBnClickedSaltar();
};
