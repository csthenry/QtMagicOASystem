#ifndef _ATTENDANCE_H_
#define _ATTENDANCE_H_
#include <cstring>
#include <iostream>

using namespace std;
//developer:GitHub_CSTHenry(zhengke@bytecho.net)
class attendance {
public:
    static void savaAttendance(attendance *ahead);

    static attendance *loadData(attendance *ahead);

    char Uid[12] = "\0";
    attendance *next = nullptr;

    bool cheakUid(char *id)//IDƥ�䷵��true
    {
        if (!strcmp(Uid, id))
            return true;
        return false;
    }

    char *getSimpleTime() {
        return simpleTime;
    }
        char *getAttendanceTime()
        {
            return attendanceTime;
        }

    char *getBackTime() {
        return backTime;
    }

    void takeAttendance(char *Time, char *simple, bool todayMethod)//��Ҫ��ǰʱ���ǩ����ʽ��ǩ���ӿڣ�
    {
        strcpy(attendanceTime, Time);
        strcpy(simpleTime, simple);
        method = todayMethod;
    }

    void takeBack(char *Time)//ǩ�˽ӿ�
    {
        strcpy(backTime, Time);
    }

    void printInf(char *today)//�ۺϴ�ӡǩ����ǩ��״̬�����ڸ��˲˵������Զ�������ڼ�¼
    {
        if (!strcmp(simpleTime, today)) {
            printAttendance();
            if (strlen(backTime)) {
                cout << endl;
                printBack();
            } else
                cout << "[δǩ��]" << endl;
        } else {
            deleteYesterday();
            cout << "UID��" << Uid << "[δǩ��]" << endl;
        }
    }

    void printAdminInf(char *today)//���Դ�ӡ����״̬�����ڹ���˵���������û���Ϣ����ã����Զ�������ڼ�¼
    {
        if (!strcmp(simpleTime, today)) {
            cout << "[��ǩ��]" << "ǩ��ʱ�䣺" << attendanceTime << " ";
        } else {
            deleteYesterday();//�������ǩ����¼
            cout << "[����δǩ��]" << endl;
            return;
        }
        if (method) {
            if (strlen(backTime))
                cout << "ǩ��ʱ�䣺" << backTime;
            else
                cout << "[δǩ��]";
        }
        cout << " ǩ����ʽ��" << getMethod() << endl;
    }

    void expAdminInf(char *today, userAccount *head, int flag)//���Դ�ӡ����״̬�����ڹ���˵���������û���Ϣ����ã����Զ�������ڼ�¼
    {
        ofstream expFile("expAttendance.csv", ios::out | ios::app);
        if (flag == 1) {
            expFile << "���ڱ������ڣ�," << today << "\n";
            expFile << "UID,����,ְλ,ǩ��״̬,ǩ��ʱ��,ǩ��״̬,ǩ��ʱ��,ǩ����ʽ" << endl;
        }
        expFile << "[" << head->uid << "]," << head->uName() << "," << head->search_Situation() << ",";
        if (!strcmp(simpleTime, today)) {
            expFile << "[��ǩ��]," << attendanceTime << ",";
        } else {
            expFile << "[����δǩ��],NULL,NULL,NULL,NULL" << "\n";
            return;
        }
        if (method) {
            if (strlen(backTime))
                expFile << "[��ǩ��]," << backTime << ",";
            else
                expFile << "[δǩ��],NULL,";
        } else {
            expFile << "NULL,NULL,";
        }
        expFile << getMethod() << "\n";
    }

    void printAttendance() {
        cout << "UID��" << Uid << endl << "[��ǩ��]"
             << " ǩ����ʽ��" << getMethod() << endl;
        cout << "ǩ��ʱ�䣺" << attendanceTime << endl;
    }

    void printBack() {
        cout << "[��ǩ��]" << endl;
        cout << "ǩ��ʱ�䣺" << backTime << endl;
    }

    [[nodiscard]] string getMethod() const;

    void deleteYesterday()//�û�simpleTime����ͬʱ����
    {
        method = false;
        for (int i = 0; attendanceTime[i]; i++)
            attendanceTime[i] = '\0';
        for (int i = 0; backTime[i]; i++)
            backTime[i] = '\0';
    }

private://developer:GitHub_CSTHenry(zhengke@bytecho.net)
    bool method = false;//falseΪ��ǩ��trueΪ����ǩ��
    char attendanceTime[50] = "\0";
    char backTime[50] = "\0";
    char simpleTime[25] = "\0";//����ʾ���ڣ�����ʾ����ʱ�䣬�����жϵ����Ƿ�ǩ��
};
#endif