#include "appoveFunc.cpp"
#include "attendanceFunc.cpp"
#include <ctime>
#include <random>
#include <iostream>

using namespace std;

//developer:GitHub_CSTHenry(zhengke@bytecho.net)
void randUID(int group, char *newUid);

void userDataChange(userAccount *head, userAccount *point);

bool userMenuChoice1(userAccount *head, userAccount *point);

bool userMenuChoice2(attendance *apoint);

bool userMenuChoice3(userAccount *head, userAccount *point);

bool userMenuChoice4(userAccount *point);

bool cheakUidInAdvance(userAccount *head, char *id); //���ظ�UID����TRUE
void deleteUser(userAccount *head, attendance *ahead, char *uid);

bool adminMenuChoice2(userAccount *head, attendance *ahead, userAccount *point);

bool adminMenuChoice3();

bool adminMenuChoice4(userAccount *head, attendance *ahead);

bool adminMenuChoice5(userAccount *head, attendance *ahead, attendance *apoint);

void adminUserDataChange(userAccount *head, userAccount *target);

bool adminMenuChoice(userAccount *head, attendance *ahead, userAccount *point); //����true��ʾ������������޸ģ�false����ֱ�ӷ���
void uidApprove(userAccount *head, userAccount *target);

bool deleteApp(userAccount *head, userAccount *target);

bool userMenuChoice(userAccount *head, attendance *ahead, userAccount *point)   //����true��ʾ������������޸ģ�false����ֱ�ӷ���
{
    cin.clear();
    cin.sync();
    int ch = 0;
    cin >> ch;
    while (!(ch >= 1 && ch <= 4)) {
        cout << "ѡ����ڣ����������룺" << endl;
        cin >> ch;
    }
    attendance *apoint = searchUserAttendance(ahead, point->uid);
    switch (ch) {
        case 1:
            if (userMenuChoice1(head, point))
                return true;
            else
                return false;
        case 2:
            if (userMenuChoice2(apoint))
                return true;
            else
                return false;
        case 3:
            if (userMenuChoice3(head, point))
                return true;
            else
                return false;
        default:
            if (userMenuChoice4(point))
                return true;
            else
                return false;
    }
}

bool adminMenuChoice(userAccount *head, attendance *ahead, userAccount *point) {
    cin.clear();
    cin.sync();
    int ch = 0;
    cin >> ch;
    attendance *apoint = searchUserAttendance(ahead, point->uid);
    while (!(ch >= 1 && ch <= 5)) {
        cout << "ѡ����ڣ����������룺" << endl;
        cin >> ch;
    }
    switch (ch) {
        case 1:
            if (userMenuChoice1(head, point))
                return true;
            else
                return false;
        case 2:
            if (adminMenuChoice2(head, ahead, point))
                return true;
            else
                return false;
        case 3:
            if (adminMenuChoice3())
                return true;
            else
                return false;
        case 4:
            if (adminMenuChoice4(head, ahead))
                return true;
            else
                return false;
        default:
            if (adminMenuChoice5(head, ahead, apoint))
                return true;
            else
                return false;
    }
}

bool userMenuChoice1(userAccount *head, userAccount *point) {
    system("CLS");
    cin.clear();
    cin.sync();
    point->welcomeUser();
    cout << "��ĸ�����Ϣ���£�" << endl;
    point->print_userInf();
    int uch = 0;
    cout << endl;
    cout << "����1 ���ĸ�����Ϣ������2 ���ظ��˲˵���" << endl;
    cin >> uch;
    while (uch != 1 && uch != 2) {
        cout << "ѡ����ڣ����������룺" << endl;
        cin >> uch;
    }
    if (uch == 1) {
        userDataChange(head, point);
        cout << "��Ϣ���³ɹ��������û��˵���" << endl;
        system("pause");
        system("CLS");
        return true;
    } else {
        system("CLS");
        return false;
    }
}

