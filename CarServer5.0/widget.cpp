#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets/QWidget>
#include <QWidget>
#include <QPalette>
#include<QPixmap>
#include<QWebView>
#include<QFile>
#include<QPushButton>
#include <QGridLayout>
#include<QLineEdit>
#include <QFileInfo>


#include<QByteArray>
#include<QCryptographicHash>
#include<QString>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //----
   // QWidget *w = new QWidget(this);
    QWebView *view = new QWebView(ui->widget3);



    //this->setParent(view);
    view->load(QUrl::fromLocalFile("D:/FILE/QTcode/build-CarServer-Desktop_Qt_5_5_1_MinGW_32bit-Debug/resources/background/index.html"));
    //view->load(QUrl::fromLocalFile("./resources/background/index.html"));
 //  view->resize(ui->widget3->width(),ui->widget3->height());
    view->resize(this->width(),this->height());
    view->move(0,0);

    ui->widget2->setParent(this);
   //ui->widget2->setParent(ui->widget3);


 // w->show();

  // ui->tableWidget->setParent(view);
   //ui->pushButton->setParent(view);
    //----

    setView(); //设置托盘
    getSelectedRow();//获取行 初始化信号

    myHelper::SetStyle(this,"gray");//按钮样式

    //Widget->setAutoFillBackground(true);
//    QPalette palette;
//    QPixmap pixmap("./1.jpg"); //显示背景
//    palette.setBrush(QPalette::Window, QBrush(pixmap));
//    this->setPalette(palette);
    ui->tableWidget->setStyleSheet("background-color:rgba(0,0,0,0)"); //tablewidget 透明
    ui->tableView->setStyleSheet("background-color:rgba(0,0,0,0)"); //tablewidget 透明
    ui->tableWidget->verticalHeader()->hide(); //隐藏航标题
  //ui->tableWidget->horizontalHeader()->hide(); //隐藏列标题
  //----隐藏页面-----------------------------------------------------
    //页面2
    ui->enterRecognition->hide();
    ui->return_2->hide();
    ui->lineEdit_8->hide();

    flagPage=1;
    selectROW=false;
    //页面3
    ui->comboBox_2->hide();
    ui->dateTimeEdit->hide();
    ui->dateTimeEdit_2->hide();
    ui->lineEdit_9->hide();
    ui->querry->hide();
   //页面4
     hidePage4();
  //初始化图片---------------------------------------------------------
    ui->label_8->setPixmap(QPixmap(tr("./2.jpg")).scaled(477,250));

 //初始化服务器端口---------------------------------------------
    portNumber=1234;

    if(!myServer.listen(QHostAddress::Any,portNumber))
      {
            qDebug()<<"服务器端没连接上";
            //QMessageBox::critical 提示对话框
            this->close();
            return;
      }else{
     ui->lineEdit_7->setText(tr("服务器端口:%1").arg(portNumber));
    }
  //---------------------------------------------------------------


}



Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_6_clicked()  //页面4 数据库管理
{
    //隐藏页面1----------------------------
        ui->lineEdit->hide();
        ui->lineEdit_2->hide();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();

         ui->label->hide();
         ui->label_2->hide();
         ui->label_3->hide();
         ui->label_4->hide();
         ui->label_5->hide();

        ui->pushButton->hide();
        ui->comboBox->hide();
        ui->return_2->show();
        ui->label_8->hide();//图片
        ui->tableWidget->hide();
     //隐藏页面2-----------------
            ui->enterRecognition->hide();
            //ui->return_2->hide();
            ui->lineEdit_8->hide();
     //隐藏页面3-----------------------
               ui->comboBox_2->hide();
               ui->dateTimeEdit->hide();
               ui->dateTimeEdit_2->hide();
               ui->lineEdit_9->hide();
               ui->querry->hide();

      //显示页面4
      showPage4();
    //modle-------------------------------------------
        model =new QSqlTableModel(this);
        ui->progressBar->setValue(0);
}

void Widget::on_pushButton_2_clicked()//页面 3 查询信息
{
    //q.show();

    //隐藏页面1----------------------------
        ui->lineEdit->hide();
        ui->lineEdit_2->hide();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();

         ui->label->hide();
         ui->label_2->hide();
         ui->label_3->hide();
         ui->label_4->hide();
         ui->label_5->hide();

         ui->pushButton->hide();
         ui->comboBox->hide();

         ui->label_8->hide();
     //隐藏页面2-----------------
         ui->enterRecognition->hide();
         ui->return_2->hide();
         ui->lineEdit_8->hide();
     //隐藏页面4
           hidePage4();

     //---------------------------------

         //显示页面3
         ui->comboBox_2->show();
         ui->dateTimeEdit->show();
         ui->dateTimeEdit_2->show();
         ui->lineEdit_9->show();
         ui->querry->show();
         ui->return_2->show();
         //初始化
         flagPage=3;

         flagIndex=0;//初始化查询类型
         ui->tableWidget->show();
         ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
         ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//自适应
         ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//等宽
         ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
         ui->tableWidget->clear();
         ui->tableWidget->horizontalHeader()->hide(); //隐藏列标题

}

