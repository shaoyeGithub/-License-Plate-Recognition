#ifndef DISTINGUISH_H
#define DISTINGUISH_H

#include <QWidget>
#include <QWidget>
#include <QTimer>
#include <QTableWidgetItem>
#include <ccheckboxheaderview.h>
#include  "db.h"
#include  <QTableWidget>

namespace Ui {
class distinguish;
}

class distinguish : public QWidget
{
    Q_OBJECT

public:
    explicit distinguish(QWidget *parent = 0);
    ~distinguish();
    void  showQTableWidget();

private:
    Ui::distinguish *ui;
    QTableWidgetItem *itemX ;
    bool selectROW;

private slots:

    void getSelectedRow();
    void getSelectedItem(int row,int column);

    void on_pushButton_clicked();
};

#endif // DISTINGUISH_H
