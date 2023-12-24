#pragma once

#include <QWidget>
#include "ui_HomeView.h"
#include "Define/AppDefine.h"	
#include "Communication/CommunicationRtu.h"	

class HomeView : public QWidget
{
	Q_OBJECT

public:
	HomeView(QWidget *parent = nullptr);
	~HomeView();

private:
	Ui::HomeViewClass ui;
	QList<StatusButtonNormalType> m_lstQAbstractButton;
private:
    //初始化
    void init();
    //初始化页面
    void initForm();
    //初始化表格
    void initTableWidget();
};
