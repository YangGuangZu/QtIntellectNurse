#pragma once
#include "Define/AppDefine.h"


class BasicMachine :public QObject
{
	Q_OBJECT
public:
	BasicMachine();
	~BasicMachine() {};
private:
private:
	//初始化
	virtual void init() = NULL;
public:
	//链接
	virtual bool connectDevice() = NULL;
	//断开链接
	virtual void disconnectDevice() = NULL;
	//是否完成链接
	virtual bool isConnectDevice() = NULL;
signals:
public slots:
};
