#pragma once
#include <QObject>
#include "Manager/AppDataManager/BasicSqlData/BasicSqlData.h"
class NetworkManager :public BasicSqlData
{
	Q_OBJECT
private:
	NetworkManager();
	~NetworkManager() {};

public:
	static NetworkManager& Instance() {
		static NetworkManager Instance;
		return Instance;
	}
public:
	struct NetworkInfoParam
	{
		QString wifiName = QStringLiteral("暂无");
		QString wifiPassword = QStringLiteral("暂无");
	};

private:
	NetworkInfoParam m_stNetworkInfoParam;
public:
	//初始化
	void init();
	//设置信息
	void setWifiName(const QString& wifiName);
	void setWifiPassword(const QString& wifiPassword);
	//获取信息
	QString getWifiName() const;
	QString getWifiPassword() const;
	//信息存取
	void readConfig();
	void saveConfig();
signals:
	void signals_networkStatusChanged(NetworkInfoParam stNetworkInfoParam);
};