void Widget::on_pushButton_3_clicked()//页面 2 人工复查
{
//    d = new distinguish();

//    d->show();
//    d->showQTableWidget();


//隐藏页面1----------------------------
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();

     ui->label->hide();
     ui->label_2->hide();
     ui->label_3->hide();
     ui->label_4->hide();
     ui->label_5->hide();

    ui->pushButton->hide();
    ui->comboBox->hide();
 //隐藏页面3-----------------------
    ui->comboBox_2->hide();
    ui->dateTimeEdit->hide();
    ui->dateTimeEdit_2->hide();
    ui->lineEdit_9->hide();
    ui->querry->hide();
  //隐藏页面4
          hidePage4();

 //显示页面2---------------------------------
    ui->label_8->show();
     ui->tableWidget->show();
    ui->enterRecognition->show();
    ui->return_2->show();
    ui->lineEdit_8->show();
    ui->label_8->setPixmap(QPixmap(tr("./2.jpg")).scaled(477,320));
    flagPage=2;
    showQTableWidget();
    selectROW=false;

}

void Widget::on_return_2_clicked() //返回页面 1
{
    //隐藏页面2
    ui->enterRecognition->hide();
    ui->return_2->hide();
    ui->lineEdit_8->hide();
    ui->label_8->setPixmap(QPixmap(tr("./2.jpg")).scaled(477,250));

    //隐藏页面3
    ui->comboBox_2->hide();
    ui->dateTimeEdit->hide();
    ui->dateTimeEdit_2->hide();
    ui->lineEdit_9->hide();
    ui->querry->hide();
    //隐藏页面4
            hidePage4();
  //显示页面1------------------------------------
    ui->lineEdit->show();
      ui->tableWidget->show();
    ui->lineEdit_2->show();
    ui->lineEdit_3->show();
    ui->lineEdit_4->show();
    ui->lineEdit_5->show();

     ui->label->show();
     ui->label_2->show();
     ui->label_3->show();
     ui->label_4->show();
     ui->label_5->show();

     ui->pushButton->show();
     ui->comboBox->show();
     ui->label_8->show();
     on_comboBox_activated(0);// 页面1 显示未处理图片
     flagPage=1;
}

void Widget::on_enterRecognition_clicked() // 页面 2 确认复查
{
    if(!selectROW){
        QMessageBox::about(NULL, "复查", "请先选一行");
        return;
    }
    int row =itemX->row();
    QString getLineEdit =ui->lineEdit_8->text();
    QString pPath= ui->tableWidget->item(row,0)->text();
    QSqlQuery sql_query;
    QString update_pirture = tr("UPDATE pirture SET carNumber = '%1' ,flag =1  WHERE pPath ='%2' ")
            .arg(getLineEdit).arg(pPath);
    qDebug()<<"update_pirture"<<update_pirture;

    sql_query.prepare(update_pirture);

    if(!sql_query.exec())
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
    qDebug()<<"updated!";
    }


    qDebug()<<"itemX->row()"<<row;
    ui->tableWidget->item(row,1)->setText(getLineEdit);
    ui->tableWidget->item(row,4)->setText("已复查");
}
void Widget::on_comboBox_activated(int index)  //页面1 combox 选择 已处理 未处理
{
    //qDebug()<<index;

   ui->tableWidget->setRowCount(0);

   ui->tableWidget->setColumnCount(5);
   ui->tableWidget->horizontalHeader()->show();
   QStringList header;
   header<<tr(" ")<<tr("ID")<<tr("图像")<<tr("车牌")<<tr("违章时间--地点");
   ui->tableWidget->setHorizontalHeaderLabels(header);

    if(index==0)
    {
        QSqlQuery sql_query;
        QString select_sql = "select pId,pPath,carNumber,time,pAdress from pirture where flag = 0";
        if(!sql_query.exec(select_sql))
        {
        qDebug()<<sql_query.lastError();
        }
        else
        {
            int i=1;

        while(sql_query.next())
        {
           ui->tableWidget->setRowCount(i++);
        int pId = sql_query.value("pId").toInt();
        QString pPath = sql_query.value("pPath").toString();
        QString carNumber=sql_query.value("carNumber").toString();
        QString pTime=sql_query.value("time").toString();
        QString pAdress=sql_query.value("pAdress").toString();
        //qDebug()<<QString("pId:%1    pPath:%2").arg(pId).arg(pPath);

         QTableWidgetItem *item0= new QTableWidgetItem;
         QTableWidgetItem *item1= new QTableWidgetItem;
         QTableWidgetItem *item2= new QTableWidgetItem;
         QTableWidgetItem *item3= new QTableWidgetItem;

         QLabel *label = new QLabel("");
         label->setPixmap(QPixmap(QObject::tr("./temp/%1").arg(pPath)).scaled(60,30));

         QTableWidgetItem *check=new QTableWidgetItem;
         check->setCheckState (Qt::Unchecked);

//        if(((i-1)%2)!=0){
//           //  check->setBackgroundColor("#BFEFFF");
//            // item0->setBackgroundColor("#BFEFFF");
//            // item1->setBackgroundColor("#BFEFFF");
//             //item2->setBackgroundColor("#BFEFFF");
//             //item3->setBackgroundColor("#BFEFFF");
//            // item0->setBackground();
//        }else{
//            check->setBackgroundColor("#EAEAEA");
//            item0->setBackgroundColor("#EAEAEA");
//            item1->setBackgroundColor("#EAEAEA");
//            item2->setBackgroundColor("#EAEAEA");
//            item3->setBackgroundColor("#EAEAEA");
//        }


         item0->setText(QString::number(pId));
         item1->setIcon(QIcon(QObject::tr("./temp/%1").arg(pPath)));
      // item1->setText(pPath);
         item2->setText(carNumber);
         item3->setText(pTime+" "+pAdress);
            ui->tableWidget->setItem(i-2,0,check); //插入复选框
            ui->tableWidget->setItem(i-2,1,item0);
            ui->tableWidget->setCellWidget(i-2,2,label);
            ui->tableWidget->setItem(i-2,3,item2);
            ui->tableWidget->setItem(i-2,4,item3);

        }
        }

    }
    if(index==1)
    {
        QSqlQuery sql_query;
        QString select_sql = "select pId,pPath,carNumber,time,pAdress from pirture where flag = 1";
        if(!sql_query.exec(select_sql))
        {
        qDebug()<<sql_query.lastError();
        }
        else
        {
            int i=1;

        while(sql_query.next())
        {
           ui->tableWidget->setRowCount(i++);
        int pId = sql_query.value("pId").toInt();
        QString pPath = sql_query.value("pPath").toString();
        QString carNumber=sql_query.value("carNumber").toString();
        QString pTime=sql_query.value("time").toString();
        QString pAdress=sql_query.value("pAdress").toString();
        //qDebug()<<QString("pId:%1    pPath:%2").arg(pId).arg(pPath);

         QTableWidgetItem *item0= new QTableWidgetItem;
         QTableWidgetItem *item1= new QTableWidgetItem;
         QTableWidgetItem *item2= new QTableWidgetItem;
         QTableWidgetItem *item3= new QTableWidgetItem;

         QLabel *label = new QLabel("");
         label->setPixmap(QPixmap(QObject::tr("./temp/%1").arg(pPath)).scaled(60,30));

         QTableWidgetItem *check=new QTableWidgetItem;
         check->setCheckState (Qt::Unchecked);

//        if(((i-1)%2)!=0){
//           //  check->setBackgroundColor("#BFEFFF");
//           // item0->setBackgroundColor("#BFEFFF");
//           // item1->setBackgroundColor("#BFEFFF");
//           //item2->setBackgroundColor("#BFEFFF");
//           //item3->setBackgroundColor("#BFEFFF");
//           // item0->setBackground();
//        }else{
//            check->setBackgroundColor("#EAEAEA");
//            item0->setBackgroundColor("#EAEAEA");
//            item1->setBackgroundColor("#EAEAEA");
//            item2->setBackgroundColor("#EAEAEA");
//            item3->setBackgroundColor("#EAEAEA");
//        }


         item0->setText(QString::number(pId));
         item1->setIcon(QIcon(QObject::tr("./temp/%1").arg(pPath)));
      // item1->setText(pPath);
         item2->setText(carNumber);
         item3->setText(pTime+" "+pAdress);
            ui->tableWidget->setItem(i-2,0,check); //插入复选框
            ui->tableWidget->setItem(i-2,1,item0);
            ui->tableWidget->setCellWidget(i-2,2,label);
            ui->tableWidget->setItem(i-2,3,item2);
            ui->tableWidget->setItem(i-2,4,item3);

        }
        }
    }
    //将行和列的大小设为与内容相匹配
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    itemX = new QTableWidgetItem;
}

