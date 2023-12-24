#pragma once
#include <QObject>
#include "Manager/AppDataManager/BasicSqlData/BasicSqlData.h"
class ScreenManager :public BasicSqlData
{
	Q_OBJECT
private:
	ScreenManager();
	~ScreenManager() {};

public:
	static ScreenManager& Instance() {
		static ScreenManager Instance;
		return Instance;
	}
public:
	struct ScreenInfoParam
	{
		//亮度
		int screenBrightness = 50;
		//关闭屏幕时间
		QString screenOffTime = QStringLiteral("十分钟");
	};
private:
	ScreenInfoParam m_stScreenInfoParam;
public:
	//初始化
	void init();
	//设置信息
	void setBrightness(int brightness);
	void setScreenOffTime(const QString& time);
	//获取信息
	int getBrightness() const;
	QString getScreenOffTime() const;
	//信息存取
	void readConfig();
	void saveConfig();
signals:
	void signals_screenStatusChanged(ScreenInfoParam stScreenInfoParam);
};
