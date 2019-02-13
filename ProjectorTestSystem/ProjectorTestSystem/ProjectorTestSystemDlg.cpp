
// ProjectorTestSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "ProjectorTestSystemDlg.h"
#include "afxdialogex.h"
#include<afxcmn.h>
#include "AdoDB.h"
#include "AdminiPassDlg.h"
#include "SetIndexDlg.h"
#include "ResizeCtrl.h"

/*״̬��*/
static UINT BASED_CODE indicators[] =
{
	IDS_STATEBAR
};

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*ȫ�ֱ���*/
BOOL ConnectFlag = FALSE;
//BOOL GetOnFlag = FALSE;
CProjectorTestSystemDlg * ProjectorTestSystemDlg;
extern CMainDlg *MainDlg;
extern CPloDlg *PloDlg;
extern CBefroeOldDlg *BrforeOldDlg;
extern COldUpDlg *OldUpDlg;
extern COldDownDlg *OldDownDlg;
extern CAfterOldDlg *AfterOldDlg;
extern CBeforeBrightDlg *BeforeBrightDlg;
extern CFixDlg *FixDlg;
extern CPackDlg *PackDlg;
CWindowSizeMange PJTestSystemDlg;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���MO

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAdminiGetOn();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//ON_COMMAND(ID_32771, &CAboutDlg::OnAdminiGetOn)
END_MESSAGE_MAP()


// CProjectorTestSystemDlg �Ի���



CProjectorTestSystemDlg::CProjectorTestSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProjectorTestSystemDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MYICON);
}

void CProjectorTestSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CProjectorTestSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CProjectorTestSystemDlg::OnTcnSelchangeTab1)
	ON_COMMAND(ID_32771, &CProjectorTestSystemDlg::OnAdminiGetOn)
	ON_COMMAND(ID_32772, &CProjectorTestSystemDlg::OnSetIndex)
	ON_COMMAND(ID_32773, &CProjectorTestSystemDlg::OnLogOut)
	ON_COMMAND(ID_32775, &CProjectorTestSystemDlg::OnExitSystem)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CProjectorTestSystemDlg ��Ϣ�������

BOOL CProjectorTestSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	/*��ȡ�ؼ�ԭʼλ��*/
	PJTestSystemDlg.Init(m_hWnd);

	/*��ȡ���ڴ�С*/
	CRect DlgRect;
	GetClientRect(&DlgRect);     //ȡ�ͻ�����С    
	old.x = DlgRect.right - DlgRect.left;
	old.y = DlgRect.bottom - DlgRect.top;

	/*״̬��*/
	m_StateBar.Create(this);//����״̬��
	m_StateBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT)); //����״̬����Ŀ
	CRect StataBarRect;
	GetClientRect(&StataBarRect);
	m_StateBar.SetPaneInfo(0, IDS_STATEBAR, SBPS_NORMAL, StataBarRect.Width());
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, IDS_STATEBAR);

	/*��ǩҳ*/
	CRect tabRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С   
	m_Tab.InsertItem(0, _T("��ѯ������"),0);  
	m_Tab.InsertItem(1, _T("����������"),1);
	m_Tab.InsertItem(2, _T("�ϻ�ǰ����λ"),2);  
	m_Tab.InsertItem(3, _T("�ϻ����ϼ�ʱ�䣩"),3);
	m_Tab.InsertItem(4, _T("�ϻ����¼�ʱ�䣩"),4);
	m_Tab.InsertItem(5, _T("�ϻ������"),5);
	m_Tab.InsertItem(6, _T("���Ȳ���ǰ"),6);
	m_Tab.InsertItem(7, _T("ά  ��"),7);
	m_Tab.InsertItem(8, _T("��  װ"),8);	
	m_Main.Create(IDD_MAIN, &m_Tab);    // ������һ����ǩҳ   
	m_Plo.Create(IDD_PLO, &m_Tab); // �����ڶ�����ǩҳ
	m_BeforeOld.Create(IDD_BEFOREOLD, &m_Tab);
	m_OldUp.Create(IDD_OLDUP, &m_Tab);
	m_OldDown.Create(IDD_OLDDOWN, &m_Tab);
	m_AfterOld.Create(IDD_AFTEROLD, &m_Tab);
	m_BeforeBright.Create(IDD_BEFOREBRIGHT, &m_Tab);
	m_Fix.Create(IDD_FIX, &m_Tab);
	m_Pack.Create(IDD_PACK, &m_Tab);
	m_Tab.GetClientRect(&tabRect);    // ��ȡ��ǩ�ؼ��ͻ���Rect   
	// ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
	/*tabRect.left += 1;
	tabRect.right -= 1;	
	tabRect.bottom -= 1;*/
	tabRect.top += 25;
	// ���ݵ����õ�tabRect����m_jzmDlg�ӶԻ��򣬲�����Ϊ��ʾ   
	m_Main.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_Plo.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	m_BeforeOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_OldUp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_OldDown.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_AfterOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_BeforeBright.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_Fix.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_Pack.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_Tab.SetCurSel(1);

	ProjectorTestSystemDlg = this;

	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CProjectorTestSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CProjectorTestSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CProjectorTestSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*��ǩҳ��Ӧ*/
void CProjectorTestSystemDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   
	// ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
	m_Tab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	switch (m_Tab.GetCurSel())
	{ 
	case 0:
		if (GetOnFlag == TRUE)
		{
			m_Main.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_Plo.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldUp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldDown.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_AfterOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeBright.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Fix.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Pack.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Main.m_MainZhiDan.SetFocus();
		}
		else
		{
			m_Tab.SetCurSel(1);
			MessageBox(_T("�˲�����Ҫ����ԱȨ�ޣ����ȵ�¼"));
		}
		break;
	case 1:
		if (GetOnFlag == TRUE)
		{
			m_Main.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Plo.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_BeforeOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldUp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldDown.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_AfterOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeBright.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Fix.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Pack.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Plo.m_PloBodyNumSub.SetFocus();
		}
		else
		{
			m_Tab.SetCurSel(1);
			MessageBox(_T("�˲�����Ҫ����ԱȨ�ޣ����ȵ�¼"));
		}
		break;
	case 2:
		if (GetOnFlag == TRUE)
		{
			m_Main.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Plo.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_OldUp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldDown.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_AfterOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeBright.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Fix.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Pack.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeOld.m_BeforeOldEditContrl.SetFocus();
		}
		else
		{
			m_Tab.SetCurSel(1);
			MessageBox(_T("�˲�����Ҫ����ԱȨ�ޣ����ȵ�¼"));
		}
		break;
	case 3:
		if (GetOnFlag == TRUE)
		{
			m_Main.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Plo.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldUp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_OldDown.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_AfterOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeBright.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Fix.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Pack.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldUp.m_OldUpEdit.SetFocus();
		}
		else
		{
			m_Tab.SetCurSel(1);
			MessageBox(_T("�˲�����Ҫ����ԱȨ�ޣ����ȵ�¼"));
		}
		break;
	case 4:
		if (GetOnFlag == TRUE)
		{
			m_Main.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Plo.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldUp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldDown.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_AfterOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeBright.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Fix.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Pack.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldDown.m_OldDownEdit.SetFocus();
		}
		else
		{
			m_Tab.SetCurSel(1);
			MessageBox(_T("�˲�����Ҫ����ԱȨ�ޣ����ȵ�¼"));
		}
		break;
	case 5:
		if (GetOnFlag == TRUE)
		{
			m_Main.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Plo.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldUp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldDown.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_AfterOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_BeforeBright.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Fix.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Pack.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_AfterOld.m_AfterOldEditContrl.SetFocus();
		}
		else
		{
			m_Tab.SetCurSel(1);
			MessageBox(_T("�˲�����Ҫ����ԱȨ�ޣ����ȵ�¼"));
		}
		break;
	case 6:
		if (GetOnFlag == TRUE)
		{
			m_Main.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Plo.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldUp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldDown.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_AfterOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeBright.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_Fix.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Pack.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeBright.m_BrightBodyEdit.SetFocus();
		}
		else
		{
			m_Tab.SetCurSel(1);
			MessageBox(_T("�˲�����Ҫ����ԱȨ�ޣ����ȵ�¼"));
		}
		break;
	case 7:
		if (GetOnFlag == TRUE)
		{
			m_Main.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Plo.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldUp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldDown.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_AfterOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeBright.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Fix.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_Pack.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Fix.m_FixSingleNumEdit.SetFocus();
		}
		else
		{
			m_Tab.SetCurSel(1);
			MessageBox(_T("�˲�����Ҫ����ԱȨ�ޣ����ȵ�¼"));
		}
		break;
	case 8:
		if (GetOnFlag == TRUE)
		{
			m_Main.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Plo.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldUp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_OldDown.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_AfterOld.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_BeforeBright.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Fix.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_Pack.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_Pack.m_PackEdit.SetFocus();

		}
		else
		{
			m_Tab.SetCurSel(1);
			MessageBox(_T("�˲�����Ҫ����ԱȨ�ޣ����ȵ�¼"));
		}
		break;
	default:
		break;
	}
}

