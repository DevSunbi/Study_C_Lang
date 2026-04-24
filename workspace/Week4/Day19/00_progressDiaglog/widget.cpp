#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    pd = new QProgressDialog("File Copy Progress", "Cancel", 0, 100, this);
    connect(pd, SIGNAL(canceled()), this, SLOT(cancel()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(perform()));
    steps = 0;
    timer->start(1000);

}

void Widget::cancel()
{
    timer->stop();
}

void Widget::perform()
{
    pd->setValue(steps++);
    if(steps > pd->maximum())
    {
        timer->stop();
    }
}

Widget::~Widget() = default;
