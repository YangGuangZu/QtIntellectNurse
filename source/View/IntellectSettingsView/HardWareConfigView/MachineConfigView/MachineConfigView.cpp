#include "MachineConfigView.h"

MachineConfigView::MachineConfigView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

MachineConfigView::~MachineConfigView()
{}

void MachineConfigView::init()
{
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自动设置列宽

}
