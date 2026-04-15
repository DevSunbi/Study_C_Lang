#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QComboBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    QComboBox* combo;

private slots:
    void valueChanged(int i);
    void textChanged(QString str);

};
#endif // WIDGET_H
