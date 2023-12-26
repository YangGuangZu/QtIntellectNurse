#include "HomeView.h"

HomeView::HomeView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

HomeView::~HomeView()
{}

void HomeView::init()
{
	initForm();
}

void HomeView::initForm()
{
	initTableWidget();
	ui.widget_11->setPixmap(QPixmap(":/image/home/mianimg.png"));
	ui.widget_11->setDrawSize(QSize(752, 234));

	ui.widget_17->setPixmap(QPixmap(":/image/common/启动.png"));
	ui.widget_17->setDrawSize(QSize(130, 130));

	ui.widget_6->setPixmap(QPixmap(":/image/common/暂停.png"));
	ui.widget_6->setDrawSize(QSize(130, 130));

	ui.widget_5->setPixmap(QPixmap(":/image/common/复位.png"));
	ui.widget_5->setDrawSize(QSize(130, 130));

	StatusButtonNormalType stStatusButton;
	stStatusButton.pBtn = ui.toolButton_17;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::HelpStoolStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::HelpStoolPause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::BackNurseReset;
	m_lstQAbstractButton.append(stStatusButton);

	stStatusButton.pBtn = ui.toolButton_15;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::PositionStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::PositionPause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::PositionReset;
	m_lstQAbstractButton.append(stStatusButton);

	stStatusButton.pBtn = ui.toolButton_16;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::BigStoolStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::BigStoolPause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::BigStoolReset;
	m_lstQAbstractButton.append(stStatusButton);

	stStatusButton.pBtn = ui.toolButton_18;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::SmallStoolStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::SmallStoolPause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::SmallStoolReset;
	m_lstQAbstractButton.append(stStatusButton);

	connect(ui.widget_17, &PixmapWidget::clicked, [=]() {
		for (const StatusButtonNormalType& stStatusButton : m_lstQAbstractButton)
		{
			if (ui.buttonGroup->checkedButton() == stStatusButton.pBtn)
			{
				//CommunicationRtu::Instance().sendCommunicationMassage(stStatusButton.start);
			}
		}
		}
	);

	connect(ui.widget_6, &PixmapWidget::clicked, [=]() {
		for (const StatusButtonNormalType& stStatusButton : m_lstQAbstractButton)
		{
			if (ui.buttonGroup->checkedButton() == stStatusButton.pBtn)
			{
				//CommunicationRtu::Instance().sendCommunicationMassage(stStatusButton.pause);
			}
		}
		}
	);
		
	connect(ui.widget_5, &PixmapWidget::clicked, [=]() {
		for (const StatusButtonNormalType& stStatusButton : m_lstQAbstractButton)
		{
			if (ui.buttonGroup->checkedButton() == stStatusButton.pBtn)
			{
				//CommunicationRtu::Instance().sendCommunicationMassage(stStatusButton.reset);
			}
		}
		}
	);
}

void HomeView::initTableWidget()
{
	ui.tableWidget->setFocusPolicy(Qt::NoFocus);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);;
	ui.tableWidget->horizontalHeader()->setStyleSheet("background-color: #F4F6F8");
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	//用一个for嵌套循环遍历每一个表格让其元素居中
	//下面是我只调用了一个日期信息让其显示在一个表格子里而已
	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		ui.tableWidget->setRowHeight(i, 50);
		for (int j = 0; j < ui.tableWidget->columnCount(); j++)
		{
			ui.tableWidget->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			
			ui.tableWidget->item(i, j)->setFont(QFont("Microsoft Yahei", 12));
		}
	}
}
