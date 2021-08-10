#include "approve.h"
#include "approveList.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

//developer:GitHub_CSTHenry(zhengke@bytecho.net)
//approveList* createList(char *title, char *tips, bool content);
approveList *appSearch(approveList *aphead, int num);

void addList(approveList *aphead, char *title, char *tips, bool content);

void editApprove(approve *uahead, char *uid);

void saveApprove(approve *uahead);

void saveList(approveList *aphead);

bool deleteList(approveList *aphead, int listNumber);

bool getList(approve *uahead);

bool adminApprove(approve *target, userAccount *head);

bool getUserApprove(userAccount *point, approve *uahead);

void addList(approveList *aphead, char *title, char *tips, bool content) {
    approveList *head = aphead;
    if (aphead->listNum == 0) {
        aphead->listNum += 1;
        aphead->setTitle(title);
        aphead->setTips(tips);
        aphead->isContent = content;
    } else {
        while (aphead->next)
            aphead = aphead->next; //ת��Ϊ����β��ַ
        auto *nextPtr = new approveList();
        nextPtr->listNum = aphead->listNum + 1;
        nextPtr->setTitle(title);
        nextPtr->setTips(tips);
        nextPtr->isContent = content;
        aphead->next = nextPtr;
    }
    saveList(head);
}

void editList(approveList *aphead) {
    int num = 0;
    char title[21] = "\0", tips[100] = "\0", ch = '\0';
    approveList *target = nullptr;
    cout << "��������Ҫ�༭�����̱�ţ�" << endl;
    cin >> num;
    while (!(target = appSearch(aphead, num))) {
        cout << "δ���������ڵ����̣����������룺" << endl;
        cin >> num;
    }
    cout << "���ڱ༭ [" << target->listNum << " " << target->reListTitle() << "] ����" << endl;
    cout << "������������Ŀ���ƣ�10�����ڣ���" << endl;
    cin >> title;
    target->setTitle(title);
    cout << "������������ʾ/ָ����50�����ڣ���" << endl;
    cin >> tips;
    target->setTips(tips);
    cout << "�Ƿ�����������ѡ���y����n�رգ���" << endl;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
        target->isContent = true;
    else
        target->isContent = false;
    cout << "�༭������ɡ�" << endl;
    saveList(aphead);
}

void saveList(approveList *aphead) //./src/appList.dat
{
    ofstream saveList("./src/appList.dat",
                      ios::binary | ios::out); //F:\\VSCode_Projects\\VSCode-C++\\oa\\src\\appList.dat
    while (aphead) {
        saveList.write((char *) &aphead->listNum, sizeof(aphead->listNum));
        saveList.write((char *) aphead->reListTitle(), 21);
        saveList.write((char *) aphead->reListTips(), 100);
        saveList.write((char *) &aphead->isContent, sizeof(aphead->isContent));
        aphead = aphead->next;
    }
    saveList.close();
}

approveList *approveList::loadList(approveList *aphead) {
    //approveList *aphead = new approveList();
    approveList *next = nullptr, *temp = nullptr;
    ifstream loadList("./src/appList.dat", ios::binary | ios::in);
    if (!loadList.fail()) {
        while (!loadList.eof()) {
            loadList.read((char *) &aphead->listNum, sizeof(aphead->listNum));
            loadList.read((char *) aphead->listTitle, sizeof(aphead->listTitle));
            loadList.read((char *) aphead->listTips, sizeof(aphead->listTips));
            loadList.read((char *) &aphead->isContent, sizeof(aphead->isContent));
            if (!aphead->listNum) {
                delete[] aphead;
                aphead = temp;
                aphead->next = nullptr;
                break;
            } else {
                next = new approveList();
                aphead->next = next;
                temp = aphead;
                aphead = next;
            }
        }
        loadList.close();
        return aphead; //βָ��
    } else {
        loadList.close();
        return nullptr; //���ļ�ʧ�ܷ���nullptr
    }
}

