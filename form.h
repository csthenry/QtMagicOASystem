#ifndef FORM_H
#define FORM_H

#include <QDialog>

namespace Ui {
class Form;
}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

public:
    Ui::Form *ui;
private slots:
    void on_about_btn_clicked();
};

#endif // FORM_H
