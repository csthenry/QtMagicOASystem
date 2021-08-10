#include "attendance.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

//developer:GitHub_CSTHenry(zhengke@bytecho.net)
char *simpleTime();

char *nowTime() {
    static char nowTime[50];
    time_t now = time(nullptr);
    strftime(nowTime, 50, "%Y��%m��%d�� %H:%M:%S", localtime(&now));
    return nowTime;
}

char *simpleTime() {
    static char simpleTime[25];
    time_t now = time(nullptr);
    strftime(simpleTime, 50, "%Y��%m��%d��", localtime(&now));
    return simpleTime;
}

attendance *searchUserAttendance(attendance *head, char *uid)//�ҵ��û�ǩ�����ݷ���ָ�룬���򷵻�Nullptr
{
    while (head) {
        if (head->cheakUid(uid))
            break;
        head = head->next;
    }
    return head;
}

attendance *userToData(userAccount *head)//����ǰ�����û�IDд��ǩ�����ݱ����ڳ����ʼ��
{
    auto *ahead = new attendance();
    attendance *nextPtr;
    nextPtr = nullptr;
    auto ptr = ahead;
    while (head)//���û����ݱ��е�����UIDд�뿼�����ݱ�UID���������������ݱ���
    {
        nextPtr = new attendance();
        strcpy(ahead->Uid, head->uid);
        ahead->next = nextPtr;
        ahead = ahead->next;
        head = head->next;
    }
    return ptr;
}//developer:GitHub_CSTHenry(zhengke@bytecho.net)
void attendance::savaAttendance(attendance *ahead)//��������������������,�ڶԿ��ڽ��в����󣬾�Ҫִ�д˺���
{
    ofstream openUserFile("./src/attendanceData.dat", ios::binary | ios::out);//./src/attendanceData.dat
    if (!openUserFile.fail()) {
        do {
            openUserFile.write((char *) ahead->Uid, sizeof(ahead->Uid));
            openUserFile.write((char *) &ahead->method, sizeof(bool));
            openUserFile.write((char *) ahead->attendanceTime, sizeof(ahead->attendanceTime));
            openUserFile.write((char *) ahead->backTime, sizeof(ahead->backTime));
            openUserFile.write((char *) &ahead->simpleTime, sizeof(ahead->simpleTime));
            ahead = ahead->next;
        } while (ahead);
    } else {
        cout << "fault,code:attendanceSaveError." << endl;
        openUserFile.close();
        return;
    }
    openUserFile.close();
}

[[maybe_unused]] attendance *searchUserPtr(attendance *ahead, char *id)//���ҿ��������е���ӦUID�������ض�Ӧָ�룬�޴�UID����Nullptr
{
    while (ahead) {
        if (ahead->cheakUid(id))
            break;
        ahead = ahead->next;
    }
    return ahead;
}//developer:GitHub_CSTHenry(zhengke@bytecho.net)
attendance *attendance::loadData(attendance *ahead)//���뿼�����ݣ�����ͷָ�룬����βָ�룬����ʧ�ܷ���Nullptr
{
    int flag = 0;
    attendance *temp = ahead;
    attendance *last = nullptr;
    ifstream loadUserFile("./src/attendanceData.dat",
                          ios::binary | ios::in); // F:\\VSCode_Projects\\VSCode-C++\\oa\\src\\attendanceData.dat
    if (!loadUserFile.fail()) {
        do {
            loadUserFile.read((char *) temp->Uid, sizeof(temp->Uid));
            loadUserFile.read((char *) &temp->method, sizeof(bool));
            loadUserFile.read((char *) temp->attendanceTime, sizeof(temp->attendanceTime));
            loadUserFile.read((char *) temp->backTime, sizeof(temp->backTime));
            loadUserFile.read((char *) &temp->simpleTime, sizeof(temp->simpleTime));
            if (!strlen(temp->Uid)) //���loadUserFile.eof()������һ�ε�����
            {
                flag = 1;
                last->next = nullptr;
            }
            auto *next = new attendance();
            if (!flag)
                last = temp;
            temp->next = next;
            temp = temp->next;
        } while (!loadUserFile.eof());
    } else {
        //cout << "fault,code:fun_146." << endl;
        delete[] temp;
        temp = nullptr;
        ahead = nullptr;
        loadUserFile.close();
        return ahead;
    }
    loadUserFile.close();
    return last;
}

string attendance::getMethod() const {
    if (!method)
        return "����Ա��ǩ";
    return "����ǩ��";
}

/*
bool cheakToday(attendance* target)//�жϵ����û��Ƿ�ǩ��������Ŀ���û���������ָ��
{

}*/
void userAttendance(attendance *target)//ǩ������
{
    target->takeAttendance(nowTime(), simpleTime(), true);
}

void userBack(attendance *target)//ǩ�˺���
{
    target->takeBack(nowTime());
}

void adminAttendance(attendance *target)//��ǩ����
{
    target->takeAttendance(nowTime(), simpleTime(), false);
}

void printAttendance(userAccount *head, attendance *ahead)//���ڹ���Ա�˵�05
{
    cout << left << setw(11) << "[�û�UID]" << setw(10) << "[����]" << setw(10) << "[ְλ]" << "[������Ϣ]" << endl;
    cout << endl;
    while (ahead && head) {
        cout << "[" << head->uid << "] " << left << setw(10) << head->uName() << setw(10) << head->search_Situation() << "ǩ��״̬->";
        ahead->printAdminInf(simpleTime());
        head = head->next;
        ahead = ahead->next;
    }
}

void addAttendance(char *newUid, attendance *last)//ע�����û�����ص��ô˺������ҵ��ô˺����������saveAttendance()
{
    auto *nextPtr = new attendance();
    strcpy(nextPtr->Uid, newUid);
    last->next = nextPtr;
}//developer:GitHub_CSTHenry(zhengke@bytecho.net)
void deleteAttendance(attendance *ahead, char *uid)//ע���û��󣬵��ô˺������ҵ��ô˺����������saveAttendance()
{
    attendance *temp = ahead;
    while (ahead)//��λĿ��UID
    {
        if (ahead->cheakUid(uid))
            break;
        temp = ahead;//��¼ǰһ�ڵĵ�ַ
        ahead = ahead->next;
    }
    temp->next = ahead->next;
}