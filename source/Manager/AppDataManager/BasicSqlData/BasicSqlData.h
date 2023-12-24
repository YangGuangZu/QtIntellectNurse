#pragma once
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include "Manager/AppDataManager/APPSqlData/APPSqlData.h"
struct OperaDetails
{
	//操作结果
	bool isOk = true;
	//操作类型
	QString strOpera;
	//操作详情
	QString strDetails;
};
class BasicSqlData :public QObject
{
	Q_OBJECT
public:
	BasicSqlData();
	~BasicSqlData() {};
protected:
	QString m_strAppFuncName;
protected:
	//自用接口
	bool isPathExists(const QString& path);
protected:
	QJsonObject readJsonObjectFromSql();
	void saveJsonObjectFromSql(QJsonObject & strJson);

};
