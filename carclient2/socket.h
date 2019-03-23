#ifndef SOCKET_H
#define SOCKET_H
#include <QWidget>
#include <QDialog>
#include <QTcpSocket>
#include <QBuffer>
#include <QImage>
#include <QDir>
#include <QTime>
#include <QImageWriter>
#include <QTimer>
#include <QFileInfo>
class Socket:public QObject
{
     Q_OBJECT
public:
    static Socket* getSocket()
    {
         if(socketClient==NULL)
         {
            socketClient = new Socket;
         }
         return socketClient;
    }
    Socket();
    QTcpSocket * getTcpSocket();
    void setTcpSocket(QTcpSocket *tcp);

    void sendMessage(QString msg);
    void newConnect();
    void sendPicture(QString filePath,QString nowTime);
    QImage randomImage();

private:
    QTcpSocket *tcpSocket;
    static Socket *socketClient;
signals:
    void changeBar();
    void getLoginMsg();
private slots:
    void readMessage();
    void sendFileData();
public:
    QString message;
    quint16 bufSize;
    quint32 picSize;
    qint64  sendSize;//已经发送文件
    QFile file;
    qint64 fileSize;
    QString fileName;


};

#endif // SOCKET_H
