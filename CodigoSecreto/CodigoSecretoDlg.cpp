#include "stdafx.h"
#include "CodigoSecreto.h"
#include "CodigoSecretoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_TIEMPO WM_USER+80

CCodigoSecretoDlg::CCodigoSecretoDlg(CWnd* pParent)
: CDialogEx(IDD_CODIGOSECRETO_DIALOG, pParent),m_digitos(6),m_intentos(0),m_tiempo(_T("")),m_primero(true),m_saltar(false)
{
	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for(int i=0;i<MAX_CODIGO;i++)
	{
		m_numero_actual[i]=0;
		m_numero_anterior[i]=0;
	}
	for(int i=0;i<10;i++)
		m_posibles[i]=i;
}

void CCodigoSecretoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_COMPROBAR,m_comprobar);
	DDX_Text(pDX,IDC_TIEMPO,m_tiempo);
}

BEGIN_MESSAGE_MAP(CCodigoSecretoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK,&CCodigoSecretoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL,&CCodigoSecretoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SALIR,&CCodigoSecretoDlg::OnBnClickedSalir)
	ON_BN_CLICKED(IDC_COMPROBAR,&CCodigoSecretoDlg::OnBnClickedComprobar)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_NUEVA_PARTIDA,&CCodigoSecretoDlg::OnBnClickedNuevaPartida)
	ON_BN_CLICKED(IDC_VER_CODIGO,&CCodigoSecretoDlg::OnBnClickedVerCodigo)
	ON_MESSAGE(WM_CHECADO,OnChecado)
	ON_MESSAGE(WM_BORRAR,OnBorrar)
	ON_MESSAGE(WM_MCLICK,OnMClick)
	ON_COMMAND_RANGE(IDC_DIGITO1,IDC_DIGITO6,OnBnClickedDigito)
	ON_NOTIFY(NM_RCLICK,IDC_DIGITO1,&CCodigoSecretoDlg::OnBnRClickedDigito)
	ON_NOTIFY(NM_RCLICK,IDC_DIGITO2,&CCodigoSecretoDlg::OnBnRClickedDigito)
	ON_NOTIFY(NM_RCLICK,IDC_DIGITO3,&CCodigoSecretoDlg::OnBnRClickedDigito)
	ON_NOTIFY(NM_RCLICK,IDC_DIGITO4,&CCodigoSecretoDlg::OnBnRClickedDigito)
	ON_NOTIFY(NM_RCLICK,IDC_DIGITO5,&CCodigoSecretoDlg::OnBnRClickedDigito)
	ON_NOTIFY(NM_RCLICK,IDC_DIGITO6,&CCodigoSecretoDlg::OnBnRClickedDigito)
	ON_BN_CLICKED(IDC_SALTAR,&CCodigoSecretoDlg::OnBnClickedSaltar)
END_MESSAGE_MAP()

BOOL CCodigoSecretoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_digito1.Create(L"-",WS_VISIBLE | BS_OWNERDRAW,CRect(000,0,140,140),this,IDC_DIGITO1);
	m_digito2.Create(L"-",WS_VISIBLE | BS_OWNERDRAW,CRect(140,0,280,140),this,IDC_DIGITO2);
	m_digito3.Create(L"-",WS_VISIBLE | BS_OWNERDRAW,CRect(280,0,420,140),this,IDC_DIGITO3);
	m_digito4.Create(L"-",WS_VISIBLE | BS_OWNERDRAW,CRect(420,0,560,140),this,IDC_DIGITO4);
	m_digito5.Create(L"-",WS_VISIBLE | BS_OWNERDRAW,CRect(560,0,700,140),this,IDC_DIGITO5);
	m_digito6.Create(L"-",WS_VISIBLE | BS_OWNERDRAW,CRect(700,0,840,140),this,IDC_DIGITO6);
	DWORD sty=GetClassLong(m_digito1.m_hWnd,GCL_STYLE);
	sty&=(~CS_DBLCLKS);
	SetClassLong(m_digito1.m_hWnd,GCL_STYLE,sty);
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	srand((unsigned)time(NULL));
	GenerarCodigo();
	m_fuente.CreatePointFont(300,L"Verdana");
	m_digito1.SetFont(&m_fuente);
	m_digito2.SetFont(&m_fuente);
	m_digito3.SetFont(&m_fuente);
	m_digito4.SetFont(&m_fuente);
	m_digito5.SetFont(&m_fuente);
	m_digito6.SetFont(&m_fuente);
	CRect re;
	m_digito1.GetWindowRect(&re);
	m_tam=re.Width();
	GetDlgItem(IDC_TIEMPO)->SetFont(&m_fuente);
	return TRUE;
}

