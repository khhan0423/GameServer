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
							//void ���� ��ȯ�ϴ� void �� ���ڰ��� �Լ���
							//�� ���ٸ� �޾Ƽ� ����.
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


