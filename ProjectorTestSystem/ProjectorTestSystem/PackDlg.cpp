// PackDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "PackDlg.h"
#include "afxdialogex.h"
#include "ResizeCtrl.h"
#include "ProjectorTestSystemDlg.h"
// CPackDlg �Ի���


/*ȫ�ֱ���*/
int PackFirstRow = 0;
CPackDlg *PackDlg;
CWindowSizeMange Pack;
extern CProjectorTestSystemDlg *ProjectorTestSystemDlg;
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
	CString m_PackEditStr, PackSelectSql, PackTimeStr, PackUpdataSql, AfterSelectPre;
	int m_PackStaticLength;
	LONG PackRecordestCount;
	_variant_t BrightTime,PackTimeVal;
	UpdateData(TRUE);
	AfterSelectPre.Format(_T("select [TypeName] from ProjectorInformation_EncodingRules where TypeName = '%s'"), DanNum);
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
			OperateDB.OpenRecordset(AfterSelectPre);
			if (OperateDB.m_pRecordset->adoEOF)
			{
				MessageBox(_T("��ǰ׺�ѱ�ɾ����������ѡ��ǰ׺"), _T("��ʾ"));
				DanNum = _T("");
				OperateDB.CloseRecordset();
				m_PackEdit.SetFocus();
				m_PackEditVal = "";
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
				PackTimeVal = OperateDB.m_pRecordset->GetCollect(_T("PackingTime"));
				if (PackTimeVal.vt!=VT_NULL)
				{
					SYSTEMTIME myPackTime;
					VariantTimeToSystemTime((COleDateTime)PackTimeVal, &myPackTime);
					CString decrition;
					decrition.Format(_T("�ò�Ʒ�Ѿ���ɨ���װ,ɨ��ʱ��Ϊ �� %d-%d-%d %d:%d:%d"), myPackTime.wYear, myPackTime.wMonth, myPackTime.wDay\
						, myPackTime.wHour, myPackTime.wMinute, myPackTime.wSecond);
					MessageBox(decrition, _T("��ʾ"));
					OperateDB.CloseRecordset();
					m_PackEdit.SetFocus();
					m_PackEditVal = "";
					UpdateData(FALSE);
					return CDialogEx::PreTranslateMessage(pMsg);
				}
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
					m_PackList.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
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
