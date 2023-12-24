#include "AppStatusManager.h"
#include "Manager/AppDataManager/AppDataManager.h"

AppStatusManager::AppStatusManager() 
{
	init();
}

void AppStatusManager::init()
{
}

QMap<AppControlType, QStringList>* AppStatusManager::getMapFuncProcess()
{
	return &m_mapFuncProcess;
}

void AppStatusManager::slotSetCurrAppControlType(const AppControlType& eAppControlType)
{
	if (eAppControlType == m_currAppControlType)
	{
		return;
	}
	m_currAppControlType = eAppControlType;
	//数据记录
	AppDataManager::Instance().setCurrAppControlType(m_currAppControlType);
	emit sigCurrAppControlTypeChanged(m_currAppControlType);
}
