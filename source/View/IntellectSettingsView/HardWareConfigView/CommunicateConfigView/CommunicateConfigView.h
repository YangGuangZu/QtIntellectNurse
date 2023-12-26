#pragma once

#include <QWidget>
#include "ui_CommunicateConfigView.h"

class CommunicateConfigView : public QWidget
{
	Q_OBJECT

public:
	CommunicateConfigView(QWidget *parent = nullptr);
	~CommunicateConfigView();

private:
	Ui::CommunicateConfigView ui;
private:
	void init();
public slots:
	void on_addBtn_clicked();
	void on_deleteBtn_clicked();
	void on_saveBtn_clicked();
	void on_updateBtn_clicked();
};
