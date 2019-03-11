// BefroeOldDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "BefroeOldDlg.h"
#include "afxdialogex.h"
#include "ResizeCtrl.h"

// CBefroeOldDlg �Ի���


/*ȫ�ֱ���*/
int BeforeOldFirstRow = 0;
CBefroeOldDlg *BrforeOldDlg;
CWindowSizeMange BeforeOld;


IMPLEMENT_DYNAMIC(CBefroeOldDlg, CDialogEx)

CBefroeOldDlg::CBefroeOldDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBefroeOldDlg::IDD, pParent)
	, m_BeforeOldBody(_T(""))
	, m_BeforeOldBodyEdit(_T(""))
{

}

CBefroeOldDlg::~CBefroeOldDlg()
{
}

void CBefroeOldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_BeforeOldList);
	DDX_Control(pDX, IDC_BEFOREOLD_STATIC, m_BeforeOld);
	DDX_Text(pDX, IDC_BEFOREOLD_STATIC, m_BeforeOldBody);
	DDX_Text(pDX, IDC_BEFOREOLD_BODY, m_BeforeOldBodyEdit);
	DDX_Control(pDX, IDC_BEFOREOLD_BODY, m_BeforeOldEditContrl);
}


BEGIN_MESSAGE_MAP(CBefroeOldDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CBefroeOldDlg ��Ϣ�������


BOOL CBefroeOldDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BeforeOldList.SetExtendedStyle(m_BeforeOldList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_BeforeOldList.InsertColumn(0, _T("������"), LVCFMT_CENTER, 150, 0);
	m_BeforeOldList.InsertColumn(1, _T("��һ�β���ʱ��"), LVCFMT_CENTER, 150, 1);
	m_BeforeOldList.InsertColumn(2, _T("�ڶ��β���ʱ��"), LVCFMT_CENTER, 150, 2);
	BrforeOldDlg = this;
	BeforeOld.Init(m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

/*��Ӧ�س���*/
BOOL CBefroeOldDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CString BeforeOldNum, BeforeOldSelectSql, BeforeOldBodyEditStr, BeforeOldUpdateSql;
	CString FirstBeforeTimeStr, SecondBeforeTimeStr, sTimeOneStr, sTimeTwoStr;
	_variant_t mPreAgingTestTime, mPreAgingTestTime2;
	LONG BeforeOldRecodCount;
	SYSTEMTIME sTimeOne;
	int BefordOldStaticLength;
	UpdateData(TRUE);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_BEFOREOLD_BODY)
		{
			if (DanNum == "")
			{
				MessageBox(_T("��������ǰ׺�Ͷ����ţ�"), _T("��ʾ"));
				m_BeforeOldEditContrl.SetFocus();
				m_BeforeOldBodyEdit = "";
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			BefordOldStaticLength = m_BeforeOldBody.GetLength();
			BeforeOldBodyEditStr = m_BeforeOldBodyEdit.Left(BefordOldStaticLength);
			if (BeforeOldBodyEditStr != m_BeforeOldBody || m_BeforeOldBodyEdit == "")
			{
				MessageBox(_T("���������"), _T("��ʾ"));
				m_BeforeOldEditContrl.SetFocus();
				m_BeforeOldBodyEdit = "";
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			try
			{
				BeforeOldSelectSql.Format(_T("select * from ProjectorInformation_MainTable where FuselageCode = '%s' and ZhiDan = '%s'"), m_BeforeOldBodyEdit,DanNum);
				OperateDB.OpenRecordset(BeforeOldSelectSql);
				BeforeOldRecodCount = OperateDB.GetRecordCount();
				if (BeforeOldRecodCount == 0)
				{
					MessageBox(_T("�������ڲ����ڸû�����"), _T("��ʾ"));
					m_BeforeOldEditContrl.SetFocus();
					m_BeforeOldBodyEdit = "";
					UpdateData(FALSE);
					OperateDB.CloseRecordset();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				else
				{
					if (!OperateDB.m_pRecordset->BOF)
						OperateDB.m_pRecordset->MoveFirst();
					mPreAgingTestTime = OperateDB.m_pRecordset->GetCollect(_T("PreAgingTestTime"));
					mPreAgingTestTime2 = OperateDB.m_pRecordset->GetCollect(_T("PreAgingTestTime2"));
				}
				if (mPreAgingTestTime.vt == VT_NULL)
				{
					FirstBeforeTimeStr = GetTime();
					BeforeOldUpdateSql.Format(_T("UPDATE ProjectorInformation_MainTable SET PreAgingTestTime = '%s' WHERE FuselageCode = '%s'"), FirstBeforeTimeStr, m_BeforeOldBodyEdit);
					OperateDB.ExecuteByConnection(BeforeOldUpdateSql);
					m_BeforeOldList.InsertItem(BeforeOldFirstRow, m_BeforeOldBodyEdit);
					m_BeforeOldList.SetItemText(BeforeOldFirstRow, 1, FirstBeforeTimeStr);
					m_BeforeOldList.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
					BeforeOldFirstRow++;
					OperateDB.CloseRecordset();
					m_BeforeOldEditContrl.SetFocus();
					m_BeforeOldBodyEdit = "";
					UpdateData(FALSE);
				}
				if ((mPreAgingTestTime.vt != VT_NULL&&mPreAgingTestTime2.vt == VT_NULL) || (mPreAgingTestTime.vt != VT_NULL&&mPreAgingTestTime2.vt != VT_NULL))
				{
					SecondBeforeTimeStr = GetTime();
					COleDateTime oleTime = (COleDateTime)mPreAgingTestTime;
					VariantTimeToSystemTime(oleTime,&sTimeOne);
					sTimeOneStr.Format(_T("%d-%d-%d  %d:%d:%d"), sTimeOne.wYear, sTimeOne.wMonth, sTimeOne.wDay, sTimeOne.wHour, sTimeOne.wMinute, sTimeOne.wSecond);
					BeforeOldUpdateSql.Format(_T("UPDATE ProjectorInformation_MainTable SET PreAgingTestTime2 = '%s' WHERE FuselageCode = '%s'"), SecondBeforeTimeStr, m_BeforeOldBodyEdit);
					OperateDB.ExecuteByConnection(BeforeOldUpdateSql);
					m_BeforeOldList.InsertItem(BeforeOldFirstRow, m_BeforeOldBodyEdit);
					m_BeforeOldList.SetItemText(BeforeOldFirstRow, 1, sTimeOneStr);
					m_BeforeOldList.SetItemText(BeforeOldFirstRow, 2, SecondBeforeTimeStr);
					m_BeforeOldList.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
					BeforeOldFirstRow++;
					OperateDB.CloseRecordset();
					m_BeforeOldEditContrl.SetFocus();
					m_BeforeOldBodyEdit = "";
					UpdateData(FALSE);
				}
			}
			catch (_com_error &e)
			{
				AfxMessageBox(e.Description());
				return FALSE;
			}
			
		}
		
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


/*��ȡ��ǰʱ��*/
CString CBefroeOldDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString Tiemstr;
	Tiemstr = time.Format(_T("%Y-%m-%d  %H:%M:%S"));
	return Tiemstr;
}


void CBefroeOldDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CBefroeOldDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	/*CDialogEx::OnCancel();*/
}


void CBefroeOldDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		BeforeOld.ResizeWindow();
	}
}
