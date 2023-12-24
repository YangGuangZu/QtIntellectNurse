#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
	m_strAppFuncName = "NetworkManager";
}

void NetworkManager::init()
{
	readConfig();
}

void NetworkManager::setWifiName(const QString& wifiName)
{
	m_stNetworkInfoParam.wifiName = wifiName;
	emit signals_networkStatusChanged(m_stNetworkInfoParam);
}

void NetworkManager::setWifiPassword(const QString& wifiPassword)
{
	m_stNetworkInfoParam.wifiPassword = wifiPassword;
	emit signals_networkStatusChanged(m_stNetworkInfoParam);
}

QString NetworkManager::getWifiName() const
{
	return m_stNetworkInfoParam.wifiName;
}

QString NetworkManager::getWifiPassword() const
{
	return m_stNetworkInfoParam.wifiPassword;
}

void NetworkManager::readConfig()
{
	QJsonObject jsonObject = readJsonObjectFromSql();

	// Read from JSON object and set values
	if (jsonObject.contains("WifiName")) {
		QJsonValue value = jsonObject.value("WifiName");
		m_stNetworkInfoParam.wifiName = value.toString();
	}

	if (jsonObject.contains("WifiPassword")) {
		QJsonValue value = jsonObject.value("WifiPassword");
		m_stNetworkInfoParam.wifiPassword = value.toString();
	}

	emit signals_networkStatusChanged(m_stNetworkInfoParam);
}

void NetworkManager::saveConfig()
{
	QJsonObject jsonObject;

	// Insert values into JSON object
	jsonObject.insert("WifiName", m_stNetworkInfoParam.wifiName);
	jsonObject.insert("WifiPassword", m_stNetworkInfoParam.wifiPassword);

	// Save JSON object to file or perform necessary operations
	saveJsonObjectFromSql(jsonObject);
}
