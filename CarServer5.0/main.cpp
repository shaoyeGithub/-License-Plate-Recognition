#include "widget.h"
#include <QApplication>
#include "db.h"
#include "login.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    if(createData())
    {
            qDebug()<<"数据库打开成功";
    }else{
            qDebug()<<"数据库打开失败";
    }
//    Widget w;
//    w.show();

//    return a.exec();

//------------------------------------------
    int nExitCode=0;

        Dialog dlg;

      if(dlg.exec()== QDialog::Accepted )
         {

           Widget w;
           w.show();
           nExitCode = a.exec();
         }


        return nExitCode;
}
