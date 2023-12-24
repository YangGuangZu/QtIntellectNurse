#pragma once
#include <QObject>
#include "Manager/AppDataManager/BasicSqlData/BasicSqlData.h"
class BasicConfigManager :public BasicSqlData
{
	Q_OBJECT
private:
	BasicConfigManager();
	~BasicConfigManager() {};

public:
	static BasicConfigManager& Instance() {
		static BasicConfigManager Instance;
		return Instance;
	}
public:
	struct DailyListParam
	{
		QTime time;
		QString somthing;
	};
	struct DayInfoStruct {
		QTime time;
		QString content;
		bool isOk;
	};
	using DailyListParams = QList<DailyListParam>;
private:
	QString m_currentPage;
	QList<DayInfoStruct> m_dayInfoList;
	DailyListParams m_lstDailyParams;
private:
	void readDayInfoList(const QJsonObject& jsonObject);
	void writeDayInfoList(QJsonObject& jsonObject) const;
public:
	//初始化
	void init();

	void setCurrentPage(const QString& currentPage);
	QString getCurrentPage() const;

	void addDayInfo(const DayInfoStruct& dayInfo);
	QList<DayInfoStruct> getDayInfoList() const;
	//信息存取
	void readConfig();
	void saveConfig();
signals:
	void signals_configChanged(const QString& currentPage, const QList<DayInfoStruct>& dayInfoList);
};
