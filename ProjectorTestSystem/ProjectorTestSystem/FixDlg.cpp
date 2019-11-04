// FixDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "FixDlg.h"
#include "afxdialogex.h"
#include "ResizeCtrl.h"
#include "ProjectorTestSystemDlg.h"
// CFixDlg 对话框

/*全局变量*/
int FixFirstRow = 0;
CFixDlg *FixDlg;
CWindowSizeMange Fix;
extern CProjectorTestSystemDlg *ProjectorTestSystemDlg;
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
	ON_BN_CLICKED(IDC_CHECK2, &CFixDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CFixDlg::OnBnClickedCheck3)
END_MESSAGE_MAP()


// CFixDlg 消息处理程序


BOOL CFixDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_FixList.SetExtendedStyle(m_FixList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_FixList.InsertColumn(0, _T("机身码"), LVCFMT_CENTER, 150, 0);
	m_FixList.InsertColumn(1, _T("维系描述"), LVCFMT_CENTER, 250, 1);
	m_FixList.InsertColumn(2, _T("维修后光机码"), LVCFMT_CENTER, 150, 2);
	m_FixList.InsertColumn(3, _T("维修后主板编码"), LVCFMT_CENTER, 150, 3);
	m_FixList.InsertColumn(4, _T("更新时间"), LVCFMT_CENTER, 150, 4);
	FixDlg = this;
	Fix.Init(m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


/*获取当前时间*/
CString CFixDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString Tiemstr;
	Tiemstr = time.Format(_T("%Y-%m-%d  %H:%M:%S"));
	return Tiemstr;
}

/*回车键响应*/
BOOL CFixDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	CString FixTimeStr, m_FixBodyNumValStr, m_FixSingleBodyNumValStr, m_FixMainBoardNumValStr, mFixFuselageCode, InsertIntoSql;
	CString mOpticalCode, SelectSqlEdit2, SelectSqlEdit1, mMainBoardCode, AfterSelectPre;
	BOOL SelectFinhFlag = FALSE;
	LONG FixRecodestCount = 0;
	int m_FixBodyNumStaticValLength, m_FixSingleBodyNumStaticValLength, m_FixMainBoardNumStaticValLength;
	int m_FixSingleBodyNumLength, m_FixMainBoardNumLength;
	FixTimeStr = GetTime();
	UpdateData(TRUE);
	AfterSelectPre.Format(_T("select [TypeName] from ProjectorInformation_EncodingRules where TypeName = '%s'"), DanNum);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_FIXBODY)
		{
			try
			{
				if (DanNum == "")
				{
					MessageBox(_T("请先配置前缀和订单号！"), _T("提示"));
					OperateDB.CloseRecordset();
					m_FixSingleNumEdit.SetFocus();
					m_FixSingleBodyEditVal = "";
					UpdateData(FALSE);
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				OperateDB.OpenRecordset(AfterSelectPre);
			if (OperateDB.m_pRecordset->adoEOF)
			{
				MessageBox(_T("该前缀已被删除，请重新选择前缀"), _T("提示"));
				DanNum = _T("");
				OperateDB.CloseRecordset();
				m_FixSingleNumEdit.SetFocus();
				m_FixSingleBodyEditVal = "";
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
				SelectSqlEdit1.Format(_T("SELECT * FROM ProjectorInformation_MainTable WHERE FuselageCode = '%s'and ZhiDan = '%s'"), m_FixSingleBodyEditVal,DanNum);
				OperateDB.OpenRecordset(SelectSqlEdit1);
				FixRecodestCount = OperateDB.GetRecordCount();
				if (FixRecodestCount == 0)
				{
					MessageBox(_T("本订单内不存在该机身码"), _T("提示"));
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
					MessageBox(_T("机身码错误！"), _T("提示"));
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
				if (DanNum == "")
				{
					MessageBox(_T("请先配置前缀和订单号！"), _T("提示"));
					OperateDB.CloseRecordset();
					m_FixSingleNumEdit.SetFocus();
					m_FixSingleBodyEditVal = "";
					UpdateData(FALSE);
					return CDialogEx::PreTranslateMessage(pMsg);
				}

				try
				{
					OperateDB.OpenRecordset(AfterSelectPre);
					if (OperateDB.m_pRecordset->adoEOF)
					{
						MessageBox(_T("该前缀已被删除，请重新选择前缀"), _T("提示"));
						DanNum = _T("");
						m_FixText.SetFocus();
						m_FixTextVal = "";
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
					InsertIntoSql.Format(_T("UPDATE ProjectorInformation_MainTable SET RepairText='%s',RepairTime='%s'  WHERE FuselageCode = '%s'"), m_FixTextVal, FixTimeStr, m_FixSingleBodyEditVal);
					OperateDB.ExecuteByConnection(InsertIntoSql);
					m_FixList.InsertItem(FixFirstRow, m_FixSingleBodyEditVal);
					m_FixList.SetItemText(FixFirstRow, 1, m_FixTextVal);
					m_FixList.SetItemText(FixFirstRow, 4, FixTimeStr);
					m_FixList.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
					FixFirstRow++;
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
				if (DanNum == "")
				{
					MessageBox(_T("请先配置前缀和订单号！"), _T("提示"));
					m_AfterFixSingleEditVal = _T("");
					UpdateData(FALSE);
					m_AfterFixSingleEdit.SetFocus();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				OperateDB.OpenRecordset(AfterSelectPre);
				if (OperateDB.m_pRecordset->adoEOF)
				{
					MessageBox(_T("该前缀已被删除，请重新选择前缀"), _T("提示"));
					DanNum = _T("");
					m_AfterFixSingleEditVal = _T("");
					UpdateData(FALSE);
					m_AfterFixSingleEdit.SetFocus();
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
				m_FixSingleBodyNumStaticValLength = m_FixSingleStaticVal.GetLength();
				m_FixSingleBodyNumValStr = m_AfterFixSingleEditVal.Left(m_FixSingleBodyNumStaticValLength);
				m_FixSingleBodyNumLength = m_AfterFixSingleEditVal.GetLength();
				if (m_FixSingleBodyNumValStr != m_FixSingleStaticVal || m_AfterFixSingleEditVal == "")
				{
					MessageBox(_T("光机码错误"), _T("提示"));
					m_AfterFixSingleEditVal = _T("");
					UpdateData(FALSE);
					m_AfterFixSingleEdit.SetFocus();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (m_FixSingleBodyNumLength > 15)
				{
					MessageBox(_T("光机码位数超限"), _T("提示"));
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
					MessageBox(_T("光机码重复"), _T("提示"));
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
					m_FixList.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
					FixFirstRow++;
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
				if (DanNum == "")
				{
					MessageBox(_T("请先配置前缀和订单号！"), _T("提示"));
					m_AfterFixMainEditVal = _T("");
					UpdateData(FALSE);
					m_AfterFixMainEdit.SetFocus();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				OperateDB.OpenRecordset(AfterSelectPre);
				if (OperateDB.m_pRecordset->adoEOF)
				{
					MessageBox(_T("该前缀已被删除，请重新选择前缀"), _T("提示"));
					DanNum = _T("");
					OperateDB.CloseRecordset();
					m_AfterFixMainEditVal = _T("");
					UpdateData(FALSE);
					m_AfterFixMainEdit.SetFocus();
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
				m_FixMainBoardNumStaticValLength = m_FixMainStaticVal.GetLength();
				m_FixMainBoardNumValStr = m_AfterFixMainEditVal.Left(m_FixMainBoardNumStaticValLength);
				m_FixMainBoardNumLength = m_AfterFixMainEditVal.GetLength();
				if (m_FixMainBoardNumValStr != m_FixMainStaticVal || m_AfterFixMainEditVal == "")
				{
					MessageBox(_T("主板编码错误"), _T("提示"));
					m_AfterFixMainEditVal = _T("");
					UpdateData(FALSE);
					m_AfterFixMainEdit.SetFocus();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (m_FixMainBoardNumLength > 16)
				{
					MessageBox(_T("主板编码位数超限"), _T("提示"));
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
					MessageBox(_T("主板编码重复"), _T("提示"));
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
				m_FixList.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
				FixFirstRow++;
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
		/*if (pMsg->message != 0 && pMsg->wParam != 0)
		{
			FixFirstRow++;
		}*/
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CFixDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CFixDlg::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	/*CDialogEx::OnCancel();*/
}


void CFixDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		Fix.ResizeWindow();
	}
}

/*维修和光机码编辑框使能*/
void CFixDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL MainBoardNumCheck = FALSE;
	UpdateData(TRUE);
	MainBoardNumCheck = m_FixSingleBodyState;
	if (MainBoardNumCheck == TRUE)
	{
		/*m_PloMainBoardNumEcit.EnableWindow(TRUE);*/
	}
	else
	{
		m_AfterFixSingleEdit.EnableWindow(FALSE);
		m_AfterFixSingleEdit.SetWindowTextA(_T(""));
	}
}


void CFixDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL MainBoardNumCheck = FALSE;
	UpdateData(TRUE);
	MainBoardNumCheck = m_FixMainBoardState;
	if (MainBoardNumCheck == TRUE)
	{
		/*m_PloMainBoardNumEcit.EnableWindow(TRUE);*/
	}
	else
	{
		m_AfterFixMainEdit.EnableWindow(FALSE);
		m_AfterFixMainEdit.SetWindowTextA(_T(""));
	}
}
