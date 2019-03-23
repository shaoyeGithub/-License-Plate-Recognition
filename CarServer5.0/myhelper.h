#ifndef MYHELPER_H
#define MYHELPER_H
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>

#include <QTimeEdit>
#include  <QDateTimeEdit>
class myHelper: public QObject
{
public:

    //设置为开机启动
    static void AutoRunWithSystem(bool IsAutoRun, QString AppName, QString AppPath)
    {
        QSettings *reg = new QSettings(
            "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
            QSettings::NativeFormat);

        if (IsAutoRun) {
            reg->setValue(AppName, AppPath);
        } else {
            reg->setValue(AppName, "");
        }
    }
    static void SetStyle( QWidget *parent,const QString &styleName)
    {
        QFile file(QString(":image/%1.css").arg(styleName));
        file.open(QFile::ReadOnly);
        QString qss = QLatin1String(file.readAll());
        parent->setStyleSheet(qss);
        parent->setPalette(QPalette(QColor("#F0F0F0")));
    }
    static void setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor)

     {

              QStringList qss;

              qss.append(QString("QLineEdit{border-style:none;padding:6px;border-radius:5px;border:2px solid %1;}").arg(normalColor));

              qss.append(QString("QLineEdit:focus{border:2px solid %1;}").arg(focusColor));

              txt->setStyleSheet(qss.join(""));

     }
    static void setDataTimeEidtQss(QDateTimeEdit *txt, QString normalColor, QString focusColor)

     {

              QStringList qss;

              qss.append(QString("QDateTimeEdit{border-style:none;padding:6px;border-radius:5px;border:2px solid %1;}").arg(normalColor));

              qss.append(QString("QDateTimeEdit:focus{border:2px solid %1;}").arg(focusColor));

              qss.append(QString("QDateTimeEdit:down-button{image:url(:/array_down.png);}"));
              qss.append(QString("QDateTimeEdit:up-button{image:url(:/array_up.PNG);}"));
              qss.append(QString("QDateTimeEdit:up-button:pressed{color:#ABABAB;background:#BFEFFF;}"));
              qss.append(QString("QDateTimeEdit:down-button:pressed{color:#ABABAB;background:#BFEFFF;}"));
              txt->setStyleSheet(qss.join(""));

     }
    static void setBtnQss(QPushButton *btn,

                             QString normalColor, QString normalTextColor,

                             QString hoverColor, QString hoverTextColor,

                             QString pressedColor, QString pressedTextColor)

     {

              QStringList qss;

              qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));

              qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));

              qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));

              btn->setStyleSheet(qss.join(""));

     }
};
#endif // MYHELPER_H