void Widget::getSelectedRow() //选择行初始化
{
    itemX = new QTableWidgetItem;
    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
//   ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//自适应
//   ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//等宽


    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(getSelectedItem(int,int)));//连接单击与曹

    myHeader = new CCheckBoxHeaderView(0, Qt::Horizontal, ui->tableWidget);
    ui->tableWidget->setHorizontalHeader(myHeader);
    connect(myHeader,SIGNAL(checkStausChange(bool)),this,SLOT(setCheck()));

    on_comboBox_activated(0);
}
void Widget::setCheck() //多选函数
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
void Widget::getSelectedItem(int row, int column) //获取行槽函数
{
    itemX = ui->tableWidget->item(row,column);

if(flagPage==1){

    QString pId=ui->tableWidget->item(row,1)->text();//获取违章图片ID
    QSqlQuery sql_query;
    QString   select_pirture = tr("select pId,pPath,carNumber,time,pAdress from pirture where pId = '%1'").arg(pId);


    if(!sql_query.exec(select_pirture))
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
       //查询车牌号--------------------------------------------
         while(sql_query.next()){
         QString carNumber=sql_query.value("carNumber").toString();
         QString pPath=sql_query.value("pPath").toString();
         QString pTime=sql_query.value("time").toString();
         QString pAdress=sql_query.value("pAdress").toString();
         ui->lineEdit->setText(carNumber);
         ui->lineEdit_4->setText("地点: "+pAdress+"  时间:"+pTime);
         ui->label_8->setPixmap(QPixmap(tr("./temp/%1").arg(pPath)).scaled(477,250));
       //根据车牌号查询车主-----------------------------------------
         QString   select_car = tr("select carOwnId,carOwnName,carType from car where carNumber = '%1'").arg(carNumber);
         if(!sql_query.exec(select_car))
         {
         qDebug()<<sql_query.lastError();
         }
         else
         {
              while(sql_query.next()){
                  QString carOwnId=sql_query.value("carOwnId").toString();
                  QString carOwnName=sql_query.value("carOwnName").toString();
                  QString carType=sql_query.value("carType").toString();
                  ui->lineEdit_2->setText(carOwnName);
                  ui->lineEdit_3->setText(carOwnId);
                  ui->lineEdit_5->setText(carType);

              }
         }
        }

    }
}else if(flagPage==2){
    itemX=ui->tableWidget->item(row,0);
    if(row!=0){
        QString pPath= itemX->text();
        qDebug()<<"row  pPath"<<row<<pPath;
        ui->label_8->setPixmap(QPixmap(tr("./temp/%1").arg(pPath)).scaled(477,320));
        ui->lineEdit_8->setText(ui->tableWidget->item(row,1)->text());
        selectROW=true;

    }else{

        ui->label_8->setPixmap(QPixmap(tr("./2.jpg")).scaled(477,320));
        selectROW=false;
    }

    }

}

