#include "EmptyChildView.h"
EmptyChildView::EmptyChildView(QWidget* parent /*= Q_NULLPTR*/)
	:QWidget(parent)
{
	ui.setupUi(this);
	initInterface();
}

EmptyChildView::~EmptyChildView()
{

}

void EmptyChildView::initInterface()
{

}


void EmptyChildView::addContentPtr(QWidget* pBasicWidget,const QString & strTitle)
{
	ui.title->setText(strTitle);
	m_pBasicWidget = pBasicWidget;
	ui.verticalLayout_2->addWidget(pBasicWidget);
	pBasicWidget->show();
}

void EmptyChildView::on_btnExit_clicked()
{
	emit singalExitEmptyChildView();
}
