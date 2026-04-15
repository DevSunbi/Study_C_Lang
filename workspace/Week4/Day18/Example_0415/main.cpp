#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Widget w;
    // w.show();

    QString str=("hello");
    // QChar *p = str.data();
    // const char* ptr = str.toStdString().c_str();
    // QString test(p);
    std::string stdStr = str.toStdString();
    const char* ptr = stdStr.c_str();

    return QCoreApplication::exec();
}
