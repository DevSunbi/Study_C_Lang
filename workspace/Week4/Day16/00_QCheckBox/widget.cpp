#include "widget.h"
//#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    //, ui(new Ui::Widget)
{
    //ui->setupUi(this);
    QString str1[3] = {"Game","Office","Develop" };
    QString str2[3] = {"P&rogramming", "Q&T", "Q&S"}; // 왜 이카나? -> 의미가 있음

    int xpos = 30;
    int ypos = 30;

    m_chk_group[0] = new QButtonGroup(this); // 어느 컨테이너에 있어서 보인다를 명시하는 this
    m_chk_group[1] = new QButtonGroup(this);

    for(int i=0; i<3; i++)
    {
        m_exclusive[i] = new QCheckBox(str1[i], this);
        m_exclusive[i]->setGeometry(xpos, ypos, 120, 30); // 시작, 시작, 크기, 크기
        m_chk_group[0]->addButton(m_exclusive[i]);

        m_non_exclusive[i] = new QCheckBox(str2[i], this);
        m_non_exclusive[i] -> setGeometry(xpos + 120, ypos, 120, 30);
        m_chk_group[1] -> addButton(m_non_exclusive[i]);

        connect(m_exclusive[i], SIGNAL(clicked()), this, SLOT(slot_chkChanged()));
        ypos += 40;
    }

    m_chk_group[0]->setExclusive(false); // 다중 선택 허용 여부
    m_chk_group[1]->setExclusive(true);
}

void Widget::slot_chkChanged()
{
    for(int i=0; i<3; i++)
    {
        if(m_exclusive[i]->checkState())
        {
            qDebug() << "checkbox selected : " + m_exclusive[i]->text();
        }
    }
}

Widget::~Widget()
{
    //delete ui; // 수동으로 작업하기 위해서는 setup으로 ui 연결 할 필요가 없음
}
