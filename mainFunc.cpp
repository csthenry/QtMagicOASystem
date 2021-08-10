#include "userAccount.h"
#include "userDataFunc.cpp"
#include <iostream>
#include <conio.h>

using namespace std;

//developer:GitHub_CSTHenry(zhengke@bytecho.net)
userAccount *searchUid(userAccount *head, char *id);

void delay(int msec);//����
bool rememberUid(char *uid, char rememberCh);

void printMenu() {
    cout << "        �칫�Զ��� V1.5       " << endl;
    cout << "===============================" << endl;
    cout << "=         01.�˻�ע��         =" << endl;
    cout << "=        02.����Ա����        =" << endl;
    cout << "=         03.�˻���¼         =" << endl;
    cout << "===============================" << endl;
    cout << "������ѡ���Ž���ѡ��" << endl;
}

[[noreturn]] void print_usersMenu(userAccount *head, attendance *ahead, char *uid) {
    userAccount *point;
    point = searchUid(head, uid);
    uHead:
    point->welcomeUser();
    cout << "��ǰʱ�䣺" << nowTime() << endl;
    cout << endl;
    cout << "             �û��˵�            " << endl;
    cout << "================================" << endl;
    cout << "=          01.������Ϣ         =" << endl;
    cout << "=          02.����ϵͳ         =" << endl;
    cout << "=          03.��������         =" << endl;
    cout << "=        04.�鿴��˽���       =" << endl;
    cout << "================================" << endl;
    cout << "������ѡ���Ž���ѡ��" << endl;
    if (userMenuChoice(head, ahead, point)) {
        userAccount::saveUserData(head);
        ahead->savaAttendance(ahead);
        goto uHead;
    } else
        goto uHead;
}

[[noreturn]] void print_adminMenu(userAccount *head, attendance *ahead, char *uid);

void userAccount::print_userInf() {
    cout << "    ��ǰ�û���Ϣ" << endl;
    cout << "====================" << endl;
    cout << "-> UID��" << uid << endl;
    cout << "-> ������" << name << endl;
    cout << "-> ְλ��" << search_Situation() << endl;
    cout << "====================" << endl;
}

userAccount *search_userInf(userAccount *p, char *id)//���ض�ӦUID��ָ��
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

void
addUser(userAccount *head, attendance *ahead, userAccount *last, attendance *alast) //��Ҫ�������ݿ���β����ĵ�ַ,����loadUserData()��ʹ��
{
    int newGroup;
    char pass[17] = "\0", newName[10] = "\0", newUID[12] = "\0";
    auto *newP = new userAccount();
    cout << "     �밴����ʾ�����˻�" << endl;//�Ѹ���Ϊ�������UID
    cout << "===========================" << endl;
    cout << "= �������û�����(2-3)�� =" << endl;
    cout << "===========================" << endl;
    cin >> newGroup;
    if (newGroup != 2 && newGroup != 3) {
        cout << "���û��鲻���ڣ����������룺" << endl;
        cin >> newGroup;
    }
    randUID(newGroup, newUID);
    while (!cheakUidInAdvance(head, newUID))
        randUID(newGroup, newUID);
    cout << "========�Զ�����UID========" << endl;
    cout << "-> " << newUID << endl;
    cout << "===========================" << endl;
    cout << " -[UID������� ���Ʊ���]-" << endl;
    cout << endl;
    cout << "===========================" << endl;
    cout << "= ������������            =" << endl;
    cout << "===========================" << endl;
    cin >> newName;
    cout << "===========================" << endl;
    cout << "= �봴�����루<=16λ����  =" << endl;
    cout << "===========================" << endl;
    cin >> pass;
    newP->signUp(newUID, newName, pass, newGroup);
    last->next = newP;
    userAccount::saveUserData(head); //������������
    addAttendance(newUID, alast);//���¿��ڱ�
    attendance::savaAttendance(ahead);
}

userAccount *createUser() //����userData���ݱ����ڳ�ʼ�����򣬲���������ͷָ��
{
    int newGroup = 1;
    char pass[17] = "\0", newName[10] = "\0", newUID[12] = "\0";
    auto *newP = new userAccount();//�Ѹ���Ϊ�������UID
    randUID(newGroup, newUID);
    cout << "    �밴����ʾ��������Ա�˻�" << endl;
    cout << endl;
    cout << "========�Զ�����UID========" << endl;
    cout << "-> " << newUID << endl;
    cout << "===========================" << endl;
    cout << " -[UID������� ���Ʊ���]-" << endl;
    cout << endl;
    cout << "=============================" << endl;//UID�Զ�����
    cout << "= ������������              =" << endl;
    cout << "=============================" << endl;
    cin >> newName;
    cout << "=============================" << endl;
    cout << "= �봴�����루<=16λ����    =" << endl;
    cout << "=============================" << endl;
    cin >> pass;
    newP->signUp(newUID, newName, pass, newGroup);
    newP->next = nullptr;
    userAccount::saveUserData(newP); //������������
    return newP;
}

