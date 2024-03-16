#pragma once
#include "task.h"
#include "LockQueueBase.h"

class TaskQueue : public enable_shared_from_this<TaskQueue>
{
public:

	void RegistTaskLine(CallbackType&& callback)
	{
		Regist(make_shared<Task>(std::move(callback)));
	}
	
	//ReturnType ExampleClass::MemberFunction(arg1 a, arg2 b, arg3 c)
	//Task( shared_ptr<ExampleClass> owner, ReturnType(ExampleClass::*MemberFunction)(arg1 a, arg2 b, arg3 c), (arg1 a, arg2 b, arg3 c))
	//Ŭ������ �ɹ������� Ÿ��, ����Ÿ��, �ɹ��Լ��� ������, �Ķ���͵�� �и��� ����,
	//���ٷ� ĸó�޾Ƽ� �����Ͽ� �ɹ��Լ� ȣ��
	template<typename T, typename Ret, typename... Args>
	void RegistTaskLine(Ret(T::* memFunc)(Args...), Args... args)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		Regist(make_shared<Task>(owner, memFunc, std::forward<Args>(args)...));
	}


	void								ClearTakeLine() { m_taskLineQueue.Clear(); }

protected:
	void								Regist(shared_ptr<Task> task);
	void								Run();

protected:
	LockQueue<shared_ptr<Task>>			m_taskLineQueue;
	atomic<__int32>						m_taskCount = 0;
};