void CCodigoSecretoDlg::GenerarCodigo()
{
	bool nums[9]={false,false,false,false,false,false,false,false,false};

	for(int i=0;i<m_digitos;i++)
	{
		int num=rand()%9+1;
		while(nums[num-1])
			num=rand()%9+1;
		m_codigo[i]=num;
		nums[num-1]=true;
		m_numero_anterior[i]=0;
	}
	//m_inicio=CTime::GetCurrentTime();
	m_primero=true;
	SetTimer(WM_TIEMPO,1000,NULL);
}

void CCodigoSecretoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()),0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
		CDialogEx::OnPaint();
}

HCURSOR CCodigoSecretoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCodigoSecretoDlg::OnBnClickedOk()
{
}

void CCodigoSecretoDlg::OnBnClickedCancel()
{
}

void CCodigoSecretoDlg::OnBnClickedSalir()
{
	if(MessageBox(L"¿Realmente quieres salir?",L"Salir",MB_ICONQUESTION | MB_YESNO)==IDYES)
		EndDialog(IDOK);
}

void CCodigoSecretoDlg::CambiarDigito(int pos,CBoton &b,int val)
{
	CString cad=L"1";

	//esto hace que no se muestren los numeros excluidos, se saltan
	if(m_saltar)
		do
		{
			m_numero_actual[pos]=(m_numero_actual[pos]+val)%10;
			if(m_numero_actual[pos]<0)
				m_numero_actual[pos]=9;
		}while(m_posibles[m_numero_actual[pos]]<0);
	else//esto pasa al siguiente numero haya sido excluido o no
	{
		m_numero_actual[pos]=(m_numero_actual[pos]+val)%10;
		if(m_numero_actual[pos]<0)
			m_numero_actual[pos]=9;
	}
	if(m_numero_actual[pos]==0)
		b.SetWindowText(L"-");
	else
	{
		cad.SetAt(0,m_numero_actual[pos]+'0');
		b.SetWindowText(cad);
	}
	if(m_posibles[m_numero_actual[pos]]<0)
		b.Color(0xff);
	else
		b.Color(0);
}

void CCodigoSecretoDlg::OnBnClickedDigito(UINT id)
{
	CBoton *b=(CBoton*)GetDlgItem(id);

	CambiarDigito(id-IDC_DIGITO1,*b);
	b->Invalidate();
	if(m_primero)
	{
		m_primero=false;
		m_inicio=CTime::GetCurrentTime();
	}
}

void CCodigoSecretoDlg::OnBnRClickedDigito(NMHDR *pNotifyStruct,LRESULT *result)
{
	CBoton *b=(CBoton*)GetDlgItem(pNotifyStruct->idFrom);
	
	CambiarDigito(pNotifyStruct->idFrom-IDC_DIGITO1,*b,-1);
	b->Invalidate();
	if(m_primero)
	{
		m_primero=false;
		m_inicio=CTime::GetCurrentTime();
	}
}

