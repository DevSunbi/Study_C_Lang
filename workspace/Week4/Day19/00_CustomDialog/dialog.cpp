#include "dialog.h"

dialog::dialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Custom Dialog");
    lbl = new QLabel("Name");
    edit = new QLineEdit("");
    okbtn = new QPushButton("Confirm");
    cancelbtn = new QPushButton("Cancel");
    QHBoxLayout *hlay1 = new QHBoxLayout();
    hlay1->addWidget(lbl);
    hlay1->addWidget(edit);
    QHBoxLayout *hlay2 = new QHBoxLayout();
    hlay2->addWidget(okbtn);
    hlay2->addWidget(cancelbtn);
    QVBoxLayout *vlay = new QVBoxLayout();
    vlay->addLayout(hlay1);
    vlay->addLayout(hlay2);
    setLayout(vlay);

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
dialog::~dialog()
{
}
