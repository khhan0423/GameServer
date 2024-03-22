#pragma once

#include "SingletonBase.h"
#include "LogBase.h"

class TaskManager
{
public:
	TaskManager() { DebugLog("[%s]", __FUNCTION__); };
	~TaskManager() { DebugLog("[%s]", __FUNCTION__); };

	void								Regist(shared_ptr<TaskQueue> taskQueue);
	shared_ptr<TaskQueue>				Pop();

private:
	LockQueue<shared_ptr<TaskQueue>>	m_globalTaskLine;
};

