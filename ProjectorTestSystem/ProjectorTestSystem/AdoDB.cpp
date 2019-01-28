#include "stdafx.h"
#include "AdoDB.h"
// Ĭ�Ϲ��캯��
// ��ʼ�����ݿ������ַ���
// ��ʼ��OLE��
CAdo::CAdo(void)
{
	m_szErrorMsg = "";

	// Ĭ�����ݿ������ַ���
	m_szConnectionString = " ";

	// ��ʼ��OLE��
	CoInitialize(NULL);

	// �����������
	CreateCommand();

	// �������Ӷ���
	CreateConnection();

	// �������������
	CreateRecordset();
}

//
// ��������
//
CAdo::~CAdo(void)
{
	// ִ�������ڴ湤��
	CloseConnection();
	CloseRecordset();

	if (m_pCmd)
	{
		m_pCmd.Release();
	}

	if (m_pRecordset)
	{
		m_pRecordset.Release();
	}

	if (m_pConn)
	{
		m_pConn.Release();
	}
}

/******************************************************************************
*��������   CreateConnection
*���������� �������ݿ����Ӷ���
*ǰ�������� ���ݿ����Ӷ��󲻴���
*���������� �������һ�����ݿ����Ӷ���
*����ֵ��   TRUE--�������ݿ����Ӷ���ɹ�
*           FALSE--�������ݿ����Ӷ���ʧ��
*******************************************************************************/
bool CAdo::CreateConnection()
{
	// �������ʧ�ܣ��򷵻�FALSE
	if (FAILED(m_pConn.CreateInstance(__uuidof(Connection))))
	{
		return FALSE;
	}

	return TRUE;
}

/******************************************************************************
*��������   CreateCommand
*���������� �������ݿ��������
*ǰ�������� ���ݿ�������󲻴���
*���������� �������һ�����ݿ��������
*����ֵ��   TRUE--�������ݿ��������ɹ�
*           FALSE--�������ݿ��������ʧ��
*******************************************************************************/
bool CAdo::CreateCommand()
{
	if (FAILED(m_pCmd.CreateInstance(__uuidof(Command))))
	{
		return FALSE;
	}

	return TRUE;
}

/******************************************************************************
*��������   CreateRecordset
*���������� �������������
*ǰ�������� ��������󲻴���
*���������� �������һ�����������
*����ֵ��   TRUE--�������������ɹ�
*           FALSE--�������������ʧ��
*******************************************************************************/
bool CAdo::CreateRecordset()
{
	if (FAILED(m_pRecordset.CreateInstance(__uuidof(Recordset))))
	{
		return FALSE;
	}

	return TRUE;
}

/******************************************************************************
*��������   OpenConnection
*���������� �����ݿ�
*ǰ�������� ���ݿ����Ӷ���Ϊ��
*���������� �����ݿ����ṩ��������
*����ֵ��   TRUE--�����ݿ�ɹ�
*           FALSE--�����ݿ�ʧ��
*******************************************************************************/
bool CAdo::OpenConnection()
{
	try
	{
		// �رյ�ǰ���Ӷ���
		CloseConnection();

		// ��FAILED�����ԣ�������!������
		if (FAILED(m_pConn->Open(_bstr_t(m_szConnectionString), _bstr_t(UserId), _bstr_t(Passwoord), adConnectUnspecified)))
		{
			return FALSE;
		}

		if (FAILED(CreateCommand()))
		{
			return FALSE;
		}

		m_pConn->CursorLocation = adUseClient;
		m_pCmd->ActiveConnection = m_pConn;

		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szErrorMsg = e.ErrorMessage();
		return FALSE;
	}
}


/******************************************************************************
*��������   CloseConnection
*���������� �ر����ݿ�
*ǰ�������� ���ݿ����Ӷ���Ϊ��
*���������� �ر����ݿ����ṩ��������
*����ֵ��   TRUE--�ر����ݿ�ɹ�
*           FALSE--�ر����ݿ�ʧ��
*******************************************************************************/
bool CAdo::CloseConnection()
{
	try
	{
		// �رս����
		CloseRecordset();

		// �ر����Ӷ���
		if (m_pConn != NULL && m_pConn->GetState() != adStateClosed)
		{
			m_pConn->Close();
		}

		return true;
	}
	catch (_com_error& e)
	{
		m_szErrorMsg = e.ErrorMessage();
		return false;
	}
}

/******************************************************************************
*��������   CloseRecordset
*���������� �رս��������
*ǰ�������� ���������Ϊ��
*���������� �رս�����������ṩ��������
*����ֵ��   TRUE--�رս��������ɹ�
*           FALSE--�رս��������ʧ��
*******************************************************************************/
bool CAdo::CloseRecordset()
{
	try
	{
		if (IsRecordsetOpened())
			m_pRecordset->Close();
		return true;
	}
	catch (_com_error& e)
	{
		m_szErrorMsg = e.ErrorMessage();
		return false;
	}
}

