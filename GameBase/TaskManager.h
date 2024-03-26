#pragma once

#include "SingletonBase.h"
#include "LogBase.h"

class TaskManager
{
public:
	TaskManager() { DebugLog("[%s]", __FUNCTION__); };
	~TaskManager() { DebugLog("[%s]", __FUNCTION__); };

	void								Regist(std::shared_ptr<TaskQueue> taskQueue);
	std::shared_ptr<TaskQueue>				Pop();

private:
	LockQueue<std::shared_ptr<TaskQueue>>	m_globalTaskLine;
};

