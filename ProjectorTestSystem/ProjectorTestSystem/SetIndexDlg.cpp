// SetIndexDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "SetIndexDlg.h"
#include "afxdialogex.h"
#include "InDanNum.h"
#include "AdoDB.h"
#include "BefroeOldDlg.h"
#include "OldUpDlg.h"
#include "OldDownDlg.h"
#include "AfterOldDlg.h"
#include "BeforeBrightDlg.h"
#include "FixDlg.h"
#include "MainDlg.h"
#include "ProjectorTestSystemDlg.h"



/*全局变量*/
CString m_TypeName,BodyNum, SingleBodyNum, MainBoardNum;
HTREEITEM IsSelect;
extern CProjectorTestSystemDlg * ProjectorTestSystemDlg;
extern CInDanNum * InDanNum;
BOOL NewIndexTypeFlag = FALSE;


//extern CSetIndexDlg * SetIndexDlg;
//extern CPloDlg * PloDlg;
// CSetIndexDlg 对话框

IMPLEMENT_DYNAMIC(CSetIndexDlg, CDialogEx)

CSetIndexDlg::CSetIndexDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetIndexDlg::IDD, pParent)
{

}

CSetIndexDlg::~CSetIndexDlg()
{
}

void CSetIndexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INDEXBUFF, m_SetIndex);
	DDX_Control(pDX, IDC_INDEXTYPE, m_IndexType);
	DDX_Control(pDX, IDC_TOOLINDEX, m_BodyNum);
	DDX_Control(pDX, IDC_SINGLETOOLINDEX, m_SingleBodyNum);
	DDX_Control(pDX, IDC_MAININDEX, m_MainBoardNum);
	DDX_Control(pDX, IDC_SAVE, m_Save);
	DDX_Control(pDX, IDC_ABORTION, m_Abortion);
	DDX_Control(pDX, IDC_CHANGE, m_Change);
	DDX_Control(pDX, IDC_DELETE, m_Delete);
	DDX_Control(pDX, IDC_SELECTINDEX, m_Select);
	DDX_Control(pDX, IDC_NEW, m_New);
}


BEGIN_MESSAGE_MAP(CSetIndexDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SELECTINDEX, &CSetIndexDlg::OnBnClickedSelectindex)
	ON_BN_CLICKED(IDC_NEW, &CSetIndexDlg::OnBnClickedNew)
	ON_BN_CLICKED(IDC_SAVE, &CSetIndexDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_ABORTION, &CSetIndexDlg::OnBnClickedAbortion)
	ON_BN_CLICKED(IDC_CHANGE, &CSetIndexDlg::OnBnClickedChange)
	ON_NOTIFY(TVN_SELCHANGED, IDC_INDEXBUFF, &CSetIndexDlg::OnTvnSelchangedIndexbuff)
	ON_BN_CLICKED(IDC_DELETE, &CSetIndexDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDOK, &CSetIndexDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetIndexDlg 消息处理程序

/*输入订单号*/
void CSetIndexDlg::OnBnClickedSelectindex()
{
	// TODO:  在此添加控件通知处理程序代码
	CInDanNum InDanNum;
	INT_PTR InDanNumnRes;
	CString SubPrefixType;
	GetDlgItemText(IDC_INDEXTYPE, SubPrefixType);
	
	//if (SubPrefixType == _T(""))
	//{
	//	MessageBox(_T("前缀类型为空，请重新选择"));
	//	return;
	//}
	//else
	//{
	//	
		InDanNumnRes = InDanNum.DoModal();
		//InDanNum.m_InDanNum.SetFocus();
	/*}	*/
	if (InDanNumnRes==IDCANCEL)
	{
		return;
	}
}

/*把数据库TypeName字段值插入tree contrl*/
BOOL CSetIndexDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化	
	CString IndexName;
	OperateDB.OpenRecordset(_T("SELECT * FROM ProjectorInformation_EncodingRules"));
	hRoot = m_SetIndex.InsertItem(_T("前缀"), NULL, NULL);
	try
	{
		if (!OperateDB.m_pRecordset->BOF)
			OperateDB.m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox(_T("表内数据为空"));
			OperateDB.CloseRecordset();
			return FALSE;
		}
		// 读入库中各字段并加入列表框中
		while (!OperateDB.m_pRecordset->adoEOF)
		{
			IndexName = OperateDB.m_pRecordset->GetCollect(_T("TypeName"));
			if (IndexName != _T(""))
			{
				m_SetIndex.InsertItem(IndexName, 1, 1, hRoot, TVI_LAST);
			}
			OperateDB.m_pRecordset->MoveNext();
		}
		OperateDB.CloseRecordset();
	}
	catch (_com_error &e)
	{
		OperateDB.m_szErrorMsg = e.ErrorMessage();
		return FALSE;
	}
	//SetIndexDlg = this;

	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