/******************************************************************************
*��������   IsConnected
*���������� �ж����ݿ������Ƿ��Ѿ�����
*ǰ�������� ���ݿ����Ӷ����Ѿ�����
*���������� �������Ӷ��������״̬���ֵ
*����ֵ��   TRUE--���ݿ����Ӷ����Ѿ���������״̬
*           FALSE--���ݿ����Ӷ����Ѿ�����������״̬
*******************************************************************************/
bool CAdo::IsConnected()
{
	if (m_pConn == NULL)
	{
		return FALSE;
	}

	if (m_pConn->GetState() == adStateClosed)
	{
		return FALSE;
	}

	return TRUE;
}

/******************************************************************************
*��������   IsRecordsetOpened
*���������� �ж����ݿ����������Ƿ��Ѿ���
*ǰ�������� ���ݿ����������Ѿ�����
*���������� ���ؽ�������������״̬���ֵ
*����ֵ��   TRUE--���ݿ����������Ѿ���������״̬
*           FALSE--���ݿ����������Ѿ�����������״̬
*******************************************************************************/
bool CAdo::IsRecordsetOpened()
{
	if (m_pRecordset == NULL)
	{
		return FALSE;
	}

	if (m_pRecordset->GetState() == adStateClosed)
	{
		return FALSE;
	}

	return TRUE;
}

/******************************************************************************
*��������   IsEndRecordset
*���������� �ж����ݿ����������Ƿ��Ѿ�����ĩβ
*ǰ�������� ���ݿ����������Ѿ�����
*���������� ���ؽ���������Ƿ񵽴�ĩβ���ֵ
*����ֵ��   TRUE--���ݿ����������Ѿ�����ĩβ
*           FALSE--���ݿ���������û�е���ĩβ
*******************************************************************************/
bool CAdo::IsEndRecordset()
{
	try
	{
		if (m_pRecordset->adoEOF == VARIANT_TRUE)
		{
			return TRUE;
		}
	}
	catch (_com_error &e)
	{
		m_szErrorMsg = e.ErrorMessage();
		return FALSE;
	}

	return FALSE;
}

