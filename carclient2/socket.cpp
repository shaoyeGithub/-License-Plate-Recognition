#include "socket.h"
#include <qDebug>

Socket* Socket::socketClient = NULL;
Socket::Socket()
{
   tcpSocket =new QTcpSocket();

   connect(this->tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
}
void Socket::readMessage()
{
       bufSize=0;
       QDataStream in(this->tcpSocket);
        // 设置数据流版本，这里要和服务器端相同
        in.setVersion(QDataStream::Qt_5_5);
       // 如果是刚开始接收数据
        if (bufSize == 0) {
            //判断接收的数据是否大于两字节，也就是文件的大小信息所占的空间
            //如果是则保存到blockSize变量中，否则直接返回，继续接收数据
            if(this->tcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;  //bytesAvailable()返回字节数
            in >> bufSize;
        }
        // 如果没有得到全部的数据，则返回，继续接收数据
        if(this->tcpSocket->bytesAvailable() < bufSize) return;
        // 将接收到的数据存放到变量中
        in >> message;
        if(message =="1")
        {
            emit changeBar();
        }else if(message == "file")
        {
           sendFileData();
        }
        else if(message == "2"||message == "3")
        {
            emit getLoginMsg();
        }
        qDebug()<<"客户端接受到信息："<<message;
        // 显示接收到的数据*/

}
void Socket::sendPicture(QString filePath,QString nowTime)
{

    QFileInfo info(filePath);
    fileName = info.fileName();//获取文件名字
    fileSize = info.size(); // 获取文件大小

    sendSize=0;// 发送文件大小

    file.setFileName(filePath);

    //打开文件
    bool isOk=file.open(QIODevice::ReadOnly);
    if(false ==isOk)
    {
       qDebug()<<"只读方式打开失败";
    }
    //发送头部信息 文件名##文件大小
    QString head =QString("%1##%2##%3").arg(fileName).arg(fileSize).arg(nowTime);

    qint64 len = tcpSocket->write(head.toUtf8());//发送头部信息
    if(len > 0)//头部信息发送成功
    {
        //发送真正的文件信息
        //防止TCP粘包文件
        // 需要定时器延时20ms
        qDebug()<<"头部信息发送成功";
    }else
    {
        qDebug()<<"头部信息发送失败";
        file.close();
    }

}
void Socket::sendFileData()
{

    qint64 len = 0;
    do{
        //每次发送数据的大小
     char buf[4*1024]={0};
     len = 0;

     //往文件中读数据
     len = file.read(buf,sizeof(buf));

     //发送数据，读取多少，发送多少
     len = tcpSocket->write(buf,len);
     // 发送数据需要累加
     sendSize +=len;
    }while(len > 0);

    //是否发送文件完毕
    if(sendSize == fileSize)
    {
        file.close();
        qDebug()<<"文件发送完成:"<<fileName;
//        tcpSocket->disconnectFromHost();
//        tcpSocket->close();
    }

}
void Socket::sendMessage(QString msg)
{
//    //数据包 ：数据的大小信息+实际数据
//    QByteArray buf;
//    //用于读写二进制数据  优点：严格定义数据流的类型和每个类型的长度
//    // 不用关心编码之间的转换问题
//    QDataStream out (&buf,QIODevice::WriteOnly);

//    out.setVersion(QDataStream::Qt_5_5);

//    out << (quint16)0;//quint16 的大小 （两字节） 用于存放数据大小信息的

//    out <<msg;

//    out.device()->seek(0);//返回起始位置

//    out << (quint16)(buf.size() - sizeof(quint16));

//    //获取已经建立的套接字
//    this->tcpSocket->write(buf);
    QString head =msg;

    qint64 len = tcpSocket->write(head.toUtf8());//发送头部信息
    qDebug()<<"客户端发送了信息："<<msg;
}
void Socket::newConnect()
{
    bufSize = 0;
    this->tcpSocket->abort();//取消已有连接
    //stcpSocket->connectToHost("10.25.49.107",1234);
    this->tcpSocket->connectToHost("127.0.0.1", 1234);
    qDebug()<<"客户端建立了连接";
}
QTcpSocket * Socket::getTcpSocket()
{
    return this->tcpSocket;
}
void Socket::setTcpSocket(QTcpSocket *tcp)
{
   this->tcpSocket=tcp;
}
QImage Socket::randomImage()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QDir dir(":/image");
    dir.setFilter( QDir::Files );
    QFileInfoList entries = dir.entryInfoList();

    if ( entries.size() == 0 )
    {
        qDebug( "No images to show!" );
        return QImage();
    }

    return QImage( entries.at( qrand() % entries.size() ).absoluteFilePath() );
}
