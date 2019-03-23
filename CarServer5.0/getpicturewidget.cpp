#include "getpicturewidget.h"
#include "ui_getpicturewidget.h"

GetPictureWidget::GetPictureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GetPictureWidget)
{
    ui->setupUi(this);
    if(!myServer.listen(QHostAddress::Any,1234))
      {
            qDebug()<<"服务器端没连接上";
            //QMessageBox::critical 提示对话框
            this->close();
            return;
      }
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updatePic()));
    timer->start(2000);
    flag=0;
}
void GetPictureWidget::updatePic()
{

    if(flag==0&&(!myServer.image.isNull()))
    {
      qDebug()<<myServer.image;
      ui->label->setPixmap(QPixmap::fromImage(myServer.image));
      ui->label->setText(tr("123"));
      ui->label->resize(QSize(myServer.image.width(),myServer.image.height()));
      ui->label->show();
      flag=1;
    }
}
GetPictureWidget::~GetPictureWidget()
{
    delete ui;
}
