#include <QFileInfo>
#include "AppDataManager.h"
#include "Manager/AppDataManager/UserManager/UserManager.h"
#include "Manager/AppDataManager/CaregiverManager/CaregiverManager.h"
#include "Manager/AppDataManager/NetworkManager/NetworkManager.h"
#include "Manager/AppDataManager/CommunicateManager/CommunicateManager.h"
#include "Manager/AppDataManager/BasicConfigManager/BasicConfigManager.h"
#include "Manager/AppDataManager/VideoManager/VideoManager.h"
#include "Manager/AppDataManager/ScreenManager/ScreenManager.h"

AppDataManager::AppDataManager() 
{
	init();
}

void AppDataManager::init()
{
	QFileInfo fileSqlite3("sqlite3.dll");
	if (!fileSqlite3.isFile())
	{
		QFile::copy(":/dll/sqlite3.dll", "./");
	}
	//初始化程序数据库表
	initSqlTable();
	//初始化用户管理
	UserManager::Instance().init();
	//初始化护理人管理
	CaregiverManager::Instance().init();
	//初始化网络信息
	NetworkManager::Instance().init();
	//初始化基础数据
	BasicConfigManager::Instance().init();
	//初始化视频数据模块
	VideoManager::Instance().init();
	//初始化屏幕
	ScreenManager::Instance().init();
	//初始化屏幕
	CommunicateManager::Instance().init();
}

void AppDataManager::initSqlTable()
{
	m_tableName = "APPConfig";
	APPSqlData::CreateTableStruct appConfigTable;
	appConfigTable.tableName = m_tableName;

	APPSqlData::CreateTableParam funcParam;
	funcParam.name = "APPFunc";
	funcParam.type = APPSqlData::CreateType::TEXT;
	funcParam.bIsCanNull = false;  
	funcParam.bIsUnique = true;    

	appConfigTable.content.append(funcParam);

	APPSqlData::CreateTableParam configParam;
	configParam.name = "APPFuncConfig";
	configParam.type = APPSqlData::CreateType::TEXT;
	configParam.bIsCanNull = false;

	appConfigTable.content.append(configParam);

	// 调用函数生成创建表的SQL语句
	APPSqlData::SqlOperaDetails stSqlOperaDetails;
	QString createTableSQL = APPSqlData::Instance().getCreateTableParamsString(appConfigTable, stSqlOperaDetails);
}

void AppDataManager::setCurrAppControlType(const AppControlType& eAppControlType)
{
	m_currAppControlType = eAppControlType;
}
