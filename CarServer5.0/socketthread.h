#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H
#include<QWidget>
#include <QTcpSocket>
#include<QThread>
#include <QDataStream>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDateTime>
#include <QBuffer>
#include <QImageReader>
#include <QFile>
class SocketThread : public QThread
{    
    Q_OBJECT
public:
    SocketThread(QObject *parent ,int socketDescriptor);
    void run();
    void saveFileInDb(QString fileName,QString nowTime );
    int login(QString,QString);
private:
    int socketDescriptor;
    QString getMsg;
    QByteArray buf;
    QString send;//用于sendMsg
    QString sendMsg;
    QTcpSocket *tcpSocket;
    qint16 blockSize;
    QSqlTableModel *model ;
    QSqlQuery query;

    qint32 PicSize;

    qint64  recSize;//已经发送文件
    QFile file;
    qint64 fileSize;
    QString fileName;
    QString nowTime;
    QString pAderss;
    QString name;
    bool isStart;
signals:
    void sendPicToMianWidget(QImage image);//发送图片到主页面
private slots:
   void readMessage();
   void sendMessage();
   void readPicture();\
   void readAll();
};

#endif // SOCKETTHREAD_H
