// BeforeBrightDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProjectorTestSystem.h"
#include "BeforeBrightDlg.h"
#include "afxdialogex.h"
#include "CApplication.h"
#include "CFont0.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "ProjectorTestSystemDlg.h"
#include "ResizeCtrl.h"


/*ȫ�ֱ���*/
int BrightFirstRow = 0;
CBeforeBrightDlg *BeforeBrightDlg;
CWindowSizeMange BeforeBright;
extern CProjectorTestSystemDlg * ProjectorTestSystemDlg;
// CBeforeBrightDlg �Ի���

IMPLEMENT_DYNAMIC(CBeforeBrightDlg, CDialogEx)

CBeforeBrightDlg::CBeforeBrightDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBeforeBrightDlg::IDD, pParent)
	, m_BrightBodyEditVal(_T(""))
	, m_BrightNessEditVal(_T(""))
	, m_WiredLessEditVal(_T(""))
	, m_WiredLessEditState(FALSE)
	, m_WiredEditVal(_T(""))
	, m_WiredEditState(FALSE)
	, m_BrightStaticVal(_T(""))
{

}

CBeforeBrightDlg::~CBeforeBrightDlg()
{
}

void CBeforeBrightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_BeforeBright);
	DDX_Control(pDX, IDC_BEFOREBRIGHT_STATIC, m_BeforeBrightNum);
	DDX_Control(pDX, IDC_BRIGHT_BODY, m_BrightBodyEdit);
	DDX_Control(pDX, IDC_BRIGHTNESS, m_BrightNessEdit);
	DDX_Text(pDX, IDC_BRIGHT_BODY, m_BrightBodyEditVal);
	DDX_Text(pDX, IDC_BRIGHTNESS, m_BrightNessEditVal);
	DDX_Control(pDX, IDC_WIREDLESSMAC, m_WiredLessEdit);
	DDX_Text(pDX, IDC_WIREDLESSMAC, m_WiredLessEditVal);
	DDX_Check(pDX, IDC_CHECK2, m_WiredLessEditState);
	DDX_Control(pDX, IDC_WIREDMAC, m_WiredEdit);
	DDX_Text(pDX, IDC_WIREDMAC, m_WiredEditVal);
	DDX_Check(pDX, IDC_CHECK3, m_WiredEditState);
	DDX_Text(pDX, IDC_BEFOREBRIGHT_STATIC, m_BrightStaticVal);
	DDX_Control(pDX, IDC_CHECK1, m_BrightCheck1);
	DDX_Control(pDX, IDC_CHECK2, m_BrightCheck2);
	DDX_Control(pDX, IDC_CHECK3, m_BrightCheck3);
	DDX_Control(pDX, IDC_RICHEDIT22, m_BrightRich);
	DDX_Control(pDX, IDC_STATIC101, m_Working);
}


BEGIN_MESSAGE_MAP(CBeforeBrightDlg, CDialogEx)
	ON_BN_CLICKED(IDC_EXCELTOSQL, &CBeforeBrightDlg::OnBnClickedExceltosql)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CBeforeBrightDlg ��Ϣ�������


