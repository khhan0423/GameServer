#pragma once
template<typename T>
class SingletonBase
{
public:
	static T* GetInstance()
	{
		call_once(m_onceFlag, []
			{
				m_pInstance.reset(new T);
			}
		);

		return m_pInstance.get();
	}

private:
	static shared_ptr<T>	m_pInstance;
	static once_flag		m_onceFlag;
};
template<typename T> shared_ptr<T> SingletonBase<T>::m_pInstance = nullptr;
template<typename T> once_flag SingletonBase<T>::m_onceFlag;
