#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QButtonGroup>

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
private:
    QButtonGroup *m_chk_group[2];
    QCheckBox *m_exclusive[3];
    QCheckBox *m_non_exclusive[3];
private:
    void slot_chkChanged();

// private:
//     Ui::Widget *ui;

};
#endif // WIDGET_H
