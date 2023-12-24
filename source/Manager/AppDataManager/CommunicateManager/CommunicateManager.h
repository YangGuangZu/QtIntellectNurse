#pragma once
#include <QObject>
#include "Manager/AppDataManager/BasicSqlData/BasicSqlData.h"
class CommunicateManager :public BasicSqlData
{
	Q_OBJECT
private:
	CommunicateManager();
	~CommunicateManager() {};

public:
	static CommunicateManager& Instance() {
		static CommunicateManager Instance;
		return Instance;
	}
public:
	struct CommunicateInfo
	{
		QString canPort = QStringLiteral("暂无");
		QString baudRate = QStringLiteral("暂无");
		QString port485A = QStringLiteral("暂无");
		QString port485B = QStringLiteral("暂无");
		QString baudRate485A = QStringLiteral("暂无");
		QString baudRate485B = QStringLiteral("暂无");
	};

private:
	CommunicateInfo m_stCommunicateInfo;
public:
	//初始化
	void init();
	//设置信息
	void setCanPort(const QString& canPort);
	void setBaudRate(const QString& baudRate);
	void setPort485A(const QString& port485A);
	void setPort485B(const QString& port485B);
	void setBaudRate485A(const QString& baudRate485A);
	void setBaudRate485B(const QString& baudRate485B);
	//获取信息
	QString getCanPort() const;
	QString getBaudRate() const;
	QString getPort485A() const;
	QString getPort485B() const;
	QString getBaudRate485A() const;
	QString getBaudRate485B() const;
	//信息存取
	void readConfig();
	void saveConfig();
signals:
	void signals_communicateStatusChanged(CommunicateInfo info);
};
