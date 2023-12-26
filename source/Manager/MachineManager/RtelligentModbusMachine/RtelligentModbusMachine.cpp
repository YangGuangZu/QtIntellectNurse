#include "Communication/CommunicationRtu.h"
#include "RtelligentModbusMachine.h"

RtelligentModbusMachine::RtelligentModbusMachine()
	: BasicMachine()
{
}

void RtelligentModbusMachine::init()
{

}

bool RtelligentModbusMachine::connectDevice()
{
	m_pSerialClient = CommunicationRtu::Instance().getSerialClientBySerialPort(m_strDeviceAddress);
	if (nullptr == m_pSerialClient)
	{
		return false;
	}
	connect(m_pSerialClient, &QModbusDevice::stateChanged, this, &RtelligentModbusMachine::onStateChanged);
	connect(m_pSerialClient, &QModbusDevice::errorOccurred, this, &RtelligentModbusMachine::handleDeviceError);

	return true;
}

void RtelligentModbusMachine::disconnectDevice()
{
	disconnect(m_pSerialClient, &QModbusDevice::stateChanged, this, &RtelligentModbusMachine::onStateChanged);
	disconnect(m_pSerialClient, &QModbusDevice::errorOccurred, this, &RtelligentModbusMachine::handleDeviceError);
	m_pSerialClient = nullptr;
}

bool RtelligentModbusMachine::isConnectDevice()
{
	if (nullptr == m_pSerialClient)
	{
		return true;
	}
	if (m_pSerialClient->state() == QModbusDevice::ConnectedState)
	{
		return true;
	}
	return false;
}

QString RtelligentModbusMachine::getDeviceAddress() const {
	return m_strDeviceAddress;
}

void RtelligentModbusMachine::setDeviceAddress(const QString& address) {
	m_strDeviceAddress = address;
}

int RtelligentModbusMachine::getBaudRate() const {
	return m_iBaud;
}

void RtelligentModbusMachine::setBaudRate(int baud) {
	m_iBaud = baud;
}

QString RtelligentModbusMachine::getParity() const {
	return m_strParity;
}

void RtelligentModbusMachine::setParity(const QString& parity) {
	m_strParity = parity;
}

int RtelligentModbusMachine::getDataBits() const {
	return m_iDataBit;
}

void RtelligentModbusMachine::setDataBits(int dataBits) {
	m_iDataBit = dataBits;
}

int RtelligentModbusMachine::getStopBits() const {
	return m_iStopBit;
}

void RtelligentModbusMachine::setStopBits(int stopBits) {
	m_iStopBit = stopBits;
}

int RtelligentModbusMachine::getSlaveAddress() const {
	return m_iSlaveAddress;
}

void RtelligentModbusMachine::setSlaveAddress(int slaveAddress) {
	m_iSlaveAddress = slaveAddress;
}

void RtelligentModbusMachine::onStateChanged(QModbusDevice::State state)
{

}

void RtelligentModbusMachine::handleDeviceError(QModbusDevice::Error newError)
{

}
