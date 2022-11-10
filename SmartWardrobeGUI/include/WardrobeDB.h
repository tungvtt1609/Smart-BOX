#ifndef WARDROBEDB_H
#define WARDROBEDB_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QSqlError>
#include <QSqlQueryModel>

class WardrobeDB
{
public:
    static WardrobeDB* getInstance();
    static void resetInstance();
    QSqlDatabase getDBInstance();
    ~WardrobeDB();

private:
    WardrobeDB();
    static WardrobeDB *instance;
    void init();
    QSqlDatabase m_db;
};

#endif // WARDROBEDB_H
