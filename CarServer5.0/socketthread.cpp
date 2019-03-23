#include "SocketThread.h"
#include <qDebug>
#include"db.h"
SocketThread::SocketThread(QObject *parent ,int socketDescriptor
                         ):QThread(parent),socketDescriptor(socketDescriptor)
{
   blockSize=0;
   PicSize =0;
   model =new QSqlTableModel(parent);
   isStart = true;
   name ="";

}

void SocketThread::run(){
    tcpSocket = new QTcpSocket;
    //将Server传来的socketDescriptor与刚创建的tcpSocket关联
    if (!tcpSocket->setSocketDescriptor(socketDescriptor))
    {
        return;
    }
    //Qt::AutoConnection表示系统自动选择相应的连接方式，
    //如果信号与槽在同一线程，就采用Qt::DirectConnection,一旦信号产生，立即执行槽函数。
    connect(tcpSocket, SIGNAL(readyRead()), this,
        SLOT(readAll()), Qt::DirectConnection);
    exec();
}

void SocketThread::readMessage()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_5);
    if (blockSize == 0)
    {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }
    if (tcpSocket->bytesAvailable() < blockSize)
        return;

    in >> getMsg;
    qDebug()<< "服务器接受到了消息："<<getMsg;
    blockSize = 0;

}
void SocketThread::readAll(){
    buf = tcpSocket->readAll();
    //qDebug()<<"buf:"<<QString(buf);

     if(QString(buf).contains("login|")){

        QStringList str =QString(buf).split("|");
        QStringList strList = str.at(1).split("/");
        name= strList.at(0);
        QString password = strList.at(1);
        sendMsg = QString::number(login(name,password));
        sendMessage();
    }else {
         readPicture();
     }
}
void SocketThread::readPicture()
{

 if(true == isStart)
 {   // 接受头部信息
     isStart = false;
     //buf=hello##1024
     fileName = QString (buf).section("##",0,0);
     fileSize = QString (buf).section("##",1,1).toInt();
     nowTime = QString (buf).section("##",2,2);
     recSize =0;

     file.setFileName(tr("./temp/")+fileName);
     bool isOk = file.open(QIODevice::WriteOnly);
     if(false == isOk)
     {
         qDebug()<<"打开出错";
     }
     sendMsg = "file";
     sendMessage();
 }else{
     qint64 len =file.write(buf);
     recSize +=len;
     if(recSize == fileSize)
     {
         sendMsg="1";
         sendMessage();
         file.close();
         qDebug()<<"完成文件传输";
         isStart=true;
//             tcpSocket->disconnect();
//             tcpSocket->close();

         saveFileInDb(fileName,nowTime);
     }

 }

}
void SocketThread::sendMessage()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << sendMsg;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    tcpSocket->write(block);
    qDebug()<< "服务器发送了消息："<<sendMsg;
}
void SocketThread::saveFileInDb(QString fileName, QString nowTime){
    QSqlQuery sql_query;
    QString insert_pirture = "insert into pirture values (?,?,?,?,?,?)";
    QString select_same_pirture=tr("select pPath from pirture where pPath='%1'").arg(fileName);
    QString select_max_pirtureId = "select max(pId) from pirture ";

    //查询最大id

    if(name=="20144644")
    {
        pAderss ="顺义区-石门街";
    }else if(name == "20144645")
    {
        pAderss ="浑南新区-火石桥";
    }

    int max_id = 0;
    sql_query.prepare(select_max_pirtureId);
    if(!sql_query.exec())
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
    while(sql_query.next())
    {
    max_id = sql_query.value(0).toInt();
    qDebug()<<QString("max id:%1").arg(max_id);
    }
    }
    //查询重复
     sql_query.prepare(select_same_pirture);
    if(!sql_query.exec())
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
    while(sql_query.next()){
        qDebug()<<"当前图片存在";
        return;}
    }
    //插入
    sql_query.prepare(insert_pirture);
    sql_query.addBindValue(max_id+1);
    sql_query.addBindValue(fileName);
    sql_query.addBindValue(nowTime);
    sql_query.addBindValue(pAderss);
    sql_query.addBindValue(0);
    sql_query.addBindValue(false);

    if(!sql_query.exec())
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
    qDebug()<<"inserted!";
    }




}
int SocketThread::login(QString name,QString password)
{
    QString m;
    QSqlQuery sQuery;
    sQuery.exec(tr("select password from sendAccount where username ='%1'").arg(name));
    while (sQuery.next()) {
       m = sQuery.value(0).toString();
    }
    if(m!=NULL){
        if(m==password)
        {
            return 2;
        }else{
            return 3;
        }
    }
    else
        {
            return 3;
        }
}
