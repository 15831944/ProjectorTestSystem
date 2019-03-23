// OldUpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "OldUpDlg.h"
#include "afxdialogex.h"
#include "ResizeCtrl.h"

// COldUpDlg �Ի���

/*ȫ�ֱ���*/
int OldFirstRow = 0;
COldUpDlg *OldUpDlg;
CWindowSizeMange OldUp;
IMPLEMENT_DYNAMIC(COldUpDlg, CDialogEx)

COldUpDlg::COldUpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COldUpDlg::IDD, pParent)
	, m_OldUpStatic(_T(""))
	, m_OldUpEditVal(_T(""))
{

}

COldUpDlg::~COldUpDlg()
{
}

void COldUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_OldUpList);
	DDX_Control(pDX, IDC_OLDUP_STATIC, m_OldUp);
	DDX_Text(pDX, IDC_OLDUP_STATIC, m_OldUpStatic);
	//DDX_Control(pDX, IDC_EDIT3, m_OldEdit);
	DDX_Control(pDX, IDC_OLDUPEDIT, m_OldUpEdit);
	DDX_Text(pDX, IDC_OLDUPEDIT, m_OldUpEditVal);
}


BEGIN_MESSAGE_MAP(COldUpDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// COldUpDlg ��Ϣ�������


BOOL COldUpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_OldUpList.SetExtendedStyle(m_OldUpList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_OldUpList.InsertColumn(0, _T("������"), LVCFMT_CENTER, 150, 0);
	m_OldUpList.InsertColumn(1, _T("����ʱ��"), LVCFMT_CENTER, 150, 1);
	OldUpDlg = this;
	OldUp.Init(m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

/*��Ӧ�س�����*/
BOOL COldUpDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CString m_OldUpEditStr,OldUpSelectSql,OldUpTimeStr,OldUpUpdataSql;
	_variant_t FirstOldTime,OldUpTimeVal;
	int m_OldUpStaticLength;
	LONG OldUpRecordestCount;
	UpdateData(TRUE);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_OLDUPEDIT)
		{
			if (DanNum == "")
			{
				MessageBox(_T("��������ǰ׺�Ͷ����ţ�"), _T("��ʾ"));
				m_OldUpEdit.SetFocus();
				m_OldUpEditVal = "";
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}

			m_OldUpStaticLength = m_OldUpStatic.GetLength();
			m_OldUpEditStr = m_OldUpEditVal.Left(m_OldUpStaticLength);
			if (m_OldUpEditStr != m_OldUpStatic || m_OldUpEditVal=="")
			{
				MessageBox(_T("���������"), _T("��ʾ"));
				m_OldUpEdit.SetFocus();
				m_OldUpEditVal = "";
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			try{
				OldUpSelectSql.Format(_T("select * from ProjectorInformation_MainTable where FuselageCode = '%s' and ZhiDan = '%s'"), m_OldUpEditVal,DanNum);
				OperateDB.OpenRecordset(OldUpSelectSql);
				OldUpRecordestCount = OperateDB.GetRecordCount();
				if (OldUpRecordestCount == 0)
				{
					MessageBox(_T("�������ڲ����ڸû�����"), _T("��ʾ"));
					OperateDB.CloseRecordset();
					m_OldUpEdit.SetFocus();
					m_OldUpEditVal = "";
					UpdateData(FALSE);
					OperateDB.CloseRecordset();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (!OperateDB.m_pRecordset->BOF)
					OperateDB.m_pRecordset->MoveFirst();
				FirstOldTime = OperateDB.m_pRecordset->GetCollect(_T("PreAgingTestTime"));
				OldUpTimeVal = OperateDB.m_pRecordset->GetCollect(_T("AgeingBeginTime"));
				if (OldUpTimeVal.vt!=VT_NULL)
				{
					SYSTEMTIME myOldUpTime;
					VariantTimeToSystemTime((COleDateTime)OldUpTimeVal, &myOldUpTime);
					CString decrition;
					decrition.Format(_T("�ò�Ʒ�Ѿ����ϻ��ϼ�, �ϼ�ʱ��Ϊ�� %d-%d-%d %d:%d:%d"), myOldUpTime.wYear, myOldUpTime.wMonth, myOldUpTime.wDay\
						, myOldUpTime.wHour, myOldUpTime.wMinute, myOldUpTime.wSecond);
					MessageBox(decrition, _T("��ʾ"));
					OperateDB.CloseRecordset();
					m_OldUpEdit.SetFocus();
					m_OldUpEditVal = "";
					UpdateData(FALSE);
					OperateDB.CloseRecordset();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (FirstOldTime.vt == VT_NULL)
				{
					MessageBox(_T("�ò�Ʒδ���ϻ�ǰ����"), _T("��ʾ"));
					OperateDB.CloseRecordset();
					m_OldUpEdit.SetFocus();
					m_OldUpEditVal = "";
					UpdateData(FALSE);
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				else
				{
					OldUpTimeStr = GetTime();
					OldUpUpdataSql.Format(_T("UPDATE ProjectorInformation_MainTable SET AgeingBeginTime = '%s' WHERE FuselageCode = '%s'"), OldUpTimeStr, m_OldUpEditVal);
					OperateDB.ExecuteByConnection(OldUpUpdataSql);
					m_OldUpList.InsertItem(OldFirstRow, m_OldUpEditVal);
					m_OldUpList.SetItemText(OldFirstRow, 1, OldUpTimeStr);
					m_OldUpList.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
					OldFirstRow++;
					OperateDB.CloseRecordset();
					m_OldUpEdit.SetFocus();
					m_OldUpEditVal = "";
					UpdateData(FALSE);
				}
			}
			catch (_com_error &e)
			{
				AfxMessageBox(e.Description());
				return CDialogEx::PreTranslateMessage(pMsg);;
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

/*��ȡ��ǰʱ��*/
CString COldUpDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString Tiemstr;
	Tiemstr = time.Format(_T("%Y-%m-%d  %H:%M:%S"));
	return Tiemstr;
}

void COldUpDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	/*CDialogEx::OnOK();*/
}


void COldUpDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	/*CDialogEx::OnCancel();*/
}


void COldUpDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		OldUp.ResizeWindow();
	}
}
