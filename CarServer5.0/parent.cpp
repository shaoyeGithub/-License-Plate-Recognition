#include "parent.h"
#include "ui_parent.h"

parent::parent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::parent)
{
    ui->setupUi(this);
}

parent::~parent()
{
    delete ui;
}
