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


void CInDanNum::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_DANNUMBER, DanNum);
	//ProjectorTestSystemDlg->SetIndex.OnBnClickedOk();
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
