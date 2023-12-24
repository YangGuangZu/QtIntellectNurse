#pragma once
#include <QWidget>
#include "Define/AppDefine.h"
class AppDataManager :public QObject
{
	Q_OBJECT
private:
	AppDataManager();
	~AppDataManager() {};
public:
	static AppDataManager& Instance() {
		static AppDataManager Instance;
		return Instance;
	}
private:
	//表明
	QString m_tableName;
	//当前页面功能
	AppControlType m_currAppControlType = AppControlType::TypeIntellectDefault;
private:
	//初始化
	void init();
	//初始化
	void initSqlTable();
public:
	void setCurrAppControlType(const AppControlType & eAppControlType);
};
