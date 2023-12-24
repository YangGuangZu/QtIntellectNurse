#pragma once
#include <QObject>
#include "Manager/AppDataManager/BasicSqlData/BasicSqlData.h"
class CaregiverManager :public BasicSqlData
{
	Q_OBJECT
private:
	CaregiverManager();
	~CaregiverManager() {};

public:
	static CaregiverManager& Instance() {
		static CaregiverManager Instance;
		return Instance;
	}
private:
	//护理人
	QString m_strCaregiver = QStringLiteral("暂无");
	//工程师
	QString m_strEngineer = QStringLiteral("暂无");
	//维护人
	QString m_strMaintainer = QStringLiteral("暂无");
public:
	//初始化
	void init();
	//设置信息
	void setCaregiver(const QString& value);
	void setEngineer(const QString& value);
	void setMaintainer(const QString& value);
	//获取信息
	QString getCaregiver();
	QString getEngineer();
	QString getMaintainer();
	//信息存取
	void readConfig();
	void saveConfig();
signals:
	void signals_caregiverStatusChanged(QString strCaregiver, QString strEngineer, QString strMaintainer);
};
