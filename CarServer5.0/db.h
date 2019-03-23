#ifndef DB_H
#define DB_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <qDebug>
#include <QMessageBox>
#include <QHostAddress>
static bool createData()
{

    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("car");
    db.setUserName("root");
    db.setPassword("");


    if(!db.open())
    {
        qDebug()<<db.lastError();
        qFatal("failed to connect.") ;

      return false;
    }else
    {
        //建表----------------
          QSqlQuery sql_query;
          QString create_sql1 =  "create table carOwner (id varchar(30) primary key, name varchar(30), age int, tel int(11),adress varchar(30))";
          QString create_sql2 =  " create table car(carNumber varchar(10) primary key,carOwnId varchar(30),carOwnName varchar(30),carType varchar(30))";
          QString create_sql3 =  " create table pirture(pId int(10) primary key,pPath varchar(30),time datatime,pAdress varchar(30),carNumber varchar(10),flag bool)";
          QString create_sql4 =  " create table sendAccount(sendId int primary key,username varchar(30),password varchar(30))";
          QString create_sql5 =  "create table receiveAccount(receiveId int primary key,username varchar(30),password varchar(30))";
          QString select_max_sql = "select max(sendId) from sendAccount";
          QString select_max_rec = "select max(receiveId) from receiveAccount";
          QString insert_sql = "insert into sendAccount values (?, ?, ?)";
          QString select_max_carOwner = "select max(id) from carOwner";
          QString insert_carOwner="insert into carOwner values (?,?,?,?,?)";
          QString insert_car="insert into car values (?,?,?,?)";
          QString clear_carOwner = "delete from carOwner";
          QString clear_car = "delete from car";
          QString drop_car = "drop table car";
          QString drop_carOwner = "drop table carOwner";
          QString drop_picture = "drop table pirture";

//清空表....................................
          sql_query.prepare(clear_carOwner);
          if(!sql_query.exec())
          {
          qDebug()<<sql_query.lastError();
          }
          else
          {
          qDebug()<<"cleared";
          }
          sql_query.prepare(clear_car);
          if(!sql_query.exec())
          {
          qDebug()<<sql_query.lastError();
          }
          else
          {
          qDebug()<<"cleared";
          }
          sql_query.prepare(drop_car);
          if(!sql_query.exec())
          {
          qDebug()<<sql_query.lastError();
          }
          else
          {
          qDebug()<<"droped";
          }

          sql_query.prepare(drop_carOwner);
          if(!sql_query.exec())
          {
          qDebug()<<sql_query.lastError();
          }
          else
          {
          qDebug()<<"droped";
          }

//          sql_query.prepare(drop_picture);
//          if(!sql_query.exec())
//          {
//          qDebug()<<sql_query.lastError();
//          }
//          else
//          {
//          qDebug()<<"droped";
//          }

//        QString create_sql =    "create table carOwner (id int(18) primary key, name varchar(30), age int, tel int(11),adress varchar(30))";
//                               " create table car(carNumber varchar(10) primary key,carOwnId int(18),carType varchar(30))"
//                               " create table pirture(pId int(10) primary key,pPath varchar(30),carNumber varchar(10),flag bool)"
//                               " create table sendAccount(sendId int primary key,username varchar(30),password varchar(30))"
//                               "create table receiveAccount(receiveId int primary key,username varchar(30),password varchar(30))";



       //建表.......................................
          sql_query.prepare(create_sql1);
        if(!sql_query.exec())
        {
        qDebug()<<sql_query.lastError();
        }
        else
        {
        qDebug()<<"table1 created!";
        }

        sql_query.prepare(create_sql2);
         if(!sql_query.exec())
         {
         qDebug()<<sql_query.lastError();
         }
         else
         {
         qDebug()<<"table2 created!";
         }

         sql_query.prepare(create_sql3);
          if(!sql_query.exec())
          {
          qDebug()<<sql_query.lastError();
          }
          else
          {
          qDebug()<<"table3 created!";
          }

          sql_query.prepare(create_sql4);
           if(!sql_query.exec())
           {
           qDebug()<<sql_query.lastError();
           }
           else
           {
           qDebug()<<"table4 created!";
           }

           sql_query.prepare(create_sql5);
            if(!sql_query.exec())
            {
            qDebug()<<sql_query.lastError();
            }
            else
            {
            qDebug()<<"table5 created!";
            }

//        //查询最大id
//        int max_id = 0;
//        sql_query.prepare(select_max_sql);
//        if(!sql_query.exec())
//        {
//        qDebug()<<sql_query.lastError();
//        }
//        else
//        {
//        while(sql_query.next())
//        {
//        max_id = sql_query.value(0).toInt();
//        qDebug()<<QString("max id:%1").arg(max_id);
//        }
//        }

//        //插入数据
//        sql_query.prepare(insert_sql);
//        sql_query.addBindValue(max_id+1);
//        sql_query.addBindValue("name");
//        sql_query.addBindValue("25");
//        if(!sql_query.exec())
//        {
//        qDebug()<<sql_query.lastError();
//        }
//        else
//        {
//        qDebug()<<"inserted!";
//        }

             int max_carOwmer_id =29617;
          //   qDebug()<<"max_carOwmer_id"<<max_carOwmer_id;
             int carNumber_1 =12;
             int carNumber_2 =81;


        for(int i=0;i<30;i++){

             max_carOwmer_id= max_carOwmer_id+1521;

            //插入数据
          //  qDebug()<<"max_carOwmer_id"<<max_carOwmer_id;
            sql_query.prepare(insert_carOwner);
            sql_query.addBindValue(QObject::tr("410329199301").append(QString::number(max_carOwmer_id)));

            QString name ="张"+QString::number(10+i);
            sql_query.addBindValue(name);
            sql_query.addBindValue(i+10);
            sql_query.addBindValue(i+101);
            QString address ="石景苑"+QString::number(50-i)+"号";
            sql_query.addBindValue(address);
            if(!sql_query.exec())
            {
            qDebug()<<sql_query.lastError();
            }
            else
            {
          //  qDebug()<<"inserted carOwner"<<i;
            }


            carNumber_1++;
            carNumber_2--;
            sql_query.prepare(insert_car);
            QString carNumber="辽*A"+QString::number(carNumber_1)+"X"+QString::number(carNumber_2);
           // qDebug()<<"carNumber="<<carNumber;
            sql_query.addBindValue(carNumber);
            sql_query.addBindValue(QObject::tr("410329199301").append(QString::number(max_carOwmer_id)));
            sql_query.addBindValue(name);
            QString carType="奇瑞"+QString::number(i)+"30XL";
            sql_query.addBindValue(carType);
            if(!sql_query.exec())
            {
            qDebug()<<sql_query.lastError();
            }
            else
            {
          //  qDebug()<<"inserted car"<<i;
            }



        }





        //初始化两个账户
        sql_query.exec("insert into sendAccount values('1','20144644','20144644')");
        sql_query.exec("insert into sendAccount values('2','20144645','20144645')");
        sql_query.exec("insert into receiveAccount values('1','20144644','20144644')");

        return true;
    }




}
#endif // DB_H

