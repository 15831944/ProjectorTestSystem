#pragma once
#include "afxwin.h"


// CAdminiPassDlg �Ի���

class CAdminiPassDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminiPassDlg)

public:
	CAdminiPassDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdminiPassDlg();

// �Ի�������
	enum { IDD = IDD_ADMINIPASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit m_PassWord;
};
