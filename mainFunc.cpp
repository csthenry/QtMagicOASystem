#include "userAccount.h"
#include "userDataFunc.cpp"
#include <iostream>

using namespace std;

//developer:GitHub_CSTHenry(zhengke@bytecho.net)
userAccount *searchUid(userAccount *head, char *id);

void delay(int msec);//毫秒
bool rememberUid(char *uid, bool flag);

void printMenu() {
    cout << "        办公自动化 V1.5       " << endl;
    cout << "===============================" << endl;
    cout << "=         01.账户注册         =" << endl;
    cout << "=        02.管理员申请        =" << endl;
    cout << "=         03.账户登录         =" << endl;
    cout << "===============================" << endl;
    cout << "请输入选项编号进行选择：" << endl;
}

void print_usersMenu(userAccount *head, attendance *ahead, char *uid) {
    userAccount *point;
    point = searchUid(head, uid);
    uHead:
    point->welcomeUser();
    cout << "当前时间：" << nowTime() << endl;
    cout << endl;
    cout << "             用户菜单            " << endl;
    cout << "================================" << endl;
    cout << "=          01.个人信息         =" << endl;
    cout << "=          02.考勤系统         =" << endl;
    cout << "=          03.发起申请         =" << endl;
    cout << "=        04.查看审核进度       =" << endl;
    cout << "================================" << endl;
    cout << "请输入选项编号进行选择：" << endl;
    if (userMenuChoice(head, ahead, point)) {
        userAccount::saveUserData(head);
        ahead->savaAttendance(ahead);
        goto uHead;
    } else
        goto uHead;
}

void print_adminMenu(userAccount *head, attendance *ahead, char *uid);

void userAccount::print_userInf() {
    cout << "    当前用户信息" << endl;
    cout << "====================" << endl;
    cout << "-> UID：" << uid << endl;
    cout << "-> 姓名：" << name << endl;
    cout << "-> 职位：" << search_Situation() << endl;
    cout << "====================" << endl;
}

userAccount *search_userInf(userAccount *p, char *id)//返回对应UID的指针
{//developer:GitHub_CSTHenry(zhengke@bytecho.net)
    userAccount *head = nullptr;
    do {
        if (!strcmp(p->uid, id)) {
            p = p->next;
        } else {
            head = p;
            break;
        }
    } while (p != nullptr);
    return head;
}

void addUser(userAccount *head, attendance *ahead, userAccount *last, attendance *alast, const char* newUID, const char* newName, const char* pass, int newGroup) //需要传入数据库首尾链表的地址,调用loadUserData()后使用
{
    auto *newP = new userAccount();
    newP->signUp(newUID, newName, pass, newGroup);
    last->next = newP;
    userAccount::saveUserData(head); //保存整个链表
    addAttendance(newUID, alast);//更新考勤表
    delete newP;
    newP = nullptr;
    attendance::savaAttendance(ahead);
}

userAccount *createUser(const char* pass, const char* newName, const char* newUID) //创建userData数据表，用于初始化程序，并返回链表头指针
{
    auto *newPtr = new userAccount();//已更新为随机生成UID
    newPtr->signUp(newUID, newName, pass, 1);
    newPtr->next = nullptr;
    userAccount::saveUserData(newPtr); //保存整个链表
    return newPtr;
}

void userAccount::saveUserData(userAccount *head) //保存内存中的整个链表,并覆盖文件./src/userData.dat
{
    ofstream openUserFile("./src/userData.dat", ios::binary | ios::out);
    if (!openUserFile.fail()) {
        do {
            openUserFile.write((const char *) head->uid, sizeof(head->uid));
            openUserFile.write((const char *) head->name, sizeof(head->name));
            openUserFile.write((const char *) head->password, sizeof(head->password));
            openUserFile.write((const char *) &head->group, sizeof(head->group));
            cout << "writing..."<< head->uName() <<endl;
            head = head->next;
        } while (head);
    } else {
        cout << "fault,code:fun_146." << endl;
        return;
    }
    openUserFile.close();
}

userAccount *userAccount::loadUserData(userAccount *head) //将返回链表尾指针，即其next==nullptr，若数据表不存在，返回空指针
{
    //userAccount *head = new userAccount();
    int flag = 0;
    userAccount *temp = head;
    userAccount *last = nullptr;
    ifstream loadUserFile("./src/userData.dat",
                          ios::binary | ios::in); // F:\\VSCode_Projects\\VSCode-C++\\github_oa\\src\\userData.dat
    if (!loadUserFile.fail()) {
        do {
            loadUserFile.read((char *) temp->uid, sizeof(temp->uid));
            loadUserFile.read((char *) temp->name, sizeof(head->name));
            loadUserFile.read((char *) temp->password, sizeof(head->password));
            loadUserFile.read((char *) &temp->group, sizeof(int));
            if (!temp->group) //解决loadUserFile.eof()会多操作一次的问题
            {
                flag = 1;
                last->next = nullptr;
            }
            auto *next = new userAccount();
            if (!flag)
                last = temp;
            temp->next = next;
            temp = temp->next;
        } while (!loadUserFile.eof());
    }//developer:GitHub_CSTHenry(zhengke@bytecho.net)
    else {
        //cout << "fault,code:fun_146." << endl;
        delete[] temp;
        head = nullptr;
        loadUserFile.close();
        return head;
    }
    loadUserFile.close();
    return last;
}

