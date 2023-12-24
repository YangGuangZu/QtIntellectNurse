#include <QDir>
#include "BasicSqlData.h"

BasicSqlData::BasicSqlData()
{

}

bool BasicSqlData::isPathExists(const QString& path)
{
	QDir directory(path);
	return directory.exists();
}

QJsonObject BasicSqlData::readJsonObjectFromSql()
{
	QString queryString = QString("SELECT * FROM APPConfig WHERE APPFunc='%2';").arg(m_strAppFuncName);
	//数据库查询
	APPSqlData::SqlOperaDetails stSqlOperaDetails;
	QSqlQuery query = APPSqlData::Instance().execQueryFunc(queryString, stSqlOperaDetails);

	if (query.next()) 
	{
		QString strJson = query.value("APPFuncConfig").toString();
		/*转为Json对象*/
		QJsonParseError jsonError;
		QJsonDocument documentJson = QJsonDocument::fromJson(strJson.toStdString().data(), &jsonError);
		if (jsonError.error == QJsonParseError::NoError)
		{
			QJsonObject json = documentJson.object();
			return json;
		}
	}
	return QJsonObject();
}

void BasicSqlData::saveJsonObjectFromSql(QJsonObject& json)
{
	//构建JSON文档
	QJsonDocument documentStr;
	documentStr.setObject(json);
//#if 0
	QByteArray byteArray = documentStr.toJson(QJsonDocument::Compact);//不换行
//#else
//	QByteArray byteArray = documentStr.toJson(QJsonDocument::Indented);//会缩进, 会换行
//#endif
	//存储字符
	QString strJson(byteArray);


	QString queryString = QString("SELECT * FROM APPConfig WHERE APPFunc='%2';").arg(m_strAppFuncName);
	//数据库查询
	APPSqlData::SqlOperaDetails stSqlOperaDetails;
	QSqlQuery query = APPSqlData::Instance().execQueryFunc(queryString, stSqlOperaDetails);

	if (query.next())
	{
		QString str = QString("UPDATE APPConfig SET APPFuncConfig = :newConfig WHERE APPFunc = :appName");

		QList<APPSqlData::SqlUpdateParams> lstSqlUpdateParams;

		APPSqlData::SqlUpdateParams stSqlUpdateParams;
		stSqlUpdateParams.name = QString(":newConfig");
		stSqlUpdateParams.value = strJson;
		lstSqlUpdateParams.append(stSqlUpdateParams);

		stSqlUpdateParams.name = QString(":appName");
		stSqlUpdateParams.value = m_strAppFuncName;
		lstSqlUpdateParams.append(stSqlUpdateParams);

		APPSqlData::SqlOperaDetails stSqlOperaDetails;
		APPSqlData::Instance().execUpdateFunc(str, lstSqlUpdateParams, stSqlOperaDetails);
	}
	else
	{
		QString queryString = QString("INSERT INTO APPConfig (APPFunc, APPFuncConfig) VALUES ('%1', '%2');").arg(m_strAppFuncName).arg(strJson);
		APPSqlData::SqlOperaDetails stSqlOperaDetails;
		APPSqlData::Instance().execInsertFunc(queryString, stSqlOperaDetails);
	}
}