/*新建按钮*/
void CSetIndexDlg::OnBnClickedNew()
{
	// TODO:  在此添加控件通知处理程序代码
	m_BodyNum.SetReadOnly(FALSE);
	m_SingleBodyNum.SetReadOnly(FALSE);
	m_MainBoardNum.SetReadOnly(FALSE);
	m_IndexType.SetReadOnly(FALSE);
	m_Save.EnableWindow(TRUE);
	m_Abortion.EnableWindow(TRUE);
	m_Change.EnableWindow(FALSE);
	m_Select.EnableWindow(FALSE);
	m_Delete.EnableWindow(FALSE);
	m_SetIndex.EnableWindow(FALSE);
	m_New.EnableWindow(FALSE);
	SetDlgItemText(IDC_TOOLINDEX,_T(""));
	SetDlgItemText(IDC_SINGLETOOLINDEX, _T(""));
	SetDlgItemText(IDC_INDEXTYPE, _T(""));
	SetDlgItemText(IDC_MAININDEX,_T(""));
	NewIndexTypeFlag = TRUE;
	m_IndexType.SetFocus();
}

/*保存按钮*/
void CSetIndexDlg::OnBnClickedSave()
{
	// TODO:  在此添加控件通知处理程序代码
	CString Indextype, SubBodyNum, SubSingleBodyNum, SubMainBoardNum, IndexName, SqlUpdate, SqlInsert,CheckSql;
	BOOL InsertFinshFlag = FALSE;
	int IndexCount,RecodCount;	
	int SubSingleBodyNumLength, SubMainBoardNumLength;
	GetDlgItemText(IDC_INDEXTYPE,Indextype);
	GetDlgItemText(IDC_TOOLINDEX, SubBodyNum);
	GetDlgItemText(IDC_SINGLETOOLINDEX, SubSingleBodyNum);
	GetDlgItemText(IDC_MAININDEX, SubMainBoardNum);
	if (Indextype=="")
	{
		MessageBox(_T("前缀类型名不能为空"), _T("提示"));
		NewIndexTypeFlag = FALSE;
		return;
	}
	SubSingleBodyNumLength = SubSingleBodyNum.GetLength();
	SubMainBoardNumLength = SubMainBoardNum.GetLength();
	if (SubSingleBodyNumLength>15)
	{
		MessageBox(_T("光机码前缀位数超限，请重新输入"), _T("提示"));
		NewIndexTypeFlag = FALSE;
		return;
	}
	if (SubMainBoardNumLength>16)
	{
		MessageBox(_T("主板编码前缀位数超限，请重新输入"), _T("提示"));
		NewIndexTypeFlag = FALSE;
		return;
	}
	CheckSql.Format(_T("SELECT * FROM ProjectorInformation_EncodingRules WHERE TypeName = '%s' and Prefix_BodyCode = '%s' and Prefix_OpticalCode = '%s' and Prefix_MotherboardEncoding = '%s'"), Indextype, SubBodyNum, SubSingleBodyNum, SubMainBoardNum);
    OperateDB.OpenRecordset(CheckSql);
	IndexCount = OperateDB.GetRecordCount();
	OperateDB.CloseRecordset();
	if (IndexCount!=0)
	{
		MessageBox(_T("前缀已存在,无需新建或修改"), _T("提示"));
		NewIndexTypeFlag = FALSE;
		InsertFinshFlag = TRUE;
		m_BodyNum.SetReadOnly(FALSE);
		m_SingleBodyNum.SetReadOnly(FALSE);
		m_MainBoardNum.SetReadOnly(FALSE);
		m_IndexType.SetReadOnly(FALSE);
		m_Save.EnableWindow(TRUE);
		m_Abortion.EnableWindow(TRUE);
		m_Change.EnableWindow(FALSE);
		m_Select.EnableWindow(FALSE);
		m_Delete.EnableWindow(FALSE);
		m_SetIndex.EnableWindow(FALSE);
		m_New.EnableWindow(FALSE);
		return;
	}
	else
	{
		CheckSql.Format(_T("SELECT * FROM ProjectorInformation_EncodingRules WHERE TypeName = '%s'"), Indextype);
		OperateDB.OpenRecordset(CheckSql);
		RecodCount = OperateDB.GetRecordCount();
		OperateDB.CloseRecordset();
		if (RecodCount == 0)
		{
			SqlInsert.Format(_T("insert into ProjectorInformation_EncodingRules values('%s','%s','%s','%s')"), Indextype, SubBodyNum, SubSingleBodyNum, SubMainBoardNum);
			InsertFinshFlag = OperateDB.ExecuteByConnection(SqlInsert);
			NewIndexTypeFlag = FALSE;
			if (InsertFinshFlag != TRUE)
			{
				MessageBox(_T("保存失败，请重新修改！"), _T("提示"));
				return;
			}
			MessageBox(_T("保存成功！"), _T("提示"));
			SetDlgItemText(IDC_INDEXTYPE, "");
			SetDlgItemText(IDC_TOOLINDEX, _T(""));
			SetDlgItemText(IDC_SINGLETOOLINDEX, _T(""));
			SetDlgItemText(IDC_MAININDEX, _T(""));
		}
		else
		{
			if (NewIndexTypeFlag==TRUE)
			{
				MessageBox(_T("前缀类型名重复，请重新新建！"),_T("提示"));
				return;
			}
			else
			{
				SqlInsert.Format(_T("UPDATE ProjectorInformation_EncodingRules SET Prefix_BodyCode ='%s',Prefix_OpticalCode='%s',Prefix_MotherboardEncoding='%s' WHERE TypeName = '%s'"), SubBodyNum, SubSingleBodyNum, SubMainBoardNum, Indextype);
				InsertFinshFlag = OperateDB.ExecuteByConnection(SqlInsert);
				NewIndexTypeFlag = FALSE;
	          if(InsertFinshFlag!=TRUE)
	          {
		          MessageBox(_T("保存失败，请重新修改！"), _T("提示"));
		          return;
	          }
				MessageBox(_T("保存成功！"), _T("提示"));
				SetDlgItemText(IDC_INDEXTYPE, "");
				SetDlgItemText(IDC_TOOLINDEX, _T(""));
				SetDlgItemText(IDC_SINGLETOOLINDEX, _T(""));
				SetDlgItemText(IDC_MAININDEX, _T(""));
			}
		
		}		
	}
	//if (Indextype == m_TypeName&&IndexCount != 0)
	//{
	//	SqlUpdate.Format(_T("UPDATE ProjectorInformation_EncodingRules SET Prefix_BodyCode ='%s',Prefix_OpticalCode='%s',Prefix_MotherboardEncoding='%s' WHERE TypeName = '%s'"), BodyNum, SingleBodyNum, MainBoardNum, Indextype);
	//	InsertFinshFlag = OperateDB.ExecuteByConnection(SqlUpdate);
	//	MessageBox(_T("保存成功！"));
	//}
	if (InsertFinshFlag==TRUE)
	{
		m_SetIndex.DeleteAllItems();
		hRoot = m_SetIndex.InsertItem(_T("前缀"), NULL, NULL);
		OperateDB.OpenRecordset(_T("SELECT * FROM ProjectorInformation_EncodingRules"));
		try
		{
			if (!OperateDB.m_pRecordset->BOF)
				OperateDB.m_pRecordset->MoveFirst();
			else
			{
				AfxMessageBox(_T("表内数据为空"));
				return;
			}
			// 读入库中各字段并加入列表框中
			while (!OperateDB.m_pRecordset->adoEOF)
			{
				IndexName = OperateDB.m_pRecordset->GetCollect(_T("TypeName"));
				if (IndexName != _T(""))
				{
					m_SetIndex.InsertItem(IndexName, 1, 1, hRoot, TVI_LAST);
				}
				OperateDB.m_pRecordset->MoveNext();
			}
			OperateDB.CloseRecordset();
		}
		catch (_com_error &e)
		{
			OperateDB.m_szErrorMsg = e.ErrorMessage();
			return;
		}
		OperateDB.CloseRecordset();
		m_BodyNum.SetReadOnly(TRUE);
		m_SingleBodyNum.SetReadOnly(TRUE);
		m_MainBoardNum.SetReadOnly(TRUE);
		m_IndexType.SetReadOnly(TRUE);
		m_Save.EnableWindow(FALSE);
		m_Abortion.EnableWindow(FALSE);
		m_Change.EnableWindow(TRUE);
		m_Select.EnableWindow(TRUE);
		m_Delete.EnableWindow(TRUE);
		m_New.EnableWindow(TRUE);
		m_SetIndex.EnableWindow(TRUE);
	}

}

