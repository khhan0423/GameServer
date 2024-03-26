#include "pch.h"
#include "SingletonBase.h"
#include "LockQueueBase.h"
#include "TaskQueue.h"
#include "TaskManager.h"

void TaskManager::Regist(std::shared_ptr<TaskQueue> taskQueue)
{
	m_globalTaskLine.Push(taskQueue);
}

std::shared_ptr<TaskQueue> TaskManager::Pop()
{
	return m_globalTaskLine.Pop();
}