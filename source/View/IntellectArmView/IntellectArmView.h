#pragma once

#include <QWidget>
#include "ui_IntellectArmView.h"

class IntellectArmView : public QWidget
{
	Q_OBJECT

public:
	IntellectArmView(QWidget *parent = nullptr);
	~IntellectArmView();

private:
	Ui::IntellectArmViewClass ui;
private:
    //初始化
    void init();
    //初始化页面
    void initForm();
};
