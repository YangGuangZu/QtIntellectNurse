#include <QJsonArray>
#include "basicconfigmanager.h"

BasicConfigManager::BasicConfigManager()
{
	m_strAppFuncName = "BasicConfigManager";
}

void BasicConfigManager::init()
{
	m_lstDailyParams.clear();

	DailyListParam stDailyListParam;
	stDailyListParam.time = QTime(7, 00);
	stDailyListParam.somthing = QStringLiteral("起床洗漱");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(7, 15);
	stDailyListParam.somthing = QStringLiteral("两便清洗");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(7, 30);
	stDailyListParam.somthing = QStringLiteral("服药早餐");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(8, 00);
	stDailyListParam.somthing = QStringLiteral("身体护理");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(9, 30);
	stDailyListParam.somthing = QStringLiteral("户外活动");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(11, 00);
	stDailyListParam.somthing = QStringLiteral("返回喝水");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(12, 00);
	stDailyListParam.somthing = QStringLiteral("午餐");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(14, 00);
	stDailyListParam.somthing = QStringLiteral("身体护理");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(14, 30);
	stDailyListParam.somthing = QStringLiteral("视听娱乐");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(15, 30);
	stDailyListParam.somthing = QStringLiteral("就医");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(16, 30);
	stDailyListParam.somthing = QStringLiteral("喝水");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(17, 00);
	stDailyListParam.somthing = QStringLiteral("身体护理");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(18, 00);
	stDailyListParam.somthing = QStringLiteral("服药晚餐");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(19, 00);
	stDailyListParam.somthing = QStringLiteral("亲情连线");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(20, 00);
	stDailyListParam.somthing = QStringLiteral("喝水洗澡");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(21, 00);
	stDailyListParam.somthing = QStringLiteral("睡前清洗");
	m_lstDailyParams.append(stDailyListParam);

	stDailyListParam.time = QTime(22, 00);
	stDailyListParam.somthing = QStringLiteral("休息");
	m_lstDailyParams.append(stDailyListParam);

	readConfig();
}

void BasicConfigManager::setCurrentPage(const QString& currentPage)
{
	m_currentPage = currentPage;
	emit signals_configChanged(m_currentPage, m_dayInfoList);
}

QString BasicConfigManager::getCurrentPage() const
{
	return m_currentPage;
}

void BasicConfigManager::addDayInfo(const DayInfoStruct& dayInfo)
{
	m_dayInfoList.append(dayInfo);
	emit signals_configChanged(m_currentPage, m_dayInfoList);
}

QList<BasicConfigManager::DayInfoStruct> BasicConfigManager::getDayInfoList() const
{
	return m_dayInfoList;
}

void BasicConfigManager::readConfig()
{
	QJsonObject jsonObject = readJsonObjectFromSql();

	// Read from JSON object and set values
	if (jsonObject.contains("CurrentPage")) {
		QJsonValue value = jsonObject.value("CurrentPage");
		m_currentPage = value.toString();
	}

	if (jsonObject.contains("DayInfoList")) {
		QJsonValue value = jsonObject.value("DayInfoList");
		readDayInfoList(value.toObject());
	}

	emit signals_configChanged(m_currentPage, m_dayInfoList);
}

void BasicConfigManager::saveConfig()
{
	QJsonObject jsonObject;

	// Insert values into JSON object
	jsonObject.insert("CurrentPage", m_currentPage);
	writeDayInfoList(jsonObject);

	// Save JSON object to file or perform necessary operations
	saveJsonObjectFromSql(jsonObject);
}

void BasicConfigManager::readDayInfoList(const QJsonObject& jsonObject)
{
	m_dayInfoList.clear();
	QJsonArray dayInfoArray = jsonObject.value("DayInfoList").toArray();

	for (const QJsonValue& value : dayInfoArray) {
		QJsonObject dayInfoObject = value.toObject();
		DayInfoStruct dayInfo;

		dayInfo.time = QTime::fromString(dayInfoObject.value("Time").toString());
		dayInfo.content = dayInfoObject.value("Content").toString();
		dayInfo.isOk = dayInfoObject.value("IsOk").toBool();

		m_dayInfoList.append(dayInfo);
	}
}

void BasicConfigManager::writeDayInfoList(QJsonObject& jsonObject) const
{
	QJsonArray dayInfoArray;
	for (const DayInfoStruct& dayInfo : m_dayInfoList) {
		QJsonObject dayInfoObject;
		dayInfoObject.insert("Time", dayInfo.time.toString("hh:mm"));
		dayInfoObject.insert("Content", dayInfo.content);
		dayInfoObject.insert("IsOk", dayInfo.isOk);

		dayInfoArray.append(dayInfoObject);
	}

	jsonObject.insert("DayInfoList", dayInfoArray);
}
