
// DesgloseIEPSDlg.cpp: archivo de implementación
//

#include "pch.h"
#include "framework.h"
#include "DesgloseIEPS.h"
#include "DesgloseIEPSDlg.h"
#include "afxdialogex.h"
#include "Combust.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cuadro de diálogo de CDesgloseIEPSDlg



CDesgloseIEPSDlg::CDesgloseIEPSDlg(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_DESGLOSEIEPS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDesgloseIEPSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDesgloseIEPSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED( IDC_DESGLOSAR, &CDesgloseIEPSDlg::OnBnClickedDesglosar )
END_MESSAGE_MAP()


// Controladores de mensajes de CDesgloseIEPSDlg

BOOL CDesgloseIEPSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de diálogo.  El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// TODO: agregar aquí inicialización adicional
	SetDlgItemText( IDC_STATICRESULT, "" );
	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CDesgloseIEPSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CDesgloseIEPSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CDesgloseIEPSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDesgloseIEPSDlg::OnBnClickedDesglosar()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	CString litros;
	CString importe;
	CString flete;
	CString iva;
	CString retencion;

	GetDlgItemText( IDC_EDIT1, importe );
	GetDlgItemText( IDC_EDIT2, litros );
	GetDlgItemText( IDC_EDIT3, flete );
	GetDlgItemText( IDC_EDIT4, iva );
	GetDlgItemText( IDC_EDIT5, retencion );

	if ( importe.IsEmpty() || litros.IsEmpty() || flete.IsEmpty() || 
		iva.IsEmpty() || retencion.IsEmpty() )
	{
		MessageBox( "Llene primero todos los datos!.", "Atencion", MB_ICONASTERISK );
		GetDlgItem( IDC_EDIT1 )->SetFocus();

		return;
	}

	Combust combust( atof( litros ), atof( importe ), atof( flete ),
		atof( iva ), atof( retencion ) );

	CString precioUnitario;
	precioUnitario.Format( "%.*f", 4, combust.PrecioRealUnit() );

	CString iepsCosto;
	iepsCosto.Format( "%.*f", 4, combust.Ieps() );

	CString total;
	total.Format( "%.*f", 4, combust.Total() );

	CString resultado = "Precio real unitario: $ " + precioUnitario +
		"\nIEPS: $ " + iepsCosto +
		"\nTOTAL: $ " + total;

	SetDlgItemText( IDC_STATICRESULT, resultado );
}