bool userMenuChoice2(attendance *apoint) {
    int ch = 0;
    system("CLS");
    cout << "��ǰ�û�������Ϣ��" << endl;
    cout << endl;
    apoint->printInf(simpleTime()); //������տ�����Ϣ����չ�����Ϣ
    cout << endl;
    cout << "����1 ǩ��������2 ǩ�ˣ�����3 ���ظ��˲˵���" << endl;
    cin >> ch;
    if (ch == 1) {
        if (strlen(apoint->getAttendanceTime())) {
            cout << "�����ظ�ǩ����" << endl;
            system("pause");
            system("CLS");
            return false;
        } else {
            userAttendance(apoint);
            cout << "ǩ���ɹ���ǩ��ʱ�䣺" << nowTime() << endl;
            system("pause");
            system("CLS");
            return true;
        }
    } else if (ch == 2) {
        if (!strcmp(apoint->getSimpleTime(), simpleTime())) //�жϵ����Ƿ�ǩ��->ǩ������
        {
            if (strlen(apoint->getBackTime())) {
                cout << "�����ظ�ǩ�ˡ�" << endl;
                system("pause");
                system("CLS");
                return false;
            } else {
                userBack(apoint);
                cout << "ǩ�˳ɹ���ǩ��ʱ�䣺" << nowTime() << endl;
                system("pause");
                system("CLS");
                return true;
            }
        } else {
            cout << "��ǩ�����ٽ���ǩ�ˡ�" << endl;
            system("pause");
            system("CLS");
            return false;
        }
    } else {
        system("CLS");
        return false;
    }
}

bool userMenuChoice3(userAccount *head, userAccount *point) {
    system("CLS");
    char ch = 'n';
    int num = 0;
    char content[200] = "\0", apply[200] = "\0";
    auto *aphead = new approveList();
    auto *uahead = new approve();
    approve *cheak = uahead;
    approveList *temp = aphead;
    approve::loadList(uahead);
    approveList::loadList(aphead);
    cout << "����������Ŀ��" << endl;
    cout << endl;
    cout << "[���]"
         << "\t"
         << "[������Ŀ]"
         << "\t"
         << "[�Ƿ���д��������]" << endl;
    cout << left << "1025" << "\t" << setw(16) << "������UID" << "const" << endl;
    cout << left << "1026" << "\t" << setw(16) << "����ע���˻�" << "const" << endl;
    while (aphead) {
        cout << right << setw(4) << setfill('0') << aphead->listNum << "\t" << setw(16) << setfill(' ') << left
             << aphead->reListTitle();
        if (aphead->isContent)
            cout << "��" << endl;
        else
            cout << "��" << endl;
        aphead = aphead->next;
    }
    aphead = temp;
    cout << endl;
    cout << "����y �����µ����룬����n �����û��˵���" << endl;
    cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        cout << "��������Ҫ�������Ŀ��ţ�" << endl;
        re:
        cin >> num;
        while (aphead) {
            if (num == aphead->listNum)
                break;
            aphead = aphead->next;
        }
        if (num == 1025) {
            while (cheak->next) {
                if (cheak->listNum == num && !strcmp(cheak->Uid, point->uid) && (!cheak->statu || !cheak->flag)) {
                    cout << "�����ظ�����ͬһ��δ��˵���Ŀ������ϵ����Ա��ʱ������" << endl;
                    cout << "���δͨ������Ŀ��ǰ����˽���ҳ��༭�������ύ��" << endl;
                    system("pause");
                    system("CLS");
                    return false;
                }
                cheak = cheak->next;
            }
            uidApprove(head, point);
            cout << "����ɹ�����������뷵���û��˵��鿴��" << endl;
            system("pause");
            system("CLS");
            return true;
        }
        if (num == 1026) {
            while (cheak->next) {
                if (cheak->listNum == num && !strcmp(cheak->Uid, point->uid) && (!cheak->statu || !cheak->flag)) {
                    cout << "�����ظ�����ͬһ��δ��˵���Ŀ������ϵ����Ա��ʱ������" << endl;
                    cout << "���δͨ������Ŀ��ǰ����˽���ҳ��༭�������ύ��" << endl;
                    system("pause");
                    system("CLS");
                    return false;
                }
                cheak = cheak->next;
            }
            if (deleteApp(head, point)) {
                cout << "����ɹ�����������뷵���û��˵��鿴��" << endl;
                system("pause");
                system("CLS");
            }
            return true;
        }
        while (!aphead) {
            cout << "�ñ�Ų����ڣ����������룺" << endl;
            goto re;
        }
        while (cheak) {
            if (cheak->listNum == num && !strcmp(cheak->Uid, point->uid) && (!cheak->statu || !cheak->flag)) {
                cout << "�����ظ�����ͬһ��δ��˵���Ŀ������ϵ����Ա��ʱ������" << endl;
                cout << "���δͨ������Ŀ��ǰ����˽���ҳ��༭�������ύ��" << endl;
                system("pause");
                system("CLS");
                return false;
            }
            cheak = cheak->next;
        }
        system("CLS");
        cout << "�������� [" << aphead->reListTitle() << "] :" << endl;
        cout << "����˵����" << aphead->reListTips() << endl;
        if (aphead->isContent) {
            cout << "�������������ݣ�100�����ڣ���" << endl;
            cin >> content;
        }
        cout << "�������������ɣ�100�����ڣ���" << endl;
        cin >> apply;
        addApprove(uahead, aphead, point->uid, point->uName(), apply, content);
        cout << "����ɹ�����������뷵���û��˵��鿴��" << endl;
        system("pause");
        system("CLS");
    } else {
        system("CLS");
        return false;
    }
    return true;
}

