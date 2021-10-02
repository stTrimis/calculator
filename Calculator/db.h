/* A simple calculator, with sqlite.It was for a University Project.
 * All Rights Reserved By Stelios Trimis */

#ifndef DB_H
#define DB_H

#include<QtSql>
#include<QMessageBox>
#include "calculator.h"

class db
{

public:
    //bool insertnumber(Calculator &c);
    db();
    //~db();
    QSqlDatabase BasiDedomenon;
    void connClose()
    {
        BasiDedomenon.close();
        BasiDedomenon.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        BasiDedomenon=QSqlDatabase::addDatabase("QSQLITE");
        BasiDedomenon.setDatabaseName("C:/Users/straq/Desktop/Optikos Ergasia/Calculator/calculator.db");
        if(!BasiDedomenon.open()){
            qDebug()<<("error");
            return false;
        }
        else{
                qDebug()<<("connect...");
                return true;
        }
     }


};

#endif // DB_H
