// PackDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "PackDlg.h"
#include "afxdialogex.h"
#include "ResizeCtrl.h"

// CPackDlg �Ի���


/*ȫ�ֱ���*/
int PackFirstRow = 0;
CPackDlg *PackDlg;
CWindowSizeMange Pack;
IMPLEMENT_DYNAMIC(CPackDlg, CDialogEx)

CPackDlg::CPackDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPackDlg::IDD, pParent)
	, m_PackEditVal(_T(""))
	, m_PackStatic(_T(""))
{

}

CPackDlg::~CPackDlg()
{
}

void CPackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_PackList);
	DDX_Control(pDX, IDC_PACK_STATIC, m_Pack);
	DDX_Control(pDX, IDC_PACKEDIT, m_PackEdit);
	DDX_Text(pDX, IDC_PACKEDIT, m_PackEditVal);
	DDX_Text(pDX, IDC_PACK_STATIC, m_PackStatic);
}


BEGIN_MESSAGE_MAP(CPackDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPackDlg ��Ϣ�������


BOOL CPackDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_PackList.SetExtendedStyle(m_PackList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_PackList.InsertColumn(0, _T("������"), LVCFMT_CENTER, 150, 0);
	m_PackList.InsertColumn(1, _T("��װʱ��"), LVCFMT_CENTER, 150, 1);
	PackDlg = this;
	Pack.Init(m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

/*�س�����Ӧ*/
BOOL CPackDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CString m_PackEditStr, PackSelectSql, PackTimeStr, PackUpdataSql;
	int m_PackStaticLength;
	LONG PackRecordestCount;
	_variant_t BrightTime;
	UpdateData(TRUE);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_PACKEDIT)
		{
			if (DanNum == "")
			{
				MessageBox(_T("��������ǰ׺�Ͷ�����"), _T("��ʾ"));
				m_PackEdit.SetFocus();
				m_PackEditVal = "";
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			m_PackStaticLength = m_PackStatic.GetLength();
			m_PackEditStr = m_PackEditVal.Left(m_PackStaticLength);
			if (m_PackEditStr != m_PackStatic || m_PackEditVal == "")
			{
				MessageBox(_T("���������"), _T("��ʾ"));
				m_PackEdit.SetFocus();
				m_PackEditVal = "";
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			try{
				PackSelectSql.Format(_T("select * from ProjectorInformation_MainTable where FuselageCode = '%s' and ZhiDan = '%s'"), m_PackEditVal,DanNum);
				OperateDB.OpenRecordset(PackSelectSql);
				PackRecordestCount = OperateDB.GetRecordCount();
				if (PackRecordestCount == 0)
				{
					MessageBox(_T("�������ڲ����ڸû�����"), _T("��ʾ"));
					OperateDB.CloseRecordset();
					m_PackEdit.SetFocus();
					m_PackEditVal = "";
					UpdateData(FALSE);
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (!OperateDB.m_pRecordset->BOF)
					OperateDB.m_pRecordset->MoveFirst();
				BrightTime = OperateDB.m_pRecordset->GetCollect(_T("LuminanceTestTime"));
				if (BrightTime.vt == VT_NULL)
				{
					MessageBox(_T("�ò�Ʒû�н������Ȳ���"), _T("��ʾ"));
					OperateDB.CloseRecordset();
					m_PackEdit.SetFocus();
					m_PackEditVal = "";
					UpdateData(FALSE);
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				else
				{
					PackTimeStr = GetTime();
					PackUpdataSql.Format(_T("UPDATE ProjectorInformation_MainTable SET PackingTime = '%s' WHERE FuselageCode = '%s'"), PackTimeStr, m_PackEditVal);
					OperateDB.ExecuteByConnection(PackUpdataSql);
					m_PackList.InsertItem(PackFirstRow, m_PackEditVal);
					m_PackList.SetItemText(PackFirstRow, 1, PackTimeStr);
					PackFirstRow++;
					OperateDB.CloseRecordset();
					m_PackEdit.SetFocus();
					m_PackEditVal = "";
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


void CPackDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CPackDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	/*CDialogEx::OnCancel();*/
}

/*��ȡ��ǰʱ��*/
CString CPackDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString Tiemstr;
	Tiemstr = time.Format(_T("%Y-%m-%d  %H:%M:%S"));
	return Tiemstr;
}

void CPackDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		Pack.ResizeWindow();
	}
}
