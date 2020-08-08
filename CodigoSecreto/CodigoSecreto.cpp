#include "stdafx.h"
#include "CodigoSecreto.h"
#include "CodigoSecretoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CCodigoSecretoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CCodigoSecretoApp::CCodigoSecretoApp()
{
}

CCodigoSecretoApp theApp;

BOOL CCodigoSecretoApp::InitInstance()
{
	CWinApp::InitInstance();
	CShellManager *pShellManager = new CShellManager;
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	SetRegistryKey(_T("Aplicaciones generadas con el Asistente para aplicaciones local"));

	CCodigoSecretoDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif
	return FALSE;
}
