// AfterOldDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "AfterOldDlg.h"
#include "afxdialogex.h"
#include "ResizeCtrl.h"

// CAfterOldDlg �Ի���

/*ȫ�ֱ���*/
int AfterOldFirstRow = 0;
CAfterOldDlg *AfterOldDlg;
CWindowSizeMange AfterOld;
IMPLEMENT_DYNAMIC(CAfterOldDlg, CDialogEx)

CAfterOldDlg::CAfterOldDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAfterOldDlg::IDD, pParent)
	, m_AfterOldBodyEdit(_T(""))
	, m_AfterOldBody(_T(""))
{

}

CAfterOldDlg::~CAfterOldDlg()
{
}

void CAfterOldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_AfetrOldList);
	DDX_Control(pDX, IDC_AFTEROLD_STATIC, m_AfterOldNum);
	DDX_Control(pDX, IDC_AFTEROLDBODY, m_AfterOldEditContrl);
	DDX_Text(pDX, IDC_AFTEROLDBODY, m_AfterOldBodyEdit);
	DDX_Text(pDX, IDC_AFTEROLD_STATIC, m_AfterOldBody);
}


BEGIN_MESSAGE_MAP(CAfterOldDlg, CDialogEx)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CAfterOldDlg::OnLvnItemchangedList2)
END_MESSAGE_MAP()


// CAfterOldDlg ��Ϣ�������


BOOL CAfterOldDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_AfetrOldList.SetExtendedStyle(m_AfetrOldList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_AfetrOldList.InsertColumn(0, _T("������"), LVCFMT_CENTER, 150, 0);
	m_AfetrOldList.InsertColumn(1, _T("��һ�β���ʱ��"), LVCFMT_CENTER, 150, 1);
	m_AfetrOldList.InsertColumn(2, _T("�ڶ��β���ʱ��"), LVCFMT_CENTER, 150, 2);
	AfterOldDlg = this;
	AfterOld.Init(m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

/*�س�����Ӧ*/
BOOL CAfterOldDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CString AfterOldNum, AfterOldSelectSql, AfterOldBodyEditStr, AfterOldUpdateSql;
	CString FirstAfterTimeStr, SecondAfterTimeStr, sTimeOneAfterStr, sTimeTwoAfterStr;
	_variant_t mPostAgingTestTime, mPostAgingTestTime2,OldDownTime;
	LONG AfterOldRecodCount;
	SYSTEMTIME sTimeOneAfter;
	int AfterOldStaticLength;
	UpdateData(TRUE);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_AFTEROLDBODY)
		{	
			AfterOldStaticLength = m_AfterOldBody.GetLength();
			AfterOldBodyEditStr = m_AfterOldBodyEdit.Left(AfterOldStaticLength);
			if (AfterOldBodyEditStr != m_AfterOldBody || m_AfterOldBodyEdit == "")
			{
				MessageBox(_T("���������"));
				m_AfterOldEditContrl.SetFocus();
				m_AfterOldBodyEdit = _T("");
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			try
			{
				AfterOldSelectSql.Format(_T("select * from ProjectorInformation_MainTable where FuselageCode = '%s'"), m_AfterOldBodyEdit);
				OperateDB.OpenRecordset(AfterOldSelectSql);
				AfterOldRecodCount = OperateDB.GetRecordCount();
				if (AfterOldRecodCount == 0)
				{
					MessageBox(_T("�����ڵĻ�����"));
					m_AfterOldEditContrl.SetFocus();
					m_AfterOldBodyEdit = "";
					UpdateData(FALSE);
					OperateDB.CloseRecordset();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (!OperateDB.m_pRecordset->BOF)
					OperateDB.m_pRecordset->MoveFirst();
				OldDownTime = OperateDB.m_pRecordset->GetCollect(_T("AgeingEndTime"));
				if (OldDownTime.vt==VT_NULL)
				{
					MessageBox(_T("�ò�Ʒ��û���¼��ϻ�"));
					m_AfterOldEditContrl.SetFocus();
					m_AfterOldBodyEdit = "";
					UpdateData(FALSE);
					OperateDB.CloseRecordset();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				else
				{
					if (!OperateDB.m_pRecordset->BOF)
						OperateDB.m_pRecordset->MoveFirst();
					mPostAgingTestTime = OperateDB.m_pRecordset->GetCollect(_T("PostAgingTestTime"));
					mPostAgingTestTime2 = OperateDB.m_pRecordset->GetCollect(_T("PostAgingTestTime2"));
				}
				if (mPostAgingTestTime.vt == VT_NULL)
				{
					FirstAfterTimeStr = GetTime();
					AfterOldUpdateSql.Format(_T("UPDATE ProjectorInformation_MainTable SET PostAgingTestTime = '%s' WHERE FuselageCode = '%s'"), FirstAfterTimeStr, m_AfterOldBodyEdit);
					OperateDB.ExecuteByConnection(AfterOldUpdateSql);
					m_AfetrOldList.InsertItem(AfterOldFirstRow, m_AfterOldBodyEdit);
					m_AfetrOldList.SetItemText(AfterOldFirstRow, 1, FirstAfterTimeStr);
					OperateDB.CloseRecordset();
					m_AfterOldEditContrl.SetFocus();
					m_AfterOldBodyEdit = "";
					UpdateData(FALSE);
				}
				if ((mPostAgingTestTime.vt != VT_NULL&&mPostAgingTestTime2.vt == VT_NULL) || (mPostAgingTestTime.vt != VT_NULL&&mPostAgingTestTime2.vt != VT_NULL))
				{
					SecondAfterTimeStr = GetTime();
					COleDateTime oleTime = (COleDateTime)mPostAgingTestTime;
					VariantTimeToSystemTime(oleTime, &sTimeOneAfter);
					sTimeOneAfterStr.Format(_T("%d-%d-%d  %d:%d:%d"), sTimeOneAfter.wYear, sTimeOneAfter.wMonth, sTimeOneAfter.wDay, sTimeOneAfter.wHour, sTimeOneAfter.wMinute, sTimeOneAfter.wSecond);
					AfterOldUpdateSql.Format(_T("UPDATE ProjectorInformation_MainTable SET PostAgingTestTime2 = '%s' WHERE FuselageCode = '%s'"), SecondAfterTimeStr, m_AfterOldBodyEdit);
					OperateDB.ExecuteByConnection(AfterOldUpdateSql);
					m_AfetrOldList.InsertItem(AfterOldFirstRow, m_AfterOldBodyEdit);
					m_AfetrOldList.SetItemText(AfterOldFirstRow, 1, sTimeOneAfterStr);
					m_AfetrOldList.SetItemText(AfterOldFirstRow, 2, SecondAfterTimeStr);
					OperateDB.CloseRecordset();
					m_AfterOldEditContrl.SetFocus();
					m_AfterOldBodyEdit = "";
					UpdateData(FALSE);
				}
			}
			catch (_com_error &e)
			{
				AfxMessageBox(e.Description());
				return FALSE;
			}

		}
		AfterOldFirstRow++;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

/*��ȡ��ǰʱ��*/
CString CAfterOldDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString Tiemstr;
	Tiemstr = time.Format(_T("%Y-%m-%d  %H:%M:%S"));
	return Tiemstr;
}




void CAfterOldDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CAfterOldDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnCancel();
}


void CAfterOldDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		AfterOld.ResizeWindow();
	}
	// TODO:  �ڴ˴������Ϣ����������
}


void CAfterOldDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
