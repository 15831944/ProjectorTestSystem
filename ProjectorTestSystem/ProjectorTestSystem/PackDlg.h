#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CPackDlg �Ի���

class CPackDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPackDlg)

public:
	CPackDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPackDlg();

// �Ի�������
	enum { IDD = IDD_PACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_PackList;
	virtual BOOL OnInitDialog();
	CStatic m_Pack;
	CEdit m_PackEdit;
	CString m_PackEditVal;
	CString m_PackStatic;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	virtual void OnCancel();
public:
	CString GetTime();
};
