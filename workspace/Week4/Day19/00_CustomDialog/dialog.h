#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
class dialog : public QDialog
{
    Q_OBJECT
public:
    dialog(QWidget *parent = 0);
    ~dialog();
private:
    QLabel *lbl;
    QLineEdit *edit;
    QPushButton *okbtn;
    QPushButton *cancelbtn;
private slots:
    void slot_okbtn();
    void slot_cancelbtn();
};
#endif // DIALOG_H