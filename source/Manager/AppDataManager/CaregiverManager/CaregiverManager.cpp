#include "CaregiverManager.h"
#include "Component/PopupTips/PopupManager.h"

CaregiverManager::CaregiverManager()
{
	m_strAppFuncName = "CaregiverManager";
}

void CaregiverManager::init()
{
	readConfig();
}

void CaregiverManager::setCaregiver(const QString& value)
{
	m_strCaregiver = value;
	emit signals_caregiverStatusChanged(m_strCaregiver, m_strEngineer, m_strMaintainer);
}

void CaregiverManager::setEngineer(const QString& value)
{
	m_strEngineer = value;
	emit signals_caregiverStatusChanged(m_strCaregiver, m_strEngineer, m_strMaintainer);
}

void CaregiverManager::setMaintainer(const QString& value)
{
	m_strMaintainer = value;
	emit signals_caregiverStatusChanged(m_strCaregiver, m_strEngineer, m_strMaintainer);
}

QString CaregiverManager::getCaregiver()
{
	return m_strCaregiver;
}

QString CaregiverManager::getEngineer()
{
	return m_strEngineer;
}

QString CaregiverManager::getMaintainer()
{
	return m_strMaintainer;
}

void CaregiverManager::readConfig()
{
	QJsonObject jsonObject = readJsonObjectFromSql();
	if (jsonObject.contains("Caregiver"))
	{
		QJsonValue value = jsonObject.value("Caregiver");
		m_strCaregiver = value.toString();
	}

	if (jsonObject.contains("Engineer"))
	{
		QJsonValue value = jsonObject.value("Engineer");
		m_strEngineer = value.toString();
	}

	if (jsonObject.contains("Maintainer"))
	{
		QJsonValue value = jsonObject.value("Maintainer");
		m_strMaintainer = value.toString();
	}
	emit signals_caregiverStatusChanged(m_strCaregiver, m_strEngineer, m_strMaintainer);
}

void CaregiverManager::saveConfig()
{
	QJsonObject jsonObject;
	jsonObject.insert("Caregiver",m_strCaregiver);
	jsonObject.insert("Engineer", m_strEngineer);
	jsonObject.insert("Maintainer", m_strMaintainer);
	saveJsonObjectFromSql(jsonObject);
}