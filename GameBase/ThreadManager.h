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
	void					Launch(std::function<void(void)> callback);
	void					Join();

	static void				Run();

	static void				InitTLS();
	static void				ReleaseTLS();

	std::atomic<bool>			m_startFlag = false;

private:
	std::recursive_mutex		m_lock;
	std::vector<std::thread>		m_threadList;	
};


