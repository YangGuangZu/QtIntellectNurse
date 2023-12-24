#include "CommunicationRtu.h"

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QCoreApplication>

#include <bitset>
#include <QFile>
#include <chrono>
#include <thread>
#include "Component/PopupTips/PopupManager.h"
//读取csv的内容应是每行四个 指令1,指令2,指令3,映射枚举值
#define CSVVALUENUMBER 4

CommunicationRtu::CommunicationRtu()
{
    initInstructionID();
	initModbus();
	for (int i = 0; i < m_qCommunicationIdTypeEnum.keyCount(); ++i)
	{
		sendCommunicationMassage(CommunicationDefine::CommunicationIdType(m_qCommunicationIdTypeEnum.keyToValue(m_qCommunicationIdTypeEnum.key(i))));
	}
}

CommunicationRtu::~CommunicationRtu()
{
    disconnectDevice();
}

void CommunicationRtu::initModbus()
{
	//端口号
	m_modbusDevice.setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM3");
	//波特率
	m_modbusDevice.setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
	//校验
	m_modbusDevice.setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
	//数据位
	m_modbusDevice.setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
	//停止位
	m_modbusDevice.setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);

	QModbusDataUnitMap reg;
	reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10 });
	reg.insert(QModbusDataUnit::DiscreteInputs, { QModbusDataUnit::DiscreteInputs, 0, 10 });
	reg.insert(QModbusDataUnit::InputRegisters, { QModbusDataUnit::InputRegisters, 0, 10 });
	reg.insert(QModbusDataUnit::HoldingRegisters, { QModbusDataUnit::HoldingRegisters, 0, 10 });

	m_modbusDevice.setMap(reg);

	connect(&m_modbusDevice, &QModbusServer::dataWritten, this, &CommunicationRtu::updateCommunication);
	connect(&m_modbusDevice, &QModbusServer::stateChanged, this, &CommunicationRtu::onStateChanged);
	connect(&m_modbusDevice, &QModbusServer::errorOccurred, this, &CommunicationRtu::handleDeviceError);
}

void CommunicationRtu::initInstructionID()
{
	m_qCommunicationIdTypeEnum = QMetaEnum::fromType<CommunicationDefine::CommunicationIdType>();
	QFile file(":/CommunicationInstructionID/CommunicationInstructionID.csv");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return;
	}
	QTextStream in(&file);
	while (!in.atEnd()) 
	{
		QString line = in.readLine();
		QStringList values = line.split(',');
		values.removeAll("");
		if (values.size() == CSVVALUENUMBER)
		{
			bool isOk = false;
			CommunicationDefine::CommunicationIdType type = CommunicationDefine::CommunicationIdType(m_qCommunicationIdTypeEnum.keyToValue(values.at(3).toStdString().c_str(), &isOk));
			if (isOk)
			{
				InstructionIDParams stInstructionIDParams;
				QByteArray srcdata = QString("%1").arg(values[0].remove("0x").toUpper()).toUtf8();
				stInstructionIDParams.ID1 = QByteArray::fromHex(srcdata);
				srcdata = QString("%1").arg(values[1].remove("0x").toUpper()).toUtf8();
				stInstructionIDParams.ID2 = QByteArray::fromHex(srcdata);
				srcdata = QString("%1").arg(values[2].remove("0x").toUpper()).toUtf8();
				stInstructionIDParams.ID3 = QByteArray::fromHex(srcdata);
				m_mapInstructionID.insert(type, stInstructionIDParams);
			}
		}
	}
}

bool CommunicationRtu::connectDevice()
{
    disconnectDevice();
    if (m_modbusDevice.state() != QModbusDevice::ConnectedState)
    {
        if (m_modbusDevice.connectDevice()) 
        {
            PopupManager::Instance().addPopupTip(QStringLiteral("连接失败"), QStringLiteral("通讯链接失败 [ %1 ]").arg(m_modbusDevice.errorString()), QtMsgType::QtDebugMsg);
        }
        else
        {
            PopupManager::Instance().addPopupTip(QStringLiteral("连接成功"), QStringLiteral("通讯链接成功"), QtMsgType::QtDebugMsg);
        }
    }
    return true;
}

void CommunicationRtu::disconnectDevice()
{
    if (m_modbusDevice.state() != QModbusDevice::UnconnectedState)
    {
        m_modbusDevice.disconnectDevice();
    }
}

void CommunicationRtu::start()
{
    connectDevice();
}

bool CommunicationRtu::isConnectDevice()
{
    return (m_modbusDevice.state() == QModbusDevice::ConnectedState);
}