bool userMenuChoice4(userAccount *point) {
    auto *uahead = new approve();
    approve::loadList(uahead);
    if (getUserApprove(point, uahead))
        editApprove(uahead, point->uid);
    return true;
}

bool adminMenuChoice2(userAccount *head, attendance *ahead, userAccount *point) {
    re:
    cin.clear();
    cin.sync();
    int ch = 0, flag = 0;
    char uid[12] = "\0";
    userAccount *target = head;
    system("CLS");
    cout << "�û��б�UID ���� ְλ����" << endl;
    while (target) {
        if (flag)
            target->print_userInfSimple();
        target = target->next;
        flag++;
    }
    cout << endl;
    cout << "����1 �༭�û���Ϣ������2 ע���û��˺ţ�����3 ���ع���Ա�˵���" << endl;
    cin >> ch;
    while (ch != 1 && ch != 2 && ch != 3) {
        cout << "ѡ����ڣ����������룺";
        cin >> ch;
    }
    if (ch == 1) { //developer:GitHub_CSTHenry(zhengke@bytecho.net)
        cout << "��������Ҫ�༭���û�UID��" << endl;
        recin:
        cin >> uid;
        target = head;
        while (target) //��targetָ����Ҫ�༭���û�����
        {
            if (target->cheakUid(uid))
                break;
            target = target->next;
        }
        if (target)
            adminUserDataChange(head, target);
        else {
            cout << "UID��" << uid << "�����ڣ����������룺" << endl;
            goto recin;
        }
        return true;
    } else if (ch == 2) {
        cout << "��������Ҫע�����û�UID��������������" << endl;
        recin2:
        cin >> uid;
        while (!strcmp(uid, head->uid)) {
            cout << '\a' << "��Ȩʧ�ܣ���ֹע��������Ա�˻������������룺" << endl;
            cin >> uid;
        }
        target = head;
        if (!strcmp(uid, point->uid)) {
            cout << "���棺������ע���Լ��Ĺ���Ա�˻���ע���ɹ�����������������ݣ�" << endl;
            cout << "�����룺\"����֪����ȷ��ע���ҵĹ���Ա�˻�\"�����ע����" << endl;
            string entrance;
            cin >> entrance;
            if (entrance != "����֪����ȷ��ע���ҵĹ���Ա�˻�") {
                cout << "������֤ʧ�ܣ������û�����˵���" << endl;
                system("pause");
                system("CLS");
                goto re;
            }
        }
        while (target) //��targetָ����Ҫ�༭���û�����
        {
            if (target->cheakUid(uid))
                break;
            target = target->next;
        }
        if (target)
            deleteUser(head, ahead, uid);
        else {
            cout << "UID��" << uid << "�����ڣ����������룺" << endl;
            goto recin2;
        }
        return true;
    } else {
        system("CLS");
        return false;
    }
}