/*取消按钮*/
void CSetIndexDlg::OnBnClickedAbortion()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_TOOLINDEX, _T(""));
	SetDlgItemText(IDC_SINGLETOOLINDEX, _T(""));
	SetDlgItemText(IDC_INDEXTYPE, _T(""));
	SetDlgItemText(IDC_MAININDEX, _T(""));
	m_BodyNum.SetReadOnly(TRUE);
	m_SingleBodyNum.SetReadOnly(TRUE);
	m_MainBoardNum.SetReadOnly(TRUE);
	m_IndexType.SetReadOnly(TRUE);
	m_Save.EnableWindow(FALSE);
	m_Abortion.EnableWindow(FALSE);
	m_Change.EnableWindow(TRUE);
	m_Select.EnableWindow(TRUE);
	m_Delete.EnableWindow(TRUE);
	m_SetIndex.EnableWindow(TRUE);
	m_New.EnableWindow(TRUE);	
	NewIndexTypeFlag = FALSE;
}

/*修改按钮*/
void CSetIndexDlg::OnBnClickedChange()
{
	// TODO:  在此添加控件通知处理程序代码
	CString TypeNameFlag;
	GetDlgItemText(IDC_INDEXTYPE, TypeNameFlag);
	if (TypeNameFlag=="")
	{
		MessageBox(_T("当前未选中任何前缀类型，请重新选择"), _T("提示"));
		return;
	}
	m_Save.EnableWindow(TRUE);
	m_Abortion.EnableWindow(TRUE);
	m_Change.EnableWindow(FALSE);
	m_Select.EnableWindow(FALSE);
	m_Delete.EnableWindow(FALSE);
	m_New.EnableWindow(FALSE);
	m_BodyNum.SetReadOnly(FALSE);
	m_SingleBodyNum.SetReadOnly(FALSE);
	m_MainBoardNum.SetReadOnly(FALSE);
	m_IndexType.SetReadOnly(TRUE);
	m_SetIndex.EnableWindow(FALSE);
	m_BodyNum.SetFocus();
}

