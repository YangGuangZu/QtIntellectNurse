#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtIntellectNurse.h"

class QtIntellectNurse : public QMainWindow
{
    Q_OBJECT

public:
    QtIntellectNurse(QWidget *parent = nullptr);
    ~QtIntellectNurse();

private:
    Ui::QtIntellectNurseClass ui;
private:
    //初始化
    void init();
    //初始化样式表
    void initStyleSheet();
    //初始化页面
    void initForm();
};