/*��ȡ��Ŀ��ִ���ļ�·��*/
CString CProjectorTestSystemDlg::GetExePath()
{
	char sFileName[256] = { 0 };
	CString ProjectPath = _T("");
	GetModuleFileName(AfxGetInstanceHandle(), sFileName, 255);
	ProjectPath.Format(_T("%s"), sFileName);
	int pos = ProjectPath.ReverseFind('\\');
	if (pos != -1)
		ProjectPath = ProjectPath.Left(pos);
	else
		ProjectPath = _T("");
	return ProjectPath;
}

/*��ini�ļ���ȡ���ݿ������ַ���*/
void CProjectorTestSystemDlg::GetConnectStr()
{
	TCHAR ServerName[200];
	TCHAR UserIDChar[200];
	TCHAR PasswordChar[200];
	TCHAR DataBaseNameChar[200];
	CString IniPath, IniName;
	IniPath = GetExePath();
	IniName = _T("\\DBPATH.ini");
	IniPath += IniName;
	GetPrivateProfileString(_T("DBPATH"), _T("Data Source"), _T(""), ServerName, sizeof(ServerName), IniPath);
	GetPrivateProfileString(_T("DBPATH"), _T("User ID"), _T(""), UserIDChar, sizeof(UserIDChar), IniPath);
	GetPrivateProfileString(_T("DBPATH"), _T("Password"), _T(""), PasswordChar, sizeof(PasswordChar), IniPath);
	GetPrivateProfileString(_T("DBPATH"), _T("Initial Catalog"), _T(""), DataBaseNameChar, sizeof(DataBaseNameChar), IniPath);
	OperateDB.DataBaseName = DataBaseNameChar;
	OperateDB.DataSource = ServerName;
	OperateDB.UserId = UserIDChar;
	OperateDB.Passwoord = PasswordChar;
	OperateDB.m_szConnectionString = _T("Provider = SQLOLEDB.1; Data Source = ") + OperateDB.DataSource + _T("; Network Library = DBMSSOCN; Initial Catalog = ") + OperateDB.DataBaseName;
}

