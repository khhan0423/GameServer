#pragma once
#include <vector>
#include <queue>
#include <mutex>

#include "pch.h"

template<typename T>
class LockQueue
{
public:
	void Push(T item)
	{
		{
			lock_guard<recursive_mutex> _lock(m_lock);
			m_sometings.push(item);
		}
		
	}

	T Pop()
	{
		{
			lock_guard<recursive_mutex> _lock(m_lock);

			if (m_sometings.empty())
				return T();

			T ret = m_sometings.front();
			m_sometings.pop();
			return ret;
		}
	}

	void Pop(OUT vector<T>& sometings)
	{
		{
			lock_guard<recursive_mutex> _lock(m_lock);

			while (T _thing = Pop())
				sometings.push_back(_thing);
		}
	}

	void Clear()
	{
		{
			lock_guard<recursive_mutex> _lock(m_lock);
			m_sometings = queue<T>();
		}		
	}

private:
	recursive_mutex		m_lock;
	queue<T>			m_sometings;
};
