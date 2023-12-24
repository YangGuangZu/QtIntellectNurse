#include <QFile>
#include <QTextStream>
#include "MachineManager.h"

//锐特Modbus寄存器CSV读取个数
#define RTELLIGENT_MODBUS_CSV_VALUE_NUMBER 4

MachineManager::MachineManager()
{
}

void MachineManager::init()
{
	initRtelligentModbus();
}

void MachineManager::initRtelligentModbus()
{
	ModbusRegisters stModbusRegisters;

	QFile file(QStringLiteral(":/CommunicationInstructionID/NT60_ModbusRTU_寄存器汇总.csv"));

	if (false == file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		m_mapMachineTypeToModbusRegisters.insert(ModbusMachineType::MachineRtelligent, stModbusRegisters);
		return;
	}


	QTextStream in(&file);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		QStringList values = line.split(',');
		values.removeAll("");
		if (values.size() == RTELLIGENT_MODBUS_CSV_VALUE_NUMBER)
		{
			ModbusRegister stSingleModbusRegister;
			bool isuiRegisterAddressOk = false;
			uint uiRegisterAddress = values.at(0).toInt(&isuiRegisterAddressOk);
			if (true == isuiRegisterAddressOk)
			{
				stSingleModbusRegister.uiRegisterAddress = uiRegisterAddress;
			}
			stSingleModbusRegister.strOperationType = values.at(1);
			stSingleModbusRegister.strDataType = values.at(2);
			stSingleModbusRegister.strDetails = values.at(3);
			stModbusRegisters.append(stSingleModbusRegister);
		}
	}

	m_mapMachineTypeToModbusRegisters.insert(ModbusMachineType::MachineRtelligent, stModbusRegisters);
}
