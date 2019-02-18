// FixDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "FixDlg.h"
#include "afxdialogex.h"
#include "ResizeCtrl.h"

// CFixDlg �Ի���

/*ȫ�ֱ���*/
int FixFirstRow = 0;
CFixDlg *FixDlg;
CWindowSizeMange Fix;
IMPLEMENT_DYNAMIC(CFixDlg, CDialogEx)

CFixDlg::CFixDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFixDlg::IDD, pParent)
	, m_FixSingleBodyState(FALSE)
	, m_FixMainBoardState(FALSE)
	, m_FixSingleBodyEditVal(_T(""))
	, m_FixTextVal(_T(""))
	, m_AfterFixSingleEditVal(_T(""))
	, m_AfterFixMainEditVal(_T(""))
	, m_FixStaticVal(_T(""))
	, m_FixSingleStaticVal(_T(""))
	, m_FixMainStaticVal(_T(""))
{

}

CFixDlg::~CFixDlg()
{
}

void CFixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_FixList);
	DDX_Control(pDX, IDC_FIX_STATIC, m_FixBodyNum);
	DDX_Control(pDX, IDC_FIX_SINGLEBODYNUM_STATIC, m_FixSingleBodyNum);
	DDX_Control(pDX, IDC_FIX_MAINBOARDNUM_STATIC, m_FixMainBoardNum);
	DDX_Check(pDX, IDC_CHECK2, m_FixSingleBodyState);
	DDX_Check(pDX, IDC_CHECK3, m_FixMainBoardState);
	DDX_Control(pDX, IDC_FIXBODY, m_FixSingleNumEdit);
	DDX_Text(pDX, IDC_FIXBODY, m_FixSingleBodyEditVal);
	DDX_Control(pDX, IDC_FIXTEXT, m_FixText);
	DDX_Text(pDX, IDC_FIXTEXT, m_FixTextVal);
	DDX_Control(pDX, IDC_AFTERFIX_SINGLEBODY, m_AfterFixSingleEdit);
	DDX_Text(pDX, IDC_AFTERFIX_SINGLEBODY, m_AfterFixSingleEditVal);
	DDX_Control(pDX, IDC_AFTERFIX_MAINBOARD, m_AfterFixMainEdit);
	DDX_Text(pDX, IDC_AFTERFIX_MAINBOARD, m_AfterFixMainEditVal);
	DDX_Text(pDX, IDC_FIX_STATIC, m_FixStaticVal);
	DDX_Text(pDX, IDC_FIX_SINGLEBODYNUM_STATIC, m_FixSingleStaticVal);
	DDX_Text(pDX, IDC_FIX_MAINBOARDNUM_STATIC, m_FixMainStaticVal);
	DDX_Control(pDX, IDC_CHECK2, m_FixCheck1);
	DDX_Control(pDX, IDC_CHECK3, m_FixCheck2);
}


