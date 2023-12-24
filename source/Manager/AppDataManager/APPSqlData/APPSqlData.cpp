#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include "APPSqlData.h"
#include "Component/PopupTips/PopupManager.h"

APPSqlData::APPSqlData() : QObject()
{
	init();
}

APPSqlData::~APPSqlData()
{
	// 在对象销毁时确保关闭数据库连接
	if (m_db.isOpen())
	{
		m_db.close();
	}
}

void APPSqlData::init()
{
	// 设置数据库文件的路径和名称
	m_strDbPath = QCoreApplication::applicationDirPath() + "/SaveDbFile/";
	m_strDbName = m_strDbPath + "IntellectNurse.db";

	// 检查是否已经存在默认数据库连接，如果存在就使用它，否则创建一个新的连接
	if (QSqlDatabase::contains("qt_sql_default_connection"))
	{
		m_db = QSqlDatabase::database("qt_sql_default_connection");
	}
	else
	{
		// 建立和 SQLite 数据库的连接
		m_db = QSqlDatabase::addDatabase("QSQLITE");

		// 设置数据库文件的名字
		m_db.setDatabaseName(m_strDbName);

		// 错误处理：尝试打开数据库，如果失败则输出错误信息
		if (!openDatabase())
		{
			qDebug() << "Error opening database:" << m_db.lastError().text();
			// 处理错误，可能需要采取适当的措施，比如显示错误消息、关闭应用程序等。
		}
	}

	// 检查数据库文件路径是否存在，如果不存在则创建
	if (!checkAndCreateDirectory(m_strDbPath))
	{
		qDebug() << "Error creating directory:" << m_strDbPath;
		// 处理错误，可能需要采取适当的措施。
	}
}

bool APPSqlData::openDatabase()
{
	if (!m_db.open())
	{
		return false;
	}
	return true;
}

bool APPSqlData::checkAndCreateDirectory(const QString& path)
{
	QDir dir(path);
	if (!dir.exists())
	{
		return dir.mkpath(".");
	}
	return true;
}

void APPSqlData::setSqlOperaDetails(SqlOperaDetails& stSqlOperaDetails, const bool& isOK, const QString& strOpera, const QString& strDetails)
{
	stSqlOperaDetails.isOk = isOK;
	stSqlOperaDetails.strOpera = strOpera;
	stSqlOperaDetails.strDetails = strDetails;
	if (false == isOK)
	{
		qDebug() << stSqlOperaDetails.strDetails;
		PopupManager::Instance().addPopupTip(QStringLiteral("警告"), QStringLiteral("数据库操作失败,%1 %2")
			.arg(stSqlOperaDetails.strOpera).arg(stSqlOperaDetails.strDetails), QtMsgType::QtFatalMsg);
	}
}

void APPSqlData::execInsertFunc(const QString& strInsertFunc, SqlOperaDetails& stSqlOperaDetails)
{
	QSqlQuery query(m_db);// 执行 SQL 查询
	QString tempQueryFunc(strInsertFunc);
	tempQueryFunc.replace("\"", "\\\"");
	if (!query.exec(tempQueryFunc))
	{
		setSqlOperaDetails(stSqlOperaDetails, false, QString("插入数据"), query.lastError().text());
	}
}

QSqlQuery APPSqlData::execQueryFunc(const QString& strQueryFunc, SqlOperaDetails& stSqlOperaDetails)
{
	QSqlQuery query(m_db);// 执行 SQL 查询
	QString tempQueryFunc(strQueryFunc);
	tempQueryFunc.replace("\"", "\\\"");
	if (!query.exec(tempQueryFunc))
	{
		setSqlOperaDetails(stSqlOperaDetails, false, QString("查询数据"), query.lastError().text());
	}
	return query;
}

QSqlQuery APPSqlData::execUpdateFunc(const QString& strQueryFunc,const QList<SqlUpdateParams> & lststSqlUpdateParams, SqlOperaDetails& stSqlOperaDetails)
{
	QSqlQuery query(m_db);// 执行 SQL 修改
	QString tempQueryFunc(strQueryFunc);
	tempQueryFunc.replace("\"", "\\\"");
	query.prepare(tempQueryFunc);

	for (const SqlUpdateParams & stSqlUpdateParams : lststSqlUpdateParams)
	{
		query.bindValue(stSqlUpdateParams.name, stSqlUpdateParams.value);
	}

	if (!query.exec())
	{
		setSqlOperaDetails(stSqlOperaDetails, false, QString("修改数据"), query.lastError().text());
	}
	return query;
}

QString APPSqlData::getCreateTableParamsString(const CreateTableStruct& stCreateTableParams, SqlOperaDetails& stSqlOperaDetails)
{
	QString strCreateTable;
	strCreateTable.append(QString("CREATE TABLE IF NOT EXISTS %1 (").arg(stCreateTableParams.tableName));
	strCreateTable.append(QString("ID INTEGER PRIMARY KEY AUTOINCREMENT,"));

	//for (const CreateTableParam & stCreateTableParam : stCreateTableParams.content)
	for (int i = 0; i < stCreateTableParams.content.size(); i++)
	{
		CreateTableParam stCreateTableParam = stCreateTableParams.content.at(i);
		QString strType;
		switch (stCreateTableParam.type)
		{
		case TEXT:
			strType = "TEXT";
			break;
		case INTEGER:
			strType = "INTEGER";
			break;
		default:
			strType = "TEXT";
			break;
		}
		strCreateTable.append(QString("%1 %2%3%4%5")
			.arg(stCreateTableParam.name)
			.arg(strType)
			.arg(stCreateTableParam.bIsCanNull ? "" : " NOT NULL")
			.arg(stCreateTableParam.bIsUnique ? " UNIQUE" : "")
			.arg(i + 1 == stCreateTableParams.content.size() ? "" : ","));
	}
	strCreateTable.append(QString(");"));
	QSqlQuery query(m_db);
	// 执行 SQL 查询
	if (!query.exec(strCreateTable))
	{
		setSqlOperaDetails(stSqlOperaDetails, false, QString("创建数据表"),
			QString("[ %1 ]: %2").arg(stCreateTableParams.tableName).arg(query.lastError().text())
		);
	}
	return strCreateTable;
}