void CommunicationRtu::sendCommunicationMassage(const CommunicationDefine::CommunicationIdType& eType, 
	const quint16& uiCustDirection /* = 0x00 */, 
	const quint16& uiCustLen /* = 0x00 */, 
	const quint16& uiCustData1 /* = 0x00 */, 
	const quint16& uiCustData2 /* = 0x00 */)
{
	QString totalWord;
	QString startWord	= "AA";
	QString endWord		= "55";
	totalWord.append(startWord);
	totalWord.append(" ");
	totalWord.append(QByteArray::fromHex(QString::number(uiCustDirection, 16).toUtf8()).toHex());
	totalWord.append(" ");
	totalWord.append(m_mapInstructionID[eType].ID1.toHex());
	totalWord.append(" ");
	totalWord.append(m_mapInstructionID[eType].ID2.toHex());
	totalWord.append(" ");
	totalWord.append(m_mapInstructionID[eType].ID3.toHex());
	totalWord.append(" ");
	totalWord.append(QByteArray::fromHex(QString::number(uiCustLen, 16).toUtf8()).toHex());
	totalWord.append(" ");
	if (uiCustLen > 0)
	{
		totalWord.append(QByteArray::fromHex(QString::number(uiCustData1, 16).toUtf8()).toHex());
		totalWord.append(" ");
	}
	if (uiCustLen > 1)
	{
		totalWord.append(QByteArray::fromHex(QString::number(uiCustData2, 16).toUtf8()).toHex());
		totalWord.append(" ");
	}
	totalWord.append(endWord);
	qDebug() << totalWord;

	//bool isOk = false;
	//totalWord.append(QString::number(startWord.toInt(&isOk, 16)));
	//totalWord.append(" ");
	//totalWord.append(QByteArray::fromHex(QString::number(uiCustDirection, 16).toUtf8()).toHex());
	//totalWord.append(" ");
	//totalWord.append(QString::number(m_mapInstructionID[eType].ID1.toHex().toInt(&isOk, 16)));
	//totalWord.append(" ");
	//totalWord.append(QString::number(m_mapInstructionID[eType].ID2.toHex().toInt(&isOk, 16)));
	//totalWord.append(" ");
	//totalWord.append(QString::number(m_mapInstructionID[eType].ID3.toHex().toInt(&isOk, 16)));
	//totalWord.append(" ");
	//totalWord.append(QString::number(QByteArray::fromHex(QString::number(uiCustLen, 16).toUtf8()).toHex().toInt(&isOk, 16)));
	//totalWord.append(" ");
	//if (uiCustLen > 0)
	//{
	//	totalWord.append(QString::number(QByteArray::fromHex(QString::number(uiCustData1, 16).toUtf8()).toHex().toInt(&isOk, 16)));
	//	totalWord.append(" ");
	//}
	//if (uiCustLen > 1)
	//{
	//	totalWord.append(QString::number(QByteArray::fromHex(QString::number(uiCustData2, 16).toUtf8()).toHex().toInt(&isOk, 16)));
	//	totalWord.append(" ");
	//}
	//totalWord.append(endWord);
	//qDebug() << totalWord;

	PopupManager::Instance().addPopupTip(QStringLiteral("设备交互"), QStringLiteral("报文内容 [%1]").arg(totalWord), QtMsgType::QtDebugMsg);
}

void CommunicationRtu::write2client(unsigned int regStartAddr, unsigned int number)
{
}

void CommunicationRtu::onStateChanged(int state)
{
	/*if (state == QModbusDevice::UnconnectedState)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("通信连接"), QStringLiteral("通讯设备连接成功"), QtMsgType::QtDebugMsg);
	}
	else if (state == QModbusDevice::ConnectedState)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("通信连接"), QStringLiteral("通讯设备连接失败"), QtMsgType::QtDebugMsg);
	}*/
    emit sigStateChanged(state);
}

void CommunicationRtu::handleDeviceError(QModbusDevice::Error newError)
{
	if (newError == QModbusDevice::NoError)
		return;
    PopupManager::Instance().addPopupTip(QStringLiteral("通信错误"), QStringLiteral("通讯设备错误 [ %1 ]").arg(m_modbusDevice.errorString()), QtMsgType::QtDebugMsg);
    emit sigHandleDeviceError(newError);
}

void CommunicationRtu::updateCommunication(QModbusDataUnit::RegisterType table, int address, int size)
{
	emit sigUpdateCommunication(table, address, size);
}