bool adminMenuChoice3() //���������ʵд������������������ν
{
    int num = 0;
    auto *aphead = new approveList();
    char title[21] = "\0", tips[100] = "\0";
    char ch = '\0';
    system("CLS");
    if (!aphead->loadList(aphead)) {
        cout << "�����������̣�����y �����������̣�����n ���ع���Ա�˵���" << endl;
        cin >> ch;
        if (!(ch == 'y' || ch == 'Y')) {
            system("CLS");
            return false;
        } else {
            create:
            cout << "������������Ŀ���ƣ�10�����ڣ���" << endl;
            cin >> title;
            cout << "������������ʾ/ָ����50�����ڣ���" << endl;
            cin >> tips;
            cout << "�Ƿ�����������ѡ���y����n�رգ���" << endl;
            cin >> ch;
            if (!(ch == 'y' || ch == 'Y'))
                addList(aphead, title, tips, false);
            else
                addList(aphead, title, tips, true);
            cout << "����������ɡ�" << endl;
            system("pause");
            system("CLS");
        }
    } else {
        cout << "�Ѵ������������̣�" << endl;
        cout << "[���]"
             << "\t"
             << "[������Ŀ]"
             << "\t"
             << "[�Ƿ���д��������]" << endl;
        approveList *temp = aphead;
        while (aphead) {
            cout << aphead->listNum << "\t" << setw(16) << left << aphead->reListTitle();
            if (aphead->isContent)
                cout << "��" << endl;
            else
                cout << "��" << endl;
            aphead = aphead->next;
        }
        aphead = temp;
        cout << endl;
        cout << "����a �༭�������̣�����b ����������̣�����c ɾ���������̣�����d ���ع���Ա�˵���" << endl;
        cin >> ch;
        switch (ch) {
            case 'a':
                editList(aphead);
                system("pause");
                system("CLS");
                break;
            case 'b':
                goto create;
            case 'c':
                cout << "��������Ҫɾ�������̱�ţ�" << endl;
                cin >> num;
                while (num == 1) {
                    cout << "��������ɾ����һ���������̣����������룺" << endl;
                    cin >> num;
                }
                while (!appSearch(aphead, num)) {
                    cout << "δ���������ڵ����̣����������룺" << endl;
                    cin >> num;
                }
                deleteList(aphead, num);
                cout << "ɾ�����̳ɹ���" << endl;
                saveList(aphead);
                system("pause");
                system("CLS");
                break;
            default:
                system("CLS");
                return false;
        }
    }
    return true;
}

