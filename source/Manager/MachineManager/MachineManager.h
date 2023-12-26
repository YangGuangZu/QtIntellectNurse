#pragma once
#include <QWidget>
#include "Define/AppDefine.h"
#include "BasicMachine/BasicMachine.h"


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

	//可以控制的机器
	QList<BasicMachine*> m_lstMachine;
private:
	//初始化锐特Modbus寄存器信息
	void initRtelligentModbus();
public:
	//初始化
	void init();
signals:
public slots:
};
