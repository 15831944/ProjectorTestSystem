// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "CApplication.h"
#include "CFont0.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "ProjectorTestSystemDlg.h"
/*ȫ�ֱ���*/
CString ZhiDanNum, Body, SingleBody, MainNum, mWiredMac, mWiredLessMac,MainSelectSql;
extern CProjectorTestSystemDlg * ProjectorTestSystemDlg;
CMainDlg * MainDlg;
// CMainDlg �Ի���

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
	, m_MainBody(_T(""))
	, m_MainSingleBody(_T(""))
	, m_MainOpticalCode(_T(""))
	, m_MMainBoardNum(_T(""))
	, m_MainWiredMac(_T(""))
	, m_MainWiredlessMac(_T(""))
{

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_MainList);
	DDX_Control(pDX, IDC_ZHIDAN, m_MainZhiDan);
	DDX_Text(pDX, IDC_ZHIDAN, m_MainBody);
	DDX_Text(pDX, IDC_BODY, m_MainSingleBody);
	DDX_Text(pDX, IDC_SINGLEBODY, m_MainOpticalCode);
	DDX_Text(pDX, IDC_MAINNUM, m_MMainBoardNum);
	DDX_Text(pDX, IDC_WIRDMAC, m_MainWiredMac);
	DDX_Text(pDX, IDC_WIREDLESSMAC, m_MainWiredlessMac);
	DDX_Control(pDX, IDC_DELETEALL, m_DeleteAll);
	DDX_Control(pDX, IDC_DELETESELECT, m_DeleteSelect);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECKINDB, &CMainDlg::OnBnClickedCheckindb)
	ON_BN_CLICKED(IDC_WRITETOEXCEL, &CMainDlg::OnBnClickedWritetoexcel)
	ON_BN_CLICKED(IDC_DELETESELECT, &CMainDlg::OnBnClickedDeleteselect)
	ON_BN_CLICKED(IDC_DELETEALL, &CMainDlg::OnBnClickedDeleteall)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMainDlg ��Ϣ�������


BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/*���ڴ�С*/
	CRect DlgRect;
	GetClientRect(&DlgRect);     //ȡ�ͻ�����С    
	Mainold.x = DlgRect.right - DlgRect.left;
	Mainold.y = DlgRect.bottom - DlgRect.top;
	/*list*/
	CRect ListRect;	
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_MainList.GetClientRect(&ListRect);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_MainList.SetExtendedStyle(m_MainList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// Ϊ�б���ͼ�ؼ��������   
	m_MainList.InsertColumn(0, _T("������"), LVCFMT_CENTER, 60, 0);
	m_MainList.InsertColumn(1, _T("������"), LVCFMT_CENTER, 60, 1);
	m_MainList.InsertColumn(2, _T("�������"), LVCFMT_CENTER, 60, 2);
	m_MainList.InsertColumn(3, _T("������ҵʱ��"), LVCFMT_CENTER, 105, 3);
	m_MainList.InsertColumn(4, _T("�������"), LVCFMT_CENTER, 60, 4);
	m_MainList.InsertColumn(5, _T("��������ҵʱ��"), LVCFMT_CENTER,105, 5);
	m_MainList.InsertColumn(6, _T("�ϻ�ǰ��һ�β���ʱ��"), LVCFMT_CENTER, 150, 6);
	m_MainList.InsertColumn(7, _T("�ϻ�ǰ�ڶ��β���ʱ��"), LVCFMT_CENTER,150, 7);
	m_MainList.InsertColumn(8, _T("�ϻ��ϼ�ʱ��"), LVCFMT_CENTER, 90, 8);
	m_MainList.InsertColumn(9, _T("�ϻ��¼�ʱ��"), LVCFMT_CENTER, 90, 9);
	m_MainList.InsertColumn(10, _T("�ϻ����һ�β���ʱ��"), LVCFMT_CENTER, 150, 10);
	m_MainList.InsertColumn(11, _T("�ϻ���ڶ��β���ʱ��"), LVCFMT_CENTER, 150, 11);
	m_MainList.InsertColumn(12, _T("���Ȳ���ǰʱ��"), LVCFMT_CENTER, 105, 12);
	m_MainList.InsertColumn(13, _T("�ն�ֵ"), LVCFMT_CENTER, 60, 13);
	m_MainList.InsertColumn(14, _T("����MAC"), LVCFMT_CENTER,60, 14);
	m_MainList.InsertColumn(15, _T("����MAC"), LVCFMT_CENTER, 60, 15);
	m_MainList.InsertColumn(16, _T("���Ȳ���ʱ��"), LVCFMT_CENTER, 90, 16);
	m_MainList.InsertColumn(17, _T("ά������"), LVCFMT_CENTER, 60, 17);
	m_MainList.InsertColumn(18, _T("ά�޺�������"), LVCFMT_CENTER,105, 18);
	m_MainList.InsertColumn(19, _T("ά�޺��������"), LVCFMT_CENTER,105, 19);
	m_MainList.InsertColumn(20, _T("ά��ʱ��"), LVCFMT_CENTER,60, 20);
	m_MainList.InsertColumn(21, _T("��װʱ��"), LVCFMT_CENTER, 60, 21);
	m_MainList.InsertItem(0, NULL);  //Ϊ����ʾˮƽ������
	MainDlg = this;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

/*��ѯ��ť*/
void CMainDlg::OnBnClickedCheckindb()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString ZhiDan, FuselageCode;
	CString IlluminationValue, WiredMAC, wirelessMAC, RepairText, AfterMaintenanceOpticalCode, AfterMaintenanceMainBoardCode, MainBoardCode;
	_variant_t PloMachineTime, PreAgingTestTime, AgeingBeginTime,AgeingEndTime,PostAgingTestTime,PreAgingTestTime2,PostAgingTestTime2;
	_variant_t RepairTime, PackingTime, LuminanceTestTime, LuminanceTestQTime, MainBoardTime;
	CString OpticalCode;
	CString IlluminationValueStr, WiredMACStr, wirelessMACStr, RepairTextStr, AfterMaintenanceOpticalCodeStr, AfterMaintenanceMainBoardCodeStr, MainBoardCodeStr;
	CString PloMachineTimeStr, PreAgingTestTimeStr, AgeingBeginTimeStr, AgeingEndTimeStr, PostAgingTestTimeStr, PreAgingTestTime2Str, PostAgingTestTime2Str;
	CString OpticalCodeStr;
	CString SelectSql,TermZhiDan,TermBody,TermSingleBody,TermMainBoard,TermWired,TermWiredLess;
	int RowNum = 0;
	CString RepairTimeStr, PackingTimeStr, LuminanceTestTimeStr, LuminanceTestQTimeStr, MainBoardTimeStr;
	m_MainList.DeleteAllItems();
	GetDlgItemText(IDC_ZHIDAN, ZhiDanNum);
	GetDlgItemText(IDC_BODY, Body);
	GetDlgItemText(IDC_SINGLEBODY, SingleBody);
	GetDlgItemText(IDC_MAINNUM, MainNum);
	GetDlgItemText(IDC_WIRDMAC, mWiredMac);
	GetDlgItemText(IDC_WIREDLESSMAC, mWiredLessMac);
	if (ZhiDanNum == ""&&Body == ""&&SingleBody == ""&&MainNum == ""&&mWiredLessMac == ""&&mWiredMac == "")
	{
		MessageBox(_T("�������ѯ����"));
		return;
	}
	if (ZhiDanNum != "")
	{
		if (Body != "" || SingleBody != "" || MainNum != "" || mWiredMac != "" || mWiredLessMac != "")
		    TermZhiDan.Format(_T("ZhiDan = '%s' and "), ZhiDanNum);
		else
			TermZhiDan.Format(_T("ZhiDan = '%s'"), ZhiDanNum);
	}
	else
	{
		TermZhiDan = "";
	}

	if (Body != "")
	{
		if (SingleBody != "" || MainNum != "" || mWiredMac != "" || mWiredLessMac != "")
		    TermBody.Format(_T("FuselageCode = '%s' and "), Body);
		else
			TermBody.Format(_T("FuselageCode = '%s'"), Body);
	}
	else
	{
		TermBody = "";
	}
	
	if (SingleBody != "")
	{
		if (MainNum != "" || mWiredMac != "" || mWiredLessMac != "")
		    TermSingleBody.Format(_T("OpticalCode = '%s' and "), SingleBody);
		else
			TermSingleBody.Format(_T("OpticalCode = '%s'"), SingleBody);
	}
	else
	{
		TermSingleBody = "";
	}
	if (MainNum != "")
	{
		if (mWiredMac != "" || mWiredLessMac != "")
		    TermMainBoard.Format(_T("MainBoardCode = '%s' and "), MainNum);
		else
			TermMainBoard.Format(_T("MainBoardCode = '%s'"), MainNum);
	}
	else
	{
		TermMainBoard = "";
	}
	if (mWiredMac != "")
	{
		if (mWiredLessMac != "")
			TermWired.Format(_T("WiredMAC = '%s' and "), mWiredMac);
		else
			TermWired.Format(_T("WiredMAC = '%s'"), mWiredMac);
	}
	else
	{
		TermWired = "";
	}
	if (mWiredLessMac != "")
		TermWiredLess.Format(_T("wirelessMAC = '%s'"), mWiredLessMac);
	SelectSql = _T("select * from ProjectorInformation_MainTable where ") + TermZhiDan + TermBody + TermSingleBody + TermMainBoard + TermWired + TermWiredLess;
	OperateDB.OpenRecordset(SelectSql);
		try
		{
			if (!OperateDB.m_pRecordset->BOF)
				OperateDB.m_pRecordset->MoveFirst();
			else
			{
				AfxMessageBox(_T("���ݿ���û���������ƥ�������"));
				OperateDB.CloseRecordset();
				return;
			}
			while (!OperateDB.m_pRecordset->adoEOF)
			{
				FuselageCode = OperateDB.m_pRecordset->GetCollect(_T("FuselageCode"));//������
				OpticalCode = CheckNull( OperateDB.m_pRecordset->GetCollect(_T("OpticalCode")));//�����
				PreAgingTestTime = OperateDB.m_pRecordset->GetCollect(_T("PreAgingTestTime"));//�ϻ�ǰ��һ�β���
				IlluminationValue = CheckNull(OperateDB.m_pRecordset->GetCollect(_T("IlluminationValue")));//�ն�ֵ
				WiredMAC = CheckNull(OperateDB.m_pRecordset->GetCollect(_T("WiredMAC")));//����mac
				wirelessMAC = CheckNull( OperateDB.m_pRecordset->GetCollect(_T("wirelessMAC")));//����mac
				RepairText = CheckNull(OperateDB.m_pRecordset->GetCollect(_T("RepairText")));//ά������
				ZhiDan = OperateDB.m_pRecordset->GetCollect(_T("ZhiDan"));//������
				AfterMaintenanceOpticalCode = CheckNull( OperateDB.m_pRecordset->GetCollect(_T("AfterMaintenanceOpticalCode")));//ά�޺�����
				AfterMaintenanceMainBoardCode = CheckNull(OperateDB.m_pRecordset->GetCollect(_T("AfterMaintenanceMainBoardCode")));//ά�޺�������
				PloMachineTime = OperateDB.m_pRecordset->GetCollect(_T("PolishingMachineTime"));//����ʱ��
				AgeingBeginTime = OperateDB.m_pRecordset->GetCollect(_T("AgeingBeginTime"));//�ϻ��ϼ�
				AgeingEndTime = OperateDB.m_pRecordset->GetCollect(_T("AgeingEndTime"));//�ϻ��¼�
				PostAgingTestTime = OperateDB.m_pRecordset->GetCollect(_T("PostAgingTestTime"));//�ϻ����һ�β���
				PreAgingTestTime2 = OperateDB.m_pRecordset->GetCollect(_T("PreAgingTestTime2"));//�ϻ�ǰ�ڶ��β���
				PostAgingTestTime2 = OperateDB.m_pRecordset->GetCollect(_T("PostAgingTestTime2"));//�ϻ���ڶ��β���
				RepairTime = OperateDB.m_pRecordset->GetCollect(_T("RepairTime"));//ά��ʱ��
				PackingTime = OperateDB.m_pRecordset->GetCollect(_T("PackingTime"));//��װʱ��
				LuminanceTestTime = OperateDB.m_pRecordset->GetCollect(_T("LuminanceTestTime"));//���Ȳ���ʱ��
				LuminanceTestQTime = OperateDB.m_pRecordset->GetCollect(_T("LuminanceTestQTime"));//���Ȳ���ǰʱ��
				MainBoardCode = CheckNull(OperateDB.m_pRecordset->GetCollect(_T("MainBoardCode")));//�������
				MainBoardTime = OperateDB.m_pRecordset->GetCollect(_T("MainBoardTime"));//������ʱ��
				MainBoardTimeStr = TimeTranSlate(MainBoardTime);
				LuminanceTestQTimeStr = TimeTranSlate(LuminanceTestQTime);
				LuminanceTestTimeStr = TimeTranSlate(LuminanceTestTime);
				PackingTimeStr = TimeTranSlate(PackingTime);
				RepairTimeStr = TimeTranSlate(RepairTime);
				PostAgingTestTime2Str = TimeTranSlate(PostAgingTestTime2);
				PreAgingTestTime2Str = TimeTranSlate(PreAgingTestTime2);
				PostAgingTestTimeStr = TimeTranSlate(PostAgingTestTime);
				AgeingEndTimeStr = TimeTranSlate(AgeingEndTime);
				AgeingBeginTimeStr = TimeTranSlate(AgeingBeginTime);
				PreAgingTestTimeStr = TimeTranSlate(PreAgingTestTime);
				PloMachineTimeStr = TimeTranSlate(PloMachineTime);
				m_MainList.InsertItem(RowNum, ZhiDan);
				m_MainList.SetItemText(RowNum, 1, FuselageCode);
				m_MainList.SetItemText(RowNum, 2, OpticalCode);
				m_MainList.SetItemText(RowNum, 3, PloMachineTimeStr);
				m_MainList.SetItemText(RowNum, 4, MainBoardCode);
				m_MainList.SetItemText(RowNum, 5, MainBoardTimeStr);
				m_MainList.SetItemText(RowNum, 6, PreAgingTestTimeStr);
				m_MainList.SetItemText(RowNum, 7, PreAgingTestTime2Str);
				m_MainList.SetItemText(RowNum, 8, AgeingBeginTimeStr);
				m_MainList.SetItemText(RowNum, 9, AgeingEndTimeStr);
				m_MainList.SetItemText(RowNum, 10, PostAgingTestTimeStr);
				m_MainList.SetItemText(RowNum, 11, PostAgingTestTime2Str);
				m_MainList.SetItemText(RowNum, 12, LuminanceTestQTimeStr);
				m_MainList.SetItemText(RowNum, 13, IlluminationValue);
				m_MainList.SetItemText(RowNum, 14, WiredMAC);
				m_MainList.SetItemText(RowNum, 15, wirelessMAC);
				m_MainList.SetItemText(RowNum, 16, LuminanceTestTimeStr);
				m_MainList.SetItemText(RowNum, 17, RepairText);
				m_MainList.SetItemText(RowNum, 18, AfterMaintenanceOpticalCode);
				m_MainList.SetItemText(RowNum, 19, AfterMaintenanceMainBoardCode);
				m_MainList.SetItemText(RowNum, 20, RepairTimeStr);
				m_MainList.SetItemText(RowNum, 21, PackingTimeStr);
				OperateDB.m_pRecordset->MoveNext();
				RowNum++;
			}
			OperateDB.CloseRecordset();
			m_DeleteAll.EnableWindow(TRUE);
			m_DeleteSelect.EnableWindow(TRUE);
		}
		catch (_com_error &e)
		{
			OperateDB.m_szErrorMsg = e.ErrorMessage();
			return;
		}
}