bool adminMenuChoice4(userAccount *head, attendance *ahead) {
    int num = 0;
    char targetUid[10] = "\0", ch = 'n';
    auto *uahead = new approve();
    attendance *atarget = ahead;
    approve *Head = uahead;
    approve::loadList(uahead);
    system("CLS");
    cout << "�ȴ����������У�" << endl;
    cout << endl;
    string t1 = "[�û�UID]", t2 = "[�û�����]", t3 = "[������ż�����]", t4 = "[״̬]";
    cout << left << setw(11) << t1 << setw(16) << t2 << setw(27) << t3 << t4 << endl;
    if (!getList(uahead)) {
        system("pause");
        system("CLS");
        return false;
    } else {
        cout << endl;
        cout << "����y ������ˣ�����n ���ع���Ա�˵���" << endl;
        cin >> ch;
        if (ch == 'N' || ch == 'n') {
            system("CLS");
            return false;
        }
        cout << "�����û�UID�����Ӧ�����Ž������" << endl;
        re:
        uahead = Head;
        cout << "�������û�UID��" << endl;
        cin >> targetUid;
        cout << "�����������ţ�" << endl;
        cin >> num;
        while (uahead) {
            if (uahead->getUserapp(targetUid, num))
                break;
            uahead = uahead->next;
        }
        if (!uahead) {
            cout << "δ��������Ӧ������Ϣ�����������룺" << endl;
            goto re;
        }
        while (!atarget->cheakUid(targetUid))//��ȡ��Ӧ���ڱ�
            atarget = atarget->next;
        if (adminApprove(uahead, head)) {
            if (num == 1024) {
                attendance *temp = ahead;
                while (ahead->next)
                    ahead = ahead->next;
                addAttendance(uahead->Uid, ahead);
                attendance::savaAttendance(temp);
            }
            if (num == 1025) {
                strcpy(atarget->Uid, uahead->reContent());
                attendance::savaAttendance(ahead);
            }
            if (num == 1026)
                deleteUser(head, ahead, targetUid);
        }
        cout << endl;
        cout << "�����ɣ����ع���Ա�˵�" << endl;
        saveApprove(Head);
        system("pause");
        system("CLS");
    }
    return true;
}

bool adminMenuChoice5(userAccount *head, attendance *ahead, attendance *apoint) {
    cin.clear();
    cin.sync();
    int ch = 0;
    char Uid[12] = "\0";
    attendance *aTarget = ahead;
    system("CLS");
    cout << "�û�������Ϣ���£�" << endl;
    cout << endl;
    printAttendance(head, ahead); //����û����տ�����Ϣ������չ�����Ϣ
    cout << endl;
    cout << "����1 ��ǩ�û�������2 ����Աǩ��������3 ����Աǩ�ˣ�����4 �������쿼�ڱ�.csv������5 ���ع���Ա�˵���" << endl;
    cin >> ch;
    switch (ch) {
        case 1:
            cout << "��������Ҫ��ǩ���û�UID��" << endl;
        recin:
            cin >> Uid;
            while (aTarget) //��targetָ����Ҫ�༭���û�����
            {
                if (aTarget->cheakUid(Uid))
                    break;
                aTarget = aTarget->next;
            }
            if (aTarget) {
                if (!strlen(aTarget->getAttendanceTime())) {
                    adminAttendance(aTarget);
                    cout << "UID��" << Uid << "��ǩ��ɣ���ǩʱ�䣺" << nowTime() << endl;
                } else {
                    cout << "UID��" << Uid << "��ǩ�������貹ǩ" << endl;
                    system("pause");
                    system("CLS");
                    return false;
                }
                system("pause");
                system("CLS");
            } else {
                cout << "UID��" << Uid << "�����ڣ����������룺" << endl;
                goto recin;
            }
            return true;
        case 2:
            if (strlen(apoint->getAttendanceTime())) {
                cout << "�����ظ�ǩ����" << endl;
                system("pause");
                system("CLS");
                return false;
            } else {
                userAttendance(apoint);
                cout << "ǩ���ɹ���ǩ��ʱ�䣺" << nowTime() << endl;
                system("pause");
                system("CLS");
                return true;
            }
        case 3:
            if (!strcmp(apoint->getSimpleTime(), simpleTime())) //�жϵ����Ƿ�ǩ��->ǩ������
            {
                if (strlen(apoint->getBackTime())) {
                    cout << "�����ظ�ǩ�ˡ�" << endl;
                    system("pause");
                    system("CLS");
                    return false;
                } else {
                    userBack(apoint);
                    cout << "ǩ�˳ɹ���ǩ��ʱ�䣺" << nowTime() << endl;
                    system("pause");
                    system("CLS");
                    return true;
                }
            } else {
                cout << "��ǩ�����ٽ���ǩ�ˡ�" << endl;
                system("pause");
                system("CLS");
                return false;
            }
        case 4: {
            int flag = 1;
            while (ahead && head) {
                ahead->expAdminInf(simpleTime(), head, flag);
                head = head->next;
                ahead = ahead->next;
                flag++;
            }
            cout << "�ѵ�����expAttendance.csv�ļ���" << endl;
            system("pause");
            system("CLS");
            return false;
        }
        default:
            system("CLS");
            return false;
    }
} //developer:GitHub_CSTHenry(zhengke@bytecho.net)
void userDataChange(userAccount *head, userAccount *point) {
    cin.clear();
    cin.sync();
    int ch = 0;
    char newName[10] = "\0", newPass[17] = "\0";
    system("CLS");
    cout << "����1 �޸�����������2 �޸����룺" << endl;
    cin >> ch;
    while (ch != 1 && ch != 2) {
        cout << "ѡ����ڣ����������룺" << endl;
        cin >> ch;
    }
    if (ch == 1) {
        cout << "�������µ�������UID���û�������ϵ����Ա�޸ģ���" << endl;
        cin >> newName;
        point->nameChange(newName);
    } else {
        cout << "�������µ����루<=16λ����" << endl;
        cin >> newPass;
        point->passChange(newPass);
    }
    cout << "�޸ĳɹ��������û��˵���" << endl;
    system("pause");
    system("CLS");
}

