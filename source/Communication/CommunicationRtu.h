#ifndef COMMUNICATIONRTU_H
#define COMMUNICATIONRTU_H
#include <QWidget>
#include <QMetaEnum>
#include <QModbusRtuSerialServer>
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
	struct InstructionIDParams
	{
		QByteArray ID1;
		QByteArray ID2;
		QByteArray ID3;
	};
private:
	QMetaEnum m_qCommunicationIdTypeEnum;
	QModbusRtuSerialServer m_modbusDevice;
	QMap<CommunicationDefine::CommunicationIdType, InstructionIDParams> m_mapInstructionID;
private:
	//初始化modbus
	void initModbus();
	//初始化指令ID
	void initInstructionID();
	//链接
	bool connectDevice();
	//断开链接
	void disconnectDevice();
public:
	//启动modbus 通信
	void start();
	//是否完成链接
	bool isConnectDevice();
	/// <summary>
	/// 设置modbus发送信息
	/// </summary>
	/// <param name="eType">指令类型</param>
	/// <param name="uiCustLen">自定义数据长度</param>
	/// <param name="uiCustData1">自定义数据1</param>
	/// <param name="uiCustData2">自定义数据2</param>
	void sendCommunicationMassage(const CommunicationDefine::CommunicationIdType& eType, const quint16& uiCustDirection = 0x00, const quint16& uiCustLen = 0x00, const quint16& uiCustData1 = 0x00, const quint16& uiCustData2 = 0x00);
private:
	/// <summary>
	/// 上位机向下位机的某个寄存器写入数据
	/// 向指定下位机寄存器写入数据
	/// </summary>
	/// <param name="regStartAddr">参数a 下位机寄存器起始地址</param>
	/// <param name="number">参数b 写入值</param>
	void write2client(unsigned int regStartAddr, unsigned int number);
signals:
	//状态检测
	void sigStateChanged(int state);
	//监听设备错误
	void sigHandleDeviceError(QModbusDevice::Error newError);
	//刷新
	void sigUpdateCommunication(QModbusDataUnit::RegisterType table, int address, int size);
public slots:
	//状态检测
	void onStateChanged(int state);
	//监听设备错误
	void handleDeviceError(QModbusDevice::Error newError);
	//刷新
	void updateCommunication(QModbusDataUnit::RegisterType table, int address, int size);
};

#endif //COMMUNICATIONRTU_H