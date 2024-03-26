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
			std::lock_guard<std::mutex> _lock(m_lock);
			m_sometings.push(item);
		}
		
	}

	T Pop()
	{
		{
			std::lock_guard<std::mutex> _lock(m_lock);

			if (m_sometings.empty())
				return T();

			T ret = m_sometings.front();
			m_sometings.pop();
			return ret;
		}
	}

	void Pop(OUT std::vector<T>& sometings)
	{
		{
			std::lock_guard<std::mutex> _lock(m_lock);

			while (T _thing = Pop())
				sometings.push_back(_thing);
		}
	}

	void Clear()
	{
		{
			std::lock_guard<std::mutex> _lock(m_lock);
			m_sometings = std::queue<T>();
		}		
	}

private:
	std::mutex				m_lock;
	std::queue<T>			m_sometings;
};