BOOL CBeforeBrightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	/*list*/
	m_BeforeBright.SetExtendedStyle(m_BeforeBright.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_BeforeBright.InsertColumn(0, _T("������"), LVCFMT_CENTER, 150, 0);
	m_BeforeBright.InsertColumn(1, _T("�ն�ֵ"), LVCFMT_CENTER, 150, 1);
	m_BeforeBright.InsertColumn(2, _T("����MAC"), LVCFMT_CENTER, 150, 2);
	m_BeforeBright.InsertColumn(3, _T("����MAC"), LVCFMT_CENTER, 150, 3);
	m_BeforeBright.InsertColumn(4, _T("����ʱ��"), LVCFMT_CENTER, 150, 4);
	m_BeforeBright.InsertColumn(5, _T("������"), LVCFMT_CENTER, 150, 5);
	//map <CString, int> ExcelZiDuan = { { "������", 0 }, { "�ն�ֵ", 1 }, { "����MAC", 2 }, { "����MAC", 3 }, { "����ʱ��", 4 } };
	//ExcelZiDuan.at(pair<CString, int>("������", 0));
	//ExcelZiDuan.insert(pair<CString, int>("�ն�ֵ", 1));
	//ExcelZiDuan.insert(pair<CString, int>("����MAC", 2));
	//ExcelZiDuan.insert(pair<CString, int>("����MAC", 3));
	//ExcelZiDuan.insert(pair<CString, int>("����ʱ��", 4));
	ExcelZiDuan["������"] = 1;
	ExcelZiDuan["�ն�ֵ"] = 2;
	ExcelZiDuan["����MAC"] = 3;
	ExcelZiDuan["����MAC"] = 4;
	ExcelZiDuan["����ʱ��"] = 5;
	ExcelZiDuan[""] = 6;
	BeforeBrightDlg = this;
	BeforeBright.Init(m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

/*Excel���ݵ���*/
void CBeforeBrightDlg::OnBnClickedExceltosql() 
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HRESULT hr;
	CString str, stry, strm, strd, strh, strM, strs,BrightSelectSql,ListCtrlFalg,CtrlFlag;
	SYSTEMTIME st;
	CString UpdateBrightToSql,ListFirstColStr,MyTimeStr,ListFirstStr,SubEditVal;
	_variant_t AfterOldTestTime;
	int DataCount,ListRowNum;
	int StaticValLength;
	StaticValLength = m_BrightStaticVal.GetLength();
	ListRowNum = 0;
	UpdateData(TRUE);
	if (DanNum=="")
	{
		MessageBox(_T("��������ǰ׺���ͺͶ����ţ�"), _T("��ʾ"));
		return;
	}
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		AfxMessageBox(_T("Failed to call Coinitialize()"));
	}
	TCHAR szFilter[] = _T("�ı��ļ� | *.xls; *.xlsx");
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;
	if (IDOK == fileDlg.DoModal())
	{
		strFilePath = fileDlg.GetPathName();
		//SetDlgItemText(IDC_EDIT1, strFilePath);
	}
	else
	{
		return;
	}
	CApplication app;
	CWorkbook book;
	CWorkbooks books;
	CWorksheet sheet;
	CWorksheets sheets;
	CRange range;
	LPDISPATCH lpDisp;
	//�������
	COleVariant covOptional((long)
		DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application"), NULL))
	{
		this->MessageBox(_T("�޷�����ExcelӦ��"),_T("��ʾ"));
		return;
	}
	books = app.get_Workbooks();
	//��Excel������pathnameΪExcel���·����
	lpDisp = books.Open(strFilePath, covOptional
		, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional
		, covOptional, covOptional, covOptional
		, covOptional, covOptional, covOptional
		, covOptional);
	book.AttachDispatch(lpDisp);
	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant((short)1));
	COleVariant vResult,ExcelFirstRowName;
	//��ȡ�Ѿ�ʹ���������Ϣ�������Ѿ�ʹ�õ���������������ʼ�С���ʼ��
	range.AttachDispatch(sheet.get_UsedRange());
	range.AttachDispatch(range.get_Rows());
	//ȡ���Ѿ�ʹ�õ�����
	long iRowNum = range.get_Count();
	range.AttachDispatch(range.get_Columns());
	//ȡ���Ѿ�ʹ�õ�����
	long iColNum = range.get_Count();
	//ȡ����ʹ���������ʼ�У���1��ʼ
	long iStartRow = range.get_Row();
	//ȡ����ʹ���������ʼ�У���1��ʼ
	long iStartCol = range.get_Column();
	m_BeforeBright.DeleteAllItems();
	m_BrightRich.SetSel(0, -1);
	m_BrightRich.Clear();
	for (int i = iStartRow+1; i <= iRowNum; i++)
	{
		
		MyTimeStr = GetTime();
		CString strRowName = _T("");
		CString ExcleFirstRowNameStr;
		/*strRowName.Format(_T("%d"), i);*/
		/*m_BeforeBright.InsertItem(i - 2, strRowName);*/
		for (int j = iStartCol; j <= iColNum; j++)
		{
			//��ȡ��Ԫ���ֵ

			range.AttachDispatch(sheet.get_Cells());
			range.AttachDispatch(range.get_Item(COleVariant((long)i),
				COleVariant((long)j)).pdispVal);
			vResult = range.get_Value2();
			range.AttachDispatch(sheet.get_Cells());
			range.AttachDispatch(range.get_Item(COleVariant((long)iStartRow),
				COleVariant((long)j)).pdispVal);
			ExcelFirstRowName = range.get_Value2();
			if (ExcelFirstRowName.vt != VT_BSTR)
			{
				m_BeforeBright.DeleteAllItems();
				m_BrightRich.SetSel(0, -1);
				m_BrightRich.Clear();
				MessageBox(_T("��������ȷ��Excel��ͷ����"), _T("��ʾ"));
				/*�ͷ���Դ*/
				OperateDB.CloseRecordset();
				range.ReleaseDispatch();
				sheet.ReleaseDispatch();
				sheets.ReleaseDispatch();
				book.ReleaseDispatch();
				books.ReleaseDispatch();
				app.Quit();
				app.ReleaseDispatch();
				return;
			}
			ExcleFirstRowNameStr = ExcelFirstRowName.bstrVal;
			if (ExcleFirstRowNameStr == "������" || ExcleFirstRowNameStr == "�ն�ֵ" || ExcleFirstRowNameStr == "����MAC" || ExcleFirstRowNameStr == "����MAC" || ExcleFirstRowNameStr == "����ʱ��")
			{
				if (vResult.vt == VT_BSTR)     //�����ַ���
				{
					str = vResult.bstrVal;
				}
				if (vResult.vt == VT_R8) //8�ֽڵ�����
				{
					if (ExcleFirstRowNameStr == "������")
					{
						str.Format(_T("%g"), vResult.dblVal);
					}
					else
					{
						str.Format(_T("%f"), vResult.dblVal);
					}
				}
				if (ExcleFirstRowNameStr == _T("����ʱ��")) //ʱ���ʽ
				{
					COleDateTime oleTime = (COleDateTime)vResult;
					VariantTimeToSystemTime(oleTime, &st);
					stry.Format(_T("%d"), st.wYear);
					strm.Format(_T("%d"), st.wMonth);
					strd.Format(_T("%d"), st.wDay);
					strh.Format(_T("%d"), st.wHour);
					strM.Format(_T("%d"), st.wMinute);
					strs.Format(_T("%d"), st.wSecond);
					str = stry + _T("-") + strm + _T("-") + strd + _T(" ") + strh + _T(":") + strM + _T(":") + strs;
				}
				if (vResult.vt == VT_EMPTY) //��ԪΪ��
				{
					str = _T("");
				}
				if (vResult.vt == VT_I4)
				{
					str.Format(_T("%ld"), (int)vResult.lVal);
				}
			}
			else
			{
				m_BeforeBright.DeleteAllItems();
				m_BrightRich.SetSel(0, -1);
				m_BrightRich.Clear();
				MessageBox(_T("��������ȷ��Excel��ͷ����"), _T("��ʾ"));
				/*�ͷ���Դ*/
				OperateDB.CloseRecordset();
				range.ReleaseDispatch();
				sheet.ReleaseDispatch();
				sheets.ReleaseDispatch();
				book.ReleaseDispatch();
				books.ReleaseDispatch();
				app.Quit();
				app.ReleaseDispatch();
				return;
			}
			try
			{
			switch (ExcelZiDuan[ExcleFirstRowNameStr])
			{
			case 1:
				SubEditVal = str.Left(StaticValLength);
				if (SubEditVal != m_BrightStaticVal)
				{
					m_BrightRich.SetSel(-1, -1);
					m_BrightRich.ReplaceSel(_T("����Ļ����룺") + str + _T("\r\n"));
					WritetoTxt(_T("����Ļ����룺") + str + _T("\r\n"));
					break;
				}
				BrightSelectSql.Format(_T("SELECT * FROM ProjectorInformation_MainTable WHERE FuselageCode = '%s' and ZhiDan = '%s'"), str,DanNum);
				OperateDB.OpenRecordset(BrightSelectSql);
				DataCount = OperateDB.GetRecordCount();
				if (DataCount == 0)
				{
					m_BrightRich.SetSel(-1, -1);
					m_BrightRich.ReplaceSel(_T("�������ڲ����ڸû����룺") + str + _T("\r\n"));
					WritetoTxt(_T("�������ڲ����ڸû����룺") + str + _T("\r\n"));
					/*m_BeforeBright.InsertItem(i - 2, strRowName);*/
					break;
				}
				else
				{
					if (!OperateDB.m_pRecordset->BOF)
					{
						OperateDB.m_pRecordset->MoveFirst();
						AfterOldTestTime = OperateDB.m_pRecordset->GetCollect(_T("PostAgingTestTime"));
						if (AfterOldTestTime.vt == VT_NULL)
						{
							m_BrightRich.SetSel(-1, -1);
							m_BrightRich.ReplaceSel(_T("�ò�Ʒû�н����ϻ�����ԣ�") + str + _T("\r\n"));
							WritetoTxt(_T("�ò�Ʒû�н����ϻ�����ԣ�") + str + _T("\r\n"));
							/*m_BeforeBright.InsertItem(i - 2, strRowName);*/
							break;
						}
					}
				}
				m_BeforeBright.InsertItem(ListRowNum, str);
				break;
			case 2:
				m_BeforeBright.SetItemText(ListRowNum, 1, str);//i-2
				ListFirstColStr = m_BeforeBright.GetItemText(ListRowNum, 0);
				UpdateBrightToSql.Format(_T("UPDATE ProjectorInformation_MainTable SET IlluminationValue = '%s',LuminanceTestQTime = '%s' WHERE FuselageCode = '%s'"), str, MyTimeStr, ListFirstColStr);
				OperateDB.ExecuteByConnection(UpdateBrightToSql);
				break;
			case 3:
				m_BeforeBright.SetItemText(ListRowNum, 3, str);
				ListFirstColStr = m_BeforeBright.GetItemText(ListRowNum, 0);
				UpdateBrightToSql.Format(_T("UPDATE ProjectorInformation_MainTable SET wirelessMAC = '%s', LuminanceTestQTime = '%s'WHERE FuselageCode = '%s'"), str, MyTimeStr, ListFirstColStr);
				OperateDB.ExecuteByConnection(UpdateBrightToSql);
				break;
			case 4:
				m_BeforeBright.SetItemText(ListRowNum, 2, str);
				ListFirstColStr = m_BeforeBright.GetItemText(ListRowNum, 0);
				UpdateBrightToSql.Format(_T("UPDATE ProjectorInformation_MainTable SET WiredMAC = '%s', LuminanceTestQTime = '%s' WHERE FuselageCode = '%s'"), str, MyTimeStr, ListFirstColStr);
				OperateDB.ExecuteByConnection(UpdateBrightToSql);
				break;
			case 5:
				m_BeforeBright.SetItemText(ListRowNum, 4, str);
				ListFirstColStr = m_BeforeBright.GetItemText(ListRowNum, 0);
				UpdateBrightToSql.Format(_T("UPDATE ProjectorInformation_MainTable SET LuminanceTestTime = '%s', LuminanceTestQTime = '%s' WHERE FuselageCode = '%s'"), str, MyTimeStr, ListFirstColStr);
				OperateDB.ExecuteByConnection(UpdateBrightToSql);
				break;
			case 6:
				break;
			default:
				break;
			}
		}
		   catch (_com_error &e)
		   {
			   OperateDB.m_szErrorMsg = e.ErrorMessage();
			   return;
		   }
		   if (DataCount == 0 || AfterOldTestTime.vt == VT_NULL)
		   {
			   ListRowNum = ListRowNum;
               break;
		   }
		   
		}
		ListFirstStr = m_BeforeBright.GetItemText(ListRowNum, 0);
		if (ListFirstStr!="")
		{
			m_BeforeBright.SetItemText(ListRowNum, 5, DanNum);
			ListRowNum++;
		}
		/*else
		{
			m_BeforeBright.DeleteItem(i - 2);
		}*/	
		SetDlgItemText(IDC_STATIC101,_T("������..."));
	}
	/*CString NullFlag;
	ListCount = m_BeforeBright.GetItemCount();
	for (ListStraRow = m_BeforeBright.GetItemCount() - 1; ListStraRow >= 0; ListStraRow--)
	{
		NullFlag = m_BeforeBright.GetItemText(ListStraRow, 0);
		if (NullFlag == "")
		{
			m_BeforeBright.DeleteItem(ListStraRow);
		}
	}*/
	ListCtrlFalg = m_BeforeBright.GetItemText(0,0);
	if (ListCtrlFalg == "")
	{
		MessageBox(_T("δ�����κ����ݻ���ȫ������ʧ�ܣ���ȷ���Ƿ����˴���ı��"), _T("��ʾ"));
		m_BeforeBright.DeleteAllItems();
		BrightFirstRow = 0;
		SetDlgItemText(IDC_STATIC101, _T(""));
		ListRowNum = 0;
	}
	else
	{
		MessageBox(_T("����ɹ�"), _T("��ʾ"));
		SetDlgItemText(IDC_STATIC101, _T(""));
	}	
	/*�ͷ���Դ*/
	OperateDB.CloseRecordset();
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.Quit();
	app.ReleaseDispatch();
}

