#pragma once
#include "SingletonBase.h"
#include "DataBaseBase.h"
#include "SQLiteQuery.h"
#include "SQLiteAgent.h"

using namespace DataBase;
using namespace DataBase::SQLite3;

#define GetDBManager() SQLiteManager::GetInstance()

class SQLiteManager : public DBManagerInterface<SQLiteQueryBase, SQLiteDBAgent>, public TSingletonBase<SQLiteManager>
{
public:
	bool		Start() override;
	void		Stop() override;
	void		Update() override;

public:
	__int32		GetFPS(__int32 index) const override;
	__int32		GetBadFPS() const override;

	void		SetReady();	
};

