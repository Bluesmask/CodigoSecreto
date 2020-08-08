
// CodigoSecreto.h: archivo de encabezado principal para la aplicación PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"		// Símbolos principales


// CCodigoSecretoApp:
// Consulte la sección CodigoSecreto.cpp para obtener información sobre la implementación de esta clase
//

class CCodigoSecretoApp : public CWinApp
{
public:
	CCodigoSecretoApp();

// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementación

	DECLARE_MESSAGE_MAP()
};

extern CCodigoSecretoApp theApp;
