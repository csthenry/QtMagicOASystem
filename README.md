# QtMagicOASystem

🎉新一代OA，基于ONEByteOA项目，数据以二进制形式存储在本地。

![1](https://img.shields.io/github/license/CSTHenry/QtMagicOASystem) ![2](https://img.shields.io/github/v/release/CSTHenry/QtMagicOASystem?include_prereleases) ![3](https://img.shields.io/github/downloads/CSTHenry/QtMagicOASystem/total)

> OA系统即Office Automation，简称OA，在高校、企业中应用广泛，通过开发OA系统，能够更深入地理解相关内容，更能考察数据结构能力及代码开发规范。

- 平台：Windows，Linux
- 类型：Qt程序
- 语言：C++

**特性：动态内存管理，二进制存储，函数分类管理（多文件结构）**
**实现：用户信息管理，考勤，审批，数据导出，自定义审批流程**

程序结构：

```
├── MagicOASystem（主程序）
├── src（数据文件夹）
│   ├── appList.dat（审批项目表）
│   ├── attendanceData.dat（考勤数据表）
│   ├── userApprove.dat（审批数据）
│   └── userData.dat（数据表）
└── uidInf.ini（UID配置文件）
```

### 开发进度

**已完成：**

* [x] 注册，登录（自动化UID）
* [x] 具有时效性的（动态）考勤系统，签到，签退，补签


**进行中：**
* [ ] 个人信息管理
* [ ] 用户管理（管理员）
* [ ] 发起申请
* [ ] 查看审批进度
* [ ] 审批队列
* [ ] 用户数据可视化导出
* [ ] 部分自动化审批流程
* [ ] 附加细节功能...

### 功能介绍

1. 账户注册（固定前缀，随机生成UID）
2. 管理员账户申请
3. 账户登录（可保存UID->自动获取）
4. 个人信息（管理员菜单和用户菜单均可用）
5. 用户管理（管理员菜单可用）
   1. 姓名、用户组、密码
   2. 注销账号
6. 考勤系统
   1. 用户的签到、签退
   2. 管理员查看签到状态，补签用户等
   3. 导出用户考勤数据（.csv）
7. 项目审批
   1. 创建与管理审批流程
   2. 查看审批进度
   3. 发起申请
   4. 审批队列
   5. 自动化审批操作

![exp](https://github.com/CSTHenry/ONEByteOA/blob/master/src/exp.png)


### LICENSE

[MIT License](https://github.com/CSTHenry/QtMagicOASystem/blob/main/LICENSE)
