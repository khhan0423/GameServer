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
			struct delete_ptr
			{ 
				void operator() (SingletonBase* p)
				{
					SAFE_DELETE(p); 
				} 
			};

			for_each(m_list.begin(), m_list.end(), delete_ptr());			
			{
				{
					lock_guard<mutex> _lock(m_lock);
					m_list.clear();
				}
			}
		}
		void Add(SingletonBase* singletonPtr)
		{
			{
				lock_guard<mutex> _lock(m_lock);
				m_list.push_front(singletonPtr);
			}

		}
		void Erase(SingletonBase* singletonPtr)
		{
			{
				lock_guard<mutex> _lock(m_lock);
				auto it = std::find(m_list.begin(), m_list.end(), singletonPtr);
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
	static TYPE* m_Instance;
	static mutex m_lock;

protected:
	TSingletonBase() {}
	virtual ~TSingletonBase() { if (this == m_Instance) Delete(false); }

public:
	static TYPE* GetInstance()
	{
		if (m_Instance == nullptr)
		{
			lock_guard<mutex> _lock(m_lock);
			if (m_Instance == nullptr)
			{
				m_Instance = new TYPE;
				SingletonBase::GetManager().Add(m_Instance);
			}
		}

		return m_Instance;
	}
	
	static void Delete(bool deleteFlag = true)
	{
		if (m_Instance != nullptr)
		{
			lock_guard<mutex> _lock(m_lock);
			if (m_Instance != nullptr)
			{
				TYPE* _pInstance = m_Instance;
				m_Instance = nullptr;
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
TYPE* TSingletonBase<TYPE>::m_Instance;

template<typename TYPE>
mutex TSingletonBase<TYPE>::m_lock;
