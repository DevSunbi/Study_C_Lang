#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog w;

    int result = w.exec();

    if(result == QDialog::Accepted){

        if(w.getCheckPw() == w.getPw())
        {
            qDebug()<<"ID : "<<QDialog::Accepted << w.getId();
            qDebug()<<"PW :"<< QDialog::Accepted << w.getPw();
        }
        else if(w.getCheckPw() != w.getPw()){
            qDebug() << QDialog::Rejected << "흥";
        }


    }else if(result == QDialog::Rejected){
        qDebug()<<QDialog::Rejected<<"흥";
    }

    return QCoreApplication::exec();
}
