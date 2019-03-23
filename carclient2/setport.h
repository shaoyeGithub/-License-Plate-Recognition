#ifndef SETPORT_H
#define SETPORT_H

#include <QWidget>

namespace Ui {
class SetPort;
}

class SetLoginPort : public QWidget
{
    Q_OBJECT

public:
    explicit SetPort(QWidget *parent = 0);
    ~SetPort();

private:
    Ui::SetPort *ui;
};

#endif // SETPORT_H
