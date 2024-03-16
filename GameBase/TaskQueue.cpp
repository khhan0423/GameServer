#include "pch.h"
#include <vector>
#include "LockQueueBase.h"
#include "TaskQueue.h"
#include "TaskManager.h"

void TaskQueue::Regist(shared_ptr<Task> task)
{
	const __int32 _currentTaskCount = m_taskCount.fetch_add(1);
	
	m_taskLineQueue.Push(task);	

	if (_currentTaskCount == 0)
	{
		if (TLS_CurrentTaskQueue == nullptr)
		{
			Run();
		}
		else
		{
			GetTaskManager()->Regist(shared_from_this());
		}
	}
}

void TaskQueue::Run()
{
	TLS_CurrentTaskQueue = this;

	while (true)
	{
		vector<shared_ptr<Task>> _taskLine;
		m_taskLineQueue.Pop(OUT _taskLine);

		const __int32 _taskCount = static_cast<__int32>(_taskLine.size());
		
		for (__int32 i = 0; i < _taskCount; i++)
			_taskLine[i]->Run();

		
		if (m_taskCount.fetch_sub(_taskCount) == _taskCount)
		{
			TLS_CurrentTaskQueue = nullptr;
			return;
		}

		const unsigned __int64 _now = ::GetTickCount64();
		if (_now >= TLS_EndTickCount)
		{
			TLS_CurrentTaskQueue = nullptr;
			GetTaskManager()->Regist(shared_from_this());
			break;
		}
	}
}
