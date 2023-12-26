#include "ModbusRtuSerialClient.h"

ModbusRtuSerialClient::ModbusRtuSerialClient(QObject *parent)
	: QModbusRtuSerialClient(parent)
{}

ModbusRtuSerialClient::~ModbusRtuSerialClient()
{}

QString ModbusRtuSerialClient::getDisplayName()
{
	return m_strDisplayName;
}

void ModbusRtuSerialClient::setDisplayName(const QString & strDisplayName)
{
	m_strDisplayName = strDisplayName;
}
