#pragma once

#include <QObject>
#include <QMetaEnum>

class EnumClass : public QObject
{
	Q_OBJECT

public:
	EnumClass() {};
	~EnumClass() {};

public:
	static QMetaEnum m_qQSerialPortParity;
	static QMetaEnum m_qQSerialPortBaudRate;
	static QMetaEnum m_qQSerialPortDataBits;
	static QMetaEnum m_qQSerialPortStopBits;

	static QMap<QString, QMetaEnum> m_qmapStr2Enum;

	static QMap<QString, QString> m_qmapStr2Translation; // 枚举项中英文映射

	static QStringList getItemsByEnumName(QString strName);
};