// OldDownDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "OldDownDlg.h"
#include "afxdialogex.h"
#include "ResizeCtrl.h"
#include "ProjectorTestSystemDlg.h"
// COldDownDlg 对话框


/*全局变量*/
int OldDownFirstRow = 0;
COldDownDlg *OldDownDlg;
CWindowSizeMange OldDown;
IMPLEMENT_DYNAMIC(COldDownDlg, CDialogEx)
extern CProjectorTestSystemDlg *ProjectorTestSystemDlg;
COldDownDlg::COldDownDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COldDownDlg::IDD, pParent)
	, m_OldDownStaticVal(_T(""))
	, m_OldDownEditVal(_T(""))
{

}

COldDownDlg::~COldDownDlg()
{
}

void COldDownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_OldDownlist);
	DDX_Control(pDX, IDC_OLDDOWN_STATIC, m_OldDown);
	DDX_Text(pDX, IDC_OLDDOWN_STATIC, m_OldDownStaticVal);
	//DDX_Control(pDX, IDC_EDIT3, m_OldDownEdit);
	//DDX_Text(pDX, IDC_EDIT3, m_OldDownEditVal);
	DDX_Text(pDX, IDC_OLDDOWN, m_OldDownEditVal);
	DDX_Control(pDX, IDC_OLDDOWN, m_OldDownEdit);
}


BEGIN_MESSAGE_MAP(COldDownDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// COldDownDlg 消息处理程序


BOOL COldDownDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_OldDownlist.SetExtendedStyle(m_OldDownlist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_OldDownlist.InsertColumn(0, _T("机身码"), LVCFMT_CENTER, 150, 0);
	m_OldDownlist.InsertColumn(1, _T("更新时间"), LVCFMT_CENTER, 150, 1);
	OldDownDlg = this;
	OldDown.Init(m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}



/*回车键响应*/
BOOL COldDownDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	CString m_OldDownEditStr, OldDownSelectSql, OldDownTimeStr, OldDownUpdataSql, AfterSelectPre;
	_variant_t OldUpTime,OldDownTimeVal;
	int m_OldDownStaticLength;
	LONG OldDownRecordestCount;
	UpdateData(TRUE);
	AfterSelectPre.Format(_T("select [TypeName] from ProjectorInformation_EncodingRules where TypeName = '%s'"), DanNum);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_OLDDOWN)
		{
			if (DanNum == "")
			{
				MessageBox(_T("请先配置前缀和订单号！"), _T("提示"));
				m_OldDownEdit.SetFocus();
				m_OldDownEditVal = "";
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			OperateDB.OpenRecordset(AfterSelectPre);
			if (OperateDB.m_pRecordset->adoEOF)
			{
				MessageBox(_T("该前缀已被删除，请重新选择前缀"), _T("提示"));
				DanNum = _T("");
				OperateDB.CloseRecordset();
				m_OldDownEdit.SetFocus();
				m_OldDownEditVal = "";
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
			m_OldDownStaticLength = m_OldDownStaticVal.GetLength();
			m_OldDownEditStr = m_OldDownEditVal.Left(m_OldDownStaticLength);
			if (m_OldDownEditStr != m_OldDownStaticVal || m_OldDownEditVal == "")
			{
				MessageBox(_T("机身码错误"), _T("提示"));
				m_OldDownEdit.SetFocus();
				m_OldDownEditVal = "";
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			try{
				OldDownSelectSql.Format(_T("select * from ProjectorInformation_MainTable where FuselageCode = '%s' and ZhiDan = '%s'"), m_OldDownEditVal,DanNum);
				OperateDB.OpenRecordset(OldDownSelectSql);
				OldDownRecordestCount = OperateDB.GetRecordCount();
				if (OldDownRecordestCount == 0)
				{
					MessageBox(_T("本订单内不存在该机身码"), _T("提示"));
					OperateDB.CloseRecordset();
					m_OldDownEdit.SetFocus();
					m_OldDownEditVal = "";
					UpdateData(FALSE);
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (!OperateDB.m_pRecordset->BOF)
					OperateDB.m_pRecordset->MoveFirst();
				OldUpTime = OperateDB.m_pRecordset->GetCollect(_T("AgeingBeginTime"));
				OldDownTimeVal = OperateDB.m_pRecordset->GetCollect(_T("AgeingEndTime"));
				if (OldDownTimeVal.vt!=VT_NULL)
				{
					SYSTEMTIME myOldDownTime;
					VariantTimeToSystemTime((COleDateTime)OldDownTimeVal, &myOldDownTime);
					CString decrition;
					decrition.Format(_T("该产品已经过老化下架, 下架时间为： %d-%d-%d %d:%d:%d"), myOldDownTime.wYear, myOldDownTime.wMonth, myOldDownTime.wDay\
						, myOldDownTime.wHour, myOldDownTime.wMinute, myOldDownTime.wSecond);
					MessageBox(decrition, _T("提示"));
					OperateDB.CloseRecordset();
					m_OldDownEdit.SetFocus();
					m_OldDownEditVal = "";
					UpdateData(FALSE);
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (OldUpTime.vt == VT_NULL)
				{
					MessageBox(_T("该产品没有上架老化"), _T("提示"));
					OperateDB.CloseRecordset();
					m_OldDownEdit.SetFocus();
					m_OldDownEditVal = "";
					UpdateData(FALSE);
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				else
				{
					OldDownTimeStr = GetTime();
					OldDownUpdataSql.Format(_T("UPDATE ProjectorInformation_MainTable SET AgeingEndTime = '%s' WHERE FuselageCode = '%s'"), OldDownTimeStr, m_OldDownEditVal);
					OperateDB.ExecuteByConnection(OldDownUpdataSql);
					m_OldDownlist.InsertItem(OldDownFirstRow, m_OldDownEditVal);
					m_OldDownlist.SetItemText(OldDownFirstRow, 1, OldDownTimeStr);
					m_OldDownlist.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
					OldDownFirstRow++;
					OperateDB.CloseRecordset();
					m_OldDownEdit.SetFocus();
					m_OldDownEditVal = "";
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
CString COldDownDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString Tiemstr;
	Tiemstr = time.Format(_T("%Y-%m-%d  %H:%M:%S"));
	return Tiemstr;
}



void COldDownDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	/*CDialogEx::OnOK();*/
}


void COldDownDlg::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	/*CDialogEx::OnCancel();*/
}


void COldDownDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		OldDown.ResizeWindow();
	}
}