/*�س�����Ӧ����*/
BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_ZHIDAN)
		{
			OnBnClickedCheckindb();
		}
		if (GetFocus()->GetDlgCtrlID() == IDC_BODY)
		{
			OnBnClickedCheckindb();
		}
		if (GetFocus()->GetDlgCtrlID() == IDC_SINGLEBODY)
		{
			OnBnClickedCheckindb();
		}
		if (GetFocus()->GetDlgCtrlID() == IDC_MAINNUM)
		{
			OnBnClickedCheckindb();
		}
		if (GetFocus()->GetDlgCtrlID() == IDC_WIRDMAC)
		{
			OnBnClickedCheckindb();
		}
		if (GetFocus()->GetDlgCtrlID() == IDC_WIREDLESSMAC)
		{
			OnBnClickedCheckindb();
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

/*������ť*/
void CMainDlg::OnBnClickedWritetoexcel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	WriteToExcelFunc();
}

/*��list������excel�ĺ���*/
void CMainDlg::WriteToExcelFunc()
{
	TCHAR szFilter[] = _T("�ı��ļ� | *.xls; *.xlsx");
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;
	if (IDOK == fileDlg.DoModal())
	{
		strFilePath = fileDlg.GetPathName();
	}
	else
	{
		return;
	}
	COleVariant
	covTrue((short)TRUE),
	covFalse((short)FALSE),
	covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	CApplication   app;
	CWorkbooks   books;
	CWorkbook   book;
	CWorksheets   sheets;
	CWorksheet   sheet;
	CRange   range;
	CFont0   font;
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		MessageBox(_T("����ʧ�ܣ�"));
		return;
	}
	books = app.get_Workbooks();
	book = books.Add(covOptional);
	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant((short)1));
	CHeaderCtrl   *pmyHeaderCtrl;
	pmyHeaderCtrl = m_MainList.GetHeaderCtrl();//�˾�ȡ��CListCtrl�ؼ����б��^
	int   iRow, iCol;
	int   m_cols = pmyHeaderCtrl->GetItemCount();
	int   m_rows = m_MainList.GetItemCount();
	HDITEM   hdi;
	TCHAR     lpBuffer[256];
	bool       fFound = false;
	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = 256;
	CString   colname;
	CString strTemp;
	for (iCol = 0; iCol <m_cols; iCol++)//���б�ı���ͷд��EXCEL
	{
		GetCellName(1, iCol + 1, colname);
		range = sheet.get_Range(COleVariant(colname), COleVariant(colname));
		pmyHeaderCtrl->GetItem(iCol, &hdi);
		range.put_Value2(COleVariant(hdi.pszText));
		int   nWidth = m_MainList.GetColumnWidth(iCol) / 6;
		//�õ���iCol+1��  
		range.AttachDispatch(range.get_Item(_variant_t((long)(iCol + 1)), vtMissing).pdispVal, true);
		//�����п� 
		range.put_ColumnWidth(_variant_t((long)nWidth));
	}
	range = sheet.get_Range(COleVariant(_T("A1 ")), COleVariant(colname));
	range.put_RowHeight(_variant_t((long)50));//�����еĸ߶�
	font = range.get_Font();
	font.put_Bold(covTrue);
	range.put_VerticalAlignment(COleVariant((short)-4108));//xlVAlignCenter   =   -4108
	COleSafeArray   saRet;
	DWORD   numElements[] = { m_rows, m_cols };       //5x2   element   array
	saRet.Create(VT_BSTR, 2, numElements);
	range = sheet.get_Range(COleVariant(_T("A2 ")), covOptional);
	range = range.get_Resize(COleVariant((short)m_rows), COleVariant((short)m_cols));
	long   index[2];
	range = sheet.get_Range(COleVariant(_T("A2 ")), covOptional);
	range = range.get_Resize(COleVariant((short)m_rows), COleVariant((short)m_cols));
	for (iRow = 1; iRow <= m_rows; iRow++)//���б�����д��EXCEL
	{
		for (iCol = 1; iCol <= m_cols; iCol++)
		{
			index[0] = iRow - 1;
			index[1] = iCol - 1;
			CString   szTemp;
			szTemp = m_MainList.GetItemText(iRow - 1, iCol - 1);
			BSTR   bstr = szTemp.AllocSysString();
			saRet.PutElement(index, bstr);
			SysFreeString(bstr);
		}
	}
	range.put_Value2(COleVariant(saRet));
	saRet.Detach();
	book.SaveCopyAs(COleVariant(strFilePath));
	book.put_Saved(true);
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.Quit();
	app.ReleaseDispatch();
	MessageBox(_T("�����ɹ���"));
}

