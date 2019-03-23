#include "sendpicturewidget.h"
#include "ui_sendpicturewidget.h"
#include <QDebug>

sendPictureWidget::sendPictureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sendPictureWidget)
{
    ui->setupUi(this);
    //RoundRect();
    socketClient =Socket::getSocket();
    myHelper::SetStyle(this,"gray");
    beauty();
    myHeader = new CCheckBoxHeaderView(0, Qt::Horizontal, ui->tableWidget);
    myHeader->setDefaultAlignment(Qt::AlignCenter);
    ui->tableWidget->setHorizontalHeader(myHeader);
    connect(myHeader,SIGNAL(checkStausChange(bool)),this,SLOT(setCheck()));
    connect(socketClient,SIGNAL(changeBar()),this,SLOT(changeBar()));
    recFlag=1;
    nowRow=0;
    ui->progressBar->hide();
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//自适应



    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
}
sendPictureWidget::~sendPictureWidget()
{
    delete ui;
}
void sendPictureWidget::changeBar()
{
   sumsend++;
   recFlag=1;
   QWidget *widget = ui->tableWidget->cellWidget(nowRow,4);
   QProgressBar* progress = (QProgressBar*)widget;
   progress->setValue(10000);
   ui->tableWidget->item(nowRow,3)->setText(tr("已发送"));
   ui->tableWidget->item(nowRow,0)->setCheckState(Qt::Unchecked);
   ui->progressBar->setValue(sumsend);
   sendPic();
   if(sumsend==sum)
   {
   ui->progressBar->hide();
   nowRow=0;
   if(myHeader->isChecked == true)
   {
       myHeader->isChecked = false;
   }
   }
}
void sendPictureWidget::on_pushButton_clicked()
{

    //socketClient->newConnect();
    sum=0;
    sumsend=0;
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        if(ui->tableWidget->item(i,0)->checkState()==Qt::Checked)
            sum++;
    }
    ui->progressBar->setRange(0,sum);
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    sendPic();
}
void sendPictureWidget::sendPic()
{
    for(int i=nowRow;i<ui->tableWidget->rowCount();i++)
    {
        if(recFlag==1)
        if(ui->tableWidget->item(i,0)->checkState()==Qt::Checked)
        {
          nowRow =i;
          socketClient->sendPicture(ui->tableWidget->item(i,2)->text(),ui->tableWidget->item(i,1)->text());
          QWidget *widget = ui->tableWidget->cellWidget(i,4);
          QProgressBar* progress = (QProgressBar*)widget;
          for(int i=0;i<10000-1;i++)
              progress->setValue(i);

          recFlag=0;
        }

    }


}
void sendPictureWidget::setCheck()
{
  if(myHeader->isChecked)
  for(int i=0;i<ui->tableWidget->rowCount();i++)
  {
    ui->tableWidget->item(i,0)->setCheckState(Qt::Checked);
  }
  else{
      for(int i=0;i<ui->tableWidget->rowCount();i++)
      {
        ui->tableWidget->item(i,0)->setCheckState(Qt::Unchecked);
      }
  }
}
void sendPictureWidget::on_pushButton_2_clicked()
{
    QStringList filePathList =QFileDialog::getOpenFileNames(this,tr("选取图片"),".",
                                                    tr("Image files (*.png *.jpg *.bmp)"));
    if(filePathList.size()>0)
    {
    QDateTime time =QDateTime::currentDateTime();
    QString nowTime =time.toString("yyyy-MM-dd hh:mm:ss");


    ui->tableWidget->setRowCount(filePathList.size());
    for(int i=0;i<filePathList.size();i++)
    {
    QTableWidgetItem *check=new QTableWidgetItem;

    QProgressBar *pgbar = new QProgressBar(ui->tableWidget);
    pgbar->setTextVisible(false);

    ui->tableWidget->setCellWidget(i,4,pgbar);
    pgbar->setRange(0,10000);

    //pgbar->setStyleSheet("QProgressBar{border: 2px solid grey;border-radius: 5px;text-align: center;}");
    //pgbar->setStyleSheet("QProgressBar::chunk {background-color: #4D4D4D;width: 10px;margin: 1px;}");
    check->setCheckState (Qt::Unchecked);


    QTableWidgetItem *item1 = new QTableWidgetItem;
    QTableWidgetItem *item2 = new QTableWidgetItem;
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item1->setText(nowTime);
    item2->setText(filePathList.at(i));
    item3->setText(tr("未发送"));
//    if(i%2==0)
//    {
//    check->setBackgroundColor("#575757");
//    item1->setBackgroundColor("#575757");
//    item2->setBackgroundColor("#575757");
//    item3->setBackgroundColor("#575757");
//    }else{
//        check->setBackgroundColor("#808080");
//        item1->setBackgroundColor("#808080");
//        item2->setBackgroundColor("#808080");
//        item3->setBackgroundColor("#808080");
//    }
    ui->tableWidget->setItem(i,0,check); //插入复选框
    ui->tableWidget->setItem(i,1,item1);
    ui->tableWidget->setItem(i,2,item2);
    ui->tableWidget->setItem(i,3,item3);

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    }
  }else{
        qDebug()<<"图片打开无效";
    }

}
void sendPictureWidget::beauty(){
    //html5
//   QWebView *view = new QWebView(ui->widget_2);
//   view->load(QUrl::fromLocalFile("D:/FILE/QTcode/build-CarServer-Desktop_Qt_5_5_1_MinGW_32bit-Debug/resources/background/15/index.html"));
//   view->resize(ui->widget_2->width(),ui->widget_2->height());
//   view->move(0,0);
//   ui->widget->setParent(this);

  ui->tableWidget->setStyleSheet("background-color:rgba(0,0,0,0)"); //tablewidget 透明


  //无边框
  //去边框 设置最小化、关闭按钮
  //this->setAttribute(Qt::WA_TranslucentBackground,true);//将背景透明-windows下显示为黑色
  this->setWindowFlags(Qt::FramelessWindowHint);//去边框

  int width = this->width();//获取界面的宽度


   //构建最小化、最大化、关闭按钮
   QToolButton *minButton = new QToolButton(this);
   QToolButton *closeButton= new QToolButton(this);


//   //获取最小化、关闭按钮图标
//   QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
//   QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
     QPixmap closePix(":/image/close.png");
     QPixmap minPix(":/image/min.png");

   //设置最小化、关闭按钮图标
   minButton->setIcon(minPix.scaled(25 , 25));
   closeButton->setIcon(closePix.scaled(25 , 25));


   //设置最小化、关闭按钮在界面的位置

   minButton->setGeometry(width-50,5,25,25);
   closeButton->setGeometry(width-25,5,25,25);



   //设置鼠标移至按钮上的提示信息

   minButton->setToolTip(tr("最小化"));

   closeButton->setToolTip(tr("关闭"));


   //设置最小化、关闭按钮的样式
   minButton->setStyleSheet("background-color:transparent;");
   closeButton->setStyleSheet("background-color:transparent;");



   //设置按钮动作
  connect(closeButton,SIGNAL(clicked(bool)),this,SLOT(close()));
  connect(minButton,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
}
void sendPictureWidget::mouseMoveEvent(QMouseEvent *e){
    if(mousePressed && (e->buttons() && Qt::LeftButton)){
       this->move(e->globalPos() - mousePoint);
       e->accept();
       //globalPos是相对于屏幕的坐标 全局坐标
       //pos()是窗体左上角相对与屏幕的坐标
       //button()  返回产生事件的按钮
       //buttons()   返回产生事件的按钮状态
    }
}

void sendPictureWidget::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        mousePressed = true;
        mousePoint = e->globalPos()-this->pos();
        e->accept();
    }
}

void sendPictureWidget::mouseReleaseEvent(QMouseEvent *e){
    mousePressed = false;
    e->accept();
}
void sendPictureWidget::RoundRect()
{

        QBitmap bmp(this->size());
        bmp.fill(this,0,0);
        QPainter p(&bmp);
            p.setPen(Qt::NoPen);
            p.setBrush(Qt::black);
            p.setRenderHint(QPainter::Antialiasing);
            p.drawRoundedRect(bmp.rect(),20,20,Qt::AbsoluteSize);
            setMask(bmp);

}

void sendPictureWidget::on_pushButton_3_clicked()
{
    if(ui->tableWidget->rowCount()>0)
    {
       QString sXlsFile =QFileDialog::getSaveFileName(this, tr("Save as..."),
                    QString(), tr("EXCEL files (*.xls *.xlsx);;HTML-Files (*.txt);;"));
            Table2Excel excel(sXlsFile);
            excel.Open();
            excel.SaveDataFrTable(ui->tableWidget); //导出报表
            excel.Close();
    }
}
