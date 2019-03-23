#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"query.h"
#include "distinguish.h"
#include "server.h"
#include <QWidget>
#include <QTimer>
#include <QTableWidgetItem>
#include <ccheckboxheaderview.h>
#include  "db.h"
#include  <QTableWidget>
#include "myhelper.h"
#include <QToolButton>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QDesktopWidget>
#include <QRect>
#include "cv.h"
#include "include//easypr.h"
#include "string.h"
#include <QSqlTableModel>
#include <QString>
#include <QList>
#include <QFile>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QLabel>
#include <QTextCodec>
#include <QtCore/QCoreApplication>

using namespace cv;
using namespace std;
using namespace easypr ;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
     string plateRec(QString);
private slots:

    void getSelectedRow();
    void getSelectedItem(int row,int column);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


   void on_comboBox_activated(int index);
   void setCheck();
   void on_pushButton_5_clicked();

   void on_pushButton_4_clicked();
   //-----------------
   void setView();
 //  void opreationJournal(QString Message);
   void showMessage(char *msg);
   void iconActivated(QSystemTrayIcon::ActivationReason reason);
   void createActions();
   void createTrayIcon();
   void on_return_2_clicked();

   void on_enterRecognition_clicked();



   void on_comboBox_2_activated(int index);


   void on_querry_clicked();

   void on_pushButton_clicked();

   void on_pushButton_6_clicked();

   void on_comboBox_3_activated(int index);

   void on_DBaddData_clicked();

   void on_DBmodifyData_clicked();

   void on_DBdeleteData_clicked();

   void on_DBexportData_clicked();

   void on_DBselectFile_clicked();

   void on_DBimportData_clicked();

   void on_DBclearData_clicked();

protected:
   void mouseMoveEvent(QMouseEvent *);//移动
   void mousePressEvent(QMouseEvent *);//按下
   void mouseReleaseEvent(QMouseEvent *);//释放

private:
    Ui::Widget *ui;
    query q;
    distinguish *d;
    quint16 portNumber;
    QMenu *trayIconMenu;
    Server myServer;
    QTimer *timer;
    int flag;
    QSystemTrayIcon *trayIcon;
    CCheckBoxHeaderView *myHeader;
    QTableWidgetItem *itemX ;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QPoint mousePoint;//鼠标拖动时的坐标
    bool mousePressed;//是否按下
    int flagPage;//页面标志 1 主页面  2  修改页面   3查询页面 页面4 数据库管理
    void  showQTableWidget();//页面2 显示
    bool selectROW; //页面2  是否选取行
    int   flagIndex;//页面3  查询类型
    void hidePage4();
    void showPage4();
 //页面4--------------------------------------------------------------------------
private:
    QSqlTableModel *model;

    int   flagIndex4;//页面 4查询类型

    QString curFile;

    QString insert_carOwner="insert into carOwner values (?,?,?,?,?)";
    QString insert_car="insert into car values (?,?,?,?)";
    QString insert_pirture="insert into pirture values (?,?,?,?,?,?)";
    QString insert_sendAccount="insert into sendAccount values (?,?,?)";
    QString insert_receiveAccount="insert into receiveAccount values (?,?,?)";

    QString clear_carOwner = "delete from carOwner";
    QString clear_car = "delete from car";
    QString clear_pirture = "delete from pirture";
    QString clear_sendAccount = "delete from sendAccount";
    QString clear_receiveAccount = "delete from receiveAccount";
};

#endif // WIDGET_H