/*��ȡ��Ԫͷ*/
void  CMainDlg::GetCellName(int nRow, int nCol, CString &strName)

{
	int nSeed = nCol;
	CString strRow;
	char cCell = 'A' + nCol - 1;
	strName.Format(_T("%c"), cCell);
	strRow.Format(_T("%d "), nRow);
	strName += strRow;
}

/*ɾ��ѡ����*/
void CMainDlg::OnBnClickedDeleteselect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	BOOL DeleteItemFinshFlag = FALSE;
	BOOL DeleteSqlFinshFlag = FALSE;
	POSITION pos;
	int BeSelectCount, ErgodicOne,Index;
	CString BeSelectBodyNum,DeleteSql;
	BeSelectCount = m_MainList.GetSelectedCount();
	if (BeSelectCount == 0)
	{
		MessageBox(_T("δѡ������"));
	}
	else
	{
		pos = m_MainList.GetFirstSelectedItemPosition();
		for (ErgodicOne = 0; ErgodicOne <= BeSelectCount; ErgodicOne++)
		{
			Index = m_MainList.GetNextSelectedItem(pos);
			BeSelectBodyNum = m_MainList.GetItemText(Index, 1);
			DeleteSql.Format(_T("DELETE FROM ProjectorInformation_MainTable WHERE FuselageCode = '%s'"), BeSelectBodyNum);		
			DeleteSqlFinshFlag = OperateDB.ExecuteByConnection(DeleteSql);
			m_MainList.DeleteItem(Index);
		}
			
	}
	if (DeleteSqlFinshFlag==TRUE)
	{
		MessageBox(_T("ɾ���ɹ���"));
	}
}

