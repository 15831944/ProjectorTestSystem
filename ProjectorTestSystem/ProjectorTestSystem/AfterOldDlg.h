#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CAfterOldDlg �Ի���

class CAfterOldDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAfterOldDlg)

public:
	CAfterOldDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAfterOldDlg();

// �Ի�������
	enum { IDD = IDD_AFTEROLD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_AfetrOldList;
	virtual BOOL OnInitDialog();
	CStatic m_AfterOldNum;
	CEdit m_AfterOldEditContrl;
	CString m_AfterOldBodyEdit;
	CString m_AfterOldBody;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	CString GetTime();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
};
