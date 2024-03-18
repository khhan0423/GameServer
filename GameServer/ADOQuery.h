#pragma once
#include "comdef.h"

class ADOAgent;

//ADO ��� ���� �ۼ��� �����ӿ�
//�� Ŭ���� ����Ͽ� ���������
class ADOQuery
{
public:
	ADOQuery() { m_Result = 0; }
	virtual ~ADOQuery() {}

protected:
	WORD	m_Result = 0;
	bool	m_IsThreadSafe = false;

public:
	void Excute(ADOAgent* pAgent)
	{
		try
		{
			Run(pAgent);
		}
		catch (_com_error e)
		{
			m_Result = Protocol_DBError;
			ErrorLog("DB Error[%s] - %s", GetQueryName(), (const char*)e.Description());
		}
		catch (...)
		{
			m_Result = Protocol_DBError;
			ErrorLog("DB Excute failed [%s]", GetQueryName());
		}
	}

	virtual const char* GetQueryName() const = 0;
	virtual void Run(ADOAgent* pAgent) = 0;
	virtual void Complete() = 0;
	WORD GetResult() const { return m_Result; }
	bool IsThreadSafeQuery() const { return m_IsThreadSafe; }
	void SetThreadSafeQuery(bool isSafe) { m_IsThreadSafe = isSafe; }
};

