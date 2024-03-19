#pragma once
#include <vector>
#include <mutex>
#include <thread>
#include <functional>

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();
							//void 형을 반환하는 void 가 인자값인 함수자
							//즉 람다를 받아서 실행.
	void					Launch(function<void(void)> callback);
	void					Join();

	static void				Run();

	static void				InitTLS();
	static void				ReleaseTLS();

	atomic<bool>			m_startFlag = false;

private:
	recursive_mutex		m_lock;
	vector<thread>		m_threadList;	
};


