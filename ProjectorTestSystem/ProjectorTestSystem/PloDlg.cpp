// PloDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "PloDlg.h"
#include "afxdialogex.h"
#include "ProjectorTestSystemDlg.h"
#include "ResizeCtrl.h"

extern CProjectorTestSystemDlg * ProjectorTestSystemDlg;

/*ȫ�ֱ���*/
int FirstRow = 0;
CPloDlg *PloDlg;
CWindowSizeMange Plo;
// CPloDlg �Ի���

IMPLEMENT_DYNAMIC(CPloDlg, CDialogEx)

CPloDlg::CPloDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPloDlg::IDD, pParent)
	, m_SingleBodyNumState(FALSE)
	, m_MainBoardNumState(FALSE)
	, m_BodyNumVal(_T(""))
	, m_SingleBodyNumVal(_T(""))
	, m_MainBoardNumVal(_T(""))
	, m_PloBodyNumStaticVal(_T(""))
	, m_SingleBdoyStaticVal(_T(""))
	, m_PloMainBoardStaticVal(_T(""))
{

}

CPloDlg::~CPloDlg()
{
}

void CPloDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_PloList);
	DDX_Control(pDX, IDC_PLO_BODYNUM_STATIC, m_PloBodyNum);
	DDX_Control(pDX, IDC_PLO_SINGLEBODYNUM_STATIC, m_PloSingleBodyNum);
	DDX_Control(pDX, IDC_MAINBOARDNUM_STATIC, m_PloMainBoardNum);
	DDX_Control(pDX, IDC_SINGLEBODY_CHECK, m_SingleBodyCheck);
	DDX_Control(pDX, IDC_MAINBOARD_CHECK, m_MainBoardCheck);
	DDX_Control(pDX, IDC_PLO_SINGLEBODYNUM, m_PloSingleBodyNumEdit);
	DDX_Control(pDX, IDC_PLO_MAINBOARDNUM, m_PloMainBoardNumEcit);
	DDX_Check(pDX, IDC_SINGLEBODY_CHECK, m_SingleBodyNumState);
	DDX_Check(pDX, IDC_MAINBOARD_CHECK, m_MainBoardNumState);
	DDX_Text(pDX, IDC_PLO_BODYNUM, m_BodyNumVal);
	DDX_Text(pDX, IDC_PLO_SINGLEBODYNUM, m_SingleBodyNumVal);
	DDX_Text(pDX, IDC_PLO_MAINBOARDNUM, m_MainBoardNumVal);
	DDX_Text(pDX, IDC_PLO_BODYNUM_STATIC, m_PloBodyNumStaticVal);
	DDX_Text(pDX, IDC_PLO_SINGLEBODYNUM_STATIC, m_SingleBdoyStaticVal);
	DDX_Text(pDX, IDC_MAINBOARDNUM_STATIC, m_PloMainBoardStaticVal);
	DDX_Control(pDX, IDC_PLO_BODYNUM, m_PloBodyNumSub);
}


BEGIN_MESSAGE_MAP(CPloDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SINGLEBODY_CHECK, &CPloDlg::OnBnClickedSinglebodyCheck)
	ON_BN_CLICKED(IDC_MAINBOARD_CHECK, &CPloDlg::OnBnClickedMainboardCheck)
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPloDlg ��Ϣ�������


BOOL CPloDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_PloList.SetExtendedStyle(m_PloList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_PloList.InsertColumn(0, _T("������"), LVCFMT_CENTER, 150, 0);
	m_PloList.InsertColumn(1, _T("�������"),LVCFMT_CENTER, 150, 1);
	m_PloList.InsertColumn(2, _T("�������"), LVCFMT_CENTER, 150, 2);
	m_PloList.InsertColumn(3, _T("����ʱ��"), LVCFMT_CENTER, 150, 3);
	m_PloList.InsertColumn(4, _T("������"), LVCFMT_CENTER, 150, 4);
	PloDlg = this;
	Plo.Init(m_hWnd);
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

/*�����༭��ʹ��*/
void CPloDlg::OnBnClickedSinglebodyCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*BOOL SingleBodyNumCheck = FALSE;
	UpdateData(TRUE);
	SingleBodyNumCheck = m_SingleBodyNumState;
	if (SingleBodyNumCheck == TRUE)
	{
		m_PloSingleBodyNumEdit.EnableWindow(TRUE);
	}
	else
	{
		m_PloSingleBodyNumEdit.EnableWindow(FALSE);
	}*/
}

