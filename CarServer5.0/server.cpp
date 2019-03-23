#include "server.h"
#include <qDebug>
Server::Server(QObject *parent):QTcpServer(parent)
{

}
void Server::incomingConnection(int socketDescriptor)
{
    qDebug()<<"有新的连接";
    //QMessageBox::about(0,tr("提示"),tr("有新连接"));
    thread = new SocketThread(this,socketDescriptor);
    thread->start();
    connect(thread,SIGNAL(sendPicToMianWidget(QImage)),this,SLOT(changePic(QImage)));
    //emit server2widget(logtext);
}
void Server::changePic(QImage image)
{

   this->image=image;
   //qDebug()<<"logtext"<<logtext;
}
