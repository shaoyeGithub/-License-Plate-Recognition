#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QToolButton>
//#include "db.h"
#include "myhelper.h"
int Dialog::privilege =0;
QString Dialog::userName ="";
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);
    //设置窗口背景透明度

    this->setWindowTitle("服务器端登录");
    //设置窗口图标
    QIcon icon = QIcon(":/image/error.png");
    myHelper::SetStyle(this,"gray");
    this->setWindowIcon(icon);

    QString fileName;
    fileName = QCoreApplication::applicationDirPath();
    fileName  +="/SendTaskInfo/test.ini";




    ui->accountComboBox->setEditable(true);
    QLineEdit* lineEdit = ui->accountComboBox->lineEdit();
    lineEdit->setPlaceholderText(QStringLiteral("手机/邮箱"));
    QRegExp regExp("[a-zA-Z0-9]{0,10}");
    lineEdit->setValidator(new QRegExpValidator(regExp,this));
    ui->passwordEdit->setPlaceholderText(QStringLiteral("密码"));
    QRegExp regExp2("[a-zA-Z0-9]{0,100}");
    ui->passwordEdit->setValidator(new QRegExpValidator(regExp2,this));

    //隐藏边框
    this->setWindowFlags(Qt::FramelessWindowHint);

    //自定义最小化和关闭
    // 获取页面宽度
    int width =this->width();

    //构建最小化和关闭按钮
    QToolButton *minButton = new QToolButton(this);
    QToolButton *closeButton = new QToolButton(this);

    //获取最小化、关闭图标
    QPixmap minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);

    //ui->checkBox->setChecked(true);

    //设置按钮图标
    minButton->setIcon(minPix);
    closeButton->setIcon(closePix);

    //设置按钮在界面的位置
    minButton ->setGeometry(width-46,5,20,20);
    closeButton ->setGeometry(width-25,5,20,20);

    //设置鼠标移至的按钮提示信息
    minButton ->setToolTip(tr("最小化"));
    closeButton ->setToolTip(tr("关闭"));

    minButton ->setStyleSheet("background-color:transparent");
    closeButton ->setStyleSheet("background-color:transparent");

    minButton->setFixedSize(25,25);
    closeButton->setFixedSize(25,25);


    connect(minButton,SIGNAL(clicked()),this,SLOT(on_minWindow()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));

    QFile f("./test.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open failed3." << endl;
    }
    int i=0;
    int j=0;

    QTextStream txtInput(&f);
    QString lineStr[1000];
    while(!txtInput.atEnd())
    {

        lineStr[i] = txtInput.readLine();
        i++;
    }
    for(j=i-1;j>-1;j--)
    {
        ui->accountComboBox->addItem(lineStr[j]);
        //qDebug() << lineStr[j] << endl;
    }
    f.close();
    QSettings iniSet("./SendTaskInfo/test.ini", QSettings::IniFormat);
        QString passWord = iniSet.value(ui->accountComboBox->lineEdit()->text()+"/Password").toString();
        QString user=iniSet.value(ui->accountComboBox->lineEdit()->text()+"/AutoLogin").toString();

    if(user== ui->accountComboBox->lineEdit()->text())
    {

        ui->passwordEdit->setText(passWord);
        if(ui->passwordEdit->text().isEmpty()){

        ui->checkBox->setCheckState(Qt::Unchecked);
            }else
            ui->checkBox->setCheckState(Qt::Checked);


    }

    ui->accountComboBox->setFocus();




}


void Dialog::on_minWindow()
{
    this->showMinimized();

}
Dialog::~Dialog()
{

    delete ui;
}

void Dialog::mouseMoveEvent(QMouseEvent *e)
{
    //globalPos是相对于屏幕的坐标 全局坐标
    //Pos()是窗体 左上角相对于屏幕左上角的坐标
    //button() 返回产生事件的按钮
    //buttons()  返回产生事件的按钮 的状态  发生时间时那些按钮处于按下状态
    if(mousePressed&&(e->buttons() &&Qt::LeftButton))
    {

    this->move(e->globalPos()-mousePoint);

    e->accept();
    }

}

void Dialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        mousePressed=true;
        mousePoint =e->globalPos()-this->pos();
        e->accept();
    }


}
void Dialog::mouseReleaseEvent(QMouseEvent *)
{

    mousePressed=false;
}