void Widget::on_pushButton_5_clicked() //关闭服务
{
        myServer.close();
        ui->lineEdit_7->setText("服务器已关闭");
}

void Widget::on_pushButton_4_clicked() //开启服务
{
     myServer.close();
    if(ui->lineEdit_6->text().isEmpty()){
         portNumber=1234;
    }else{
        portNumber=ui->lineEdit_6->text().toInt();
    }
    if(!myServer.listen(QHostAddress::Any,portNumber))
      {
            qDebug()<<"服务器端没连接上";
            //QMessageBox::critical 提示对话框
            this->close();
            return;
      }else{
     ui->lineEdit_7->setText(tr("服务器端口:%1").arg(portNumber));
    }
}

void Widget::showQTableWidget() //页面 2显示 TableWidget
{

    int row=1;
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->clear();
    ui->tableWidget->horizontalHeader()->hide();
    QSqlQuery sql_query;
    QString select_sql = "select pId,pPath,carNumber,time,pAdress from pirture where flag =0";

    ui->tableWidget->setColumnCount(5);
    QStringList header;
    header<<tr("图像")<<tr("车牌")<<tr(" 违章时间")<<tr("地点")<<tr("人工复查");
    ui->tableWidget->setHorizontalHeaderLabels(header);//设置标题

    for(int i=0;i<5;i++){
      QTableWidgetItem *itemH= new QTableWidgetItem;
      itemH->setText(ui->tableWidget->horizontalHeaderItem(i)->text());
      ui->tableWidget->setItem(0,i,itemH);
    }

//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//自适应
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//等宽

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽

    if(!sql_query.exec(select_sql))
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {


    while(sql_query.next())
    {
    ui->tableWidget->setRowCount(++row);
    int pId = sql_query.value("pId").toInt();
    QString pPath = sql_query.value("pPath").toString();
    QString carNumber=sql_query.value("carNumber").toString();
    QString pTime=sql_query.value("time").toString();
    QString pAdress=sql_query.value("pAdress").toString();
    //qDebug()<<QString("pId:%1    pPath:%2").arg(pId).arg(pPath);

     QTableWidgetItem *item0= new QTableWidgetItem;
     QTableWidgetItem *item1= new QTableWidgetItem;
     QTableWidgetItem *item2= new QTableWidgetItem;
     QTableWidgetItem *item3= new QTableWidgetItem;
     QTableWidgetItem *item4= new QTableWidgetItem;




        item0->setText(pPath);
        item1->setText(carNumber);
        item2->setText(pTime);
        item3->setText(pAdress);
        item4->setText("未复查");
        ui->tableWidget->setItem(row-1,0,item0);
        ui->tableWidget->setItem(row-1,1,item1);
        ui->tableWidget->setItem(row-1,2,item2);
        ui->tableWidget->setItem(row-1,3,item3);
        ui->tableWidget->setItem(row-1,4,item4);

    }
    }

     selectROW=false;
}

void Widget::on_comboBox_2_activated(int index) //页面 3 查询类型
{
         flagIndex=index;
}


