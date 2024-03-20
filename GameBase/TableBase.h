#pragma once

template<typename T>
class TableBaseSingleton : public TSingletonBase<T>
{
public:
	virtual const char*			GetFileName() abstract;
public:
	virtual bool				LoadXLSX(const char* XLSXfileName) abstract;
	virtual bool				LoadCompleted() { return true; }

public:
	virtual bool Load()
	{
		if (LoadXLSX(GetFileName()) == false)
		{
			ErrorLog("%s Table Loading Fail", GetFileName());
			return false;
		}

		return true;
	}
};