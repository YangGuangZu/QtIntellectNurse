#pragma once
#include <QWidget>

/*----------------------------------------------------------------
* 类 名 称 ：AppGUIManager
* 类 描 述 ：用于APP层常用功能
* 作    者 ：
* 创建时间 ：
* 更新时间 ：
* 版 本 号 ：v1.0.0.0
*******************************************************************/

class AppGUIManager :public QObject
{
	Q_OBJECT
private:
	AppGUIManager();
	~AppGUIManager() {};
public:
	static AppGUIManager& Instance() {
		static AppGUIManager Instance;
		return Instance;
	}
private:
	//应用程序的顶级节点
	QWidget* m_widgetTopLevel = nullptr;
private:
	//初始化
	void init();
public:
	//设置顶级节点
	void setAppTopLevelWidget(QWidget* w);
	//获取顶级节点
	QWidget* getAppTopLevelWidget();
	//激活顶级节点
	void activateTopLevelWindow();
};
