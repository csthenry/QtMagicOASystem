#ifndef _APPROVE_H_
#define _APPROVE_H_

#include <cstring>
#include <iostream>

using namespace std;
//developer:GitHub_CSTHenry(zhengke@bytecho.net)
class approve {
public:
    char Uid[12] = "\0", name[10] = "\0";
    int listNum = 0;
    approve *next = nullptr;
    bool statu = false;//����״̬��f����У�t�����ɣ����ڸ��˲˵�
    bool flag = false;//��˽����tͨ����f�ܾ������ڸ��˲˵�
    static approve *loadList(approve *uahead);

    bool getUserapp(char *uid, int num) {
        if (!strcmp(Uid, uid) && num == listNum && !statu)
            return true;
        else
            return false;
    }

    char *reContent()//��ȡ�������ݣ�����Ϊ\0��ȡ������������
    {
        return content;
    }

    char *reApply() {
        return apply;
    }
        char *reReply()
        {
            return reply;
        }
        char *reTitle()
        {
            return title;
        }
        void setContent(const char *con)
        {
            strcpy(content, con);
        }
        void setTitle(const char* tit)
        {
            strcpy(title, tit);
        }
        void setApply(const char *app)
        {
            strcpy(apply, app);
        }

    void setReply(const char *re) {
        strcpy(reply, re);
    }

    void cheakStatu() const//��ȡ���״̬
    {
        if (statu) {
            if (flag)
                cout << "ͨ ��" << endl;
            else
                cout << "��ͨ��" << endl;
        } else
            cout << "�����" << endl;
    }

    [[maybe_unused]] void printStatu() {
        cout << "��Ŀ��" << title << " ���״̬��";
        cheakStatu();
        cout << endl;
    }

private:
    char content[200] = "\0";//�������ݣ���ѡ��
    char title[21] = "\0";//������
    char apply[200] = "\0";//��������
    char reply[101] = "\0";//������
};

#endif