/*�˵�--����Ա��¼*/
void CProjectorTestSystemDlg::OnAdminiGetOn()
{
	// TODO:  �ڴ���������������
	INT_PTR AdminiGetOnRes;
	CAdminiPassDlg m_AdminiPass;
	AdminiGetOnRes = m_AdminiPass.DoModal();
	if (IDCANCEL == AdminiGetOnRes)
	{
		return;
	}
	if (PassWord==_T("admini"))
	{
		GetConnectStr();
		OperateDB.OpenConnection();
		ConnectFlag = OperateDB.IsConnected();
		if (ConnectFlag==TRUE)
		{
			GetOnFlag = TRUE;
			m_StateBar.SetPaneText(0,_T("�ѵ�¼"));
			GetMenu()->GetSubMenu(0)->EnableMenuItem(0, MF_BYPOSITION | MF_DISABLED);
			GetMenu()->GetSubMenu(0)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			GetMenu()->GetSubMenu(0)->EnableMenuItem(2, MF_BYPOSITION | MF_ENABLED);
		}
		else
		{
			MessageBox(_T("��¼ʧ�ܣ������µ�¼"));
			GetOnFlag = FALSE;
			return;
		}
	}
	else
	{
		GetOnFlag = FALSE;
		MessageBox(_T("�������"));
		return;
	}
	
}

/*�˵�--����ǰ׺*/
void CProjectorTestSystemDlg::OnSetIndex()
{
	// TODO:  �ڴ���������������
	INT_PTR SetIndexnRes;
	CString IndexName;	
	SetIndexnRes = SetIndex.DoModal();
	if (SetIndexnRes==IDCANCEL)
	{
		return;
	}
	//PloDlg->SetDlgItemTextA(IDC_ZHIDANNUM, DanNum);
}

/*ע����¼*/
void CProjectorTestSystemDlg::OnLogOut()
{
	// TODO:  �ڴ���������������
	BOOL CloseFinshFlag = FALSE;
	CloseFinshFlag = OperateDB.CloseConnection();
	if (CloseFinshFlag==TRUE)
	{
		GetOnFlag = FALSE;
		ConnectFlag = FALSE;
		m_StateBar.SetPaneText(0, _T("δ��¼"));
		GetMenu()->GetSubMenu(0)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
		GetMenu()->GetSubMenu(0)->EnableMenuItem(1, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(0)->EnableMenuItem(2, MF_BYPOSITION | MF_DISABLED);
	}
}

/*�˳�ϵͳ*/
void CProjectorTestSystemDlg::OnExitSystem()
{
	// TODO:  �ڴ���������������
	OperateDB.CloseConnection();
	OnCancel();
}

/*�����е�Cancel����*/
void CProjectorTestSystemDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}

/*��ȡ��ǰʱ��*/
CString CProjectorTestSystemDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString Tiemstr;
	Tiemstr = time.Format(_T("%Y-%m-%d  %H:%M:%S"));
	return Tiemstr;
}


void CProjectorTestSystemDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		/*״̬��*/
		if (m_StateBar.GetSafeHwnd())
			{
				//RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);  
				CRect    m_Rect, rectBar;
				GetClientRect(&m_Rect);         //��ȡ�Ի���ľ�������
				m_StateBar.GetClientRect(&rectBar);
				m_Rect.top = m_Rect.bottom - 20;    //����״̬���ľ�������
				m_StateBar.MoveWindow(0, cy - m_Rect.Height(), m_Rect.Width(), rectBar.Height());
			}		
		PJTestSystemDlg.ResizeWindow();
		CRect TabCtrlRect;
		CWnd *TabPtr;
		TabPtr = GetDlgItem(IDC_TAB1);
		if (TabPtr == NULL)
		{
			return;
		}
		TabPtr->GetClientRect(&TabCtrlRect);
		TabCtrlRect.top += 25;
		MainDlg->MoveWindow(&TabCtrlRect, TRUE);		
		PloDlg->MoveWindow(&TabCtrlRect, TRUE);
		BrforeOldDlg->MoveWindow(&TabCtrlRect, TRUE);
		OldUpDlg->MoveWindow(&TabCtrlRect, TRUE);
		OldDownDlg->MoveWindow(&TabCtrlRect, TRUE);
		AfterOldDlg->MoveWindow(&TabCtrlRect, TRUE);
		BeforeBrightDlg->MoveWindow(&TabCtrlRect, TRUE);
		FixDlg->MoveWindow(&TabCtrlRect, TRUE);
		PackDlg->MoveWindow(&TabCtrlRect, TRUE);
	}
}
