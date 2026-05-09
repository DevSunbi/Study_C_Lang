#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProgressDialog>
#include <QTimer>


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    QProgressDialog *pd;
    QTimer *timer;
    int steps;

private slots:
    void cancel();
    void perform();
};
#endif // WIDGET_H
