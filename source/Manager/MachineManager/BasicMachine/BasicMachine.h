#pragma once
#include <QWidget>
#include "Define/AppDefine.h"


class BasicMachine :public QObject
{
	Q_OBJECT
public:
	BasicMachine();
	~BasicMachine() {};
private:
	//初始化
	void init();
signals:
public slots:
};
