#pragma once

#include <QWidget>
#include "ui_HardWareConfigView.h"
#include "MachineConfigView/MachineConfigView.h"
#include "CommunicateConfigView/CommunicateConfigView.h"

struct HardWareChildView
{
	QString title;
	QWidget* pWidget = nullptr;
};

class HardWareConfigView : public QWidget
{
	Q_OBJECT

public:
	HardWareConfigView(QWidget *parent = nullptr);
	~HardWareConfigView();

private:
	Ui::HardWareConfigViewClass ui;
	//机械配置
	MachineConfigView* m_pMachineConfigView = nullptr;
	//通信配置
	CommunicateConfigView* m_pCommunicateConfigView = nullptr;

	QList<HardWareChildView> m_lstHardWareChildViews;

private:
	void init();
	void initForm();
};
