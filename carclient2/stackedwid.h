#ifndef STACKEDWID_H
#define STACKEDWID_H

#include <QWidget>
#include "login.h"
namespace Ui {
class StackedWid;
}

class StackedWid : public QWidget
{
    Q_OBJECT

public:
    explicit StackedWid(QWidget *parent = 0);
    ~StackedWid();
     void showSend();
     Dialog* login;//登录界面;
     // 网络设置界面;

     // 初始化旋转的窗口;
     void initRotateWindow();
private:
    Ui::StackedWid *ui;
};

#endif // STACKEDWID_H