/*树形控件响应函数*/
void CSetIndexDlg::OnTvnSelchangedIndexbuff(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	CString SqlStr;
	IsSelect = m_SetIndex.GetSelectedItem();
	m_TypeName = m_SetIndex.GetItemText(IsSelect);
	if (IsSelect==hRoot)
	{
		SetDlgItemText(IDC_INDEXTYPE,"");
		SetDlgItemText(IDC_TOOLINDEX, _T(""));
		SetDlgItemText(IDC_SINGLETOOLINDEX, _T(""));
		SetDlgItemText(IDC_MAININDEX, _T(""));
		return;
	}
	SqlStr.Format(_T("select Prefix_BodyCode,Prefix_OpticalCode,Prefix_MotherboardEncoding from ProjectorInformation_EncodingRules where TypeName='%s'"), m_TypeName);
	OperateDB.OpenRecordset(SqlStr);
	BodyNum = OperateDB.m_pRecordset->GetCollect(_T("Prefix_BodyCode"));
	SingleBodyNum = OperateDB.m_pRecordset->GetCollect(_T("Prefix_OpticalCode"));
	MainBoardNum = OperateDB.m_pRecordset->GetCollect(_T("Prefix_MotherboardEncoding"));
	SetDlgItemText(IDC_INDEXTYPE, m_TypeName);
	SetDlgItemText(IDC_TOOLINDEX, BodyNum);
	SetDlgItemText(IDC_SINGLETOOLINDEX, SingleBodyNum);
	SetDlgItemText(IDC_MAININDEX, MainBoardNum);
	OperateDB.CloseRecordset();
	*pResult = 0;
}