void mainSignup() //主页面注册函数，可以判断userData
{
    auto *ahead = new attendance();
    auto *head = new userAccount();
    userAccount *last = nullptr;
    attendance *alast = nullptr;
    alast = ahead->loadData(ahead);
    if (!(last = head->loadUserData(head))) //载入当前数据库
    {
        cout << "请创建管理员账户（用户组编号：1）：" << endl;
        //createUser();
    } else
        //addUser(head, ahead, last, alast);
    system("CLS");
    cout << "注册完成！返回主菜单。" << endl;
    cout << endl;
    delete head;
}

void newadminApprove() //主页面管理员申请函数
{
    auto *head = new userAccount();
    char apply[200] = "\0", newName[10] = "\0", newUID[12] = "\0", content[200] = "\0";
    randUID(1, newUID);
    while (!cheakUidInAdvance(head, newUID))
        randUID(1, newUID);
    cout << "     请按照提示申请账户" << endl;//已更改为随机生成UID
    cout << "========自动生成UID========" << endl;
    cout << "-> " << newUID << endl;
    cout << "===========================" << endl;
    cout << " -[UID创建完成 妥善保管]-" << endl;
    cout << endl;
    cout << "===========================" << endl;
    cout << "= 请输入姓名：            =" << endl;
    cout << "===========================" << endl;
    cin >> newName;
    cout << "===========================" << endl;
    cout << "= 请输入申请管理员理由：  =" << endl;
    cout << "===========================" << endl;
    cin >> apply;
    cout << "===========================" << endl;
    cout << "= 请输入联系邮箱：        =" << endl;
    cout << "===========================" << endl;
    cin >> content;
    cout << "申请提交完成，审核结果及账号信息会发送至你的邮箱 [" << content << "]" << endl;
    auto *uahead = new approve();
    approve::loadList(uahead);
    addSimpleApp(uahead, newUID, newName, apply, content);
    saveApprove(uahead);
    system("pause");
    system("CLS");
}

bool mainLogin(userAccount* head, const char* loginID, const char* pass) //登录函数，登录失败返回false，登录成功返回true
{
    userAccount *target = head;
    bool flag = false;
    while (target) {
        if (target->cheakUid(loginID) && target->logIn(pass)) {
             flag = true;
             break;
        }
            target = target->next;
        }

        if (!flag)
            return false;
        else {
            return true;
//            switch (target->getGroup()) {
//                case 0:
//                    system("CLS");
//                    cout << '\a' << "UID不存在或密码不匹配，返回主菜单" << endl;
//                    cout << endl;
//                    return false;
//                case 1:
//                    system("CLS");
//                    print_adminMenu(head, ahead, loginID);
//                default:
//                    system("CLS");
//                    print_usersMenu(head, ahead, loginID);
//            }
        }
}

userAccount *searchUid(userAccount *head, char *id) //搜索uid，并返回指针指向相应uid
{
    //userAccount *head = new userAccount();
    userAccount *point = nullptr;
    head->loadUserData(head);
    while (head) {
        if (head->cheakUid(id))
            point = head;
        head = head->next;
    }
    return point;
}

void userAccount::print_userInfSimple() {
    cout << "UID: " << uid << "\t" << left << setw(10) << name << search_Situation() << endl;
}

bool rememberUid(char *uid, bool flag) {
    int i;
    char loadUID[32] = "\0";
    if(!strcmp(uid, "NaN"))
    {
        ofstream savaUidInf("uidInf.ini", ios::out | ios::trunc);
        savaUidInf << uid;
        savaUidInf.close();
    }
    ifstream loadUidInf("uidInf.ini", ios::in);
    if (loadUidInf.fail()) {
        if (!flag)
            return false;
        else {
            ofstream savaUidInf("uidInf.ini", ios::out | ios::trunc);
            savaUidInf << "UID = " << uid;
            savaUidInf.close();
        }
    } else {
        loadUidInf.getline(loadUID, sizeof(loadUID));
        if(!strcmp(loadUID, "NaN"))
        {
            if(flag)
            {
                ofstream savaUidInf("uidInf.ini", ios::out | ios::trunc);
                savaUidInf << "UID = " << uid;
                savaUidInf.close();
                return true;
            }
            return false;
        }
        for (i = 6; loadUID[i]; i++) {
            loadUID[i - 6] = loadUID[i];
            loadUID[i] = '\0';
        }
        strcpy(uid, loadUID);
        return true;
    }
    loadUidInf.close();
    return false;
}

void print_adminMenu(userAccount *head, attendance *ahead, char *uid) {
    userAccount *point;
    point = searchUid(head, uid);
    aHead:
    point->welcomeUser();
    cout << "当前时间：" << nowTime() << endl;
    cout << endl;
    cout << "           管理员菜单           " << endl;
    cout << "===============================" << endl;
    cout << "=         01.个人信息         =" << endl;
    cout << "=         02.用户管理         =" << endl;
    cout << "=    03.创建与管理审批流程    =" << endl;
    cout << "=       04.查看审批队列       =" << endl;
    cout << "=       05.用户考勤状态       =" << endl;
    cout << "===============================" << endl;
    cout << "请输入选项编号进行选择：" << endl;
    if (adminMenuChoice(head, ahead, point)) {
        head->saveUserData(head);
        ahead->savaAttendance(ahead);
        goto aHead;
    } else
        goto aHead;
}

void delay(int msec) {
    clock_t start_time, cur_time;
    start_time = clock();
    do { cur_time = clock(); } while ((cur_time - start_time) < msec);
}

void databaseReload(userAccount *head, attendance *ahead, userAccount *&last, attendance *&alast)
{
    alast = attendance::loadData(ahead);
    last = userAccount::loadUserData(head);
}
