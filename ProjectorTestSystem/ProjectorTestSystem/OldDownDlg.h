#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// COldDownDlg �Ի���

class COldDownDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COldDownDlg)

public:
	COldDownDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COldDownDlg();

// �Ի�������
	enum { IDD = IDD_OLDDOWN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_OldDownlist;
	virtual BOOL OnInitDialog();
	CStatic m_OldDown;
	CString m_OldDownStaticVal;
	//CEdit m_OldDownEdit;
	//CString m_OldDownEditVal;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	CString GetTime();
	virtual void OnOK();
	virtual void OnCancel();
	CString m_OldDownEditVal;
	CEdit m_OldDownEdit;
};