/*ɾ��������������*/
void CMainDlg::OnBnClickedDeleteall()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	BOOL DeleteAllFinshFlag = FALSE;
	BOOL DeleteAllSqlFinshFlag = FALSE;
	int ItemCount,ErgodicAll;
	CString  SqlDeleteAll,DeleteAllBodyNum;
	ItemCount = m_MainList.GetItemCount();
	if (ItemCount == 0)
	{
		MessageBox(_T("��ǰ����û�����ݣ�ɾ��ʧ�ܣ�"));
		return;
	}
	else
	{
		for (ErgodicAll = 0; ErgodicAll< ItemCount; ErgodicAll++)
		{
			DeleteAllBodyNum = m_MainList.GetItemText(ErgodicAll, 1);
			SqlDeleteAll.Format(_T("DELETE FROM ProjectorInformation_MainTable WHERE FuselageCode = '%s'"), DeleteAllBodyNum);
			DeleteAllSqlFinshFlag = OperateDB.ExecuteByConnection(SqlDeleteAll);
		}
		DeleteAllFinshFlag = m_MainList.DeleteAllItems();
	}	
	if (DeleteAllFinshFlag == TRUE&&DeleteAllSqlFinshFlag==TRUE)
	{
		MessageBox(_T("ɾ���ɹ���"));
		m_DeleteAll.EnableWindow(FALSE);
	}
	else
	{
		MessageBox(_T("ɾ��ʧ�ܣ�"));
	}
}