bool deleteList(approveList *aphead, int listNumber) //����flase��δ�ҵ���Ӧ����
{
    approveList *temp = nullptr;
    while (aphead) {
        if (listNumber == aphead->listNum)
            break;
        temp = aphead;
        aphead = aphead->next;
    }
    if (!aphead)
        return false;
    else {
        temp->next = aphead->next;
        return true;
    }
}

approveList *appSearch(approveList *aphead, int num) {
    while (aphead) {
        if (num == aphead->listNum)
            break;
        aphead = aphead->next;
    }
    return aphead;
}

void addApprove(approve *uahead, approveList *aphead, char *uid, char *uName, char *apply, char *content) {
    approve *head = uahead;
    if (uahead->listNum == 0) {
        uahead->listNum = aphead->listNum;
        strcpy(uahead->Uid, uid);
        strcpy(uahead->name, uName);
        uahead->setTitle(aphead->reListTitle());
        uahead->setContent(content);
        uahead->setApply(apply);
    } else {
        while (uahead->next)
            uahead = uahead->next; //ת��Ϊ����β��ַ
        auto *nextPtr = new approve();
        nextPtr->listNum = aphead->listNum;
        strcpy(nextPtr->Uid, uid);
        strcpy(nextPtr->name, uName);
        nextPtr->setTitle(aphead->reListTitle());
        nextPtr->setContent(content);
        nextPtr->setApply(apply);
        uahead->next = nextPtr;
    }
    saveApprove(head);
}

void addSimpleApp(approve *uahead, char *uid, char *uName, char *apply, char *content) {
    approve *head = uahead;
    if (uahead->listNum == 0) {
        uahead->listNum = 1024;//����Ա�������Ĭ��Ϊ1024
        strcpy(uahead->Uid, uid);
        strcpy(uahead->name, uName);
        uahead->setTitle("��ҳ����Ա����");
        uahead->setContent(content);
        uahead->setApply(apply);
    } else {
        while (uahead->next)
            uahead = uahead->next; //ת��Ϊ����β��ַ
        auto *nextPtr = new approve();
        nextPtr->listNum = 1024;
        strcpy(nextPtr->Uid, uid);
        strcpy(nextPtr->name, uName);
        nextPtr->setTitle("��ҳ����Ա����");
        nextPtr->setContent(content);
        nextPtr->setApply(apply);
        uahead->next = nextPtr;
    }
    saveApprove(head);
}

void addStaticApp(approve *uahead, userAccount *target, const int listNum, const char *title, const char *apply,
                  const char *content) {
    approve *head = uahead;
    if (uahead->listNum == 0) {
        uahead->listNum = listNum;//����Ա�������Ĭ��Ϊ1024,UID������Ϊ1025���˺�ע��������Ϊ1026
        strcpy(uahead->Uid, target->uid);
        strcpy(uahead->name, target->uName());
        uahead->setTitle(title);
        uahead->setContent(content);
        uahead->setApply(apply);
    } else {
        while (uahead->next)
            uahead = uahead->next; //ת��Ϊ����β��ַ
        auto *nextPtr = new approve();
        nextPtr->listNum = listNum;
        strcpy(nextPtr->Uid, target->uid);
        strcpy(nextPtr->name, target->uName());
        nextPtr->setTitle(title);
        nextPtr->setContent(content);
        nextPtr->setApply(apply);
        uahead->next = nextPtr;
    }
    saveApprove(head);
}

void saveApprove(approve *uahead) //./src/userApprove.dat
{
    ofstream saveList("./src/userApprove.dat",
                      ios::binary | ios::out); //F:\\VSCode_Projects\\VSCode-C++\\oa\\src\\userApprove.dat
    while (uahead) {
        saveList.write((char *) uahead->Uid, sizeof(uahead->Uid));
        saveList.write((char *) uahead->name, sizeof(uahead->name));
        saveList.write((char *) &uahead->listNum, sizeof(uahead->listNum));
        saveList.write((char *) &uahead->statu, sizeof(uahead->statu));
        saveList.write((char *) &uahead->flag, sizeof(uahead->flag));
        saveList.write((char *) uahead->reContent(), 200);
        saveList.write((char *) uahead->reTitle(), 21);
        saveList.write((char *) uahead->reApply(), 200);
        saveList.write((char *) uahead->reReply(), 101);
        uahead = uahead->next;
    }
    saveList.close();
}

