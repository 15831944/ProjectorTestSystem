// BefroeOldDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "BefroeOldDlg.h"
#include "afxdialogex.h"
#include "ResizeCtrl.h"
#include "ProjectorTestSystemDlg.h"
// CBefroeOldDlg 对话框


/*全局变量*/
int BeforeOldFirstRow = 0;
CBefroeOldDlg *BrforeOldDlg;
CWindowSizeMange BeforeOld;
extern CProjectorTestSystemDlg *ProjectorTestSystemDlg;

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


// CBefroeOldDlg 消息处理程序


BOOL CBefroeOldDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_BeforeOldList.SetExtendedStyle(m_BeforeOldList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_BeforeOldList.InsertColumn(0, _T("机身码"), LVCFMT_CENTER, 150, 0);
	m_BeforeOldList.InsertColumn(1, _T("第一次测试时间"), LVCFMT_CENTER, 150, 1);
	m_BeforeOldList.InsertColumn(2, _T("第二次测试时间"), LVCFMT_CENTER, 150, 2);
	BrforeOldDlg = this;
	BeforeOld.Init(m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

/*响应回车键*/
BOOL CBefroeOldDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	CString BeforeOldNum, BeforeOldSelectSql, BeforeOldBodyEditStr, BeforeOldUpdateSql;
	CString FirstBeforeTimeStr, SecondBeforeTimeStr, sTimeOneStr, sTimeTwoStr, AfterSelectPre;
	_variant_t mPreAgingTestTime, mPreAgingTestTime2;
	LONG BeforeOldRecodCount;
	SYSTEMTIME sTimeOne;
	int BefordOldStaticLength;
	UpdateData(TRUE);
	AfterSelectPre.Format(_T("select [TypeName] from ProjectorInformation_EncodingRules where TypeName = '%s'"), DanNum);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_BEFOREOLD_BODY)
		{
			if (DanNum == "")
			{
				MessageBox(_T("请先配置前缀和订单号！"), _T("提示"));
				m_BeforeOldEditContrl.SetFocus();
				m_BeforeOldBodyEdit = "";
				UpdateData(FALSE);
				return CDialogEx::PreTranslateMessage(pMsg);
			}		
			OperateDB.OpenRecordset(AfterSelectPre);
			if (OperateDB.m_pRecordset->adoEOF)
			{
				MessageBox(_T("该前缀已被删除，请重新选择前缀"), _T("提示"));
				DanNum = _T("");
				OperateDB.CloseRecordset();
				m_BeforeOldEditContrl.SetFocus();
				m_BeforeOldBodyEdit = "";
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
			BefordOldStaticLength = m_BeforeOldBody.GetLength();
			BeforeOldBodyEditStr = m_BeforeOldBodyEdit.Left(BefordOldStaticLength);
			if (BeforeOldBodyEditStr != m_BeforeOldBody || m_BeforeOldBodyEdit == "")
			{
				MessageBox(_T("机身码错误"), _T("提示"));
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
					MessageBox(_T("本订单内不存在该机身码"), _T("提示"));
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
				if (mPreAgingTestTime2.vt!=VT_NULL)
				{
					SYSTEMTIME myBefroeTime;
					VariantTimeToSystemTime((COleDateTime)mPreAgingTestTime2, &myBefroeTime);
					CString decrition;
					decrition.Format(_T("该产品已经过两次老化前测试, 第二次测试时间为： %d-%d-%d %d:%d:%d"), myBefroeTime.wYear, myBefroeTime.wMonth, myBefroeTime.wDay\
						, myBefroeTime.wHour, myBefroeTime.wMinute, myBefroeTime.wSecond);
					MessageBox(decrition, _T("提示"));
					m_BeforeOldEditContrl.SetFocus();
					m_BeforeOldBodyEdit = "";
					UpdateData(FALSE);
					OperateDB.CloseRecordset();
					return CDialogEx::PreTranslateMessage(pMsg);
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


/*获取当前时间*/
CString CBefroeOldDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString Tiemstr;
	Tiemstr = time.Format(_T("%Y-%m-%d  %H:%M:%S"));
	return Tiemstr;
}


void CBefroeOldDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CBefroeOldDlg::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	/*CDialogEx::OnCancel();*/
}


void CBefroeOldDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		BeforeOld.ResizeWindow();
	}
}