/*删除按钮*/
void CSetIndexDlg::OnBnClickedDelete()
{
	// TODO:  在此添加控件通知处理程序代码
	CString SqlDelete,TypeNameDeleteFlag;
	CString myIndexName;
	BOOL DeleteFinshFlag = FALSE;
	GetDlgItemText(IDC_INDEXTYPE, TypeNameDeleteFlag);
	if (TypeNameDeleteFlag=="")
	{
		MessageBox(_T("当前未选中任何前缀类型，请重新选择"), _T("提示"));
		return;
	}
	SqlDelete.Format(_T("DELETE FROM ProjectorInformation_EncodingRules WHERE TypeName = '%s'"), m_TypeName);
	DeleteFinshFlag = OperateDB.ExecuteByConnection(SqlDelete);	
	if (DeleteFinshFlag==TRUE)
	{
		if (m_TypeName == DanNum)
		{
			//ProjectorTestSystemDlg->m_Plo.SetDlgItemTextA(IDC_ZHIDANNUM, _T(""));
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
			DanNum = _T("");
		}
		m_SetIndex.DeleteItem(IsSelect);
		SetDlgItemText(IDC_INDEXTYPE, _T(""));
		SetDlgItemText(IDC_TOOLINDEX, _T(""));
		SetDlgItemText(IDC_SINGLETOOLINDEX, _T(""));
		SetDlgItemText(IDC_MAININDEX, _T(""));
			
		MessageBox(_T("删除成功"), _T("提示"));
		OperateDB.OpenRecordset(_T("SELECT * FROM ProjectorInformation_EncodingRules"));
		try
		{
			if (!OperateDB.m_pRecordset->BOF)
				OperateDB.m_pRecordset->MoveFirst();
			else
			{
				AfxMessageBox(_T("表内数据为空"));
				OperateDB.CloseRecordset();
				return ;
			}
			// 读入库中各字段并加入列表框中
			while (!OperateDB.m_pRecordset->adoEOF)
			{
				myIndexName = OperateDB.m_pRecordset->GetCollect(_T("TypeName"));
				if (myIndexName != _T(""))
				{
					m_SetIndex.InsertItem(myIndexName, 1, 1, hRoot, TVI_LAST);
				}
				OperateDB.m_pRecordset->MoveNext();
			}
			OperateDB.CloseRecordset();
		}
		catch (_com_error &e)
		{
			OperateDB.m_szErrorMsg = e.ErrorMessage();
			return ;
		}
	}
	else
	{
		MessageBox(_T("删除失败"), _T("提示"));
	}
}

