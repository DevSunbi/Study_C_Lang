#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    tab = new QTabWidget(this);
    tab->setGeometry(20, 20, 300, 250);

    QWidget *first = new QWidget;
    QWidget *second = new QWidget;
    QWidget *third  = new QWidget;
    tab->addTab(first, "First Tab");
    tab->addTab(second, "Second Tab");
    tab->addTab(third, "Third Tab");
    connect(tab, SIGNAL(currentChanged(int)), this, SLOT(test(int)));

    lcd = new QLCDNumber(2, first);
    lcd->setGeometry(50, 30, 200, 100);
    lcd->setSegmentStyle(QLCDNumber::Filled);
    lcd->display(10);

    edit = new QLineEdit("Init Value", second);
    edit->setGeometry(50, 150, 200, 30);
    edit->setEchoMode(QLineEdit::Normal);
    connect(edit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));


    progress = new QProgressBar(third);
    progress->setGeometry(50, 200, 200, 30);
    // progress->setMinimum(0);
    // progress->setMaximum(100);
    progress->setRange(0, 100);
    progress->setOrientation(Qt::Horizontal);
    progress->setInvertedAppearance(true);
    progress->setValue(20);

}

void Widget::textChanged(QString str)
{
    qDebug() << "Input Text : " << str;
}

void Widget::test(int i)
{
    qDebug()<<"Current Index" << i;
}

Widget::~Widget() = default;
