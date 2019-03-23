#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QWidget>
#include "socketthread.h"
#include <QImage>
class Server :public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent =0);
    SocketThread *thread;
    QString logtext;
    QImage image;
private slots:
    void changePic(QImage);
//signals:
//    void server2widget(QString val);
protected:
    void incomingConnection(int socketDescriptor);

};
#endif // SERVER_H
