#pragma once
#include <list>
#include <algorithm>

class SingletonBase
{
protected:
	class SManager
	{
	private:
		list<SingletonBase*>		m_list;
		mutex						m_lock;

	public:
		virtual ~SManager()
		{
			Release();
		}
		void Release()
		{
			struct delete_ptr { void operator() (SingletonBase* p) { delete p; } };
			for_each(m_list.begin(), m_list.end(), delete_ptr());
			
			{
				lock_guard<mutex> _lock(m_lock);
				m_list.clear();
			}
		}
		void Add(SingletonBase* pSingleton)
		{
			{
				lock_guard<mutex> _lock(m_lock);
				m_list.push_front(pSingleton);
			}

		}
		void Erase(SingletonBase* pSingleton)
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
	SingletonBase() {}

public:
	virtual ~SingletonBase() {}
};

template<typename TYPE>
class TSingletonBase : public SingletonBase
{

protected:
	static TYPE* _static_pInstance;
	static mutex _static_lock;

protected:
	TSingletonBase() {}
	virtual ~TSingletonBase() { if (this == _static_pInstance) Delete(false); }

public:
	static TYPE* GetInstance()
	{
		if (_static_pInstance == nullptr)
		{
			lock_guard<mutex> _lock(_static_lock);
			if (_static_pInstance == nullptr)
			{
				_static_pInstance = new TYPE;
				SingletonBase::GetManager().Add(_static_pInstance);
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
					SingletonBase::GetManager().Erase(_pInstance);
					SAFE_DELETE(_pInstance);
				}
			}
		}
	}

private:
	TSingletonBase(const TSingletonBase<TYPE>&);
	const TSingletonBase<TYPE>& operator = (const TSingletonBase<TYPE>&);
};

template<typename TYPE>
TYPE* TSingletonBase<TYPE>::_static_pInstance;

template<typename TYPE>
mutex TSingletonBase<TYPE>::_static_lock;
