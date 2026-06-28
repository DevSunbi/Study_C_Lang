#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLCDNumber>
#include <QLineEdit>
#include <QProgressBar>
#include <QTabWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    QLCDNumber *lcd;
    QLineEdit *edit;
    QProgressBar *progress;
    QTabWidget *tab;

private slots:
    void textChanged(QString);
    void test(int);
};
#endif // WIDGET_H