void Widget::on_querry_clicked()//页面3  插叙按钮
{
    int row =1;
    ui->tableWidget->setRowCount(row);

    QString getLineEdit=ui->lineEdit_9->text();
    QSqlQuery sql_query;
    QSqlQuery sql_query2;
    QString select_sql;
    QString time1=ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString time2=ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    //设置标题------------------------------------
    ui->tableWidget->setColumnCount(7);
    QStringList header;
    header<<tr("违章号")<<tr("身份证")<<tr("姓名")<<tr("车牌")<<tr("车型 ")<<tr(" 违章时间")<<tr("地点");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    for(int i=0;i<7;i++){
      QTableWidgetItem *itemH= new QTableWidgetItem;
      itemH->setText(ui->tableWidget->horizontalHeaderItem(i)->text());
      ui->tableWidget->setItem(0,i,itemH);
    }



    if(flagIndex==0)//按姓名查询
    {

    //    QString create_sql2 =  " create table car(carNumber varchar(10) primary key,carOwnId varchar(30),carOwnName varchar(30),carType varchar(30))";
    //    QString create_sql3 =  " create table pirture(pId int(10) primary key,pPath varchar(30),time datatime,pAdress varchar(30),carNumber varchar(10),flag bool)";

        select_sql = tr("select carNumber,carOwnId,carOwnName,carType from car where carOwnName  = '%1'").arg(getLineEdit);



    }else if(flagIndex==1){//按身份证查询
        select_sql = tr("select carNumber,carOwnId,carOwnName,carType from car where carOwnId  = '%1'").arg(getLineEdit);
    }else if(flagIndex==2){//按车牌号查询
         select_sql = tr("select carNumber,carOwnId,carOwnName,carType from car where carNumber  = '%1'").arg(getLineEdit);
    }

    if(getLineEdit.isEmpty()){
        select_sql = tr("select carNumber,carOwnId,carOwnName,carType from car ");
    }


    if(!sql_query.exec(select_sql))
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
       //查询车--------------------------------------------
         while(sql_query.next())
         {
             QString carNumber=sql_query.value("carNumber").toString();
             QString carOwnId=sql_query.value("carOwnId").toString();
             QString carOwnName=sql_query.value("carOwnName").toString();
             QString carType=sql_query.value("carType").toString();
             //查询违章信息----------------------------------
             QString select_pirture = tr("select pId,pPath,carNumber,time,pAdress from pirture where carNumber = '%1' and time >= '%2' and time <= '%3'")
                     .arg(carNumber).arg(time1).arg(time2);

             if(!sql_query2.exec(select_pirture))
             {
             qDebug()<<sql_query2.lastError();
             }
             else
             {
                 while(sql_query2.next()){
                     QString pId=sql_query2.value("pId").toString();
                     QString pTime=sql_query2.value("time").toString();
                     QString pAdress=sql_query2.value("pAdress").toString();
                     ui->tableWidget->setRowCount(++row);

                     //违章号  身份证 姓名 车牌 车型  违章时间 地点
                     QTableWidgetItem *item0= new QTableWidgetItem;
                     QTableWidgetItem *item1= new QTableWidgetItem;
                     QTableWidgetItem *item2= new QTableWidgetItem;
                     QTableWidgetItem *item3= new QTableWidgetItem;
                     QTableWidgetItem *item4= new QTableWidgetItem;
                     QTableWidgetItem *item5= new QTableWidgetItem;
                     QTableWidgetItem *item6= new QTableWidgetItem;


                     item0->setText(pId);
                     item1->setText(carOwnId);
                     item2->setText(carOwnName);
                     item3->setText(carNumber);
                     item4->setText(carType);
                     item5->setText(pTime);
                     item6->setText(pAdress);
                        ui->tableWidget->setItem(row-1,0,item0);
                        ui->tableWidget->setItem(row-1,1,item1);
                        ui->tableWidget->setItem(row-1,2,item2);
                        ui->tableWidget->setItem(row-1,3,item3);
                        ui->tableWidget->setItem(row-1,4,item4);
                        ui->tableWidget->setItem(row-1,5,item5);
                        ui->tableWidget->setItem(row-1,6,item6);
                 }
             }
         }

    }
}



//托盘以及样式----------------------------------------------------------------------------------------------------------------------------


