#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CBefroeOldDlg �Ի���

class CBefroeOldDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBefroeOldDlg)

public:
	CBefroeOldDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBefroeOldDlg();

// �Ի�������
	enum { IDD = IDD_BEFOREOLD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_BeforeOldList;
	virtual BOOL OnInitDialog();
	CStatic m_BeforeOld;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString m_BeforeOldBody;
	CString m_BeforeOldBodyEdit;
public:
	CString GetTime();
	CEdit m_BeforeOldEditContrl;
	virtual void OnOK();
	virtual void OnCancel();
};
