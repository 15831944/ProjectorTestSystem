// AfterOldDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "AfterOldDlg.h"
#include "afxdialogex.h"
#include "ResizeCtrl.h"
#include "ProjectorTestSystemDlg.h"
// CAfterOldDlg �Ի���

/*ȫ�ֱ���*/
int AfterOldFirstRow = 0;
CAfterOldDlg *AfterOldDlg;
CWindowSizeMange AfterOld;
extern CProjectorTestSystemDlg * ProjectorTestSystemDlg;
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
	CString FirstAfterTimeStr, SecondAfterTimeStr, sTimeOneAfterStr, sTimeTwoAfterStr,AfterSelectPre;
	_variant_t mPostAgingTestTime, mPostAgingTestTime2,OldDownTime;
	LONG AfterOldRecodCount;
	SYSTEMTIME sTimeOneAfter;
	int AfterOldStaticLength;
	UpdateData(TRUE);	
	AfterSelectPre.Format(_T("select [TypeName] from ProjectorInformation_EncodingRules where TypeName = '%s'"), DanNum);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_AFTEROLDBODY)
		{	
			if (DanNum == "")
			{
				MessageBox(_T("��������ǰ׺�Ͷ�����"), _T("��ʾ"));
				m_AfterOldEditContrl.SetFocus();
				m_AfterOldBodyEdit = _T("");
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}			
			OperateDB.OpenRecordset(AfterSelectPre);
			if (OperateDB.m_pRecordset->adoEOF)
			{
				MessageBox(_T("��ǰ׺�ѱ�ɾ����������ѡ��ǰ׺"), _T("��ʾ"));
				DanNum = _T("");
				OperateDB.CloseRecordset();
				m_AfterOldEditContrl.SetFocus();
				m_AfterOldBodyEdit = _T("");
				UpdateData(FALSE);
				ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_PLO_BODYNUM_STATIC, _T("δѡ��"));
				ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_PLO_SINGLEBODYNUM_STATIC, _T("δѡ��"));
				ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_MAINBOARDNUM_STATIC, _T("δѡ��"));
				ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_ZHIDANNUM, _T("δѡ��"));
				ProjectorTestSystemDlg->m_BeforeOld.SetDlgItemText(IDC_BEFOREOLD_STATIC, _T("δѡ��"));
				ProjectorTestSystemDlg->m_OldUp.SetDlgItemText(IDC_OLDUP_STATIC, _T("δѡ��"));
				ProjectorTestSystemDlg->m_OldDown.SetDlgItemText(IDC_OLDDOWN_STATIC, _T("δѡ��"));
				ProjectorTestSystemDlg->m_AfterOld.SetDlgItemText(IDC_AFTEROLD_STATIC, _T("δѡ��"));
				ProjectorTestSystemDlg->m_BeforeBright.SetDlgItemText(IDC_BEFOREBRIGHT_STATIC, _T("δѡ��"));
				ProjectorTestSystemDlg->m_Fix.SetDlgItemText(IDC_FIX_STATIC, _T("δѡ��"));
				ProjectorTestSystemDlg->m_Fix.SetDlgItemText(IDC_FIX_SINGLEBODYNUM_STATIC, _T("δѡ��"));
				ProjectorTestSystemDlg->m_Fix.SetDlgItemTextA(IDC_FIX_MAINBOARDNUM_STATIC, _T("δѡ��"));
				ProjectorTestSystemDlg->m_Pack.SetDlgItemText(IDC_PACK_STATIC, _T("δѡ��"));
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			AfterOldStaticLength = m_AfterOldBody.GetLength();
			AfterOldBodyEditStr = m_AfterOldBodyEdit.Left(AfterOldStaticLength);
			if (AfterOldBodyEditStr != m_AfterOldBody || m_AfterOldBodyEdit == "")
			{
				MessageBox(_T("���������"),_T("��ʾ"));
				m_AfterOldEditContrl.SetFocus();
				m_AfterOldBodyEdit = _T("");
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			try
			{
				AfterOldSelectSql.Format(_T("select * from ProjectorInformation_MainTable where FuselageCode = '%s' and ZhiDan = '%s'"), m_AfterOldBodyEdit,DanNum);
				OperateDB.OpenRecordset(AfterOldSelectSql);
				AfterOldRecodCount = OperateDB.GetRecordCount();
				if (AfterOldRecodCount == 0)
				{
					MessageBox(_T("�������ڲ����ڸû�����"),_T("��ʾ"));
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
					MessageBox(_T("�ò�Ʒ��û���¼��ϻ�"), _T("��ʾ"));
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
				if (mPostAgingTestTime2.vt != VT_NULL)
				{
					SYSTEMTIME myAfterTime;
					VariantTimeToSystemTime((COleDateTime)mPostAgingTestTime2, &myAfterTime);
					CString decrition;
					decrition.Format(_T("�ò�Ʒ�Ѿ��������ϻ������, �ڶ��β���ʱ��Ϊ�� %d-%d-%d %d:%d:%d"), myAfterTime.wYear,myAfterTime.wMonth,myAfterTime.wDay\
					,myAfterTime.wHour,myAfterTime.wMinute,myAfterTime.wSecond);
					MessageBox(decrition, _T("��ʾ"));
					m_AfterOldEditContrl.SetFocus();
					m_AfterOldBodyEdit = "";
					UpdateData(FALSE);
					OperateDB.CloseRecordset();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (mPostAgingTestTime.vt == VT_NULL)
				{
					FirstAfterTimeStr = GetTime();
					AfterOldUpdateSql.Format(_T("UPDATE ProjectorInformation_MainTable SET PostAgingTestTime = '%s' WHERE FuselageCode = '%s'"), FirstAfterTimeStr, m_AfterOldBodyEdit);
					OperateDB.ExecuteByConnection(AfterOldUpdateSql);
					m_AfetrOldList.InsertItem(AfterOldFirstRow, m_AfterOldBodyEdit);
					m_AfetrOldList.SetItemText(AfterOldFirstRow, 1, FirstAfterTimeStr);
					m_AfetrOldList.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
					AfterOldFirstRow++;
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
					m_AfetrOldList.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
					AfterOldFirstRow++;
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
