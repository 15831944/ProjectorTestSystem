#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CFixDlg 对话框

class CFixDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFixDlg)

public:
	CFixDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFixDlg();

// 对话框数据
	enum { IDD = IDD_FIX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_FixList;
	virtual BOOL OnInitDialog();
	CStatic m_FixBodyNum;
	CStatic m_FixSingleBodyNum;
	CStatic m_FixMainBoardNum;
public:
	CString GetTime();
	BOOL m_FixSingleBodyState;
	BOOL m_FixMainBoardState;
	CEdit m_FixSingleNumEdit;
	CString m_FixSingleBodyEditVal;
	CEdit m_FixText;
	CString m_FixTextVal;
	CEdit m_AfterFixSingleEdit;
	CString m_AfterFixSingleEditVal;
	CEdit m_AfterFixMainEdit;
	CString m_AfterFixMainEditVal;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString m_FixStaticVal;
	CString m_FixSingleStaticVal;
	CString m_FixMainStaticVal;
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_FixCheck1;
	CButton m_FixCheck2;
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
};
