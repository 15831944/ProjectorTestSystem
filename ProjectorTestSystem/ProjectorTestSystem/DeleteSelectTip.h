#pragma once
#include "afxwin.h"
#include "Resource.h"
// CDeleteSelectTip �Ի���

class CDeleteSelectTip : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteSelectTip)

public:
	CDeleteSelectTip(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeleteSelectTip();

// �Ի�������
	enum { IDD = IDD_DELETESELECTTIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