void userAccount::saveUserData(userAccount *head) //�����ڴ��е���������,�������ļ�./src/userData.dat
{
    ofstream openUserFile("./src/userData.dat", ios::binary | ios::out);
    if (!openUserFile.fail()) {
        do {
            openUserFile.write((const char *) head->uid, sizeof(head->uid));
            openUserFile.write((const char *) head->name, sizeof(head->name));
            openUserFile.write((const char *) head->password, sizeof(head->password));
            openUserFile.write((const char *) &head->group, sizeof(head->group));
            head = head->next;
        } while (head);
    } else {
        cout << "fault,code:fun_146." << endl;
        return;
    }
    openUserFile.close();
}

userAccount *userAccount::loadUserData(userAccount *head) //����������βָ�룬����next==nullptr�������ݱ����ڣ����ؿ�ָ��
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
            if (!temp->group) //���loadUserFile.eof()������һ�ε�����
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

void mainSignup() //��ҳ��ע�ắ���������ж�userData
{
    auto *ahead = new attendance();
    auto *head = new userAccount();
    userAccount *last = nullptr;
    attendance *alast = nullptr;
    alast = ahead->loadData(ahead);
    if (!(last = head->loadUserData(head))) //���뵱ǰ���ݿ�
    {
        cout << "�봴������Ա�˻����û����ţ�1����" << endl;
        createUser();
    } else
        addUser(head, ahead, last, alast);
    system("CLS");
    cout << "ע����ɣ��������˵���" << endl;
    cout << endl;
    delete head;
}

void newadminApprove() //��ҳ�����Ա���뺯��
{
    auto *head = new userAccount();
    char apply[200] = "\0", newName[10] = "\0", newUID[12] = "\0", content[200] = "\0";
    randUID(1, newUID);
    while (!cheakUidInAdvance(head, newUID))
        randUID(1, newUID);
    cout << "     �밴����ʾ�����˻�" << endl;//�Ѹ���Ϊ�������UID
    cout << "========�Զ�����UID========" << endl;
    cout << "-> " << newUID << endl;
    cout << "===========================" << endl;
    cout << " -[UID������� ���Ʊ���]-" << endl;
    cout << endl;
    cout << "===========================" << endl;
    cout << "= ������������            =" << endl;
    cout << "===========================" << endl;
    cin >> newName;
    cout << "===========================" << endl;
    cout << "= �������������Ա���ɣ�  =" << endl;
    cout << "===========================" << endl;
    cin >> apply;
    cout << "===========================" << endl;
    cout << "= ��������ϵ���䣺        =" << endl;
    cout << "===========================" << endl;
    cin >> content;
    cout << "�����ύ��ɣ���˽�����˺���Ϣ�ᷢ����������� [" << content << "]" << endl;
    auto *uahead = new approve();
    approve::loadList(uahead);
    addSimpleApp(uahead, newUID, newName, apply, content);
    saveApprove(uahead);
    system("pause");
    system("CLS");
}

