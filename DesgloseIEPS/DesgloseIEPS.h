
// DesgloseIEPS.h: archivo de encabezado principal para la aplicación PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// Símbolos principales


// CDesgloseIEPSApp:
// Consulte DesgloseIEPS.cpp para obtener información sobre la implementación de esta clase
//

class CDesgloseIEPSApp : public CWinApp
{
public:
	CDesgloseIEPSApp();

// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementación

	DECLARE_MESSAGE_MAP()
};

extern CDesgloseIEPSApp theApp;
