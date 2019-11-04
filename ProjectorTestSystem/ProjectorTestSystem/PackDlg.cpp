// PackDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "PackDlg.h"
#include "afxdialogex.h"
#include "ResizeCtrl.h"
#include "ProjectorTestSystemDlg.h"
// CPackDlg 对话框


/*全局变量*/
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


// CPackDlg 消息处理程序


BOOL CPackDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_PackList.SetExtendedStyle(m_PackList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_PackList.InsertColumn(0, _T("机身码"), LVCFMT_CENTER, 150, 0);
	m_PackList.InsertColumn(1, _T("包装时间"), LVCFMT_CENTER, 150, 1);
	PackDlg = this;
	Pack.Init(m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

/*回车键响应*/
BOOL CPackDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
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
				MessageBox(_T("请先配置前缀和订单号"), _T("提示"));
				m_PackEdit.SetFocus();
				m_PackEditVal = "";
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			OperateDB.OpenRecordset(AfterSelectPre);
			if (OperateDB.m_pRecordset->adoEOF)
			{
				MessageBox(_T("该前缀已被删除，请重新选择前缀"), _T("提示"));
				DanNum = _T("");
				OperateDB.CloseRecordset();
				m_PackEdit.SetFocus();
				m_PackEditVal = "";
				UpdateData(FALSE);
				ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_PLO_BODYNUM_STATIC, _T("未选择"));
				ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_PLO_SINGLEBODYNUM_STATIC, _T("未选择"));
				ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_MAINBOARDNUM_STATIC, _T("未选择"));
				ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_ZHIDANNUM, _T("未选择"));
				ProjectorTestSystemDlg->m_BeforeOld.SetDlgItemText(IDC_BEFOREOLD_STATIC, _T("未选择"));
				ProjectorTestSystemDlg->m_OldUp.SetDlgItemText(IDC_OLDUP_STATIC, _T("未选择"));
				ProjectorTestSystemDlg->m_OldDown.SetDlgItemText(IDC_OLDDOWN_STATIC, _T("未选择"));
				ProjectorTestSystemDlg->m_AfterOld.SetDlgItemText(IDC_AFTEROLD_STATIC, _T("未选择"));
				ProjectorTestSystemDlg->m_BeforeBright.SetDlgItemText(IDC_BEFOREBRIGHT_STATIC, _T("未选择"));
				ProjectorTestSystemDlg->m_Fix.SetDlgItemText(IDC_FIX_STATIC, _T("未选择"));
				ProjectorTestSystemDlg->m_Fix.SetDlgItemText(IDC_FIX_SINGLEBODYNUM_STATIC, _T("未选择"));
				ProjectorTestSystemDlg->m_Fix.SetDlgItemTextA(IDC_FIX_MAINBOARDNUM_STATIC, _T("未选择"));
				ProjectorTestSystemDlg->m_Pack.SetDlgItemText(IDC_PACK_STATIC, _T("未选择"));
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			m_PackStaticLength = m_PackStatic.GetLength();
			m_PackEditStr = m_PackEditVal.Left(m_PackStaticLength);
			if (m_PackEditStr != m_PackStatic || m_PackEditVal == "")
			{
				MessageBox(_T("机身码错误"), _T("提示"));
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
					MessageBox(_T("本订单内不存在该机身码"), _T("提示"));
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
					decrition.Format(_T("该产品已经过扫码包装,扫码时间为 ： %d-%d-%d %d:%d:%d"), myPackTime.wYear, myPackTime.wMonth, myPackTime.wDay\
						, myPackTime.wHour, myPackTime.wMinute, myPackTime.wSecond);
					MessageBox(decrition, _T("提示"));
					OperateDB.CloseRecordset();
					m_PackEdit.SetFocus();
					m_PackEditVal = "";
					UpdateData(FALSE);
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (BrightTime.vt == VT_NULL)
				{
					MessageBox(_T("该产品没有进行亮度测试"), _T("提示"));
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
	// TODO:  在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CPackDlg::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	/*CDialogEx::OnCancel();*/
}

/*获取当前时间*/
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

	// TODO:  在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		Pack.ResizeWindow();
	}
}