approve *approve::loadList(approve *uahead) {
    approve *next = nullptr, *temp = nullptr;
    ifstream loadList("./src/userApprove.dat", ios::binary | ios::in);
    if (!loadList.fail()) {
        while (!loadList.eof()) {
            loadList.read((char *) uahead->Uid, sizeof(uahead->Uid));
            loadList.read((char *) uahead->name, sizeof(uahead->name));
            loadList.read((char *) &uahead->listNum, sizeof(uahead->listNum));
            loadList.read((char *) &uahead->statu, sizeof(uahead->statu));
            loadList.read((char *) &uahead->flag, sizeof(uahead->flag));
            loadList.read((char *) uahead->content, sizeof(uahead->content));
            loadList.read((char *) uahead->title, sizeof(uahead->title));
            loadList.read((char *) uahead->apply, sizeof(uahead->apply));
            loadList.read((char *) uahead->reply, sizeof(uahead->reply));
            if (!uahead->listNum) {
                delete[] uahead;
                uahead = temp;
                uahead->next = nullptr;
                break;
            } else {
                next = new approve();
                uahead->next = next;
                temp = uahead;
                uahead = next;
            }
        }
        loadList.close();
        return uahead; //βָ��
    } else {
        loadList.close();
        return nullptr; //���ļ�ʧ�ܷ���nullptr
    }
}

bool getList(approve *uahead) {
    bool flag = false;
    cout << endl;
    while (uahead) {
        if (!uahead->listNum)
            break;
        if (uahead->statu) {
            uahead = uahead->next;
            continue;
        }
        cout << "[" << left << setw(8) << uahead->Uid << "] " << setw(16) << setfill(' ') << uahead->name
             << "[" << right << setfill('0') << setw(4) << uahead->listNum << "]" << left << setw(20) << setfill(' ')
             << uahead->reTitle()
             << "��δ��ˡ�" << endl;
        flag = true;
        uahead = uahead->next;
    }
    if (!flag) {
        cout << "������Ҫ��������롣" << endl;
        return false;
    }
    return true;
}

bool adminApprove(approve *target, userAccount *head) {
    userAccount *temp = head, *last = head;
    while (last->next)//��ȡβ��ַ
        last = last->next;
    char ch = 'n', re[101] = "\0";
    cout << endl;
    system("CLS");
    cout << "������� [" << target->name << " " << target->reTitle() << "]" << endl;
    cout << endl;
    if (strlen(target->reContent())) {
        cout << "[��������]" << endl;
        cout << target->reContent() << endl;
    }
    cout << endl;
    cout << "[��������]" << endl;
    cout << target->reApply() << endl;
    cout << endl;
    if(target->listNum == 1026)//�û�ע�����
        cout << "ע�⣺ͨ�������ζ���˺� [" << target->Uid << "] ���ݽ���ȫ������������������" << endl;
    cout << "����y ͨ����ˣ�����n �ܾ�ͨ����" << endl;
    cin >> ch;
    if (ch == 'Y' || ch == 'y')
        target->flag = true;
    cout << "��������������50�����ڣ���" << endl;
    cin >> re;
    target->setReply(re);
    target->statu = true;
    if (target->listNum == 1024 && (ch == 'y' || ch == 'Y'))//��ҳ����Ա���
    {
        char pass[17]{};
        auto *nextptr = new userAccount();
        cout << "��Ϊ���˻����ó�ʼ���룺" << endl;
        cin >> pass;
        nextptr->signUp(target->Uid, target->name, pass, 1);
        last->next = nextptr;
        nextptr->next = nullptr;
        userAccount::saveUserData(temp);
        system("CLS");
        cout << "��������Ա->[" << target->Uid << "] " << target->name << endl;
        cout << "��ʼ����Ϊ->" << pass << endl;
        cout << "�뽫������Ϣ���������� [" << target->reContent() << "]" << endl;
        return true;
    }
    if (target->listNum == 1025 && (ch == 'y' || ch == 'Y'))//UID���
    {
        while(!head->cheakUid(target->Uid))
            head = head->next;
        strcpy(target->Uid, target->reContent());
        strcpy(head->uid,target->reContent());
        return true;
    }
    if (target->listNum == 1026 && (ch == 'y' || ch == 'Y'))
        return true;
    return false;
}