/*ʱ��ת������*/
CString CMainDlg::TimeTranSlate(_variant_t SourceTime)
{
	SYSTEMTIME MyTime;
	CString MyTimeStr;
	CString NULLStr = "";
	if (SourceTime.vt!=VT_NULL)
	{
		COleDateTime OleTime = (COleDateTime)SourceTime;
		VariantTimeToSystemTime(OleTime, &MyTime);
		MyTimeStr.Format(_T("%d-%d-%d  %d:%d:%d"), MyTime.wYear, MyTime.wMonth, MyTime.wDay, MyTime.wHour, MyTime.wMinute, MyTime.wSecond);
		return MyTimeStr;
	}
	else
	{
		return NULLStr;
	}

}

void CMainDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnCancel();
}


void CMainDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	/*CDialogEx::OnOK();*/
}


void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	/*if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}*/
}

void CMainDlg::ReSize()
{
	//float fsp[2];
	//POINT Newp; //��ȡ���ڶԻ���Ĵ�С  
	//CRect recta;
	//GetClientRect(&recta);     //ȡ�ͻ�����С    
	//Newp.x = recta.right - recta.left;
	//Newp.y = recta.bottom - recta.top;
	//fsp[0] = (float)Newp.x / Mainold.x;
	//fsp[1] = (float)Newp.y / Mainold.y;
	//CRect Rect;
	//int woc;
	//CPoint OldTLPoint, TLPoint; //���Ͻ�  
	//CPoint OldBRPoint, BRPoint; //���½�  
	//HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�    
	//while (hwndChild)
	//{
	//	woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID  
	//	GetDlgItem(woc)->GetWindowRect(Rect);
	//	ScreenToClient(Rect);
	//	OldTLPoint = Rect.TopLeft();
	//	TLPoint.x = long(OldTLPoint.x*fsp[0]);
	//	TLPoint.y = long(OldTLPoint.y*fsp[1]);
	//	OldBRPoint = Rect.BottomRight();
	//	BRPoint.x = long(OldBRPoint.x *fsp[0]);
	//	BRPoint.y = long(OldBRPoint.y *fsp[1]);
	//	Rect.SetRect(TLPoint, BRPoint);
	//	GetDlgItem(woc)->MoveWindow(Rect, TRUE);
	//	hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	//}
	//Mainold = Newp;
}


CString CMainDlg::CheckNull(_variant_t Source)
{
	CString DestStr;
	if (Source.vt ==VT_NULL)
	{
		DestStr = "";
		return DestStr;
	}
	else
	{
		DestStr = Source.bstrVal;
		return DestStr;
	}
}