#pragma once
#include "SQLiteQuery.h"

using namespace DataBase::SQLite3;

class FindAccount : public SQLiteQueryBase
{
public:
	FindAccount(std::shared_ptr<PacketSession> sessionShared, const std::wstring& accountID);

void	Complete() override;

};

