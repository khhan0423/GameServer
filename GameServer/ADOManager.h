#pragma once
#include <vector>
#include "SingletonBase.h"
#include "ADOAgnet.h"

using namespace DataBase;
using namespace DataBase::SQLite3;

class ADOManager : public TSingleton<ADOManager>
{
public:
	public:
		ADOManager() { }
		virtual ~ADOManager() { Stop(); }

	public:
		virtual bool				Start();
		virtual void				Stop();
		virtual void				Update();

	public:
		void						Insert(int DBGUID, ADOQuery* Query);
		ADOAgent*					GetDBAgent(int DBGUID);
		size_t						GetAgentCount() const { return m_DBAgentList.size(); }

	public:
		virtual int					GetFPS(int index) const;
		virtual int					GetBadFPS() const;

	public:
		int							GetWaitQueueCount(int index) const;
		int							GetCompleteQueueCount(int index) const;

	private:
		ADOAgent*					m_pDBAgentForPool = nullptr;
		vector<ADOAgent*>			m_DBAgentList;
		DataBaseCoInitialize		m_CoInit;


public:

	//Contents
};