void Widget::setView()//设置无边框 以及托盘响应
{

//    QDesktopWidget* desktopWidget = QApplication::desktop();
//        //获取可用桌面大小
//        //QRect deskRect = desktopWidget->availableGeometry();
//        //resize(deskRect.width(),deskRect.height());
//        //获取设备屏幕大小
//   QRect screenRect = desktopWidget->screenGeometry();
//   this->resize(screenRect.width()-700,screenRect.height()-400);
//   ui->widget2->resize(screenRect.width()-700,screenRect.height()-400);
//   ui->widget3->resize(screenRect.width()-700,screenRect.height()-400);



     //隐藏bar
     ui->progressBar->hide();
    //去边框 设置最小化、关闭按钮
    //this->setAttribute(Qt::WA_TranslucentBackground,true);//将背景透明-windows下显示为黑色
    this->setWindowFlags(Qt::FramelessWindowHint);//去边框

    int width = this->width();//获取界面的宽度

//    myHelper::setBtnQss(ui->pushButton, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
//    myHelper::setBtnQss(ui->pushButton_3, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
//    myHelper::setBtnQss(ui->pushButton_2, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
//    myHelper::setBtnQss(ui->pushButton_4, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
//    myHelper::setBtnQss(ui->pushButton_5, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
//    myHelper::setBtnQss(ui->enterRecognition, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
//    myHelper::setBtnQss(ui->return_2, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
//    myHelper::setBtnQss(ui->querry, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");

//    myHelper::setBtnQss(ui->pushButton_6, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");

//    myHelper::setBtnQss(ui->DBaddData, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
//    myHelper::setBtnQss(ui->DBclearData, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
//    myHelper::setBtnQss(ui->DBdeleteData, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
//     myHelper::setBtnQss(ui->DBexportData, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
//      myHelper::setBtnQss(ui->DBimportData, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
//       myHelper::setBtnQss(ui->DBmodifyData, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
//        myHelper::setBtnQss(ui->DBselectFile, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");

    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_4->setEnabled(false);
    ui->lineEdit_5->setEnabled(false);
    ui->lineEdit_7->setEnabled(false);
//    myHelper::setTxtQss(ui->lineEdit, "#DCE4EC", "#34495E");
//    myHelper::setTxtQss(ui->lineEdit_2, "#DCE4EC", "#34495E");
//    myHelper::setTxtQss(ui->lineEdit_3, "#DCE4EC", "#34495E");
//    myHelper::setTxtQss(ui->lineEdit_4, "#DCE4EC", "#34495E");
//    myHelper::setTxtQss(ui->lineEdit_5, "#DCE4EC", "#34495E");
//    myHelper::setTxtQss(ui->lineEdit_6, "#DCE4EC", "#34495E");
//    myHelper::setTxtQss(ui->lineEdit_7, "#DCE4EC", "#34495E");
//    myHelper::setTxtQss(ui->lineEdit_8, "#DCE4EC", "#34495E");
//    myHelper::setTxtQss(ui->lineEdit_9, "#DCE4EC", "#34495E");

//    myHelper::setDataTimeEidtQss(ui->dateTimeEdit, "#DCE4EC", "#34495E");
//    myHelper::setDataTimeEidtQss(ui->dateTimeEdit_2, "#DCE4EC", "#34495E");


     //构建最小化、最大化、关闭按钮
     QToolButton *minButton = new QToolButton(this);
     QToolButton *closeButton= new QToolButton(this);


     //获取最小化、关闭按钮图标
    // QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
//     QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);


     QPixmap closePix(":/image/close.png");
     QPixmap minPix(":/image/min.png");

   //设置最小化、关闭按钮图标
   minButton->setIcon(minPix.scaled(30 , 30));
   closeButton->setIcon(closePix.scaled(30 , 30));






     //设置最小化、关闭按钮图标
     minButton->setIcon(minPix);
     closeButton->setIcon(closePix);


     //设置最小化、关闭按钮在界面的位置

     minButton->setGeometry(width-60,5,30,30);
     closeButton->setGeometry(width-30,5,30,30);



     //设置鼠标移至按钮上的提示信息

     minButton->setToolTip(tr("最小化"));

     closeButton->setToolTip(tr("关闭"));


     //设置最小化、关闭按钮的样式
     minButton->setStyleSheet("background-color:transparent;");
     closeButton->setStyleSheet("background-color:transparent;");



     //设置按钮动作
    connect(closeButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    //connect(minButton,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));

    //托盘




            QIcon icon = QIcon(":/image/btn_ok.png");

            setWindowIcon(icon);

            trayIcon = new QSystemTrayIcon(this);

            trayIcon->setIcon(icon);

            trayIcon->setToolTip("car recognition");

            QString titlec=tr("欢迎使用");

            QString textc=tr("服务器正在运行");

            createActions();
            createTrayIcon();


            trayIcon->show();

            trayIcon->showMessage(titlec,textc,QSystemTrayIcon::Information,5000);

            setWindowTitle(tr("Systray"));


            connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                                 this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
            connect(minButton,SIGNAL(clicked()),this,SLOT(hide()));

}


void Widget:: showMessage(char *msg)
{
QString titlec=tr(msg);
QString textc=tr("测试内容单击、双击、中键、按钮");
trayIcon->showMessage(titlec,textc,QSystemTrayIcon::Information,5000);
}

void Widget:: iconActivated(QSystemTrayIcon::ActivationReason reason)
{
   switch (reason) {
      case QSystemTrayIcon::Trigger:
       //showMessage("单击");
       this->show();
         break;
     case QSystemTrayIcon::DoubleClick:{
        //showMessage("双击啦");
       this->show();
             }

            break;
  case QSystemTrayIcon::MiddleClick:
showMessage("你用的是三轮鼠标还是滚轮鼠标啊");
break;
default:
;
}
}
void Widget::createActions()
{
     minimizeAction = new QAction(tr("最小化 (&I)"), this);
     connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

     maximizeAction = new QAction(tr("最大化 (&X)"), this);
     connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

     restoreAction = new QAction(tr("还原 (&R)"), this);
     connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

     quitAction = new QAction(tr("退出 (&Q)"), this);
     connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Widget::createTrayIcon()
{
     trayIconMenu = new QMenu(this);
     trayIconMenu->addAction(minimizeAction);
     trayIconMenu->addAction(maximizeAction);
     trayIconMenu->addAction(restoreAction);
     trayIconMenu->addSeparator();
     trayIconMenu->addAction(quitAction);
     trayIcon->setContextMenu(trayIconMenu);
}

void Widget::mouseMoveEvent(QMouseEvent *e)//鼠标事件
{
    if(mousePressed && (e->buttons() && Qt::LeftButton)){
       this->move(e->globalPos() - mousePoint);
       //ui->widget2->move(e->globalPos() - mousePoint);
       e->accept();
       //globalPos是相对于屏幕的坐标 全局坐标
       //pos()是窗体左上角相对与屏幕的坐标
       //button()  返回产生事件的按钮
       //buttons()   返回产生事件的按钮状态
    }
}

void Widget::mousePressEvent(QMouseEvent *e){
    //qDebug()<<"mouse";
    if(e->button() == Qt::LeftButton){
        mousePressed = true;
        mousePoint = e->globalPos()-this->pos();
        //mousePoint = e->globalPos()-ui->widget2->pos();
        //qDebug()<<"mouse"<<QString::number(mousePoint.x());
        //qDebug()<<"mouse"<<QString::number(mousePoint.y());

        e->accept();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *e){
    mousePressed = false;
    e->accept();
}








//识别
void Widget::on_pushButton_clicked()
{


    //qDebug()<<"rowCount"<<ui->tableWidget->rowCount();
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        ui->progressBar->setRange(0,ui->tableWidget->rowCount());
        if(ui->tableWidget->item(i,0)->checkState()==Qt::Checked)
        {
             ui->progressBar->show();
             ui->progressBar->setValue(i);
             QString pId = ui->tableWidget->item(i,1)->text();
             QSqlQuery sql_query;
             sql_query.exec(tr("select pPath from pirture where pId =%1").arg(pId));
             //qDebug()<<"pid"<<pId;
             while(sql_query.next())
             {
                 QString pPath = sql_query.value("pPath").toString();

                 //修改文件名字解决中文图片问题
                 QString path1 = tr("./temp/%1").arg(pPath);
                 QString path2 = tr("./temp/%1").arg("opencv_picture");
                 bool isok = QFile::rename(path1,path2);
                 if(isok == true)
                 {
                     qDebug()<<"文件改名成功";
                 }else{
                     qDebug()<<"文件改名失败";
                 }

                 //判断是不是有车牌

                 Mat src = imread(path2.toStdString());
                 vector<CPlate> resultVec;
                 CPlateDetect pd;
                 pd.setPDLifemode(true);
                 QSqlQuery sql_query2;
                 int result = pd.plateDetect(src, resultVec);
                 if(resultVec.size()>0)
                  {
                  string carNumber = plateRec(path2).substr(3);

                  const char * p =carNumber.c_str();

                  if(!QString::fromLocal8Bit(p).isEmpty())
                  {
                 //qDebug()<<"carNumber:"<<QString::fromLocal8Bit(p);

                  QString  insert_carNum= tr("update pirture set carNumber = '%1',flag = 1 where pId = '%2'").arg(QString::fromLocal8Bit(p)).arg(pId);
                  sql_query2.exec(insert_carNum);
                  }else{

                      QString  insert_carNum= tr("update pirture set carNumber = '%1',flag = 0 where pId = '%2'").arg("识别不了").arg(pId);
                      sql_query2.exec(insert_carNum);
                  }
                  }else{

                     QString  insert_carNum= tr("update pirture set carNumber = '%1',flag = 0 where pId = '%2'").arg("没有车牌").arg(pId);
                     sql_query2.exec(insert_carNum);
                 }

                 bool isok1 = QFile::rename(path2,path1);
                 if(isok1 == true)
                 {
                     qDebug()<<"文件还原成功";
                 }else{
                     qDebug()<<"文件还原失败";
                 }
             }
             ui->tableWidget->item(i,0)->setCheckState(Qt::Unchecked);

        }

    }
    ui->progressBar->setValue(ui->tableWidget->rowCount());
    ui->progressBar->hide();
    on_comboBox_activated(0);

    if(myHeader->isChecked == true)
    {
        myHeader->isChecked = false;
    }


}
string Widget::plateRec(QString src1)
{
    Mat src = imread(src1.toStdString());

    CPlateRecognize pr;
    pr.setLifemode(true);
    pr.setDebug(false);
    pr.setMaxPlates(1);
    //pr.setDetectType(PR_DETECT_COLOR | PR_DETECT_SOBEL);
    pr.setDetectType(easypr::PR_DETECT_CMSER);

    //vector<string> plateVec;
    vector<CPlate> plateVec;

    int result = pr.plateRecognize(src, plateVec);
    //cout<<"result"<<result<<endl;
    //int result = pr.plateRecognizeAsText(src, plateVec);
    if (result == 0) {
      //size_t num = plateVec.size();
//      for (size_t j = 0; j <num; j++) {
//        cout << "plateRecognize: " << plateVec[j].getPlateStr() << endl;
//      }
        return plateVec[0].getPlateStr();
    }
}

//页面4-----------------------------------------------------------------------------------
void Widget::on_comboBox_3_activated(int index) //页面4  combox
{
    if(index==0){
         model->setTable("carOwner");
    }else if(index==1){
         model->setTable("car");
    }else if(index==2){
         model->setTable("pirture");
    }else if(index==3){
         model->setTable("sendAccount");
    }else if(index==4){
         model->setTable("receiveAccount");
    }

    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
}

void Widget::on_DBaddData_clicked()
{
    int rowNum =model->rowCount();

    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0),rowNum);
}

