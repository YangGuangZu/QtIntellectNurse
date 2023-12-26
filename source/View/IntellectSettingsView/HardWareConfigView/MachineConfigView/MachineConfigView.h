#pragma once

#include <QWidget>
#include "ui_MachineConfigView.h"

class MachineConfigView : public QWidget
{
	Q_OBJECT

public:
	MachineConfigView(QWidget *parent = nullptr);
	~MachineConfigView();

private:
	Ui::MachineConfigView ui;
private:
	void init();
};