void adminUserDataChange(userAccount *head, userAccount *target) {
    cin.clear();
    cin.sync();
    int ch = 0, newgroup = -1;
    char newName[10] = "\0", newPass[17] = "\0";
    system("CLS");
    cout << "���ڱ��༭���û���Ϣ���£�" << endl;
    cout << endl;
    target->print_userInfSimple();
    cout << endl;
    cout << "����1 �޸�����������2 �޸��û��飨ְλ��������3 �޸����루������������" << endl;
    cin >> ch;
    while (ch < 1 && ch > 3) {
        cout << "ѡ����ڣ����������룺" << endl;
        cin >> ch;
    }
    switch (ch) { //developer:GitHub_CSTHenry(zhengke@bytecho.net)
        /*case 1://�������ط��գ��ѽ���
            system("CLS");
            cout << "��ע�⣺UIDΪ��¼ƾ֤��������޸ģ��޸���ɺ���ʹ����UID��¼��" << endl;
            cout << "���ڸ��� " << target->uName() << " ��UID��"
                 << "�������µ�UID��" << endl;
            cin >> newUid;
            while (!cheakUidInAdvance(head, newUid)) {
                cout << "��ǰUID��" << newUid << " �Ѵ��ڣ����������룺" << endl;
                cin >> newUid;
            }
            strcpy(target->uid, newUid);
            break;*/
        case 1:
            system("CLS");
            cout << "���ڸ��� " << target->uName() << " ���������������µ�������" << endl;
            cin >> newName;
            target->nameChange(newName);
            break;
        case 2:
            system("CLS");
            cout << "���ڸ��� " << target->uName() << " ���û��飬"
                 << "��ǰ�û���Ϊ��" << target->getGroup() << endl;
            cout << "�������µ��û����ţ�1.����Ա������ѡ�� 2.������ 3.��ͨ�û���" << endl;
            cin >> newgroup;
            while (newgroup < 1 && newgroup > 3) {
                cout << "���û����Ų����ڣ����������룺" << endl;
                cin >> newgroup;
            }
            target->groupChange(newgroup);
            break;
        default:
            system("CLS");
            cout << "���ڸ��� " << target->uName() << " �����룬����Ϊ��¼ƾ֤֮һ�������������" << endl;
            cout << "�������µ����루<=16λ����" << endl;
            cin >> newPass;
            target->passChange(newPass);
            break;
    }
    cout << "�༭�û���Ϣ�ɹ������ع���Ա�˵���" << endl;
    system("pause");
    system("CLS");
}