void Widget::on_DBmodifyData_clicked()
{
    model->submitAll();
    model->database().commit();
}

void Widget::on_DBdeleteData_clicked()
{
    int currow=ui->tableView->currentIndex().row();

    model->removeRow(currow);
    int ok = QMessageBox::warning(this,tr("删除当前行？"),tr("确定吗？"),QMessageBox::Yes,QMessageBox::No);
          if(ok == QMessageBox::No){
              model->revertAll();//不删除 撤销
          }else{
              model->submitAll();//提交
          }

}

void Widget::on_DBexportData_clicked()
{
    curFile=QFileDialog::getSaveFileName(this);

       QFile file( curFile);//建立目标文件路径
       QTextCodec *codec = QTextCodec::codecForName("UTF-8");
       QTextCodec::setCodecForLocale(codec);
       if(!file.open(QFile::WriteOnly|QFile::Text))
       {
            QMessageBox::warning(this,tr("警告"),tr("另存为文件错误"));
       }
       QTextStream out (&file);
       for(int i=0;i<5;i++)
       {
           if(i==0){
                model->setTable("carOwner");
           }else if(i==1){
                model->setTable("car");
           }else if(i==2){
                model->setTable("pirture");
           }else if(i==3){
                model->setTable("sendAccount");
           }else if(i==4){
                model->setTable("receiveAccount");
           }

           model->select();
           model->setEditStrategy(QSqlTableModel::OnManualSubmit);

           int row =model->rowCount();
           int column =model->columnCount();
            ui->progressBar->setRange(0,1000);
           int progressBarflag=1;
           QString line;

           for(int j=0;j<row;j++)
           {


               line=QString::number(i)+"|";
               for(int k=0;k<column;k++)
               {
                 // qDebug()<<model->index(j,k).data().toString();

                 line.append( model->index(j,k).data().toString()).append("|");
                 ui->progressBar->setValue(progressBarflag++);
               }
                // qDebug()<<"line"<<line;
               QByteArray byte_array;
               byte_array.append(line);
               QByteArray hash_byte_array = QCryptographicHash::hash(byte_array, QCryptographicHash::Md5);
               QString md5 = hash_byte_array.toHex();
               QByteArray by64 = byte_array.toBase64();
                 out<<by64<<"|"<<md5<<"|"<<"\n";

              // qDebug()<<by64<<"|"<<md5<<"|"<<"\n";


           }
        ui->progressBar->setValue(1000);
      }
     setWindowTitle( curFile);


}

