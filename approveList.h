#ifndef _APPROVELIST_H_
#define _APPROVELIST_H_

#include <cstring>
#include <iostream>

using namespace std;
//developer:GitHub_CSTHenry(zhengke@bytecho.net)

class approveList {
public:
    static approveList *loadList(approveList *aphead);

    approveList *next = nullptr;
    int listNum = 0;//�������̱��
    bool isContent = false;//�Ƿ�������������д��
    char *reListTips() {
        return listTips;
    }

    char *reListTitle() {
        return listTitle;
    }

    void setTitle(char *title) {
        strcpy(listTitle, title);
    }

    void setTips(char *tips) {
        strcpy(listTips, tips);
    }

private:
    char listTips[100] = "\0";//������ʾ
    char listTitle[21] = "\0";//������
};

#endif