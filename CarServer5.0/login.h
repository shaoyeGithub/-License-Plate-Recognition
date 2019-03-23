#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QMovie>
#include <QVBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QTcpSocket>


#include "widget.h"

#include<QFile>
#include<QTextStream>
#include<QString>
#include<QSettings>

#include <QPainter>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    static int privilege ;
    static QString userName;
    void RemUserName();
protected:

    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void  mouseReleaseEvent(QMouseEvent *);
private slots://私有槽函数

    void on_checkBox_clicked();

    void on_accountComboBox_currentIndexChanged(const QString &arg1);

    void on_accountComboBox_editTextChanged(const QString &arg1);

    void on_minWindow();

    void on_loginButton_clicked();


private:
    Ui::Dialog *ui;
    QSqlQuery sQuery;
    QMovie * movie;
    QPoint mousePoint;//鼠标拖动时的坐标
    bool mousePressed;//是否按下
    int userNum;
    QString name;
    QString password;
    int remember = 0 ;

};

#endif // DIALOG_H
