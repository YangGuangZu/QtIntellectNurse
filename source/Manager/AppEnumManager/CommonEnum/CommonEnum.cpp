#include <QSerialPort>
#include "commonenum.h"

QMetaEnum EnumClass::m_qQSerialPortParity = QMetaEnum::fromType<QSerialPort::Parity>();
QMetaEnum EnumClass::m_qQSerialPortBaudRate = QMetaEnum::fromType<QSerialPort::BaudRate>();
QMetaEnum EnumClass::m_qQSerialPortDataBits = QMetaEnum::fromType<QSerialPort::DataBits>();
QMetaEnum EnumClass::m_qQSerialPortStopBits = QMetaEnum::fromType<QSerialPort::StopBits>();

QMap<QString, QMetaEnum> EnumClass::m_qmapStr2Enum = QMap<QString, QMetaEnum>(
	{
		{EnumClass::m_qQSerialPortParity.enumName(), EnumClass::m_qQSerialPortParity},
		{EnumClass::m_qQSerialPortBaudRate.enumName(), EnumClass::m_qQSerialPortBaudRate},
		{EnumClass::m_qQSerialPortDataBits.enumName(), EnumClass::m_qQSerialPortDataBits},
		{EnumClass::m_qQSerialPortStopBits.enumName(), EnumClass::m_qQSerialPortStopBits},
	}
);

QMap<QString, QString> EnumClass::m_qmapStr2Translation = QMap<QString, QString>(
	{
		{"Baud1200", QStringLiteral("波特率1200")},
		{"Baud2400", QStringLiteral("波特率2400")},
		{"Baud4800", QStringLiteral("波特率4800")},
		{"Baud9600", QStringLiteral("波特率9600")},
		{"Baud19200", QStringLiteral("波特率19200")},
		{"Baud38400", QStringLiteral("波特率38400")},
		{"Baud57600", QStringLiteral("波特率57600")},
		{"Baud115200", QStringLiteral("波特率115200")},


		{"Data5", QStringLiteral("5位数据位")},
		{"Data6", QStringLiteral("6位数据位")},
		{"Data7", QStringLiteral("7位数据位")},
		{"Data8", QStringLiteral("8位数据位")},

		{"NoParity", QStringLiteral("无奇偶校验")},
		{"EvenParity", QStringLiteral("偶数校验")},
		{"OddParity", QStringLiteral("奇数校验")},
		{"SpaceParity", QStringLiteral("空格校验")},
		{"MarkParity", QStringLiteral("标记校验")},

		{"OneStop", QStringLiteral("1位停止位")},
		{"OneAndHalfStop", QStringLiteral("1.5位停止位")},
		{"TwoStop", QStringLiteral("2位停止位")},
	}
);

QStringList EnumClass::getItemsByEnumName(QString strName)
{
	QStringList strlst;
	for (int iIndex = 0; iIndex < m_qmapStr2Enum.value(strName).keyCount(); ++iIndex)
	{
		if (m_qmapStr2Translation.find(m_qmapStr2Enum.value(strName).key(iIndex)) != m_qmapStr2Translation.end())
		{
			strlst << m_qmapStr2Translation.value(m_qmapStr2Enum.value(strName).key(iIndex));
		}
	}

	return strlst;
}
