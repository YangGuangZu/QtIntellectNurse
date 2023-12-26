#pragma once
#include <QModbusRtuSerialClient>
#include "Manager/MachineManager/BasicMachine/BasicMachine.h"

class RtelligentModbusMachine :public BasicMachine
{
	Q_OBJECT
public:
	RtelligentModbusMachine();
	~RtelligentModbusMachine() {};
private:
	//串口
	QString m_strDeviceAddress;
	//波特率
	int m_iBaud = 9600;
	//校验位
	QString m_strParity;
	//数据位
	int m_iDataBit = 8; 
	//停止位
	int m_iStopBit = 1;
	//从站地址
	int m_iSlaveAddress = 1;
	//串口通讯对象
	QModbusRtuSerialClient* m_pSerialClient = nullptr;
private:
	//初始化
	void init() override;
public:	
	//链接
	bool connectDevice() override;
	//断开链接
	void disconnectDevice() override;
	//是否完成链接
	bool isConnectDevice() override;
	// 获取串口地址
	QString getDeviceAddress() const;

	// 设置串口地址
	void setDeviceAddress(const QString& address);

	// 获取波特率
	int getBaudRate() const;

	// 设置波特率
	void setBaudRate(int baud);

	// 获取校验位
	QString getParity() const;

	// 设置校验位
	void setParity(const QString& parity);

	// 获取数据位
	int getDataBits() const;

	// 设置数据位
	void setDataBits(int dataBits);

	// 获取停止位
	int getStopBits() const;

	// 设置停止位
	void setStopBits(int stopBits);

	// 获取从站地址
	int getSlaveAddress() const;

	// 设置从站地址
	void setSlaveAddress(int slaveAddress);
signals:
	//状态检测
	void sigStateChanged(QModbusDevice::State state);
	//监听设备错误
	void sigHandleDeviceError(QModbusDevice::Error newError);
	//刷新
	void sigUpdateCommunication(QModbusDataUnit::RegisterType table, int address, int size);
public slots:
	//状态检测
	void onStateChanged(QModbusDevice::State state);
	//监听设备错误
	void handleDeviceError(QModbusDevice::Error newError);
};