void Dialog::on_loginButton_clicked()
{
    int j = ui->accountComboBox->lineEdit()->text().length();
    int i = ui->passwordEdit->text().length();
    if(i<6||j<6||j>10){
        QMessageBox::warning(this,tr("错误"),tr("用户名或密码错误"),QMessageBox::Yes);
        ui->passwordEdit->clear();
        ui->accountComboBox->lineEdit()->clear();
        ui->accountComboBox->lineEdit()->setFocus();
    }
    else{
  QString m;
  name = ui->accountComboBox->lineEdit()->text();
  password = ui->passwordEdit->text();
  sQuery.exec(tr("select password from sendAccount where username ='%1'").arg(name));
  while (sQuery.next()) {
     m = sQuery.value(0).toString();
  }
  if(m!=NULL){
      if(m==password)
      {
          userName =ui->accountComboBox->lineEdit()->text();
          RemUserName();
         this->accept();
      }else{
          QMessageBox::warning(this,tr("错误"),tr("用户名或密码错误"),QMessageBox::Yes);
          ui->passwordEdit->clear();
          ui->accountComboBox->lineEdit()->clear();
          ui->accountComboBox->lineEdit()->setFocus();
      }
  }
  else
      {
          QMessageBox::warning(this,tr("错误"),tr("用户名或密码错误"),QMessageBox::Yes);
          ui->passwordEdit->clear();
          ui->accountComboBox->lineEdit()->clear();
          ui->accountComboBox->lineEdit()->setFocus();
      }
  }
}


void Dialog::RemUserName()
{
    if(ui->checkBox->checkState()==Qt::Checked)
        remember = 1;
    else
        remember = 0;
    QSettings iniSet("./SendTaskInfo/test.ini", QSettings::IniFormat);
             iniSet.setValue( ui->accountComboBox->lineEdit()->text()+"/AutoLogin", ui->accountComboBox->lineEdit()->text() );
             if(remember == 1)
                 iniSet.setValue(ui->accountComboBox->lineEdit()->text()+"/Password",ui->passwordEdit->text());
             else if (remember != 1)
             {
                 QString mode =NULL;
                 iniSet.setValue(ui->accountComboBox->lineEdit()->text()+"/Password",mode);
             }

             if (remember == 1)
             {
                 QFile f1("./test.txt");

                 if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
                 {
                     qDebug() << "Open failed2." << endl;
                 }
                 int i=0;
                 int j=0;
                 int k=0;

                 QTextStream txtInput(&f1);
                 QString lineStr[1000];
                 QString lineStr2[1000];
                 while(!txtInput.atEnd())
                 {

                     lineStr[i] = txtInput.readLine();
    //                 qDebug() << lineStr[i] << endl;
                     i++;
                 }
                 QString user = ui->accountComboBox->lineEdit()->text();
                 for(j =0,k=0;j<i;j++,k++)//查重
                 {

                     if(user == lineStr[j])
                     {
                         if(j+1<i){
                         lineStr2[k]=lineStr[j+1];
                         j++;}
                         else{

                             break;}

                     }
                     else{
                         lineStr2[k]=lineStr[j];
                     }
                     //qDebug()<< lineStr2[k]<<endl;

                 }

                 f1.close();

                 QFile f2("./test.txt");
                 if(!f2.open(QIODevice::WriteOnly | QIODevice::Text))
                 {

                     qDebug() << "Open failed1." << endl;
                 }


                 QTextStream txtOutput(&f2);
                 int m =0;
                 while(lineStr2[m]!=NULL)
                 {
                     txtOutput<<lineStr2[m]<<endl;
                     m++;
                 }
                 txtOutput << ui->accountComboBox->lineEdit()->text();
                 f2.close();
             }



}
void Dialog::on_checkBox_clicked()
{
    if(ui->checkBox->checkState()==Qt::Checked)
    remember = 1;
    else
        remember = 0;
}

void Dialog::on_accountComboBox_currentIndexChanged(const QString &arg1)
{
    QSettings iniSet("./SendTaskInfo/test.ini", QSettings::IniFormat);
    QString passWord = iniSet.value(ui->accountComboBox->lineEdit()->text()+"/Password").toString();
    QString user=iniSet.value(ui->accountComboBox->lineEdit()->text()+"/AutoLogin").toString();
    if(!(ui->accountComboBox->lineEdit()->text()==user))
    {
        ui->passwordEdit->clear();
        ui->checkBox->setChecked(false);
    }
    else
    {
        ui->passwordEdit->setText(passWord);
        if(ui->passwordEdit->text().isEmpty()){

        ui->checkBox->setCheckState(Qt::Unchecked);
            }else
            ui->checkBox->setCheckState(Qt::Checked);
    }
}

void Dialog::on_accountComboBox_editTextChanged(const QString &arg1)
{
    QSettings iniSet("./SendTaskInfo/test.ini", QSettings::IniFormat);
    QString passWord = iniSet.value(ui->accountComboBox->lineEdit()->text()+"/Password").toString();
    QString user=iniSet.value(ui->accountComboBox->lineEdit()->text()+"/AutoLogin").toString();
    if(!(ui->accountComboBox->lineEdit()->text()==user))
    {
        ui->passwordEdit->clear();
        ui->checkBox->setChecked(false);
    }
    else
    {
        ui->passwordEdit->setText(passWord);
        if(ui->passwordEdit->text().isEmpty()){

        ui->checkBox->setCheckState(Qt::Unchecked);
            }else
            ui->checkBox->setCheckState(Qt::Checked);
    }
}
