#pragma once
#include <QWidget>
#include "Define/AppDefine.h"


class MachineManager :public QObject
{
	Q_OBJECT
private:
	MachineManager();
	~MachineManager() {};
public:
	static MachineManager& Instance() {
		static MachineManager Instance;
		return Instance;
	}
private:
	QMap<ModbusMachineType, ModbusRegisters> m_mapMachineTypeToModbusRegisters;
private:
	//初始化锐特Modbus寄存器信息
	void initRtelligentModbus();
public:
	//初始化
	void init();
signals:
public slots:
};
