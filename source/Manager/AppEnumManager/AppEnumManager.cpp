#include "appenummanager.h"
#include "CommonEnum/CommonEnum.h"
AppEnumManager::AppEnumManager()
{
	init();
}

void AppEnumManager::init()
{
	installEnum2Translation(EnumClass::m_qmapStr2Enum, EnumClass::m_qmapStr2Translation);
}

void AppEnumManager::installEnum2Translation(const QMap<QString, QMetaEnum>& qmapStr2Enum, const QMap<QString, QString>& qmapStr2Translation)
{
	//添加枚举对象
	QStringList lststrEnumNamekeys = m_qmapEnumName2Enum.keys();
	for (QMap<QString, QMetaEnum>::const_iterator it = qmapStr2Enum.begin(); it != qmapStr2Enum.end(); ++it)
	{
		if (!lststrEnumNamekeys.contains(it.key()))
		{
			m_qmapEnumName2Enum.insert(it.key(), it.value());
		}
	}

	//添加翻译
	QStringList keys = m_qmapEnum2Translation.keys();
	for (QMap<QString, QString>::const_iterator it = qmapStr2Translation.begin(); it != qmapStr2Translation.end(); ++it)
	{
		if (!keys.contains(it.key()))
		{
			m_qmapEnum2Translation.insert(it.key(), it.value());
		}
	}
}

QStringList AppEnumManager::getItemsByEnumName(QString strName, const QStringList& strlstValue)
{
	QStringList strlst;
	for (int iIndex = 0; iIndex < m_qmapEnumName2Enum.value(strName).keyCount(); ++iIndex)
	{
		if (strlstValue.contains(m_qmapEnumName2Enum.value(strName).key(iIndex)))
		{
			if (m_qmapEnum2Translation.find(m_qmapEnumName2Enum.value(strName).key(iIndex)) != m_qmapEnum2Translation.end())
			{

				strlst << m_qmapEnum2Translation.value(m_qmapEnumName2Enum.value(strName).key(iIndex));
			}
		}
	}

	return strlst;
}

QString AppEnumManager::getOriStringByEnumNameAndKey(const QString& strName, const QString& strKey)
{
	QString string;
	for (int iIndex = 0; iIndex < m_qmapEnumName2Enum.value(strName).keyCount(); ++iIndex)
	{
		if (m_qmapEnumName2Enum.value(strName).key(iIndex))
		{
			if (m_qmapEnum2Translation.keys().contains(strKey))
			{
				string = m_qmapEnum2Translation.value(strKey);
			}
		}
	}
	return string;
}

