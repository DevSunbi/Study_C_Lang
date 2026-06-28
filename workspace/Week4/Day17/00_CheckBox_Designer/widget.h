#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private slots:
    void on_radioButton_4_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_checkBox_4_clicked();
    void on_checkBox_3_clicked();
    void on_checkBox_2_clicked();
    void test();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