/*��ȡ��ǰʱ��*/
CString CBeforeBrightDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString Tiemstr;
	Tiemstr = time.Format(_T("%Y-%m-%d  %H:%M:%S"));
	return Tiemstr;
}


/*�س���Ӧ*/
BOOL CBeforeBrightDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CString BrightTimeStr, m_BrightBodyNumValStr, InsertBrighttoSql,UpdateBrightToSql;
	CString mOpticalCode, SelectSqlEdit2, SelectSqlEdit1, mMainBoardCode;
	LONG BrightRecodestCount = 0;
	int m_BrightBodyNumStaticValLength;
	_variant_t AfterOldTime;
	BrightTimeStr = GetTime();
	UpdateData(TRUE);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_BRIGHT_BODY)
		{
			try
			{	
				if (DanNum=="")
				{
					MessageBox(_T("��������ǰ׺�Ͷ����ţ�"), _T("��ʾ"));
					m_BrightBodyEditVal = _T("");
					UpdateData(FALSE);
					m_BrightBodyEdit.SetFocus();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				m_BrightBodyNumStaticValLength = m_BrightStaticVal.GetLength();
				m_BrightBodyNumValStr = m_BrightBodyEditVal.Left(m_BrightBodyNumStaticValLength);
				if (m_BrightBodyNumValStr != m_BrightStaticVal || m_BrightBodyEditVal == "")
				{
					MessageBox(_T("���������"), _T("��ʾ"));
					m_BrightBodyEditVal = _T("");
					UpdateData(FALSE);
					m_BrightBodyEdit.SetFocus();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				SelectSqlEdit1.Format(_T("SELECT * FROM ProjectorInformation_MainTable WHERE FuselageCode = '%s' and ZhiDan = '%s'"), m_BrightBodyEditVal,DanNum);
				OperateDB.OpenRecordset(SelectSqlEdit1);
				BrightRecodestCount = OperateDB.GetRecordCount();
				if (BrightRecodestCount == 0)
				{
					MessageBox(_T("�������ڲ����ڸû�����"), _T("��ʾ"));
					m_BrightBodyEditVal = _T("");
					UpdateData(FALSE);
					m_BrightBodyEdit.SetFocus();
					OperateDB.CloseRecordset();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				if (!OperateDB.m_pRecordset->BOF)
					OperateDB.m_pRecordset->MoveFirst();
				AfterOldTime = OperateDB.m_pRecordset->GetCollect(_T("PostAgingTestTime"));
				if (AfterOldTime.vt==VT_NULL)
				{
					MessageBox(_T("�ò�Ʒû�����ϻ������"), _T("��ʾ"));
					m_BrightBodyEdit.SetFocus();
					m_BrightBodyEditVal = "";
					UpdateData(FALSE);
					OperateDB.CloseRecordset();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				OperateDB.CloseRecordset();
			}
			catch (_com_error &e)
			{
				OperateDB.m_szErrorMsg = e.ErrorMessage();
				return CDialogEx::PreTranslateMessage(pMsg);
			}			
			if (m_WiredLessEditState == TRUE&&m_WiredEditState == FALSE)
			{
				m_WiredLessEdit.EnableWindow(TRUE);
				m_WiredLessEdit.SetFocus();
				pMsg->message = 0;
				pMsg->wParam = 0;
			}
			if (m_WiredEditState == TRUE&&m_WiredLessEditState == FALSE)
			{
				m_WiredEdit.EnableWindow(TRUE);
				m_WiredEdit.SetFocus();
				pMsg->message = 0;
				pMsg->wParam = 0;
			}
			if (m_WiredEditState == TRUE&&m_WiredLessEditState == TRUE)
			{
				m_WiredLessEdit.EnableWindow(TRUE);
				m_WiredLessEdit.SetFocus();
				pMsg->message = 0;
				pMsg->wParam = 0;
			}
		}
		if (GetFocus()->GetDlgCtrlID() == IDC_WIREDLESSMAC&&pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		{
			if (m_WiredEditState == FALSE)
			{
				try
				{
					UpdateBrightToSql.Format(_T("UPDATE ProjectorInformation_MainTable SET wirelessMAC='%s',LuminanceTestQTime = '%s' WHERE FuselageCode = '%s'"), m_WiredLessEditVal, BrightTimeStr, m_BrightBodyEditVal);
					OperateDB.ExecuteByConnection(UpdateBrightToSql);
					m_BeforeBright.InsertItem(BrightFirstRow, m_BrightBodyEditVal);
					m_BeforeBright.SetItemText(BrightFirstRow, 3, m_WiredLessEditVal);
					m_BeforeBright.SetItemText(BrightFirstRow, 4, BrightTimeStr);
					m_BeforeBright.SetItemText(BrightFirstRow, 5, DanNum);
					BrightFirstRow++;
					m_WiredLessEditVal = _T("");
					m_BrightBodyEditVal = _T("");
					UpdateData(FALSE);
					m_BrightBodyEdit.SetFocus();
					m_WiredLessEdit.EnableWindow(FALSE);
				}
				catch (_com_error &e)
				{
					OperateDB.m_szErrorMsg = e.ErrorMessage();
					return CDialogEx::PreTranslateMessage(pMsg);
				}
			}
			else
			{
				m_WiredEdit.EnableWindow(TRUE);
				m_WiredEdit.SetFocus();

				pMsg->message = 0;
				pMsg->wParam = 0;
			}
		}
		if (GetFocus()->GetDlgCtrlID() == IDC_WIREDMAC&&pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		{			
			try
			{
				UpdateBrightToSql.Format(_T("UPDATE ProjectorInformation_MainTable SET wirelessMAC='%s',WiredMAC = '%s',LuminanceTestQTime = '%s' WHERE FuselageCode = '%s'"), m_WiredLessEditVal, m_WiredEditVal, BrightTimeStr, m_BrightBodyEditVal);
				OperateDB.ExecuteByConnection(UpdateBrightToSql);
				m_BeforeBright.InsertItem(BrightFirstRow, m_BrightBodyEditVal);
				m_BeforeBright.SetItemText(BrightFirstRow, 3, m_WiredLessEditVal);
				m_BeforeBright.SetItemText(BrightFirstRow, 4, BrightTimeStr);
				m_BeforeBright.SetItemText(BrightFirstRow, 2, m_WiredEditVal);
				m_BeforeBright.SetItemText(BrightFirstRow, 5, DanNum);
				BrightFirstRow++;
				m_WiredLessEditVal = _T("");
				m_BrightBodyEditVal = _T("");
				m_WiredEditVal = _T("");
				UpdateData(FALSE);
				m_BrightBodyEdit.SetFocus();
				m_WiredLessEdit.EnableWindow(FALSE);
				m_WiredEdit.EnableWindow(FALSE);
			}
			catch (_com_error &e)
			{
				OperateDB.m_szErrorMsg = e.ErrorMessage();
				return CDialogEx::PreTranslateMessage(pMsg);
			}
		}
		//if (pMsg->message != 0 && pMsg->wParam != 0)
		//{
		//	BrightFirstRow++;
		//}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CBeforeBrightDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CBeforeBrightDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnCancel();
}


void CBeforeBrightDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		BeforeBright.ResizeWindow();
	}
}

/*��null*/
CString CBeforeBrightDlg::CheckNull(_variant_t Source)
{
	CString DestStr;
	if (Source.vt == VT_NULL)
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

/*ɾ��List����*/
void CBeforeBrightDlg::DeleteNullList(CListCtrl Contrl)
{
	int StraRow,ListCount;
	CString NullFlag;
	ListCount = Contrl.GetItemCount();
	for (StraRow = 0; StraRow < ListCount; StraRow++)
	{
		NullFlag = Contrl.GetItemText(StraRow,0);
		if (NullFlag=="")
		{
			Contrl.DeleteItem(StraRow);
		}
	}
}

/*��ȡ����*/
CString  CBeforeBrightDlg::GetDate()
{
	CTime time = CTime::GetCurrentTime();
	CString DateStr,DayStr,MonthStr,YearStr;
	int day, year, month;
	day = time.GetDay();
	month = time.GetMonth();
	year = time.GetYear();
	DayStr.Format(_T("%d"), day);
	MonthStr.Format(_T("%d"), month);
	YearStr.Format(_T("%d"),year);
	DateStr = "-Default��"+YearStr + "-" + MonthStr + "-" + DayStr;
	return DateStr;
}

/*��ȡexe·��*/
CString CBeforeBrightDlg::GetExePath()
{
	char sFileName[256] = { 0 };
	CString ProjectPath = _T("");
	GetModuleFileName(AfxGetInstanceHandle(), sFileName, 255);
	ProjectPath.Format("%s", sFileName);
	int pos = ProjectPath.ReverseFind('\\');
	if (pos != -1)
		ProjectPath = ProjectPath.Left(pos);
	else
		ProjectPath = _T("");
	return ProjectPath;
}

/*д���ݵ�txt�ļ�*/
BOOL CBeforeBrightDlg::WritetoTxt(CString sValue)
{
	CString SubPath;
	SubPath = GetDate();
	SubPath = DanNum  + SubPath;
	CString sFile = GetExePath() + "\\" + SubPath + ".txt";
	CStdioFile file;
	if (file.Open(sFile, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
	{
		file.SeekToEnd(); // �ƶ��ļ�ָ�뵽ĩβ
		file.WriteString(sValue);
		file.Close();
	}
	return FALSE;
}