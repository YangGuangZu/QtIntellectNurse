#pragma once
#include <QWidget>
#include "Define/AppDefine.h"
class AppStatusManager :public QObject
{
	Q_OBJECT
private:
	AppStatusManager();
	~AppStatusManager() {};
public:
	static AppStatusManager& Instance() {
		static AppStatusManager Instance;
		return Instance;
	}
private:
	AppControlType m_currAppControlType = AppControlType::TypeIntellectDefault;
	QMap<AppControlType, QStringList> m_mapFuncProcess =
	{
		{AppControlType::TypeIntellectHome,QStringList() <<
		QStringLiteral("便前") <<
		QStringLiteral("便中") <<
		QStringLiteral("去污") <<
		QStringLiteral("清洁") <<
		QStringLiteral("烘干") <<
		QStringLiteral("完成")
		},
		{AppControlType::TypeIntellectBed,QStringList() <<
		QStringLiteral("运行") <<
		QStringLiteral("完成")
		},
		{AppControlType::TypeIntellectToilet,QStringList() <<
		QStringLiteral("运行") <<
		QStringLiteral("完成")
		},
		{AppControlType::TypeIntellectArm,QStringList() <<
		QStringLiteral("运行") <<
		QStringLiteral("完成")
		},
		{AppControlType::TypeIntellectSign,QStringList() <<
		QStringLiteral("运行") <<
		QStringLiteral("完成")
		},
		{AppControlType::TypeIntellectVideo,QStringList() <<
		QStringLiteral("运行") <<
		QStringLiteral("完成")
		},
		{AppControlType::TypeIntellectSettings,QStringList() <<
		QStringLiteral("运行") <<
		QStringLiteral("完成")
		},
	};
private:
	//初始化
	void init();
public:
	QMap<AppControlType, QStringList> * getMapFuncProcess();
signals:
	//当前程序控制状态变更
	void sigCurrAppControlTypeChanged(AppControlType eAppControlType);
public slots:
	//设置当前程序控制状态
	void slotSetCurrAppControlType(const AppControlType & eAppControlType);
};