void randUID(int group, char *newUid) //���UID������Աǰ׺ΪA����ͨ�û�ΪU��������ΪD
{
    const char *strtoC;
    char ufrontUID[12] = "U";
    char afrontUID[12] = "A";
    char dfrontUID[12] = "D";
    string behindUID;
    int randNum;
    int min = 1000000, max = 10000000;
    default_random_engine e(time(nullptr));
    uniform_int_distribution<int> u(min, max);
    randNum = u(e);
    behindUID = to_string(randNum);
    strtoC = behindUID.c_str();
    if (group == 1) {
        strcat(afrontUID, strtoC);
        strcpy(newUid, afrontUID);
    } else if (group == 3) {
        strcat(ufrontUID, strtoC);
        strcpy(newUid, ufrontUID);
    } else {
        strcat(dfrontUID, strtoC);
        strcpy(newUid, dfrontUID);
    }
}

void deleteUser(userAccount *head, attendance *ahead, char *uid) {
    userAccount *flag = nullptr;
    userAccount *target = head;
    while (target) //��targetָ����Ҫ�༭���û�����
    {
        if (target->cheakUid(uid))
            break;
        flag = target; //��¼Ŀ��֮ǰ��ָ��
        target = target->next;
    }
    flag->next = target->next;
    deleteAttendance(ahead, uid); //ͬʱɾ�����ڱ�����Ӧ����
    ahead->savaAttendance(ahead); //����
    cout << "�˺� [UID:" << uid << "] ע���ɹ���" << endl;
    system("pause");
    system("CLS");
} //developer:GitHub_CSTHenry(zhengke@bytecho.net)
bool cheakUidInAdvance(userAccount *head, char *id) //���ظ�UID����TRUE
{
    bool flag = true;
    do {
        if (head->cheakUid(id))
            flag = false;
        head = head->next;
    } while (head);
    if (flag)
        return true;
    return false;
}

void uidApprove(userAccount *head, userAccount *target) //UID���뺯��
{
    char ch;
    re:
    system("cls");
    char apply[200] = "\0", newUID[12] = "\0", content[200] = "\0";
    randUID(target->getGroup(), newUID);
    while (!cheakUidInAdvance(head, newUID))
        randUID(target->getGroup(), newUID);
    cout << "    �밴����ʾ�������UID" << endl;//�Ѹ���Ϊ�������UID
    cout << "========�Զ�����UID========" << endl;
    cout << "-> " << newUID << endl;
    cout << "===========================" << endl;
    cout << " -[UID������� ���Ʊ���]-" << endl;
    cout << "����y ȷ���������Ϊ��UID������n ��������UID��" << endl;
    cin >> ch;
    if (ch != 'Y' && ch != 'y')
        goto re;
    strcpy(content, newUID);
    cout << endl;
    cout << "��ע�⣬���ͨ���󣬽���ʹ����UID [" << newUID << "] ��¼��ԭUID��ʧЧ��" << endl;
    cout << "===========================" << endl;
    cout << "= ���������UID�����ɣ�   =" << endl;
    cout << "===========================" << endl;
    cin >> apply;
    auto *uahead = new approve();
    approve::loadList(uahead);
    addStaticApp(uahead, target, 1025, "UID�޸�����", apply, content);
    saveApprove(uahead);
}

bool deleteApp(userAccount *head, userAccount *target) {
    char apply[200]{};
    string entrance;
    system("cls");
    cout << "���棺����������ע���˻���һ�����ͨ��������������ݽ�����գ�" << endl;
    cout << "�����룺\"����֪����ȷ������ע���ҵ��˻�\"�Խ������룺" << endl;
    cin >> entrance;
    if (entrance != "����֪����ȷ������ע���ҵ��˻�") {
        cout << "��֤ʧ�ܣ��������˵���" << endl;
        system("pause");
        system("CLS");
        return false;
    }
    cout << "������ע�����˻� [" << target->uid << "] �����ɣ�" << endl;
    cin >> apply;
    auto *uahead = new approve();
    approve::loadList(uahead);
    addStaticApp(uahead, target, 1026, "�˻�ע������", apply, "\0");
    saveApprove(uahead);
    return true;
}