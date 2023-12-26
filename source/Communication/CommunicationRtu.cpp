#include "CommunicationRtu.h"

#include <QCoreApplication>

#include <bitset>
#include <QFile>
#include <chrono>
#include <thread>
#include "Component/PopupTips/PopupManager.h"

CommunicationRtu::CommunicationRtu()
{
}

CommunicationRtu::~CommunicationRtu()
{
    disconnectDevice();
}

bool CommunicationRtu::connectDevice()
{
    disconnectDevice();
	bool isConnect = true;
	for (QHash<QString, ModbusRtuSerialClient*>::iterator it = m_hashClientBySerialPort.begin(); it != m_hashClientBySerialPort.end(); ++it)
	{
		ModbusRtuSerialClient* modbusClient = it.value();
		if (false == modbusClient->connectDevice()) 
		{
			isConnect = false;
		}
	}
    return isConnect;
}

void CommunicationRtu::disconnectDevice()
{
	for (QHash<QString, ModbusRtuSerialClient*>::iterator it = m_hashClientBySerialPort.begin(); it != m_hashClientBySerialPort.end(); ++it)
	{
		ModbusRtuSerialClient* modbusClient = it.value();
		modbusClient->disconnectDevice();
	}
}

void CommunicationRtu::start()
{
    connectDevice();
}

void CommunicationRtu::addRtuSerialClientBySerialPort(const SerialPortParams& stSerialPortParams)
{
	ModbusRtuSerialClient* modbusClient = nullptr;
	//检测当前串口是否已存在
	if (m_hashClientBySerialPort.contains(stSerialPortParams.strPort))
	{
		//如果已存在
		modbusClient = m_hashClientBySerialPort[stSerialPortParams.strPort];
		// 断开连接
		modbusClient->disconnectDevice();
	}
	else
	{
		// 创建 Modbus RTU 串口客户端
		modbusClient = new ModbusRtuSerialClient();
		modbusClient->setDisplayName(stSerialPortParams.strDisplayName);
		modbusClient->setConnectionParameter(QModbusDevice::SerialPortNameParameter, stSerialPortParams.strPort);
		modbusClient->setConnectionParameter(QModbusDevice::SerialParityParameter, stSerialPortParams.eSerialParity);
		modbusClient->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, stSerialPortParams.eSerialBaudRate);
		modbusClient->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, stSerialPortParams.eSerialDataBits);
		modbusClient->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, stSerialPortParams.eSerialStopBits);
		m_hashClientBySerialPort.insert(stSerialPortParams.strPort, modbusClient);
	}
}

ModbusRtuSerialClient* CommunicationRtu::getSerialClientBySerialPort(const QString& strSerialPort)
{
	ModbusRtuSerialClient* modbusClient = nullptr;
	//检测当前串口是否已存在
	if (m_hashClientBySerialPort.contains(strSerialPort))
	{
		//如果已存在
		modbusClient = m_hashClientBySerialPort[strSerialPort];
	}
	return modbusClient;
}

bool CommunicationRtu::isConnectDeviceBySerialPort(const QString & strSerialPort)
{
	ModbusRtuSerialClient* modbusClient = nullptr;
	//检测当前串口是否已存在
	if (m_hashClientBySerialPort.contains(strSerialPort))
	{
		//如果已存在
		modbusClient = m_hashClientBySerialPort[strSerialPort];
		if (modbusClient->state() == QModbusDevice::ConnectedState)
		{
			return true;
		}
	}
	return false;
}

QList<QSerialPortInfo> CommunicationRtu::getSerialPortInfoList()
{
	// 获取系统中的串口信息列表
	QList<QSerialPortInfo> serialPortInfoList = QSerialPortInfo::availablePorts();

	// 打印串口信息
	qDebug() << "Available serial ports:";
	for (const QSerialPortInfo& serialPortInfo : serialPortInfoList) {
		qDebug() << "Port: " << serialPortInfo.portName();
		qDebug() << "Description: " << serialPortInfo.description();
		qDebug() << "Manufacturer: " << serialPortInfo.manufacturer();
		qDebug() << "System Location: " << serialPortInfo.systemLocation();
		qDebug() << "-----------------------------------";
	}
	return serialPortInfoList;
}

QStringList CommunicationRtu::getSerialPortInfoStringList()
{
	QStringList lstSerialPortStringList;
	// 获取系统中的串口信息列表
	QList<QSerialPortInfo> serialPortInfoList = QSerialPortInfo::availablePorts();

	// 打印串口信息
	qDebug() << "Available serial ports:";
	for (const QSerialPortInfo& serialPortInfo : serialPortInfoList) {
		lstSerialPortStringList.append(serialPortInfo.portName());
		qDebug() << "Port: " << serialPortInfo.portName();
		qDebug() << "Description: " << serialPortInfo.description();
		qDebug() << "Manufacturer: " << serialPortInfo.manufacturer();
		qDebug() << "System Location: " << serialPortInfo.systemLocation();
		qDebug() << "-----------------------------------";
	}
	return lstSerialPortStringList;
}