/*�������༭��ʹ��*/
void CPloDlg::OnBnClickedMainboardCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*BOOL MainBoardNumCheck = FALSE;
	UpdateData(TRUE);
	MainBoardNumCheck = m_MainBoardNumState;
	if (MainBoardNumCheck == TRUE)
	{
		m_PloMainBoardNumEcit.EnableWindow(TRUE);
	}
	else
	{
		m_PloMainBoardNumEcit.EnableWindow(FALSE);
	}*/
}

/*�༭����Ӧ�س��¼�*/
BOOL CPloDlg::PreTranslateMessage(MSG* pMsg)
{
	
	// TODO:  �ڴ����ר�ô����/����û���
	CString TimeStr, m_BodyNumValStr, m_SingleBodyNumValStr, m_MainBoardNumValStr, mFuselageCode, InsertIntoSql;
	CString mOpticalCode, SelectSqlEdit2, SelectSqlEdit1,mMainBoardCode;
	BOOL SelectFinhFlag = FALSE;
	LONG RecodestCount = 0;
	int m_PloBodyNumStaticValLength, m_PloSingleBodyNumStaticValLength, m_MainBoardNumStaticValLength;
	TimeStr = GetTime();
	UpdateData(TRUE);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		{						
			if (GetFocus()->GetDlgCtrlID() == IDC_PLO_BODYNUM)
			{
				if (GetOnFlag == FALSE)
				{
					MessageBox(_T("���ȵ�¼"));
					m_BodyNumVal = _T("");
					UpdateData(FALSE);
					m_PloBodyNumSub.SetFocus();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (DanNum=="")
				{
					MessageBox(_T("�������붩����"));
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				try
				{
					SelectSqlEdit1.Format(_T("SELECT * FROM ProjectorInformation_MainTable WHERE FuselageCode = '%s'"), m_BodyNumVal);
					OperateDB.OpenRecordset(SelectSqlEdit1);
					RecodestCount = OperateDB.GetRecordCount();
					if (RecodestCount != 0)
					{
						MessageBox(_T("�������ظ�"));
						m_BodyNumVal = _T("");
						UpdateData(FALSE);
						m_PloBodyNumSub.SetFocus();
						OperateDB.CloseRecordset();
						return CDialogEx::PreTranslateMessage(pMsg);
					}
					OperateDB.CloseRecordset();
					m_PloBodyNumStaticValLength = m_PloBodyNumStaticVal.GetLength();
					m_BodyNumValStr = m_BodyNumVal.Left(m_PloBodyNumStaticValLength);
					if (m_BodyNumValStr != m_PloBodyNumStaticVal || m_BodyNumVal == "")
					{
						MessageBox(_T("���������"));
						m_BodyNumVal = _T("");
						UpdateData(FALSE);
						m_PloBodyNumSub.SetFocus();
						return CDialogEx::PreTranslateMessage(pMsg);
					}							
				}
				catch (_com_error &e)
				{
					OperateDB.m_szErrorMsg = e.ErrorMessage();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (m_MainBoardNumState == FALSE&&m_SingleBodyNumState == FALSE)
				{
															
						try
						{																			
						    InsertIntoSql.Format(_T("INSERT INTO ProjectorInformation_MainTable (FuselageCode,ZhiDan,PolishingmachineTime) VALUES ('%s','%s','%s')"), m_BodyNumVal, DanNum, TimeStr);
							OperateDB.ExecuteByConnection(InsertIntoSql);
							m_PloList.InsertItem(FirstRow, m_BodyNumVal);
							m_PloList.SetItemText(FirstRow, 3, TimeStr);
							m_PloList.SetItemText(FirstRow, 4, DanNum);
							m_BodyNumVal = _T("");
							UpdateData(FALSE);
							m_PloBodyNumSub.SetFocus();
						}												
						catch (_com_error &e)
						{
							OperateDB.m_szErrorMsg = e.ErrorMessage();
							return CDialogEx::PreTranslateMessage(pMsg);
						}					
				}
				if (m_MainBoardNumState == TRUE&&m_SingleBodyNumState==FALSE)
				{
					m_PloMainBoardNumEcit.EnableWindow(TRUE);
					m_PloMainBoardNumEcit.SetFocus();
					
					pMsg->message =0;
					pMsg->wParam = 0;
				}
				if (m_SingleBodyNumState==TRUE&&m_MainBoardNumState==FALSE)
				{
					m_PloSingleBodyNumEdit.EnableWindow(TRUE);
					m_PloSingleBodyNumEdit.SetFocus();
					
					pMsg->message =0;
					pMsg->wParam = 0;
				}
				if (m_MainBoardNumState == TRUE&&m_SingleBodyNumState == TRUE)
				{
					m_PloSingleBodyNumEdit.EnableWindow(TRUE);
					m_PloSingleBodyNumEdit.SetFocus();
					
					pMsg->message =0;
					pMsg->wParam =0;
				}
			}
			if (GetFocus()->GetDlgCtrlID() == IDC_PLO_SINGLEBODYNUM&&pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			{
				try
				{
					m_PloSingleBodyNumStaticValLength = m_SingleBdoyStaticVal.GetLength();
					m_SingleBodyNumValStr = m_SingleBodyNumVal.Left(m_PloSingleBodyNumStaticValLength);
					if (m_SingleBodyNumValStr != m_SingleBdoyStaticVal || m_SingleBodyNumVal == "")
					{
						MessageBox(_T("��������"));
						m_SingleBodyNumVal = _T("");
						UpdateData(FALSE);
						m_PloSingleBodyNumEdit.SetFocus();
						return CDialogEx::PreTranslateMessage(pMsg);
					}
					SelectSqlEdit1.Format(_T("SELECT * FROM ProjectorInformation_MainTable WHERE OpticalCode = '%s'"), m_SingleBodyNumVal);
					OperateDB.OpenRecordset(SelectSqlEdit1);
					RecodestCount = OperateDB.GetRecordCount();
					if (RecodestCount != 0)
					{
						MessageBox(_T("������ظ�"));
						m_SingleBodyNumVal = _T("");
						UpdateData(FALSE);
						m_PloSingleBodyNumEdit.SetFocus();
						return CDialogEx::PreTranslateMessage(pMsg);
					}
					OperateDB.CloseRecordset();					
				}
				catch (_com_error &e)
				{
					OperateDB.m_szErrorMsg = e.ErrorMessage();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (m_MainBoardNumState == FALSE)
				{				
						try
						{					   
							    InsertIntoSql.Format(_T("INSERT INTO ProjectorInformation_MainTable (FuselageCode,ZhiDan,PolishingmachineTime,OpticalCode) VALUES ('%s','%s','%s','%s')"), m_BodyNumVal, DanNum, TimeStr, m_SingleBodyNumVal);
								OperateDB.ExecuteByConnection(InsertIntoSql);
								m_PloList.InsertItem(FirstRow, m_BodyNumVal);
								m_PloList.SetItemText(FirstRow, 1, m_SingleBodyNumVal);
								m_PloList.SetItemText(FirstRow, 3, TimeStr);
								m_PloList.SetItemText(FirstRow, 4, DanNum);
								m_SingleBodyNumVal = _T("");
								m_BodyNumVal = _T("");
								UpdateData(FALSE);
								m_PloBodyNumSub.SetFocus();	
								m_PloSingleBodyNumEdit.EnableWindow(FALSE);
						}
						catch (_com_error &e)
						{
							OperateDB.m_szErrorMsg = e.ErrorMessage();
							return CDialogEx::PreTranslateMessage(pMsg);
						}											
				}
				else
				{
					m_PloMainBoardNumEcit.EnableWindow(TRUE);
					m_PloMainBoardNumEcit.SetFocus();
					
					pMsg->message = 0;
					pMsg->wParam = 0;
				}
			}	
			if (GetFocus()->GetDlgCtrlID() == IDC_PLO_MAINBOARDNUM&&pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			{
				try
				{
					m_MainBoardNumStaticValLength = m_PloMainBoardStaticVal.GetLength();
					m_MainBoardNumValStr = m_MainBoardNumVal.Left(m_MainBoardNumStaticValLength);
					if (m_MainBoardNumValStr != m_PloMainBoardStaticVal || m_MainBoardNumValStr == "")
					{
						MessageBox(_T("����������"));
						m_MainBoardNumVal = _T("");
						UpdateData(FALSE);
						m_PloMainBoardNumEcit.SetFocus();
						return CDialogEx::PreTranslateMessage(pMsg);
					}
					SelectSqlEdit1.Format(_T("SELECT * FROM ProjectorInformation_MainTable WHERE MainBoardCode = '%s'"), m_MainBoardNumVal);
					OperateDB.OpenRecordset(SelectSqlEdit1);
					RecodestCount = OperateDB.GetRecordCount();
					if (RecodestCount != 0)
					{
						MessageBox(_T("��������ظ�"));
						m_MainBoardNumVal = _T("");
						UpdateData(FALSE);
						m_PloMainBoardNumEcit.SetFocus();
						return CDialogEx::PreTranslateMessage(pMsg);
					}
					OperateDB.CloseRecordset();					
				}
				catch (_com_error &e)
				{
					OperateDB.m_szErrorMsg = e.ErrorMessage();
					return CDialogEx::PreTranslateMessage(pMsg);
				}										
					try
					{
						if (m_SingleBodyNumState==TRUE)
						{
							InsertIntoSql.Format(_T("INSERT INTO ProjectorInformation_MainTable (FuselageCode,ZhiDan,PolishingmachineTime,OpticalCode,MainBoardCode,MainBoardTime) VALUES ('%s','%s','%s','%s','%s','%s')"), m_BodyNumVal, DanNum, TimeStr, m_SingleBodyNumVal, m_MainBoardNumVal, TimeStr);

						}
						else
						{
							InsertIntoSql.Format(_T("INSERT INTO ProjectorInformation_MainTable (FuselageCode,ZhiDan,PolishingmachineTime,MainBoardCode,MainBoardTime) VALUES ('%s','%s','%s','%s','%s')"), m_BodyNumVal, DanNum, TimeStr, m_MainBoardNumVal, TimeStr);

						}
							OperateDB.ExecuteByConnection(InsertIntoSql);
							m_PloList.InsertItem(FirstRow, m_BodyNumVal);
							if (m_SingleBodyNumState == TRUE)
							{
								m_PloList.SetItemText(FirstRow, 1, m_SingleBodyNumVal);
							}							
							m_PloList.SetItemText(FirstRow, 3, TimeStr);
							m_PloList.SetItemText(FirstRow, 4, DanNum);
							m_PloList.SetItemText(FirstRow,2,m_MainBoardNumVal);
							m_BodyNumVal = _T("");
							m_SingleBodyNumVal = _T("");
							m_MainBoardNumVal = _T("");
							UpdateData(FALSE);
							m_PloBodyNumSub.SetFocus();
							m_PloSingleBodyNumEdit.EnableWindow(FALSE);
							m_PloMainBoardNumEcit.EnableWindow(FALSE);
						}
					catch (_com_error &e)
					{
						OperateDB.m_szErrorMsg = e.ErrorMessage();
						return CDialogEx::PreTranslateMessage(pMsg);
					}																		
			}
			if (pMsg->message != 0 && pMsg->wParam != 0)
			{
				FirstRow++;
			}
		}			
	return CDialogEx::PreTranslateMessage(pMsg);
}

/*��ȡ��ǰʱ��*/
CString CPloDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString Tiemstr;
	Tiemstr = time.Format(_T("%Y-%m-%d  %H:%M:%S"));
	return Tiemstr;
}

void CPloDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CPloDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	/*CDialogEx::OnCancel();*/
}


void CPloDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}


void CPloDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		Plo.ResizeWindow();
	}
}
