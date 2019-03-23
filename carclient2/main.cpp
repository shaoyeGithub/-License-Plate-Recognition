#include "sendpicturewidget.h"
#include <QApplication>
#include"login.h"
#include "rotatewidget.h"
#include <QDebug>
#include "stackedwid.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
     int nExitCode = 0;
     Dialog dlg;


    if(dlg.exec()== QDialog::Accepted )
     {

       sendPictureWidget w;
       w.show();

       nExitCode = a.exec();
     }



         return nExitCode;




}
