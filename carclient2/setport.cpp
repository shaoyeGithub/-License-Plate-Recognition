#include "setport.h"
#include "ui_setport.h"

SetPort::SetPort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetPort)
{
    ui->setupUi(this);
}

SetPort::~SetPort()
{
    delete ui;
}
