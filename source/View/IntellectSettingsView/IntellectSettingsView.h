#pragma once

#include <QWidget>
#include "ui_IntellectSettingsView.h"

class IntellectSettingsView : public QWidget
{
	Q_OBJECT

public:
	IntellectSettingsView(QWidget *parent = nullptr);
	~IntellectSettingsView();

private:
	Ui::IntellectSettingsViewClass ui;
private:
    //初始化
    void init();
    //初始化页面
    void initForm();
private slots:
	void on_btnUserLogin_clicked();
	void on_btnUserRegister_clicked();
	void on_btnUserEdit_clicked();
	void on_btnUserExit_clicked();
	void on_btnCaregiverEdit_clicked();
	void on_btnScreenEdit_clicked();
	void on_btnWifiEdit_clicked();
	void on_btnNetEdit_clicked();
};
