
// ProjectorTestSystem.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "AdoDB.h"

// CProjectorTestSystemApp: 
// �йش����ʵ�֣������ ProjectorTestSystem.cpp
//

class CProjectorTestSystemApp : public CWinApp
{
public:
	CProjectorTestSystemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CProjectorTestSystemApp theApp;
extern CString  PassWord;
extern CString  DanNum;
extern HTREEITEM hRoot;
extern CAdo OperateDB;
extern CString  PrefixType;
extern CString  BodyNumPrefix;
extern CString  SingleBodyNumPrefix;
extern CString  MainBoardNumPrefix;
extern BOOL GetOnFlag;