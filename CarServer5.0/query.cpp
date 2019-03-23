#include "query.h"
#include "ui_query.h"
#include<QSqlTableModel>
#include"db.h"

query::query(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::query)
{
    ui->setupUi(this);

    flagIndex=0;//初始化查询类型
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//自适应
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//等宽
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());


    //modle-------------------------------------------
        model =new QSqlTableModel(this);


}

query::~query()
{
    delete ui;
}

void query::on_pushButton_clicked()
{
    int row =0;
    ui->tableWidget->setRowCount(row);

    QString getLineEdit=ui->lineEdit->text();
    QSqlQuery sql_query;
    QSqlQuery sql_query2;
    QString select_sql;
    QString time1=ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString time2=ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd hh:mm:ss");

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
                     ui->tableWidget->setColumnCount(7);
                     QStringList header;
                     header<<tr("违章号")<<tr("身份证")<<tr("姓名")<<tr("车牌")<<tr("车型 ")<<tr(" 违章时间")<<tr("地点");
                     ui->tableWidget->setHorizontalHeaderLabels(header);
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

void query::on_pushButton_2_clicked()
{
      model->submitAll();
      model->database().commit();
}

void query::on_comboBox_activated(int index)
{
    flagIndex=index;
}

void query::on_comboBox_2_activated(int index)
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

void query::on_pushButton_4_clicked()
{
    int rowNum =model->rowCount();

    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0),rowNum);
}

void query::on_pushButton_3_clicked()
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
