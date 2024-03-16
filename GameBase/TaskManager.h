#pragma once
#include "SingletonBase.h"

#define GetTaskManager() TaskManager::GetInstance()

class TaskManager : public SingletonBase<TaskManager>
{
public:
	TaskManager() { cout << "TaskManager::TaskManager()" << endl; };
	~TaskManager() { cout << "TaskManager::~TaskManager()" << endl; };

	void								Regist(shared_ptr<TaskQueue> taskQueue);
	shared_ptr<TaskQueue>				Pop();

private:
	LockQueue<shared_ptr<TaskQueue>>	m_globalTaskLine;
};

