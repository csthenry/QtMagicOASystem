#include "widget.h"
#include "ui_widget.h"
#include "ui_form.h"
#include "mainFunc.cpp"
#include <QMessageBox>

int group;
char temp[12];
string uid;
attendance *ahead, *aTarget;
userAccount *head, *target;
userAccount *last = nullptr;
attendance *alast = nullptr;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    Mainform = new Form(this);
    ahead = new attendance();
    head = new userAccount();
    databaseReload(head, ahead, last, alast);
    QObject::connect(Mainform->ui->pushButton, SIGNAL(clicked()), this, SLOT(aboutpushButton_clicked()));
    QObject::connect(Mainform->ui->qd_btn, SIGNAL(clicked()), this, SLOT(qd_btn_clicked()));
    QObject::connect(Mainform->ui->qt_btn, SIGNAL(clicked()), this, SLOT(qt_btn_clicked()));

    if (!last) //载入当前数据库
    {
        ui->tab1->setEnabled(false);
        ui->tab3->setEnabled(false);
        ui->sign_group->setMinimum(1);
        ui->sign_group->setValue(1);
        ui->sign_group->setEnabled(false);
    }
    else if(!alast)
    {
        ahead = userToData(head);
        attendance::savaAttendance(ahead);
        attendance::loadData(ahead);
    }
    if(rememberUid(temp, false))
    {
        uid = temp;
        ui->login_name->setText(QString::fromStdString(uid));
        ui->remUid->setChecked(true);
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_tabWidget_tabBarClicked(int index)
{
    int group = 2;
    char temp[20];
    if(index == 1)
        group = ui->sign_group->value();
    else if(index == 2)
        group = 1;
    randUID(group, temp);
    while (last && !cheakUidInAdvance(head, temp))
        randUID(group, temp);
    string uidtmp(temp);
    QString QUid = QString::fromStdString(uidtmp);
    if(index == 1)
        ui->uid1_lab->setText(QUid);
    else
        ui->uid2_lab->setText(QUid);
    uid = uidtmp;
}

void Widget::on_sign_group_valueChanged(int arg1)
{
    char temp[20];
    group = arg1;
    randUID(group, temp);
    while (last && !cheakUidInAdvance(head, temp))
        randUID(group, temp);
    string uidtmp(temp);
    QString QUid = QString::fromStdString(uidtmp);
    ui->uid1_lab->setText(QUid);
    uid = uidtmp;
}

void Widget::on_sign_btn_clicked()
{
    string pass = ui->sign_pass->text().toStdString(), name = ui->sign_name->text().toStdString();
    if(!pass.size() || !name.size())
    {
        QMessageBox::information(this, "警告", "请输入用户名和密码。");
        return;
    }
    cout << "触发注册按钮，当前last指针："<< last << endl;
    if(!last)
    {
        string t(uid);
        createUser(pass.c_str(), name.c_str(), uid.c_str());
        ui->tab1->setEnabled(true);
        ui->tab3->setEnabled(true);
        ui->sign_group->setMinimum(2);
        ui->sign_group->setValue(2);
        ui->sign_group->setEnabled(true);
        userAccount::loadUserData(head);
        ahead = userToData(head);
        attendance::savaAttendance(ahead);
        attendance::loadData(ahead);
        QMessageBox::information(this, "提示", "管理员帐号注册成功，请保管好UID及密码。");
        ui->login_name->setText(QString::fromStdString(t));
        ui->tab2->setEnabled(false);
    }
    else
    {
        addUser(head, ahead, last, alast, uid.c_str(), name.c_str(), pass.c_str(), ui->sign_group->value());
        QMessageBox::information(this, "提示", "帐号注册成功，请保管好UID及密码。");
        ui->login_name->setText(QString::fromStdString(uid));
    }
    databaseReload(head, ahead, last, alast);
    cout << "触发注册按钮（已重载），当前last指针："<< last << endl;
}

void Widget::on_login_btn_clicked()
{
    char* uidtmp = new char(12);
    string u = ui->login_name->text().toStdString(), p = ui->login_pass->text().toStdString();
    strcpy(uidtmp, u.c_str());
    if(mainLogin(head, u.c_str(), p.c_str()))
    {
        cout << u << endl;
        rememberUid(uidtmp, ui->remUid->isChecked());
        ui->tab2->setEnabled(true);
        target = searchUid(head, uidtmp);
        aTarget = searchUserPtr(ahead, target->uid);
        cout << "ok:" << string(uidtmp) << target->search_Situation() << endl;
        delete[] uidtmp;
        uidtmp = nullptr;
        this->hide();
        Mainform->show();
        Mainform->ui->userName_lab->setText(QString::fromStdString(string(target->uName())));
        Mainform->ui->uid_lab->setText(QString::fromStdString(target->uid));
        Mainform->ui->userGroup_lab->setText(QString::fromStdString(target->search_Situation()));
        Mainform->ui->qd_lab->setText(QString::fromStdString(aTarget->getQd(simpleTime())));
        Mainform->ui->qt_lab->setText(QString::fromStdString(aTarget->getQt(simpleTime())));
        Mainform->ui->qdt_lab->setText(QString::fromStdString(aTarget->getQdTime(simpleTime())));
        Mainform->ui->qtt_lab->setText(QString::fromStdString(aTarget->getQtTime(simpleTime())));
        if(aTarget->getQd(simpleTime()) == "未签到" || aTarget->getQt(simpleTime()) == "已签退")
            Mainform->ui->qt_btn->setEnabled(false);
        if(aTarget->getQd(simpleTime()) == "已签到" && aTarget->getQt(simpleTime()) == "未签退")
            Mainform->ui->qt_btn->setEnabled(true);
        if(aTarget->getQd(simpleTime()) == "已签到")
            Mainform->ui->qd_btn->setEnabled(false);
        else
            Mainform->ui->qd_btn->setEnabled(true);
        if(target->getGroup() == 1)
            Mainform->ui->menutab2->setEnabled(true);
        else
            Mainform->ui->menutab2->setEnabled(false);
    }
    else
        QMessageBox::information(this, "警告", "帐号不存在或密码不匹配。");
}

void Widget::on_remUid_clicked(bool checked)
{
    char uidtmp[12] = "NaN";
    if(!checked && rememberUid(uidtmp, false))
        rememberUid(uidtmp, true);
}

void Widget::aboutpushButton_clicked()
{
    Mainform->hide();
    this->show();
    rememberUid("NaN", false);
    databaseReload(head, ahead, last, alast);
}

void Widget::qd_btn_clicked()
{
    userAttendance(aTarget);
    Mainform->ui->qd_lab->setText(QString::fromStdString(aTarget->getQd(simpleTime())));
    Mainform->ui->qdt_lab->setText(QString::fromStdString(aTarget->getQdTime(simpleTime())));
    attendance::savaAttendance(ahead);
    alast = attendance::loadData(ahead);
    Mainform->ui->qt_btn->setEnabled(true);
    QMessageBox::information(Mainform, "提示", QString::fromStdString("签到成功，签到时间：" + string(nowTime())));
    Mainform->ui->qd_btn->setEnabled(false);
    databaseReload(head, ahead, last, alast);
}

void Widget::qt_btn_clicked()
{
    userBack(aTarget);
    Mainform->ui->qt_lab->setText(QString::fromStdString(aTarget->getQt(simpleTime())));
    Mainform->ui->qtt_lab->setText(QString::fromStdString(aTarget->getQtTime(simpleTime())));
    attendance::savaAttendance(ahead);
    alast = attendance::loadData(ahead);
    QMessageBox::information(Mainform, "提示", QString::fromStdString("签退成功，签退时间：" + string(nowTime())));
    Mainform->ui->qt_btn->setEnabled(false);
    databaseReload(head, ahead, last, alast);
}
