#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->checkBox_4,SIGNAL(clicked()),this,SLOT(test()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_radioButton_clicked()
{
    qDebug() << "Um..";
}


void Widget::on_radioButton_2_clicked()
{
    qDebug() <<"Jun...";
}


void Widget::on_radioButton_4_clicked()
{
    qDebug() <<"Sik...";
}


void Widget::on_checkBox_4_clicked()
{
    qDebug() <<"Still...";
}


void Widget::on_checkBox_3_clicked()
{
    qDebug() <<"Alive...";
}


void Widget::on_checkBox_2_clicked()
{
    qDebug() << "...";
}

void Widget::test()
{
    qDebug() <<"Um test : " << ((QCheckBox*)sender())->text();
    QCheckBox* ptr = (QCheckBox *)sender();
    ptr->setText("Changed");
}