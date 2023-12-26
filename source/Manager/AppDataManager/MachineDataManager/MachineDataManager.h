#pragma once
#include <QObject>
#include "Manager/AppDataManager/BasicSqlData/BasicSqlData.h"
class MachineDataManager :public BasicSqlData
{
	Q_OBJECT
private:
	MachineDataManager();
	~MachineDataManager() {};

public:
	static MachineDataManager& Instance() {
		static MachineDataManager Instance;
		return Instance;
	}
public:
	void init();
private:
public:
	//信息存取
	void readConfig();
	void saveConfig();
signals:
};
