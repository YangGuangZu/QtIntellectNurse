#include "CommunicateManager.h"

CommunicateManager::CommunicateManager()
{
	m_strAppFuncName = "CommunicateManager";
}

void CommunicateManager::init()
{
	readConfig();
}

void CommunicateManager::setCanPort(const QString& canPort)
{
	m_stCommunicateInfo.canPort = canPort;
	emit signals_communicateStatusChanged(m_stCommunicateInfo);
}

void CommunicateManager::setBaudRate(const QString& baudRate)
{
	m_stCommunicateInfo.baudRate = baudRate;
	emit signals_communicateStatusChanged(m_stCommunicateInfo);
}

void CommunicateManager::setPort485A(const QString& port485A)
{
	m_stCommunicateInfo.port485A = port485A;
	emit signals_communicateStatusChanged(m_stCommunicateInfo);
}

void CommunicateManager::setPort485B(const QString& port485B)
{
	m_stCommunicateInfo.port485B = port485B;
	emit signals_communicateStatusChanged(m_stCommunicateInfo);
}

void CommunicateManager::setBaudRate485A(const QString& baudRate485A)
{
	m_stCommunicateInfo.baudRate485A = baudRate485A;
	emit signals_communicateStatusChanged(m_stCommunicateInfo);
}

void CommunicateManager::setBaudRate485B(const QString& baudRate485B)
{
	m_stCommunicateInfo.baudRate485B = baudRate485B;
	emit signals_communicateStatusChanged(m_stCommunicateInfo);
}

QString CommunicateManager::getCanPort() const
{
	return m_stCommunicateInfo.canPort;
}

QString CommunicateManager::getBaudRate() const
{
	return m_stCommunicateInfo.baudRate;
}

QString CommunicateManager::getPort485A() const
{
	return m_stCommunicateInfo.port485A;
}

QString CommunicateManager::getPort485B() const
{
	return m_stCommunicateInfo.port485B;
}

QString CommunicateManager::getBaudRate485A() const
{
	return m_stCommunicateInfo.baudRate485A;
}

QString CommunicateManager::getBaudRate485B() const
{
	return m_stCommunicateInfo.baudRate485B;
}

void CommunicateManager::readConfig()
{
	QJsonObject jsonObject = readJsonObjectFromSql();

	// Read from JSON object and set values
	if (jsonObject.contains("CanPort")) {
		QJsonValue value = jsonObject.value("CanPort");
		m_stCommunicateInfo.canPort = value.toString();
	}

	if (jsonObject.contains("BaudRate")) {
		QJsonValue value = jsonObject.value("BaudRate");
		m_stCommunicateInfo.baudRate = value.toString();
	}

	if (jsonObject.contains("Port485A")) {
		QJsonValue value = jsonObject.value("Port485A");
		m_stCommunicateInfo.port485A = value.toString();
	}

	if (jsonObject.contains("Port485B")) {
		QJsonValue value = jsonObject.value("Port485B");
		m_stCommunicateInfo.port485B = value.toString();
	}

	if (jsonObject.contains("BaudRate485A")) {
		QJsonValue value = jsonObject.value("BaudRate485A");
		m_stCommunicateInfo.baudRate485A = value.toString();
	}

	if (jsonObject.contains("BaudRate485B")) {
		QJsonValue value = jsonObject.value("BaudRate485B");
		m_stCommunicateInfo.baudRate485B = value.toString();
	}

	emit signals_communicateStatusChanged(m_stCommunicateInfo);
}

void CommunicateManager::saveConfig()
{
	QJsonObject jsonObject;

	// Insert values into JSON object
	jsonObject.insert("CanPort", m_stCommunicateInfo.canPort);
	jsonObject.insert("BaudRate", m_stCommunicateInfo.baudRate);
	jsonObject.insert("Port485A", m_stCommunicateInfo.port485A);
	jsonObject.insert("Port485B", m_stCommunicateInfo.port485B);
	jsonObject.insert("BaudRate485A", m_stCommunicateInfo.baudRate485A);
	jsonObject.insert("BaudRate485B", m_stCommunicateInfo.baudRate485B);

	// Save JSON object to file or perform necessary operations
	saveJsonObjectFromSql(jsonObject);
}