bool getUserApprove(userAccount *point, approve *uahead) {
    system("CLS");
    int num = 0;
    bool flag = false;
    char ch = 'n';
    cout << "��ǰ�������ȣ�" << endl;
    cout << endl;
    approve *temp = uahead;
    while (uahead) {
        if (!strcmp(point->uid, uahead->Uid)) {
            flag = true;
            cout << "[������]-> "
                 << "[" << right << setw(4) << setfill('0') << uahead->listNum << "]" << left << setw(18)
                 << setfill(' ') << uahead->reTitle() << " [���״̬]-> ";
            uahead->cheakStatu();
        }
        uahead = uahead->next;
    }
    if (!flag) {
        cout << endl;
        cout << "���޴��������룬�����û��˵�" << endl;
        system("pause");
        system("CLS");
        return false;
    }
    uahead = temp;
    cout << endl;
    cout << "����y �鿴������飬����z �༭�������ύδ��˻򲵻ص����룬����n �����û��˵���" << endl;
    cin >> ch;
    if (!(ch == 'y' || ch == 'Y' || ch == 'z' || ch == 'Z')) {
        system("CLS");
        return false;
    }
    if (ch == 'z' || ch == 'Z') {
        return true;
    }
    cout << "������������Ų鿴������飺" << endl;
    re:
    cin >> num;
    uahead = temp;
    while (uahead) {
        if (!strcmp(point->uid, uahead->Uid) && num == uahead->listNum)
            break;
        uahead = uahead->next;
    }
    if (!uahead) {
        cout << "�˱�Ŷ�Ӧ����������ڣ����������룺" << endl;
        goto re;
    }
    system("CLS");
    cout << "���ڲ鿴 [" << uahead->listNum << "]" << uahead->reTitle() << " ������飺" << endl;
    cout << endl;
    cout << "[��˽��]->";
    uahead->cheakStatu();
    if (strlen(uahead->reContent())) {
        cout << endl;
        cout << "[��������]" << endl;
        cout << uahead->reContent() << endl;
    }
    cout << endl;
    cout << "[��������]" << endl;
    cout << uahead->reApply() << endl;
    cout << endl;
    cout << "[������]" << endl;
    if (uahead->statu)
        cout << uahead->reReply() << endl;
    else
        cout << "������������" << endl;
    cout << endl;
    system("pause");
    system("CLS");
    return false;
}

void editApprove(approve *uahead, char *uid) {
    int num;
    approve *head = uahead;
    char content[200] = "\0", apply[200] = "\0";
    cout << "���������˻򱻲��ص��������Խ��б༭��" << endl;
    re:
    uahead = head;
    cin >> num;
    while (uahead) {
        if (!strcmp(uahead->Uid, uid) && uahead->listNum == num && (!uahead->statu || !uahead->flag)) {
            system("CLS");
            cout << "���ڱ༭���� [" << uahead->reTitle() << "] :" << endl;
            if (strlen(uahead->reContent())) {
                cout << "�������������ݣ�100�����ڣ���" << endl;
                cin >> content;
            }
            cout << "�������������ɣ�100�����ڣ���" << endl;
            cin >> apply;
            cout << "�༭�ɹ������������뷵���û��˵��鿴��" << endl;
            uahead->setContent(content);
            uahead->setApply(apply);
            uahead->statu = false;
            saveApprove(head);
            system("pause");
            system("CLS");
            return;
        } else
            uahead = uahead->next;
    }
    if (!uahead) {
        cout << "����������Ų����ڻ�����༭Ҫ�����������룺" << endl;
        goto re;
    }
}
