#pragma once
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQueryModel>

#include <QJsonObject>

#include "Define/AppDefine.h"
class APPSqlData :public QObject
{
	Q_OBJECT
private:
	APPSqlData();
	~APPSqlData();

public:
 	static APPSqlData& Instance() {
		static APPSqlData Instance;
		return Instance;
	}
public:
	enum CreateType
	{
		TEXT,
		INTEGER,
	};

	struct SqlOperaDetails
	{
		//操作结果
		bool isOk = true;
		//操作类型
		QString strOpera;
		//操作详情
		QString strDetails;
	};


	struct CreateTableParam
	{
		//表头
		QString name;
		//数据库类型
		CreateType type = TEXT;
		//是否可以为空
		bool bIsCanNull = true;
		//是否唯一
		bool bIsUnique = false;
	};

	using CreateTableParams = QList<CreateTableParam>;

	struct CreateTableStruct 
	{
		QString tableName;
		CreateTableParams content;
	};

	struct SqlUpdateParams
	{
		QString name;
		QVariant value;
	};
private:
	//数据库路径
	QString m_strDbPath;
	//数据库名称
	QString m_strDbName;
	//数据库对象
	QSqlDatabase m_db;
private:
	//初始化
	void init();
	bool openDatabase();
	bool checkAndCreateDirectory(const QString& path);
	//设置详情结构体内容
	void setSqlOperaDetails(SqlOperaDetails& stSqlOperaDetails, const bool& isOK, const QString& strOpera, const QString& strDetails);
public:
	//执行插入语句
	void execInsertFunc(const QString& strInsertFunc, SqlOperaDetails& stSqlOperaDetails);
	//执行查询语句
	QSqlQuery execQueryFunc(const QString& strQueryFunc, SqlOperaDetails& stSqlOperaDetails);
	//执行修改语句
	QSqlQuery execUpdateFunc(const QString& strQueryFunc,const QList<SqlUpdateParams> & lststSqlUpdateParams, SqlOperaDetails& stSqlOperaDetails);
	//依据创建表结构体来获取创建表的字符串
	QString getCreateTableParamsString(const CreateTableStruct& stCreateTableParams, SqlOperaDetails& stSqlOperaDetails);
};
