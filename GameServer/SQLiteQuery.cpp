#include "pch.h"
#include "SQLiteQuery.h"
#include "SQLiteAgent.h"
#include "Player.h"
#include "StringUtil.h"

using namespace DataBase;
using namespace DataBase::SQLite3;

void SQLiteQueryBase::AddParamNULL()
{
	SQLiteQueryBase::m_Params.push_back(make_pair(e_NULL, "0"));
}
void SQLiteQueryBase::AddParam(const bool input)
{
	m_Params.push_back(make_pair(eINTEGER, StringUtil::IntToAnsi(input)));
}
void SQLiteQueryBase::AddParam(const __int8 input)
{
	m_Params.push_back(make_pair(eINTEGER, StringUtil::IntToAnsi(input)));
}
void SQLiteQueryBase::AddParam(const __int16 input)
{
	m_Params.push_back(make_pair(eINTEGER, StringUtil::IntToAnsi(input)));
}
void SQLiteQueryBase::AddParam(const __int32 input)
{
	m_Params.push_back(make_pair(eINTEGER, StringUtil::IntToAnsi(input)));
}
void SQLiteQueryBase::AddParam(const __int64 input)
{
	m_Params.push_back(make_pair(eINTEGERLONG, StringUtil::IntToAnsi(input)));
}
void SQLiteQueryBase::AddParam(const float input)
{
	m_Params.push_back(make_pair(eDOUBLE, StringUtil::FloatToAnsi(input)));
}
void SQLiteQueryBase::AddParam(const double input)
{
	m_Params.push_back(make_pair(eDOUBLE, StringUtil::DoubleToAnsi(input)));
}
void SQLiteQueryBase::AddParam(const char* input)
{
	m_Params.push_back(make_pair(eTEXT, input));
}
void SQLiteQueryBase::AddParam(const string input)
{
	m_Params.push_back(make_pair(eTEXT, input));
}

void SQLiteQueryBase::Prepare()
{
	//sqlite3_prepare_v2 ���� �̹�, ������ ����ȴٰ� �� �� ����.
	//SQLITE_OK �϶�, m_res �ڵ��� ���Ͽ�, ������� �ڵ鸵 �� �� �ְ� ����.
	m_excuteResult = sqlite3_prepare_v2(m_db, m_sql.c_str(), -1, &m_res, 0);
}
void SQLiteQueryBase::Bind()
{
	for (int i = 0; i < m_Params.size(); i++)
	{
		RegistSQLiteParam(m_Params[i].first, m_Params[i].second, i + 1);
	}
}
void SQLiteQueryBase::RegistSQLiteParam(const SQPLITE_TYPE type, const string str, const int cnt)
{
	switch (type)
	{
	case eINTEGER: sqlite3_bind_int(m_res, cnt, stoi(str));
		return;
	case eINTEGERLONG:sqlite3_bind_int64(m_res, cnt, stoll(str));
		return;
	case eDOUBLE:sqlite3_bind_double(m_res, cnt, stod(str));
		return;
	case eTEXT:
	{
		//������ UTF-8�� ��ȯ�ؼ� DB�� ���� SQLITE3 DB�� �⺻ ���ڵ��� UTF-8
		string _utf8Str = StringUtil::AnsiToUtf8(str);
		sqlite3_bind_text(m_res, cnt, _utf8Str.c_str(), static_cast<__int32>(_utf8Str.length()), SQLITE_TRANSIENT);
		return;
	}
	case e_NULL: sqlite3_bind_null(m_res, cnt);
		return;
	default:
		return;
	}
}
void SQLiteQueryBase::Excute(SQLiteDBAgent* agent)
{
	SetDBHandle(agent->GetDBHandler());

	Prepare();

	if (m_res == nullptr)
	{
		ErrorLog("[%s] - Fail prepare", __FUNCTION__);
		return;
	}

	Bind();

	m_commandResult = Fetch();

	if (m_commandResult != SQLITE_DONE)
	{
		ErrorLog("[%s] - Failed Fetch retrn Val : %d", __FUNCTION__, m_commandResult);
	}
	return;	
}

int SQLiteQueryBase::Fetch()
{
	int step = sqlite3_step(m_res);

	while (step == SQLITE_ROW)
	{
		vector<string> outCul;
		const int _columnCnt = sqlite3_data_count(m_res);
		for (int i = 0; i < _columnCnt; i++)
		{
			GetValue(i, outCul);
		}
		m_Result.push_back(outCul);
		step = sqlite3_step(m_res);
	}

	sqlite3_finalize(m_res);

	return step;
}

void SQLiteQueryBase::GetValue(const __int32 pos, OUT vector<string>& outCul)
{
	//������ String ���� �޾Ƽ� outCul�� ����
	//�������� ���� ��ȯ�ؼ� ���
	const char* _strPtr = reinterpret_cast<const char*>(sqlite3_column_text(m_res, pos));
	const string _outStr = _strPtr;
	outCul.push_back(_outStr);
}

void SQLiteQueryBase::SetDBHandle(sqlite3* dbHandle)
{
	m_db = dbHandle;
}

__int32 SQLiteQueryBase::IsValid()
{
	return m_excuteResult;
}

__int32 SQLiteQueryBase::GetResultCount()
{
	return static_cast<__int32>(m_Result.size());
}

void SQLiteQueryBase::SetSycnFlag()
{
	m_isSyncQuery.exchange(true);
}

bool SQLiteQueryBase::IsSyncQuery()
{
	return m_isSyncQuery;
}

void SQLiteQueryBase::SetSession(shared_ptr<PacketSession> sessionShared)
{
	m_SessionShared = sessionShared;
}
