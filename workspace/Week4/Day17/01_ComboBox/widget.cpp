#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    combo = new QComboBox(this);
    combo->setGeometry(50, 50, 200, 30);
    combo->addItem("Application");
    combo->addItem("Graphics");
    combo->addItem("Database");
    combo->addItem("Network");

    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(valueChanged(int)));
    connect(combo, SIGNAL(currentTextChanged(QString)), this, SLOT(textChanged(QString)));
}

void Widget::valueChanged(int i)
{
    qDebug() << "ComboBox value changed : " << i;
}

void Widget::textChanged(QString str)
{
    qDebug()<<str;
}

Widget::~Widget() = default;
