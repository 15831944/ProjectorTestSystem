#pragma once
#include "afxwin.h"


// CInDanNum �Ի���

class CInDanNum : public CDialogEx
{
	DECLARE_DYNAMIC(CInDanNum)

public:
	CInDanNum(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInDanNum();

// �Ի�������
	enum { IDD = IDD_INDANNUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_InDanNum;
	virtual BOOL OnInitDialog();
};
