#include "WardrobeDB.h"
#include "AppConstants.h"

WardrobeDB* WardrobeDB::instance = nullptr;

WardrobeDB::WardrobeDB()
{
    init();
}

void WardrobeDB::init()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", "Data");
    m_db.setDatabaseName(DB_PATH);

    CONSOLE << DB_PATH;

    if(QFile::exists(DB_PATH))
        CONSOLE << "DB file exist";
    else
        CONSOLE << "DB file doesn't exists";

    if (!m_db.open())
        CONSOLE << m_db.lastError().text();
    else
        CONSOLE << "Database loaded successfull!";
}

WardrobeDB *WardrobeDB::getInstance()
{

    if(instance == nullptr)
        instance = new WardrobeDB();

    return instance;
}

QSqlDatabase WardrobeDB::getDBInstance()
{
    return m_db;
}

void WardrobeDB::resetInstance()
{
    delete instance;
    instance = nullptr;
}

WardrobeDB::~WardrobeDB()
{
    m_db.close();
}
