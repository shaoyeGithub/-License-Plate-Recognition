#ifndef SENDPICTUREWIDGET_H
#define SENDPICTUREWIDGET_H

#include <QWidget>
#include "socket.h"
#include <QFileDialog>
#include <QDateTime>
#include "ccheckboxheaderview.h"
#include "myhelper.h"
#include <QWebView>
#include <QToolButton>
#include <QPoint>
#include <QFileDialog>
#include "table2excel.h"
namespace Ui {
class sendPictureWidget;
}

class sendPictureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit sendPictureWidget(QWidget *parent = 0);
    ~sendPictureWidget();
    void sendPic();
    void beauty();
    void mouseMoveEvent(QMouseEvent *);//移动
    void mousePressEvent(QMouseEvent *);//按下
    void mouseReleaseEvent(QMouseEvent *);//释放
    void RoundRect();
private slots:
    void on_pushButton_clicked();
    void setCheck();
    void on_pushButton_2_clicked();
    void changeBar();
    void on_pushButton_3_clicked();

private:
    Ui::sendPictureWidget *ui;
    Socket  *socketClient;
    CCheckBoxHeaderView *myHeader;
    int recFlag;//接受发送返回信息
    int sum;//check 的图片数量
    int sumsend;//已经发送的图片数量
    int nowRow; // 当前发送行


    QPoint mousePoint;//鼠标拖动时的坐标
    bool mousePressed;//是否按下
};

#endif // SENDPICTUREWIDGET_H