void Widget::on_DBselectFile_clicked()
{
     curFile =QFileDialog::getOpenFileName(this);
     ui->DBimportData->show();
}

void Widget::on_DBimportData_clicked()
{

    QSqlQuery sql_query;
     //中文支持
       QTextCodec *codec = QTextCodec::codecForName("UTF-8");

       QTextCodec::setCodecForLocale(codec);


     QFile file(curFile);//建立目标文件的路径

     if(!file.open(QIODevice::ReadOnly | QIODevice::Text))//打开文件

     {
         QMessageBox::warning(this,tr("警告"),tr("打开文件错误"));
     }



     //文本流  对象
     QTextStream in(&file);//建立读取的通道
     file.size();
     qDebug()<<"file.size()"<<file.size()<<file.size()/50;
     ui->progressBar->setRange(0,file.size()/50);
      int k=1;
     while(!in.atEnd()) {
             QByteArray line = file.readLine();
             QString str(line);
 // 解密------------------------------------------------------------------------------
             QStringList lineSplit=str.split("|");

             QByteArray byte_array;
             byte_array.append(lineSplit.at(0));
             QByteArray bytearrayfrombase64 = QByteArray::fromBase64(byte_array);
             QString str2(bytearrayfrombase64);

 //修改判断
             QByteArray hash_byte_array = QCryptographicHash::hash( bytearrayfrombase64, QCryptographicHash::Md5);
             QString md5 = hash_byte_array.toHex();
             if(md5!=lineSplit.at(1)){
                  qDebug()<<"文件被修改";
                QMessageBox::warning(this,tr("警告"),tr("文件被修改"));
             }


 //------------------------------------------------------------------------------

             QStringList databaseMessage=str2.split("|");
            //  qDebug()<<"str2"<<str2;
             int colum=databaseMessage.count();

             databaseMessage.at(0);
            // qDebug()<<colum<<databaseMessage.at(0)<<databaseMessage.at(1)<<databaseMessage.at(2);
             if(databaseMessage.at(0)=="0"){
                 sql_query.prepare(insert_carOwner);
             }else if(databaseMessage.at(0)=="1"){
                 sql_query.prepare(insert_car);
             }else if(databaseMessage.at(0)=="2"){
                 sql_query.prepare(insert_pirture);
             }else if(databaseMessage.at(0)=="3"){
                 sql_query.prepare(insert_sendAccount);
             }else if(databaseMessage.at(0)=="4"){
                 sql_query.prepare(insert_receiveAccount);
             }
             for(int i=1;i<colum-1;i++)
             {
                 sql_query.addBindValue(databaseMessage.at(i));

             }
             if(!sql_query.exec())
             {
             qDebug()<<sql_query.lastError();
             }
          else
             {

                 ui->progressBar->setValue(k++);
                 qDebug()<<"inserted"<<k<<databaseMessage.at(0)<<databaseMessage.at(1);
             }

         }
          ui->progressBar->setValue(file.size()/50);
      //QApplication::setOverrideCursor(Qt::WaitCursor);
      //读取文件的全部内容显示
      // ui->textEdit->setPlainText(in.readAll());//读取文件,显示

      // QApplication::restoreOverrideCursor();

      setWindowTitle(curFile);


}

void Widget::on_DBclearData_clicked()
{
    QSqlQuery sql_query;

    sql_query.prepare(clear_carOwner);
    if(!sql_query.exec())
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
    qDebug()<<"cleared";
    }


    sql_query.prepare(clear_car);
    if(!sql_query.exec())
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
    qDebug()<<"cleared";
    }

    sql_query.prepare(clear_pirture);
    if(!sql_query.exec())
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
    qDebug()<<"cleared";
    }

    sql_query.prepare(clear_sendAccount);
    if(!sql_query.exec())
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
    qDebug()<<"cleared";
    }

    sql_query.prepare(clear_receiveAccount);
    if(!sql_query.exec())
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
    qDebug()<<"cleared";
    }
}

void Widget::hidePage4()
{
    ui->tableView->hide();
    ui->DBaddData->hide();
    ui->DBclearData->hide();
    ui->DBdeleteData->hide();
    ui->DBexportData->hide();
    ui->DBimportData->hide();
    ui->DBselectFile->hide();
    ui->DBmodifyData->hide();
    ui->progressBar->hide();
    ui->comboBox_3->hide();
}
void Widget::showPage4()
{
    ui->tableView->show();
    ui->DBaddData->show();
    ui->DBclearData->show();
    ui->DBdeleteData->show();
    ui->DBexportData->show();
   // ui->DBimportData->show();
    ui->DBselectFile->show();
    ui->DBmodifyData->show();
    ui->progressBar->show();
    ui->comboBox_3->show();
}
