#include "widget.h"
#include "./ui_widget.h"
#include <QMouseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()),
            this, SLOT(changeLabelText()));
    setMouseTracking(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    QString str = QString("pos : (x:%1, y:%2)").arg(pos.x()).arg(pos.y());
    ui->label->setText(str);
}

void Widget::changeLabelText()
{
    ui->label->setText("ydg TaDa!!");
}