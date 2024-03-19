#pragma once

#include "DataBaseBase.h"
#include "SQLite.h"
#include "SQLiteAgent.h"

using namespace DataBase;
using namespace DataBase::SQLite3;

class SQLiteManager : public DBManagerInterface<SQLiteQueryBase, SQLiteConnector>
{

};

