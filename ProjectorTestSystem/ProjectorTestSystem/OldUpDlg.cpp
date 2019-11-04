// OldUpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "OldUpDlg.h"
#include "afxdialogex.h"
#include "ResizeCtrl.h"
#include "ProjectorTestSystemDlg.h"
// COldUpDlg 对话框

/*全局变量*/
int OldFirstRow = 0;
COldUpDlg *OldUpDlg;
CWindowSizeMange OldUp;
extern CProjectorTestSystemDlg *ProjectorTestSystemDlg;


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


// COldUpDlg 消息处理程序


BOOL COldUpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_OldUpList.SetExtendedStyle(m_OldUpList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_OldUpList.InsertColumn(0, _T("机身码"), LVCFMT_CENTER, 150, 0);
	m_OldUpList.InsertColumn(1, _T("更新时间"), LVCFMT_CENTER, 150, 1);
	OldUpDlg = this;
	OldUp.Init(m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

/*响应回车按键*/
BOOL COldUpDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	CString m_OldUpEditStr,OldUpSelectSql,OldUpTimeStr,OldUpUpdataSql, AfterSelectPre;
	_variant_t FirstOldTime,OldUpTimeVal;
	int m_OldUpStaticLength;
	LONG OldUpRecordestCount;
	UpdateData(TRUE);
	AfterSelectPre.Format(_T("select [TypeName] from ProjectorInformation_EncodingRules where TypeName = '%s'"), DanNum);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_OLDUPEDIT)
		{
			if (DanNum == "")
			{
				MessageBox(_T("请先配置前缀和订单号！"), _T("提示"));
				m_OldUpEdit.SetFocus();
				m_OldUpEditVal = "";
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			OperateDB.OpenRecordset(AfterSelectPre);
			if (OperateDB.m_pRecordset->adoEOF)
			{
				MessageBox(_T("该前缀已被删除，请重新选择前缀"), _T("提示"));
				DanNum = _T("");
				OperateDB.CloseRecordset();
				m_OldUpEdit.SetFocus();
				m_OldUpEditVal = "";
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
			m_OldUpStaticLength = m_OldUpStatic.GetLength();
			m_OldUpEditStr = m_OldUpEditVal.Left(m_OldUpStaticLength);
			if (m_OldUpEditStr != m_OldUpStatic || m_OldUpEditVal=="")
			{
				MessageBox(_T("机身码错误"), _T("提示"));
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
					MessageBox(_T("本订单内不存在该机身码"), _T("提示"));
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
					decrition.Format(_T("该产品已经过老化上架, 上架时间为： %d-%d-%d %d:%d:%d"), myOldUpTime.wYear, myOldUpTime.wMonth, myOldUpTime.wDay\
						, myOldUpTime.wHour, myOldUpTime.wMinute, myOldUpTime.wSecond);
					MessageBox(decrition, _T("提示"));
					OperateDB.CloseRecordset();
					m_OldUpEdit.SetFocus();
					m_OldUpEditVal = "";
					UpdateData(FALSE);
					OperateDB.CloseRecordset();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (FirstOldTime.vt == VT_NULL)
				{
					MessageBox(_T("该产品未做老化前测试"), _T("提示"));
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

/*获取当前时间*/
CString COldUpDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString Tiemstr;
	Tiemstr = time.Format(_T("%Y-%m-%d  %H:%M:%S"));
	return Tiemstr;
}

void COldUpDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	/*CDialogEx::OnOK();*/
}


void COldUpDlg::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	/*CDialogEx::OnCancel();*/
}


void COldUpDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		OldUp.ResizeWindow();
	}
}
