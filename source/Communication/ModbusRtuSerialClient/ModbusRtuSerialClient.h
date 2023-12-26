#pragma once

#include <QObject>
#include <QSerialPort>
#include <QModbusRtuSerialClient>

struct SerialPortParams
{
	QString strDisplayName;
	QString strPort;
	QSerialPort::Parity eSerialParity = QSerialPort::NoParity;
	QSerialPort::BaudRate eSerialBaudRate = QSerialPort::Baud9600;
	QSerialPort::DataBits eSerialDataBits = QSerialPort::Data8;
	QSerialPort::StopBits eSerialStopBits = QSerialPort::OneStop;
};

class ModbusRtuSerialClient  : public QModbusRtuSerialClient
{
	Q_OBJECT

public:
	ModbusRtuSerialClient(QObject *parent = nullptr);
	~ModbusRtuSerialClient();
private:
	//展示用别名
	QString m_strDisplayName;
public:
	//获取展示用别名
	QString getDisplayName();
	//设置展示用别名
	void setDisplayName(const QString & strDisplayName);
};
