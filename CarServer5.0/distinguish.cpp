#include "distinguish.h"
#include "ui_distinguish.h"
#include <QMessageBox>

distinguish::distinguish(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::distinguish)
{
    ui->setupUi(this);


    getSelectedRow();
}

distinguish::~distinguish()
{
    delete ui;
}

void distinguish::showQTableWidget()
{



    QSqlQuery sql_query;
    QString select_sql = "select pId,pPath,carNumber,time,pAdress from pirture where flag =0";

    ui->tableWidget->setColumnCount(5);
    QStringList header;
    header<<tr("图像")<<tr("车牌")<<tr(" 违章时间")<<tr("地点")<<tr("人工复查");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    if(!sql_query.exec(select_sql))
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
        int row=0;

    while(sql_query.next())
    {
    ui->tableWidget->setRowCount(++row);
    int pId = sql_query.value("pId").toInt();
    QString pPath = sql_query.value("pPath").toString();
    QString carNumber=sql_query.value("carNumber").toString();
    QString pTime=sql_query.value("time").toString();
    QString pAdress=sql_query.value("pAdress").toString();
    qDebug()<<QString("pId:%1    pPath:%2").arg(pId).arg(pPath);

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

void distinguish::getSelectedRow()
{
    itemX = new QTableWidgetItem;
    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//自适应
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//等宽
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(getSelectedItem(int,int)));//连接单击与曹

}
void distinguish::getSelectedItem(int row, int column)
{
     itemX=ui->tableWidget->item(row,column);
     itemX=ui->tableWidget->item(row,0);
     QString pPath= itemX->text();
     qDebug()<<"row  pPath"<<row<<pPath;
     ui->label->setPixmap(QPixmap(tr("./temp/%1").arg(pPath)).scaled(383,209));
     ui->lineEdit->setText(ui->tableWidget->item(row,1)->text());
     selectROW=true;
}

void distinguish::on_pushButton_clicked()

{
    if(!selectROW){
        QMessageBox::about(NULL, "复查", "请先选一行");
        return;
    }
    int row =itemX->row();
    QString getLineEdit =ui->lineEdit->text();
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
