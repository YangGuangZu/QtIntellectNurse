#pragma once

#include <QWidget>
#include "ui_IntellectBedView.h"
#include "Define/AppDefine.h"	
#include "Communication/CommunicationRtu.h"	

class IntellectBedView : public QWidget
{
	Q_OBJECT

public:
	IntellectBedView(QWidget *parent = nullptr);
	~IntellectBedView();

private:
private:
	Ui::IntellectBedViewClass ui;
	QList<StatusButtonNormalType> m_lstQAbstractButton;
	QList<CustProgressButton> m_lstCustProgressButton;
private:
    //初始化
    void init();
    //初始化页面
    void initForm();
};
