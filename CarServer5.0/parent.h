#ifndef PARENT_H
#define PARENT_H

#include <QWidget>

namespace Ui {
class parent;
}

class parent : public QWidget
{
    Q_OBJECT

public:
    explicit parent(QWidget *parent = 0);
    ~parent();

private:
    Ui::parent *ui;
};

#endif // PARENT_H