bool mainLogin() //��¼��������¼ʧ�ܷ���false����¼�ɹ�����true
{
    int index=0;
    auto *head = new userAccount();
    auto *ahead = new attendance();
    userAccount *target = head;
    attendance *aTarget = ahead;
    char loginID[12];
    int flag = 0;
    char pass[17], rememberCh = 'n';
    if (!target->loadUserData(target)) //���뵱ǰ���ݿ�
    {
        cout << "δ���������ݱ�����ע���˻���" << endl;
        cout << endl;
        return false;
    } else {
        cout << " ��¼ϵͳ������������UID������" << endl;
        if (!rememberUid(loginID, 'n')) {
            cout << "===============================" << endl;
            cout << "= ������UID��                 =" << endl;
            cout << "===============================" << endl;
            cin >> loginID;
        } else {
            cout << " ɾ��uidInf.ini�Ե�¼�����˻�" << endl;
            cout << "=========�ѻ�ȡ���UID=========" << endl;
            cout << "-> " << loginID << endl;
            cout << "===============================" << endl;
            cout << endl;
        }
        cout << "===============================" << endl;
        cout << "= ���������루<=16λ����      =" << endl;
        cout << "===============================" << endl;
        while (true)
        {
            char ch;
            ch = (char)getch();
            if (ch == 8) //�˸��
            {
                if (index)
                {
                    cout << char(8) << " " << char(8);//backspace��ASCIIΪ8
                    index--;
                }
            }
            else if (ch == 13) //�س���
            {
                pass[index] = '\0';
                cout << endl;
                break;
            }
            else
            {
                cout << "*";
                pass[index++] = ch;
            }
        }
        system("CLS");
        cout << "               ����¼�С�" << endl;
        int temp = 0;
        for (int i = 0; i < 6; i++) {
            if (!temp)
                for (int j = 0; j < 9; j++) {
                    delay(30);
                    cout << ">";
                }
            if (temp == 1)
                for (int j = 0; j < 5; j++) {
                    delay(50);
                    cout << ">";
                }
            if (temp == 2) {
                cout << "Loading";
                for (int j = 0; j < 10; j++) {
                    delay(70);
                    cout << ">";
                }
            }
            if (temp == 3)
                for (int j = 0; j < 4; j++) {
                    delay(80);
                    cout << ">";
                }
            cout << ">";
            temp++;
            delay(250);
        }
        cout << endl;
        while (target) {
            if (target->cheakUid(loginID) && target->logIn(pass)) {
                flag = 1;
                break;
            }
            target = target->next;
        }
        if (!flag) {
            system("CLS");
            cout << '\a' << "UID�����ڻ����벻ƥ�䣬�������˵�" << endl;
            cout << endl;
            return false;
        } else {
            if (!aTarget->loadData(aTarget))//��ʼ������ϵͳ,aheadΪ���ڱ�ͷָ��
            {
                ahead = aTarget = userToData(head);
                aTarget->savaAttendance(aTarget);
                ahead->loadData(ahead);
            } else {
                ahead = new attendance();
                ahead->loadData(ahead);//����βָ�룬����ͷָ��
            }
            if (!rememberUid(loginID, 'n')) {
                cout << "��ʾ����(y)��(n)���浱ǰUID [" << loginID << "] �Ա��´ε�¼��" << endl;
                cout << "���� \"y\" ���� \"n\" " << endl;
                cin >> rememberCh;
                rememberUid(loginID, rememberCh);
                if (rememberCh == 'y') {
                    cout << "UID������ɣ��´ε�¼�Զ���ȡ��" << endl;
                    cout << "����Ҫ��¼�����˻�����ɾ����Ŀ¼�µ�uidInf.ini��" << endl;
                    cout << endl;
                    system("pause");
                }
            }
            switch (target->getGroup()) {
                case 0:
                    system("CLS");
                    cout << '\a' << "UID�����ڻ����벻ƥ�䣬�������˵�" << endl;
                    cout << endl;
                    return false;
                case 1:
                    system("CLS");
                    print_adminMenu(head, ahead, loginID);
                default:
                    system("CLS");
                    print_usersMenu(head, ahead, loginID);
            }
        }
    }
}//developer:GitHub_CSTHenry(zhengke@bytecho.net)
userAccount *searchUid(userAccount *head, char *id) //����uid��������ָ��ָ����Ӧuid
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

bool rememberUid(char *uid, char rememberCh) {
    int i;
    char loadUID[32] = "\0";
    ifstream loadUidInf("uidInf.ini", ios::in);
    if (loadUidInf.fail()) {
        if (rememberCh != 'y')
            return false;
        else {
            ofstream savaUidInf("uidInf.ini", ios::out | ios::trunc);
            savaUidInf << "UID = " << uid;
            savaUidInf.close();
        }
    } else {
        loadUidInf.getline(loadUID, sizeof(loadUID));
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

[[noreturn]] void print_adminMenu(userAccount *head, attendance *ahead, char *uid) {
    userAccount *point;
    point = searchUid(head, uid);
    aHead:
    point->welcomeUser();
    cout << "��ǰʱ�䣺" << nowTime() << endl;
    cout << endl;
    cout << "           ����Ա�˵�           " << endl;
    cout << "===============================" << endl;
    cout << "=         01.������Ϣ         =" << endl;
    cout << "=         02.�û�����         =" << endl;
    cout << "=    03.�����������������    =" << endl;
    cout << "=       04.�鿴��������       =" << endl;
    cout << "=       05.�û�����״̬       =" << endl;
    cout << "===============================" << endl;
    cout << "������ѡ���Ž���ѡ��" << endl;
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
