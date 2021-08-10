#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "form.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_tabWidget_tabBarClicked(int index);

    void on_sign_group_valueChanged(int arg1);

    void on_sign_btn_clicked();

    void on_login_btn_clicked();

    void on_remUid_clicked(bool checked);

    void aboutpushButton_clicked();

    void qd_btn_clicked();

    void qt_btn_clicked();

private:
    Ui::Widget *ui;
    Form* Mainform;
};
#endif // WIDGET_H
