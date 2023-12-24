#pragma once
#include <QObject>
#include "Manager/AppDataManager/BasicSqlData/BasicSqlData.h"
class UserManager :public BasicSqlData
{
	Q_OBJECT
private:
	UserManager();
	~UserManager() {};

public:
	static UserManager& Instance() {
		static UserManager Instance;
		return Instance;
	}
public:
	struct UserInfoParam 
	{
		//账号
		QString strAccount;
		//密码
		QString strPassword;
		//用户名
		QString strUserName;
		//年龄
		uint uiAge = 0;
		//护理区域
		QString strNursingArea;
		//床位号
		uint uiBedNumber = 0;
		//入院时间
		QString strAdmissionTime = QStringLiteral("2100-10-10");
		//护理人
		QString Caregiver = QStringLiteral("无");
	}; 
private:
	//表明
	QString m_tableName;
	//当前登录账户
	UserInfoParam m_currUser;
	//建表的结构队列
	APPSqlData::CreateTableParams m_stCreateTableParams;
	//当前是否有账户登录
	bool m_bIsLogin				= false;
public:
	//初始化
	void init();
private:
	//检查康复人
	bool checkLogin(const QString& account, const QString& password, APPSqlData::SqlOperaDetails& stSqlOperaDetails);
public:
	//添加康复人
	bool insertUser(const UserInfoParam& stUserSqlStruct);
	//登录康复人
	void loginUser(const QString& account, const QString& password);
	//退出登录康复人
	void exitLoginUser();
	//信息存取
	void readConfig();
	void saveConfig();
signals:
	void signals_userLoginStatusChanged(bool bIsLogin, UserInfoParam * stUserInfoParam = nullptr);
};
