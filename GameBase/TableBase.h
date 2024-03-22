#pragma once
#include <map>
#include "LogBase.h"


template<typename T>
class TableBaseSingleton : public TSingletonBase<T>
{
public:
	virtual const char*			GetFileName() abstract {}
public:
	virtual bool				LoadXLSX(const char* XLSXfileName) abstract {}
	virtual bool				LoadCompleted()	abstract {}

public:
	virtual bool Load()
	{
		if (LoadXLSX(GetFileName()) == false)
		{
			ErrorLog("%s Table Loading Fail", GetFileName());
			return false;
		}

		return true;
	}
};

//테이블에는 Key 값으로 해당 데이터를 뽑아오는 인터페이스를 제공해 주어야 한다.
//key는 타입... pair 일 수도 있고.. 템플릿으로 뽑아야 할려나.
template <typename KEY, typename RECORD>
class TableRecordDatas
{
public:
	TableRecordDatas() {};
	virtual ~TableRecordDatas()
	{
		Release();
	}
public:

	bool Insert(const KEY& key, RECORD* dataPtr)
	{
		{
			lock_guard<mutex> _lock(m_lock);
			const __int32 _index = static_cast<__int32>(m_Data.size());

			auto _result = m_keyIndex.emplace(make_pair(key, _index));
			m_Data.push_back(dataPtr);

			return _result.second;
		}
	}

	//지우는게 필요 있을까...? 봉인
	//bool Erase(const KEY& rKey)
	//{
	//	{
	//		lock_guard<mutex> _lock(m_lock);
	//
	//		auto _iter = m_keyIndex.find(rKey);
	//		if (_iter == m_keyIndex.end())
	//			return false;
	//
	//		__int32 _index = _iter->second;
	//
	//		m_keyIndex.erase(_iter);
	//
	//		SAFE_DELETE(m_Data[_index]);
	//	}
	//}

	void Release()
	{
		{
			lock_guard<mutex> _lock(m_lock);
			for (auto&& _iter : m_Data)
			{
				SAFE_DELETE(_iter);
			}

			m_keyIndex.clear();
		}
	}

private:
	mutex				m_lock;
private:
	unordered_map<KEY, __int32>		m_keyIndex;
	vector<RECORD*>					m_Data;
};