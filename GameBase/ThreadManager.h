#pragma once
#include <vector>
#include <mutex>
#include <thread>
#include <functional>
//#include "SingletonBase.h"

//#define GetThreadManager() ThreadManager::GetInstance()

class ThreadManager //: public TSingleton<ThreadManager>
{
public:
	ThreadManager();
	~ThreadManager();
						//void ���� ��ȯ�ϴ� void �� ���ڰ��� �Լ���
						//�� ���ٸ� �޾Ƽ� ����.
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


