#include "IntellectArmView.h"

IntellectArmView::IntellectArmView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

IntellectArmView::~IntellectArmView()
{}

void IntellectArmView::init()
{
	initForm();
}

void IntellectArmView::initForm()
{
	ui.widget_3->setPixmap(QPixmap(":/image/common/管道.png"));
	ui.widget_3->setDrawSize(QSize(325, 236));
	ui.widget_4->setPixmap(QPixmap(":/image/common/TCP角度.png"));
	ui.widget_4->setDrawSize(QSize(205, 237));
}
