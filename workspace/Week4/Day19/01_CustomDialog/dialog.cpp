#include "dialog.h"

dialog::dialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Custom Dialog");
    lblId = new QLabel("ID : ");
    editId = new QLineEdit("");

    lblPw = new QLabel("PW : ");
    editPw = new QLineEdit("");

    lblCPw = new QLabel("Confirm PW : ");
    editCPw = new QLineEdit("");


    okbtn = new QPushButton("Confirm");
    cancelbtn = new QPushButton("Cancel");

    QVBoxLayout *mainLay = new QVBoxLayout();
    QHBoxLayout *h1 = new QHBoxLayout();
    h1->addWidget(lblId);
    h1->addWidget(editId);

    QHBoxLayout *h2 = new QHBoxLayout();
    h2->addWidget(lblPw);
    h2->addWidget(editPw);

    QHBoxLayout *h3 = new QHBoxLayout();
    h3->addWidget(lblCPw);
    h3->addWidget(editCPw);

    QHBoxLayout *h4 = new QHBoxLayout();
    h4->addWidget(okbtn);
    h4->addWidget(cancelbtn);


    mainLay->addLayout(h1);
    mainLay->addLayout(h2);
    mainLay->addLayout(h3);
    mainLay->addLayout(h4);

    setLayout(mainLay);

    connect(okbtn, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(cancelbtn, SIGNAL(clicked(bool)), this, SLOT(reject()));

    // connect(this, SIGNAL(accepted()), this, SLOT(accept()));
    // connect(this, SIGNAL(rejected()), this, SLOT(reject()));

}
void dialog::slot_okbtn()
{
    qDebug() << "ok";
    emit accepted();
}
void dialog::slot_cancelbtn()
{
    qDebug() << "cancel";
    emit rejected();
}

QString dialog::getId()
{
    return editId->text();
}

QString dialog::getPw()
{
    return editPw->text();
}

QString dialog::getCheckPw()
{
    return editCPw->text();
}

dialog::~dialog()
{
}
