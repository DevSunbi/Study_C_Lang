#include "widget.h"

#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog w;

    int result = w.exec();

    if(result == QDialog::Accepted){

        qDebug()<<Q_FUNC_INFO<< QDialog::Accepted;

    }else if(result == QDialog::Rejected){
        qDebug()<<Q_FUNC_INFO<<QDialog::Rejected;
    }

    return QCoreApplication::exec();
}