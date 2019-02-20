// InDanNum.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "InDanNum.h"
#include "afxdialogex.h"
#include "ProjectorTestSystemDlg.h"


/*ȫ�ֱ���*/
extern CProjectorTestSystemDlg * ProjectorTestSystemDlg;


// CInDanNum �Ի���

IMPLEMENT_DYNAMIC(CInDanNum, CDialogEx)

CInDanNum::CInDanNum(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInDanNum::IDD, pParent)
{

}

CInDanNum::~CInDanNum()
{
}

void CInDanNum::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DANNUMBER, m_InDanNum);
}


BEGIN_MESSAGE_MAP(CInDanNum, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInDanNum::OnBnClickedOk)
END_MESSAGE_MAP()


// CInDanNum ��Ϣ�������

/*ȷ�Ϻ���*/
void CInDanNum::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString InSelectFromSql;
	int TypeCount;
	_variant_t TypeVal, BodyVal, SingleBodyVal, MainVal;
	GetDlgItemText(IDC_DANNUMBER, DanNum);
	if (DanNum.IsEmpty())
	{
		MessageBox(_T("�����Ų���Ϊ�գ����������룡"),_T("��ʾ"));
		ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_PLO_BODYNUM_STATIC, _T("δѡ��"));
		ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_PLO_SINGLEBODYNUM_STATIC, _T("δѡ��"));
		ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_MAINBOARDNUM_STATIC, _T("δѡ��"));
		ProjectorTestSystemDlg->m_BeforeOld.SetDlgItemText(IDC_BEFOREOLD_STATIC, _T("δѡ��"));
		ProjectorTestSystemDlg->m_OldUp.SetDlgItemText(IDC_OLDUP_STATIC, _T("δѡ��"));
		ProjectorTestSystemDlg->m_OldDown.SetDlgItemText(IDC_OLDDOWN_STATIC, _T("δѡ��"));
		ProjectorTestSystemDlg->m_AfterOld.SetDlgItemText(IDC_AFTEROLD_STATIC, _T("δѡ��"));
		ProjectorTestSystemDlg->m_BeforeBright.SetDlgItemText(IDC_BEFOREBRIGHT_STATIC, _T("δѡ��"));
		ProjectorTestSystemDlg->m_Fix.SetDlgItemText(IDC_FIX_STATIC, _T("δѡ��"));
		ProjectorTestSystemDlg->m_Fix.SetDlgItemText(IDC_FIX_SINGLEBODYNUM_STATIC, _T("δѡ��"));
		ProjectorTestSystemDlg->m_Fix.SetDlgItemTextA(IDC_FIX_MAINBOARDNUM_STATIC, _T("δѡ��"));
		ProjectorTestSystemDlg->m_Pack.SetDlgItemText(IDC_PACK_STATIC, _T("δѡ��"));
		ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_ZHIDANNUM, _T("δѡ��"));
		m_InDanNum.SetFocus();
		return;
	}
	try
	{
		InSelectFromSql.Format(_T("select * from ProjectorInformation_EncodingRules where TypeName = '%s'"), DanNum);
		OperateDB.OpenRecordset(InSelectFromSql);
		TypeCount = OperateDB.GetRecordCount();
		if (TypeCount == 0)
		{
			MessageBox(_T("��������ǰ׺��������ƥ�䣬���������붩����"));
			OperateDB.CloseRecordset();
			return;
		}
		else
		{
			TypeVal = OperateDB.m_pRecordset->GetCollect(_T("TypeName"));
			BodyVal = OperateDB.m_pRecordset->GetCollect(_T("Prefix_BodyCode"));
			SingleBodyVal = OperateDB.m_pRecordset->GetCollect(_T("Prefix_OpticalCode"));
			MainVal = OperateDB.m_pRecordset->GetCollect(_T("Prefix_MotherboardEncoding"));
			MyTypeName = CheckNull(TypeVal);
			MyPrefixBodyCode = CheckNull(BodyVal);
			MyPrefixOpticalCode = CheckNull(SingleBodyVal);
			MyPrefixMotherboardEncoding = CheckNull(MainVal);
			ProjectorTestSystemDlg->SetIndex.SetDlgItemText(IDC_INDEXTYPE, MyTypeName);
			ProjectorTestSystemDlg->SetIndex.SetDlgItemText(IDC_TOOLINDEX, MyPrefixBodyCode);
			ProjectorTestSystemDlg->SetIndex.SetDlgItemText(IDC_SINGLETOOLINDEX, MyPrefixOpticalCode);
			ProjectorTestSystemDlg->SetIndex.SetDlgItemText(IDC_MAININDEX, MyPrefixMotherboardEncoding);
			ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_PLO_BODYNUM_STATIC, MyPrefixBodyCode);
			ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_PLO_SINGLEBODYNUM_STATIC, MyPrefixOpticalCode);
			ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_MAINBOARDNUM_STATIC, MyPrefixMotherboardEncoding);
			ProjectorTestSystemDlg->m_BeforeOld.SetDlgItemText(IDC_BEFOREOLD_STATIC, MyPrefixBodyCode);
			ProjectorTestSystemDlg->m_OldUp.SetDlgItemText(IDC_OLDUP_STATIC, MyPrefixBodyCode);
			ProjectorTestSystemDlg->m_OldDown.SetDlgItemText(IDC_OLDDOWN_STATIC, MyPrefixBodyCode);
			ProjectorTestSystemDlg->m_AfterOld.SetDlgItemText(IDC_AFTEROLD_STATIC, MyPrefixBodyCode);
			ProjectorTestSystemDlg->m_BeforeBright.SetDlgItemText(IDC_BEFOREBRIGHT_STATIC, MyPrefixBodyCode);
			ProjectorTestSystemDlg->m_Fix.SetDlgItemText(IDC_FIX_STATIC, MyPrefixBodyCode);
			ProjectorTestSystemDlg->m_Fix.SetDlgItemText(IDC_FIX_SINGLEBODYNUM_STATIC, MyPrefixOpticalCode);
			ProjectorTestSystemDlg->m_Fix.SetDlgItemTextA(IDC_FIX_MAINBOARDNUM_STATIC, MyPrefixMotherboardEncoding);
			ProjectorTestSystemDlg->m_Pack.SetDlgItemText(IDC_PACK_STATIC, MyPrefixBodyCode);
			ProjectorTestSystemDlg->m_Plo.SetDlgItemText(IDC_ZHIDANNUM, DanNum);
			OperateDB.CloseRecordset();
		}
	}
	catch (_com_error &e)
	{
		OperateDB.m_szErrorMsg = e.ErrorMessage();
		return;
	}
	CDialogEx::OnOK();
}


BOOL CInDanNum::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_InDanNum.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}



/*��NULL*/
CString CInDanNum::CheckNull(_variant_t Source)
{
	CString DestStr;
	if (Source.vt == VT_NULL)
	{
		DestStr = "";
		return DestStr;
	}
	else
	{
		DestStr = Source.bstrVal;
		return DestStr;
	}
}

/*��������ո�*/
BOOL CInDanNum::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if ( pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_SPACE)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_DANNUMBER)
		{
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
