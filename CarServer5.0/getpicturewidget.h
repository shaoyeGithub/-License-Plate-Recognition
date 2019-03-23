#ifndef GETPICTUREWIDGET_H
#define GETPICTUREWIDGET_H
#include "server.h"
#include <QWidget>
#include <QTimer>
namespace Ui {
class GetPictureWidget;
}

class GetPictureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GetPictureWidget(QWidget *parent = 0);
    ~GetPictureWidget();
private slots:
    void updatePic();
private:
    Ui::GetPictureWidget *ui;
    Server myServer;
    QTimer *timer;
    int flag;
};

#endif // GETPICTUREWIDGET_H