/******************************************************************************
*��������   MoveToNext
*���������� �Ƶ�����һ��
*ǰ�������� ���ݿ�����������
*���������� �α��Ƶ���һ��
*******************************************************************************/
void CAdo::MoveToNext()
{
	try
	{
		if (!IsEndRecordset())
		{
			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error &e)
	{
		m_szErrorMsg = e.ErrorMessage();
	}
}

/******************************************************************************
*��������   MoveToPrevious
*���������� �Ƶ�����һ��
*ǰ�������� ���ݿ�����������
*���������� �α��Ƶ���һ��
*******************************************************************************/
void CAdo::MoveToPrevious()
{
	try
	{
		// ֻ�н�������ڴ�״̬���Ҽ�¼��������Ҫ��2��
		if (IsRecordsetOpened() && GetRecordCount() >= 2)
		{
			m_pRecordset->MovePrevious();
		}
	}
	catch (_com_error &e)
	{
		m_szErrorMsg = e.ErrorMessage();
	}
}

/******************************************************************************
*��������   MoveToFirst
*���������� �α��Ƶ�����
*ǰ�������� ���ݿ�����������
*���������� ���α��Ƶ�����
*******************************************************************************/
void CAdo::MoveToFirst()
{
	try
	{
		// ֻ�н�������ڴ�״̬���Ҽ�¼��������Ҫ��һ��
		if (IsRecordsetOpened() && GetRecordCount() >= 1)
		{
			m_pRecordset->MoveFirst();
		}
	}
	catch (_com_error &e)
	{
		m_szErrorMsg = e.ErrorMessage();
	}
}

/******************************************************************************
*��������   MoveToLast
*���������� �α��Ƶ����һ��
*ǰ�������� ���ݿ�����������
*���������� ���α��Ƶ���������һ��
*******************************************************************************/
void CAdo::MoveToLast()
{
	try
	{
		// ֻ�н�������ڴ�״̬���Ҽ�¼��������Ҫ��һ��
		if (IsRecordsetOpened() && GetRecordCount() >= 1)
		{
			m_pRecordset->MoveLast();
		}
	}
	catch (_com_error &e)
	{
		m_szErrorMsg = e.ErrorMessage();
	}
}


/******************************************************************************
*��������   GetRecordCount()
*���������� �ж����ݿ���¼�������м���
*ǰ�������� ���ݿ����������Ѿ�����
*���������� ���ؽ������¼������
*����ֵ��   long����--��¼������
*******************************************************************************/
long CAdo::GetRecordCount()
{
	try
	{
		if (m_pRecordset == NULL)
			return 0;

		// ���ؼ�¼����
		return m_pRecordset->GetRecordCount();
	}
	catch (_com_error &e)
	{
		m_szErrorMsg = e.ErrorMessage();            // ��¼������Ϣ
	}

	return FALSE;
}

/******************************************************************************
*��������   OpenRecordset
*���������� �򿪽��������
*ǰ�������� ���ݿ���������Ϊ��
*���������� �򿪽�����������ṩ��������
*������     T-SQL���
*����ֵ��   TRUE--�򿪽��������ɹ�
*           FALSE--�򿪽��������ʧ��
*******************************************************************************/
bool CAdo::OpenRecordset(CString szSQL)
{
	try
	{
		// ����ر�ʱ�������쳣
		if (OpenConnection() && CloseRecordset())
		{
			m_pRecordset->Open((_variant_t)szSQL,          // T-SQL���
				m_pConn.GetInterfacePtr(), // ���Ӷ���ӿ�
				adOpenDynamic,             // ��̬�� 
				adLockOptimistic,          // ����
				adCmdText);                // ��������Ϊ�����ı�
		}
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szErrorMsg = e.ErrorMessage();                  // ��¼������Ϣ
		return FALSE;
	}
}

/******************************************************************************
*��������   ExecuteByConnection
*���������� ִ������ɾ���Ĳ���
*ǰ�������� ���ݿ��Ѿ�������
*���������� ������Ӱ�������
*����ֵ��   TRUE--�����ɹ�
*           FALSE-����ʧ��
*������     T-SQL��䣺szSQL��CString����
*******************************************************************************/
bool CAdo::ExecuteByConnection(CString szSQL)
{
	try
	{
		// �����ʧ�ܣ����˳�
		if (!OpenConnection())
		{
			return FALSE;
		}

		// ��Ӱ�������
		_variant_t recordAffected;
		m_pRecordset= m_pConn->Execute(_bstr_t(szSQL), &recordAffected, adCmdText);
	}
	catch (_com_error &e)
	{
		m_szErrorMsg = e.ErrorMessage();
		return FALSE;
	}

	return TRUE;
}


/******************************************************************************
*��������   GetErrorMsg
*���������� ��ȡ�������Ϣ
*���������� ���س�����Ϣ
*����ֵ��   �������Ϣ--���ͣ�CString
*******************************************************************************/
CString CAdo::GetErrorMsg()
{
	return m_szErrorMsg;
}

/******************************************************************************
*��������   GetFieldValue
*���������� ��ȡ�ֶ�ֵ
*ǰ�������� �����������
*���������� ����ָ�����ֶε�ֵ
*����ֵ��   TRUE--��ȡ���ֶε�ֵ
*           FALSE-��ȡ�����ֶε�ֵ
*������     pFieldName : cahr *����--��ʶ�ֶ���
*           strValue: CString����--��ʶָ�����ֶε�ֵ
*******************************************************************************/
bool CAdo::GetFieldValue(char * pFieldName, CString& strValue)
{
	try
	{
		if (!IsRecordsetOpened())
			return FALSE;

		// ��ȡ�ֶ�ֵ
		_variant_t vtFieldValue = m_pRecordset->Fields->GetItem(pFieldName)->Value;

		if (vtFieldValue.vt == VT_BSTR)  // ������ַ�������
		{
			strValue = (char *)(_bstr_t)vtFieldValue;
			strValue.Trim();
			return true;
		}
	}
	catch (_com_error &e)
	{
		m_szErrorMsg = e.ErrorMessage();
	}

	return FALSE;
}

/******************************************************************************
*��������   IsFieldValueHasExisted
*���������� �ж�ָ�����ֶ�ֵ�Ƿ����ڴ���
*����ֵ��   TRUE--ָ�����ֶε�ֵ�Ѿ�����
*           FALSE-ָ�����ֶε�ֵ������
*������     pFieldName : cahr *����--��ʶ�ֶ���
*           strValue: CString����--��ʶָ�����ֶε�ֵ
*******************************************************************************/
bool CAdo::IsFieldValueHasExisted(char * pFieldName, CString& strValue)
{
	try
	{
		CString strTempValue;

		// ��ȡ�ֶ�ֵ
		if (GetFieldValue(pFieldName, strTempValue))
		{
			if (strTempValue.Trim() == strValue)
			{
				return TRUE;
			}
		}
	}
	catch (_com_error &e)
	{
		m_szErrorMsg = e.ErrorMessage();
	}

	return FALSE;
}