void CCodigoSecretoDlg::OnBnClickedComprobar()
{
	int correct=0,present=0,aux;
	CMap<int,int,int,int> puestos;

	for(int i=0;i<m_digitos;i++)
	{
		if(m_numero_actual[i]==m_codigo[i])
		{
			correct++;
			if(!puestos.Lookup(m_numero_actual[i],aux))
				puestos.SetAt(m_numero_actual[i],m_numero_actual[i]);
			else
				present--;
		}
		for(int j=0;j<m_digitos;j++)
			if(m_numero_actual[i]==m_codigo[j] && i!=j && !puestos.Lookup(m_numero_actual[i],aux))
			{
				present++;
				puestos.SetAt(m_numero_actual[i],m_numero_actual[i]);
			}
	}
	for(int i=0;i<m_digitos;i++)
	{
		CButton *b=new CBoton();
		CString num=L"-";

		if(m_numero_actual[i]>0)
			num.Format(L"%d",m_numero_actual[i]);
		m_numero_anterior[i]=m_numero_actual[i];
		b->Create(num,BS_FLAT,CRect(i*m_tam,m_tam*m_intentos,(i+1)*m_tam,m_tam*(m_intentos+1)),this,0);
		b->EnableWindow(FALSE);
		b->ShowWindow(SW_SHOW);
		b->SetFont(&m_fuente);
		m_lista.AddTail(b);
	}
	CDibujo *dib=new CDibujo(correct,present);

	dib->Create(L"",0,CRect(m_digitos*m_tam+m_tam/4,m_tam*m_intentos+(m_tam-16)/2,(m_digitos+1)*m_tam,m_tam*(m_intentos+1)),this);
	dib->ShowWindow(SW_SHOW);
	m_lista.AddTail(dib);
	CBoton* ref[MAX_CODIGO]={&m_digito1,&m_digito2,&m_digito3,&m_digito4,&m_digito5,&m_digito6,NULL,NULL,NULL,NULL};

	m_intentos++;
	if(correct==m_digitos)
	{
		CString cad;

		KillTimer(WM_TIEMPO);
		m_comprobar.ShowWindow(SW_HIDE);
		cad.Format(L"Conseguido en %d intentos", m_intentos);
		MessageBox(cad);
		m_intentos = 0;
		GenerarCodigo();
		while(!m_lista.IsEmpty())
		{
			CWnd* s = (CWnd*)m_lista.RemoveHead();
			s->DestroyWindow();
			delete s;
		}
		Invalidate();
		m_comprobar.ShowWindow(SW_SHOW);
		for(int i=0;i<MAX_CODIGO;i++)
		{
			if(ref[i])
				ref[i]->Marcar(0);
		}
		for(int i=0;i<10;i++)
			m_posibles[i]=i;
	}
	for(int i=0;i<MAX_CODIGO;i++)
	{
		if(ref[i] && !ref[i]->Marcada())
			m_numero_actual[i]=0;
	}
	CambiarDigito(0,m_digito1,0);
	CambiarDigito(1,m_digito2,0);
	CambiarDigito(2,m_digito3,0);
	CambiarDigito(3,m_digito4,0);
	CambiarDigito(4,m_digito5,0);
	CambiarDigito(5,m_digito6,0);
	
	m_digito1.SetWindowPos(NULL,0,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
	m_digito2.SetWindowPos(NULL,m_tam,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
	m_digito3.SetWindowPos(NULL,2*m_tam,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
	m_digito4.SetWindowPos(NULL,3*m_tam,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
	m_digito5.SetWindowPos(NULL,4*m_tam,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
	m_digito6.SetWindowPos(NULL,5*m_tam,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
	m_comprobar.SetWindowPos(NULL,6*m_tam+50,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
}

void CCodigoSecretoDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==WM_TIEMPO)
	{
		if(!m_primero)
		{
			CTimeSpan sp=CTime::GetCurrentTime()-m_inicio;

			m_tiempo.Format(L"%02d:%02d",sp.GetMinutes(),sp.GetSeconds());
		}
		else
			m_tiempo.Format(L"00:00");
		UpdateData(FALSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CCodigoSecretoDlg::OnSize(UINT nType,int cx,int cy)
{
	CDialogEx::OnSize(nType,cx,cy);
	CRect re;
	CWnd *t=GetDlgItem(IDC_TIEMPO);
	int cont=10;

	if(t)
	{
		t->GetWindowRect(re);
		t->SetWindowPos(NULL,0,cy-re.Height(),0,0,SWP_NOSIZE |SWP_NOZORDER);
	}
	t=GetDlgItem(IDC_SALIR);
	if(t)
	{
		t->GetWindowRect(re);
		t->SetWindowPos(NULL,cx-re.Width()-cont,cy-re.Height()-5,0,0,SWP_NOSIZE |SWP_NOZORDER);
		cont+=re.Width()+10;
	}
	t=GetDlgItem(IDC_NUEVA_PARTIDA);
	if(t)
	{
		t->GetWindowRect(re);
		t->SetWindowPos(NULL,cx-re.Width()-cont,cy-re.Height()-5,0,0,SWP_NOSIZE |SWP_NOZORDER);
		cont+=re.Width()+10;
	}
	t=GetDlgItem(IDC_VER_CODIGO);
	if(t)
	{
		t->GetWindowRect(re);
		t->SetWindowPos(NULL,cx-re.Width()-cont,cy-re.Height()-5,0,0,SWP_NOSIZE |SWP_NOZORDER);
	}
}

void CCodigoSecretoDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x=1080;
	lpMMI->ptMinTrackSize.y=600;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CCodigoSecretoDlg::OnBnClickedNuevaPartida()
{
	if(MessageBox(L"¿Realmente quieres empezar nueva partida?",L"Nueva partida",MB_ICONQUESTION | MB_YESNO)==IDYES)
	{
		CBoton* ref[MAX_CODIGO]={&m_digito1,&m_digito2,&m_digito3,&m_digito4,&m_digito5,&m_digito6,NULL,NULL,NULL,NULL};

		for(int i=0;i<MAX_CODIGO;i++)
		{
			if (ref[i])
			{
				ref[i]->Marcar(0);
				ref[i]->SetWindowTextW(L"-");
			}
			m_numero_actual[i] = 0;
		}
		for(int i=0;i<10;i++)
			m_posibles[i]=i;
		m_intentos=0;
		GenerarCodigo();
		while(!m_lista.IsEmpty())
		{
			CWnd *s=(CWnd*)m_lista.RemoveHead();
			s->DestroyWindow();
			delete s;
		}
		Invalidate();
		m_digito1.SetWindowPos(NULL,0,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
		m_digito2.SetWindowPos(NULL,m_tam,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
		m_digito3.SetWindowPos(NULL,2*m_tam,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
		m_digito4.SetWindowPos(NULL,3*m_tam,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
		m_digito5.SetWindowPos(NULL,4*m_tam,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
		m_digito6.SetWindowPos(NULL,5*m_tam,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
		m_comprobar.SetWindowPos(NULL,6*m_tam+50,m_tam*m_intentos,0,0,SWP_NOSIZE | SWP_NOZORDER);
		CambiarDigito(0,m_digito1,0);
		CambiarDigito(1,m_digito2,0);
		CambiarDigito(2,m_digito3,0);
		CambiarDigito(3,m_digito4,0);
		CambiarDigito(4,m_digito5,0);
		CambiarDigito(5,m_digito6,0);
	}
}

void CCodigoSecretoDlg::OnBnClickedVerCodigo()
{
	if(MessageBox(L"¿Realmente quieres ver el codigo?",L"Ver codigo",MB_ICONQUESTION | MB_YESNO)==IDYES)
	{
		int num=m_codigo[0];
		for(int i=1;i<m_digitos;i++)
			num=10*num+m_codigo[i];
		CString cad;

		cad.Format(L"%d",num);
		MessageBox(cad);
	}
}

LRESULT CCodigoSecretoDlg::OnChecado(WPARAM wParam, LPARAM lParam)
{
	CString num;
	int posi=(int)wParam-IDC_DIGITO1;

	GetDlgItem((int)wParam)->GetWindowTextW(num);
	if(!num.Compare(L"-"))
	{
		if(m_numero_anterior[posi]<1)
			return 0;
		num.Format(L"%d",m_numero_anterior[posi]);
		m_numero_actual[posi]=m_numero_anterior[posi];
		GetDlgItem((int)wParam)->SetWindowTextW(num);
	}
	return 0;
}

LRESULT CCodigoSecretoDlg::OnBorrar(WPARAM wParam,LPARAM lParam)
{
	int posi=(int)wParam-IDC_DIGITO1;

	m_numero_actual[posi]=0;
	CambiarDigito(posi,*(CBoton*)GetDlgItem((int)wParam),0);
	((CBoton*)GetDlgItem((int)wParam))->Marcar(false);
	return 0;
}

LRESULT CCodigoSecretoDlg::OnMClick(WPARAM wParam,LPARAM lParam)
{
	int posi=(int)wParam-IDC_DIGITO1;

	if(m_posibles[m_numero_actual[posi]]>0)
		m_posibles[m_numero_actual[posi]]=-1;
	else
		m_posibles[m_numero_actual[posi]]=m_numero_actual[posi];
	CambiarDigito(posi,*(CBoton*)GetDlgItem((int)wParam),m_saltar?1:0);
	return 0;
}


void CCodigoSecretoDlg::OnBnClickedSaltar()
{
	m_saltar=!m_saltar;
}