/*确认键*/
void CSetIndexDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	/*GetDlgItemText(IDC_INDEXTYPE, PrefixType);
	GetDlgItemText(IDC_TOOLINDEX, BodyNumPrefix);
	GetDlgItemText(IDC_SINGLETOOLINDEX, SingleBodyNumPrefix);
	GetDlgItemText(IDC_MAININDEX, MainBoardNumPrefix);
	if (DanNum!="")
	{
		ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_PLO_BODYNUM_STATIC, BodyNumPrefix);
		ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_PLO_SINGLEBODYNUM_STATIC, SingleBodyNumPrefix);
		ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_MAINBOARDNUM_STATIC, MainBoardNumPrefix);
		ProjectorTestSystemDlg->m_BeforeOld.SetDlgItemText(IDC_BEFOREOLD_STATIC, BodyNumPrefix);
		ProjectorTestSystemDlg->m_OldUp.SetDlgItemText(IDC_OLDUP_STATIC, BodyNumPrefix);
		ProjectorTestSystemDlg->m_OldDown.SetDlgItemText(IDC_OLDDOWN_STATIC, BodyNumPrefix);
		ProjectorTestSystemDlg->m_AfterOld.SetDlgItemText(IDC_AFTEROLD_STATIC, BodyNumPrefix);
		ProjectorTestSystemDlg->m_BeforeBright.SetDlgItemText(IDC_BEFOREBRIGHT_STATIC, BodyNumPrefix);
		ProjectorTestSystemDlg->m_Fix.SetDlgItemText(IDC_FIX_STATIC, BodyNumPrefix);
		ProjectorTestSystemDlg->m_Fix.SetDlgItemText(IDC_FIX_SINGLEBODYNUM_STATIC, SingleBodyNumPrefix);
		ProjectorTestSystemDlg->m_Fix.SetDlgItemTextA(IDC_FIX_MAINBOARDNUM_STATIC, MainBoardNumPrefix);
		ProjectorTestSystemDlg->m_Pack.SetDlgItemText(IDC_PACK_STATIC, BodyNumPrefix);
		ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_ZHIDANNUM, DanNum);
		NewIndexTypeFlag = FALSE;
		CDialogEx::OnOK();
	}
	else
	{
		ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_PLO_BODYNUM_STATIC, _T("未选择"));
		ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_PLO_SINGLEBODYNUM_STATIC, _T("未选择"));
		ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_MAINBOARDNUM_STATIC, _T("未选择"));
		ProjectorTestSystemDlg->m_BeforeOld.SetDlgItemText(IDC_BEFOREOLD_STATIC, _T("未选择"));
		ProjectorTestSystemDlg->m_OldUp.SetDlgItemText(IDC_OLDUP_STATIC, _T("未选择"));
		ProjectorTestSystemDlg->m_OldDown.SetDlgItemText(IDC_OLDDOWN_STATIC, _T("未选择"));
		ProjectorTestSystemDlg->m_AfterOld.SetDlgItemText(IDC_AFTEROLD_STATIC, _T("未选择"));
		ProjectorTestSystemDlg->m_BeforeBright.SetDlgItemText(IDC_BEFOREBRIGHT_STATIC, _T("未选择"));
		ProjectorTestSystemDlg->m_Fix.SetDlgItemText(IDC_FIX_STATIC, _T("未选择"));
		ProjectorTestSystemDlg->m_Fix.SetDlgItemText(IDC_FIX_SINGLEBODYNUM_STATIC, _T("未选择"));
		ProjectorTestSystemDlg->m_Fix.SetDlgItemTextA(IDC_FIX_MAINBOARDNUM_STATIC, _T("未选择"));
		ProjectorTestSystemDlg->m_Pack.SetDlgItemText(IDC_PACK_STATIC, _T("未选择"));
		ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_ZHIDANNUM, _T("未选择"));*/
	//	NewIndexTypeFlag = FALSE;
	///*	CDialogEx::OnOK();*/
	//}
}
	
void CSetIndexDlg::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	NewIndexTypeFlag = FALSE;
	CDialogEx::OnCancel();
}
