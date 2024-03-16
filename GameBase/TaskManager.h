#pragma once

class TaskManager
{
public:
	TaskManager() { cout << "TaskManager::TaskManager()" << endl; };
	~TaskManager() { cout << "TaskManager::~TaskManager()" << endl; };

	void								Regist(shared_ptr<TaskQueue> taskQueue);
	shared_ptr<TaskQueue>				Pop();

private:
	LockQueue<shared_ptr<TaskQueue>>	m_globalTaskLine;
};