BEGIN_MESSAGE_MAP(CFixDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CFixDlg ��Ϣ�������


BOOL CFixDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_FixList.SetExtendedStyle(m_FixList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_FixList.InsertColumn(0, _T("������"), LVCFMT_CENTER, 150, 0);
	m_FixList.InsertColumn(1, _T("άϵ����"), LVCFMT_CENTER, 250, 1);
	m_FixList.InsertColumn(2, _T("ά�޺�������"), LVCFMT_CENTER, 150, 2);
	m_FixList.InsertColumn(3, _T("ά�޺��������"), LVCFMT_CENTER, 150, 3);
	m_FixList.InsertColumn(4, _T("����ʱ��"), LVCFMT_CENTER, 150, 4);
	FixDlg = this;
	Fix.Init(m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


/*��ȡ��ǰʱ��*/
CString CFixDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString Tiemstr;
	Tiemstr = time.Format(_T("%Y-%m-%d  %H:%M:%S"));
	return Tiemstr;
}

/*�س�����Ӧ*/
BOOL CFixDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CString FixTimeStr, m_FixBodyNumValStr, m_FixSingleBodyNumValStr, m_FixMainBoardNumValStr, mFixFuselageCode, InsertIntoSql;
	CString mOpticalCode, SelectSqlEdit2, SelectSqlEdit1, mMainBoardCode;
	BOOL SelectFinhFlag = FALSE;
	LONG FixRecodestCount = 0;
	int m_FixBodyNumStaticValLength, m_FixSingleBodyNumStaticValLength, m_FixMainBoardNumStaticValLength;
	FixTimeStr = GetTime();
	UpdateData(TRUE);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_FIXBODY)
		{
			try
			{
				SelectSqlEdit1.Format(_T("SELECT * FROM ProjectorInformation_MainTable WHERE FuselageCode = '%s'"), m_FixSingleBodyEditVal);
				OperateDB.OpenRecordset(SelectSqlEdit1);
				FixRecodestCount = OperateDB.GetRecordCount();
				if (FixRecodestCount == 0)
				{
					MessageBox(_T("�����ڵĻ�����"), _T("��ʾ"));
					OperateDB.CloseRecordset();
					m_FixSingleNumEdit.SetFocus();
					m_FixSingleBodyEditVal = "";
					UpdateData(FALSE);
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				OperateDB.CloseRecordset();
				m_FixBodyNumStaticValLength = m_FixStaticVal.GetLength();
				m_FixBodyNumValStr = m_FixSingleBodyEditVal.Left(m_FixBodyNumStaticValLength);
				if (m_FixBodyNumValStr != m_FixStaticVal || m_FixSingleBodyEditVal == "")
				{
					MessageBox(_T("���������"), _T("��ʾ"));
					m_FixSingleNumEdit.SetFocus();
					m_FixSingleBodyEditVal = "";
					UpdateData(FALSE);
					return CDialogEx::PreTranslateMessage(pMsg);
				}

			}
			catch (_com_error &e)
			{
				OperateDB.m_szErrorMsg = e.ErrorMessage();
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			m_FixText.SetFocus();
			pMsg->message = 0;
			pMsg->wParam = 0;
		}

		if (GetFocus()->GetDlgCtrlID() == IDC_FIXTEXT&&pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		{
			if (m_FixMainBoardState == FALSE&&m_FixSingleBodyState == FALSE)
			{

				try
				{
					InsertIntoSql.Format(_T("UPDATE ProjectorInformation_MainTable SET RepairText='%s',RepairTime='%s'  WHERE FuselageCode = '%s'"), m_FixTextVal, FixTimeStr, m_FixSingleBodyEditVal);
					OperateDB.ExecuteByConnection(InsertIntoSql);
					m_FixList.InsertItem(FixFirstRow, m_FixSingleBodyEditVal);
					m_FixList.SetItemText(FixFirstRow, 1, m_FixTextVal);
					m_FixList.SetItemText(FixFirstRow, 4, FixTimeStr);
					m_FixTextVal = _T("");
					m_FixSingleBodyEditVal = _T("");
					UpdateData(FALSE);
					m_FixSingleNumEdit.SetFocus();
				}
				catch (_com_error &e)
				{
					OperateDB.m_szErrorMsg = e.ErrorMessage();
					return CDialogEx::PreTranslateMessage(pMsg);
				}

			}
			if (m_FixMainBoardState == TRUE&&m_FixSingleBodyState == FALSE)
			{
				m_AfterFixMainEdit.EnableWindow(TRUE);
				m_AfterFixMainEdit.SetFocus();
				pMsg->message = 0;
				pMsg->wParam = 0;
			}
			if (m_FixSingleBodyState == TRUE&&m_FixMainBoardState == FALSE)
			{
				m_AfterFixSingleEdit.EnableWindow(TRUE);
				m_AfterFixSingleEdit.SetFocus();
				pMsg->message = 0;
				pMsg->wParam = 0;
			}
			if (m_FixSingleBodyState == TRUE&&m_FixMainBoardState == TRUE)
			{
				m_AfterFixSingleEdit.EnableWindow(TRUE);
				m_AfterFixSingleEdit.SetFocus();
				pMsg->message = 0;
				pMsg->wParam = 0;
			}
		}	
		if (GetFocus()->GetDlgCtrlID() == IDC_AFTERFIX_SINGLEBODY&&pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		{
			try
			{
				m_FixSingleBodyNumStaticValLength = m_FixSingleStaticVal.GetLength();
				m_FixSingleBodyNumValStr = m_AfterFixSingleEditVal.Left(m_FixSingleBodyNumStaticValLength);
				if (m_FixSingleBodyNumValStr != m_FixSingleStaticVal || m_AfterFixSingleEditVal == "")
				{
					MessageBox(_T("��������"), _T("��ʾ"));
					m_AfterFixSingleEditVal = _T("");
					UpdateData(FALSE);
					m_AfterFixSingleEdit.SetFocus();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				SelectSqlEdit1.Format(_T("SELECT * FROM ProjectorInformation_MainTable WHERE OpticalCode = '%s' OR  AfterMaintenanceOpticalCode='%s'"), m_AfterFixSingleEditVal, m_AfterFixSingleEditVal);
				OperateDB.OpenRecordset(SelectSqlEdit1);
				FixRecodestCount = OperateDB.GetRecordCount();
				if (FixRecodestCount != 0)
				{
					MessageBox(_T("������ظ�"), _T("��ʾ"));
					m_AfterFixSingleEditVal = _T("");
					UpdateData(FALSE);
					m_AfterFixSingleEdit.SetFocus();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				OperateDB.CloseRecordset();
			}
			catch (_com_error &e)
			{
				OperateDB.m_szErrorMsg = e.ErrorMessage();
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			if (m_FixMainBoardState == FALSE)
			{
				try
				{
					InsertIntoSql.Format(_T("UPDATE ProjectorInformation_MainTable SET RepairText ='%s',RepairTime='%s',AfterMaintenanceOpticalCode='%s'  WHERE FuselageCode = '%s'"), m_FixTextVal, FixTimeStr, m_AfterFixSingleEditVal, m_FixSingleBodyEditVal);
					OperateDB.ExecuteByConnection(InsertIntoSql);
					m_FixList.InsertItem(FixFirstRow, m_FixSingleBodyEditVal);
					m_FixList.SetItemText(FixFirstRow, 1, m_FixTextVal);
					m_FixList.SetItemText(FixFirstRow, 4, FixTimeStr);
					m_FixList.SetItemText(FixFirstRow, 2, m_AfterFixSingleEditVal);
					m_AfterFixSingleEditVal = _T("");
					m_FixSingleBodyEditVal = _T("");
					m_FixTextVal = _T("");
					UpdateData(FALSE);
					m_FixSingleNumEdit.SetFocus();
					m_AfterFixSingleEdit.EnableWindow(FALSE);
				}
				catch (_com_error &e)
				{
					OperateDB.m_szErrorMsg = e.ErrorMessage();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
			}
			else
			{
				m_AfterFixMainEdit.EnableWindow(TRUE);
				m_AfterFixMainEdit.SetFocus();
				pMsg->message = 0;
				pMsg->wParam = 0;
			}
		}
		if (GetFocus()->GetDlgCtrlID() == IDC_AFTERFIX_MAINBOARD&&pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		{
			try
			{
				m_FixMainBoardNumStaticValLength = m_FixMainStaticVal.GetLength();
				m_FixMainBoardNumValStr = m_AfterFixMainEditVal.Left(m_FixMainBoardNumStaticValLength);
				if (m_FixMainBoardNumValStr != m_FixMainStaticVal || m_AfterFixMainEditVal == "")
				{
					MessageBox(_T("����������"), _T("��ʾ"));
					m_AfterFixMainEditVal = _T("");
					UpdateData(FALSE);
					m_AfterFixMainEdit.SetFocus();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				SelectSqlEdit1.Format(_T("SELECT * FROM ProjectorInformation_MainTable WHERE MainBoardCode = '%s' OR AfterMaintenanceMainBoardCode='%s'"), m_AfterFixMainEditVal, m_AfterFixMainEditVal);
				OperateDB.OpenRecordset(SelectSqlEdit1);
				FixRecodestCount = OperateDB.GetRecordCount();
				if (FixRecodestCount != 0)
				{
					MessageBox(_T("��������ظ�"), _T("��ʾ"));
					m_AfterFixMainEditVal = _T("");
					UpdateData(FALSE);
					m_AfterFixMainEdit.SetFocus();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				OperateDB.CloseRecordset();			
			}
			catch (_com_error &e)
			{
				OperateDB.m_szErrorMsg = e.ErrorMessage();
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			try
			{
				if (m_FixSingleBodyState==TRUE)
				{
					InsertIntoSql.Format(_T("UPDATE ProjectorInformation_MainTable SET RepairText='%s',RepairTime='%s',AfterMaintenanceOpticalCode='%s',AfterMaintenanceMainBoardCode='%s'  WHERE FuselageCode = '%s'"), m_FixTextVal, FixTimeStr, m_AfterFixSingleEditVal, m_AfterFixMainEditVal, m_FixSingleBodyEditVal);

				}
				else
				{
					InsertIntoSql.Format(_T("UPDATE ProjectorInformation_MainTable SET RepairText='%s',RepairTime='%s',AfterMaintenanceMainBoardCode='%s'  WHERE FuselageCode = '%s'"), m_FixTextVal, FixTimeStr, m_AfterFixMainEditVal, m_FixSingleBodyEditVal);

				}
				OperateDB.ExecuteByConnection(InsertIntoSql);
				m_FixList.InsertItem(FixFirstRow, m_FixSingleBodyEditVal);
				m_FixList.SetItemText(FixFirstRow, 1, m_FixTextVal);
				m_FixList.SetItemText(FixFirstRow, 3, m_AfterFixMainEditVal);
				m_FixList.SetItemText(FixFirstRow, 4, FixTimeStr);
				if (m_FixSingleBodyState == TRUE)
				{
					m_FixList.SetItemText(FixFirstRow, 2, m_AfterFixSingleEditVal);
				}			
				m_FixSingleBodyEditVal = _T("");
				m_FixTextVal = _T("");
				m_AfterFixSingleEditVal = _T("");
				m_AfterFixMainEditVal = _T("");
				UpdateData(FALSE);
				m_FixSingleNumEdit.SetFocus();
				m_AfterFixSingleEdit.EnableWindow(FALSE);
				m_AfterFixMainEdit.EnableWindow(FALSE);
			}
			catch (_com_error &e)
			{
				OperateDB.m_szErrorMsg = e.ErrorMessage();
				return CDialogEx::PreTranslateMessage(pMsg);
			}
		}
		if (pMsg->message != 0 && pMsg->wParam != 0)
		{
			FixFirstRow++;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CFixDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CFixDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	/*CDialogEx::OnCancel();*/
}


void CFixDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		Fix.ResizeWindow();
	}
}
