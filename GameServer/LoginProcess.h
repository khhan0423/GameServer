#pragma once
#include "SQLiteQuery.h"

using namespace DataBase::SQLite3;

class FindAccount : public SQLiteQueryBase
{
public:
	FindAccount(shared_ptr<PacketSession> sessionShared, const wstring& accountID);

void	Complete() override;

};

