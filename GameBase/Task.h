#pragma once
#include <functional>

//void 타입을 리턴하는 void 타입을 인자로 가진 함수자, 즉 람다
//CallBack 으로 람다를 사용하시오.

using CallbackType = std::function<void()>;

class Task
{
public:
	Task(CallbackType&& callback) : m_callback(std::move(callback))
	{
	}

	//ReturnType ExampleClass::MemberFunction(arg1 a, arg2 b, arg3 c)
	//Task( shared_ptr<ExampleClass> owner, ReturnType(ExampleClass::*MemberFunction)(arg1 a, arg2 b, arg3 c), (arg1 a, arg2 b, arg3 c))
	//클래스의 맴버변수를 타입, 리턴타입, 맴버함수의 포인터, 파라미터들로 분리한 다음,
	//람다로 캡처받아서 조립하여 맴버함수 호출
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
