// AdminiPassDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "AdminiPassDlg.h"
#include "afxdialogex.h"


// CAdminiPassDlg �Ի���

IMPLEMENT_DYNAMIC(CAdminiPassDlg, CDialogEx)

CAdminiPassDlg::CAdminiPassDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdminiPassDlg::IDD, pParent)
{

}

CAdminiPassDlg::~CAdminiPassDlg()
{
}

void CAdminiPassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADPASSWORD, m_PassWord);
}


BEGIN_MESSAGE_MAP(CAdminiPassDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAdminiPassDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAdminiPassDlg ��Ϣ�������


void CAdminiPassDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_ADPASSWORD,PassWord);
	CDialogEx::OnOK();
}


BOOL CAdminiPassDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_PassWord.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
