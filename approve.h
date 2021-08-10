﻿#ifndef _APPROVE_H_
#define _APPROVE_H_

#include "approveList.h"
#include "userAccount.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
//developer:GitHub_CSTHenry(zhengke@bytecho.net)
class approve {
public:
    char Uid[12] = "\0", name[10] = "\0";
    int listNum = 0;
    approve *next = nullptr;
    bool statu = false;//审批状态：f审核中，t审核完成，用于个人菜单
    bool flag = false;//审核结果：t通过，f拒绝，用于个人菜单
    static approve *loadList(approve *uahead);

    bool getUserapp(char *uid, int num) {
        if (!strcmp(Uid, uid) && num == listNum && !statu)
            return true;
        else
            return false;
    }

    char *reContent()//获取申请内容，可能为\0，取决于审批流程
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

    void cheakStatu() const//获取审核状态
    {
        if (statu) {
            if (flag)
                cout << "通 过" << endl;
            else
                cout << "不通过" << endl;
        } else
            cout << "审核中" << endl;
    }

    [[maybe_unused]] void printStatu() {
        cout << "项目：" << title << " 审核状态：";
        cheakStatu();
        cout << endl;
    }

private:
    char content[200] = "\0";//申请内容（可选）
    char title[21] = "\0";//流程名
    char apply[200] = "\0";//申请理由
    char reply[101] = "\0";//审核意见
};
approveList *appSearch(approveList *aphead, int num);

void addList(approveList *aphead, char *title, char *tips, bool content);

void editApprove(approve *uahead, char *uid);

void saveApprove(approve *uahead);

void saveList(approveList *aphead);

bool deleteList(approveList *aphead, int listNumber);

bool getList(approve *uahead);

bool adminApprove(approve *target, userAccount *head);

bool getUserApprove(userAccount *point, approve *uahead);

void addApprove(approve *uahead, approveList *aphead, char *uid, char *uName, char *apply, char *content);

void addSimpleApp(approve *uahead, char *uid, char *uName, char *apply, char *content);

void addStaticApp(approve *uahead, userAccount *target, const int listNum, const char *title, const char *apply,
                  const char *content);
void saveApprove(approve *uahead);

bool getList(approve *uahead);

bool adminApprove(approve *target, userAccount *head);

bool getUserApprove(userAccount *point, approve *uahead);

void editApprove(approve *uahead, char *uid);

void editList(approveList *aphead);

#endif
