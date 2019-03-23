#ifndef QUERY_H
#define QUERY_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class query;
}

class query : public QWidget
{
    Q_OBJECT

public:
    explicit query(QWidget *parent = 0);
    ~query();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_activated(int index);

    void on_comboBox_2_activated(int index);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    QSqlTableModel *model;

    int   flagIndex;//查询类型
    Ui::query *ui;
};

#endif // QUERY_H
