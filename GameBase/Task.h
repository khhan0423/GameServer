#pragma once
#include <functional>

//void Ÿ���� �����ϴ� void Ÿ���� ���ڷ� ���� �Լ���, �� ����
//CallBack ���� ���ٸ� ����Ͻÿ�.

using CallbackType = std::function<void()>;

class Task
{
public:
	Task(CallbackType&& callback) : m_callback(std::move(callback))
	{
	}

	//ReturnType ExampleClass::MemberFunction(arg1 a, arg2 b, arg3 c)
	//Task( shared_ptr<ExampleClass> owner, ReturnType(ExampleClass::*MemberFunction)(arg1 a, arg2 b, arg3 c), (arg1 a, arg2 b, arg3 c))
	//Ŭ������ �ɹ������� Ÿ��, ����Ÿ��, �ɹ��Լ��� ������, �Ķ���͵�� �и��� ����,
	//���ٷ� ĸó�޾Ƽ� �����Ͽ� �ɹ��Լ� ȣ��
	template<typename T, typename Ret, typename... Args>
	Task(shared_ptr<T> owner, Ret(T::* memFunc)(Args...), Args&&... args)
	{
		m_callback = [owner, memFunc, args...]()
			{
				(owner.get()->*memFunc)(args...);
			};
	}

	void Run()
	{
		m_callback();
	}

private:
	
	CallbackType		m_callback;
};
