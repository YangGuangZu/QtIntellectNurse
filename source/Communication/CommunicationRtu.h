#ifndef COMMUNICATIONRTU_H
#define COMMUNICATIONRTU_H
#include <QWidget>
#include <QMetaEnum>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "ModbusRtuSerialClient/ModbusRtuSerialClient.h"
#include "CommunicationDefine.h"


class CommunicationRtu :public QObject
{
	Q_OBJECT
private:
	CommunicationRtu();
	~CommunicationRtu();
public:
	static CommunicationRtu& Instance() {
		static CommunicationRtu Instance;
		return Instance;
	}

private:
private:
	//所有的串口连接
	QHash<QString, ModbusRtuSerialClient*> m_hashClientBySerialPort;
private:
	//初始化modbus
	void initModbus();
	//链接
	bool connectDevice();
	//断开链接
	void disconnectDevice();
public:
	//启动modbus 通信
	void start();
	/// <summary>
	/// 通过串口新增modbus对象
	/// </summary>
	/// <param name="strPort">端口</param>
	/// <param name="eSerialParity">数据校验</param>
	/// <param name="eSerialBaudRate">波特率</param>
	/// <param name="eSerialDataBits">数据位</param>
	/// <param name="eSerialStopBits">停止位</param>
	void addRtuSerialClientBySerialPort(const SerialPortParams& stSerialPortParams);

	//获取串口对象
	ModbusRtuSerialClient* getSerialClientBySerialPort(const QString& strSerialPort);

	//是否完成链接
	bool isConnectDeviceBySerialPort(const QString & strSerialPort);
	// 获取系统中的串口信息列表
	static QList<QSerialPortInfo> getSerialPortInfoList();
	// 获取系统中得串口信息列表
	static QStringList getSerialPortInfoStringList();

};

#endif //COMMUNICATIONRTU_H