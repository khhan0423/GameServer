#pragma once
#include <list>
#include <algorithm>

class SSingletonBase
{
protected:
	class SManager
	{
	private:
		list<SSingletonBase*>		m_list;
		mutex						m_lock;

	public:
		virtual ~SManager()
		{
			Release();
		}
		void Release()
		{
			struct delete_ptr { void operator() (SSingletonBase* p) { delete p; } };
			for_each(m_list.begin(), m_list.end(), delete_ptr());
			
			{
				lock_guard<mutex> _lock(m_lock);
				m_list.clear();
			}
		}
		void Add(SSingletonBase* pSingleton)
		{
			{
				lock_guard<mutex> _lock(m_lock);
				m_list.push_front(pSingleton);
			}

		}
		void Erase(SSingletonBase* pSingleton)
		{
			{
				lock_guard<mutex> _lock(m_lock);
				auto it = std::find(m_list.begin(), m_list.end(), pSingleton);
				if (it != m_list.end()) m_list.erase(it);
			}
		}
	};

public:
	static SManager& GetManager()
	{
		static mutex _static_lock;
		{
			lock_guard<mutex> _lock(_static_lock);
			static SManager s_Manager;
			return s_Manager;
		}
	}

protected:
	SSingletonBase() {}

public:
	virtual ~SSingletonBase() {}
};

template<typename TYPE>
class TSingleton : public SSingletonBase
{

protected:
	static TYPE* _static_pInstance;
	static mutex _static_lock;

protected:
	TSingleton() {}
	virtual ~TSingleton() { if (this == _static_pInstance) Delete(false); }

public:
	static TYPE* GetInstance()
	{
		if (_static_pInstance == nullptr)
		{
			lock_guard<mutex> _lock(_static_lock);
			if (_static_pInstance == nullptr)
			{
				_static_pInstance = new TYPE;
				SSingletonBase::GetManager().Add(_static_pInstance);
			}
		}

		return _static_pInstance;
	}
	
	static void Delete(bool deleteFlag = true)
	{
		if (_static_pInstance != nullptr)
		{
			lock_guard<mutex> _lock(_static_lock);
			if (_static_pInstance != nullptr)
			{
				TYPE* _pInstance = _static_pInstance;
				_static_pInstance = nullptr;
				if (deleteFlag)
				{
					SSingletonBase::GetManager().Erase(_pInstance);
					delete _pInstance;
				}
			}
		}
	}

private:
	TSingleton(const TSingleton<TYPE>&);
	const TSingleton<TYPE>& operator = (const TSingleton<TYPE>&);
};

template<typename TYPE>
TYPE* TSingleton<TYPE>::_static_pInstance;

template<typename TYPE>
mutex TSingleton<TYPE>::_static_lock;
