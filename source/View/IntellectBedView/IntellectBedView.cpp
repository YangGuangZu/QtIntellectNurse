#include "IntellectBedView.h"

IntellectBedView::IntellectBedView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

IntellectBedView::~IntellectBedView()
{}

void IntellectBedView::init()
{
	initForm();
}

void IntellectBedView::initForm()
{
	ui.widget->setPixmap(QPixmap(":/image/common/智能体位护理.png"));
	//ui.widget->setDrawSize(QSize(1205, 210));

	ui.widget_17->setPixmap(QPixmap(":/image/common/启动.png"));
	ui.widget_17->setDrawSize(QSize(130, 130));

	ui.widget_6->setPixmap(QPixmap(":/image/common/暂停.png"));
	ui.widget_6->setDrawSize(QSize(130, 130));

	ui.widget_5->setPixmap(QPixmap(":/image/common/复位.png"));
	ui.widget_5->setDrawSize(QSize(130, 130));


	ui.widget_19->setPixmap(QPixmap(":/image/common/智能体位护理.png"));
	//ui.widget_19->setDrawSize(QSize(1205, 210));


	ui.widget_28->setPixmap(QPixmap(":/image/common/正转.png"));
	ui.widget_28->setDrawSize(QSize(130, 130));

	ui.widget_24->setPixmap(QPixmap(":/image/common/反转.png"));
	ui.widget_24->setDrawSize(QSize(130, 130));

	ui.widget_25->setPixmap(QPixmap(":/image/common/暂停.png"));
	ui.widget_25->setDrawSize(QSize(130, 130));

	ui.widget_26->setPixmap(QPixmap(":/image/common/复位.png"));
	ui.widget_26->setDrawSize(QSize(130, 130));

	StatusButtonNormalType stStatusButton;
	stStatusButton.pBtn = ui.toolButton_7;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::BackNurseStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::BackNursePause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::BackNurseReset;
	m_lstQAbstractButton.append(stStatusButton);

	stStatusButton.pBtn = ui.toolButton_8;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::LegsNurseStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::LegsNursePause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::LegsNurseReset;
	m_lstQAbstractButton.append(stStatusButton);

	stStatusButton.pBtn = ui.toolButton_9;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::BedNurseStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::BedNursePause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::BedNurseReset;
	m_lstQAbstractButton.append(stStatusButton);

	stStatusButton.pBtn = ui.toolButton_10;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::TertiaryNurseStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::TertiaryNursePause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::TertiaryNurseReset;
	m_lstQAbstractButton.append(stStatusButton);

	stStatusButton.pBtn = ui.toolButton_14;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::BackTertiaryNurseStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::BackTertiaryNursePause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::BackTertiaryNurseReset;
	m_lstQAbstractButton.append(stStatusButton);

	stStatusButton.pBtn = ui.toolButton_17;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::CPRNurseStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::CPRNursePause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::CPRNurseReset;
	m_lstQAbstractButton.append(stStatusButton);

	stStatusButton.pBtn = ui.toolButton_15;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::SemiNurseStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::SemiNursePause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::SemiNurseReset;
	m_lstQAbstractButton.append(stStatusButton);

	stStatusButton.pBtn = ui.toolButton_18;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::LeftFlipNurseStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::LeftFlipNursePause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::LeftFlipNurseReset;
	m_lstQAbstractButton.append(stStatusButton);

	stStatusButton.pBtn = ui.toolButton_19;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::RightFlipNurseStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::RightFlipNursePause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::RightFlipNurseReset;
	m_lstQAbstractButton.append(stStatusButton);

	stStatusButton.pBtn = ui.toolButton_16;
	stStatusButton.start = CommunicationDefine::CommunicationIdType::HeartNurseStart;
	stStatusButton.pause = CommunicationDefine::CommunicationIdType::HeartNursePause;
	stStatusButton.reset = CommunicationDefine::CommunicationIdType::HeartNurseReset;
	m_lstQAbstractButton.append(stStatusButton);

	connect(ui.widget_17, &PixmapWidget::clicked, [=]() {
		for (const StatusButtonNormalType & stStatusButton : m_lstQAbstractButton)
		{
			if (ui.buttonGroup->checkedButton() == stStatusButton.pBtn)
			{
				CommunicationRtu::Instance().sendCommunicationMassage(stStatusButton.start);
			}
		}
		}
	);

	connect(ui.widget_6, &PixmapWidget::clicked, [=]() {
		for (const StatusButtonNormalType& stStatusButton : m_lstQAbstractButton)
		{
			if (ui.buttonGroup->checkedButton() == stStatusButton.pBtn)
			{
				CommunicationRtu::Instance().sendCommunicationMassage(stStatusButton.pause);
			}
		}
		}
	);

	connect(ui.widget_5, &PixmapWidget::clicked, [=]() {
		for (const StatusButtonNormalType& stStatusButton : m_lstQAbstractButton)
		{
			if (ui.buttonGroup->checkedButton() == stStatusButton.pBtn)
			{
				CommunicationRtu::Instance().sendCommunicationMassage(stStatusButton.reset);
			}
		}
		}
	);

	CustProgressButton stCustProgressButton;
	stCustProgressButton.mix			= 0;
	stCustProgressButton.max			= 5;
	stCustProgressButton.progressBar	= ui.progressBar;
	stCustProgressButton.addBtn			= ui.pushButton;
	stCustProgressButton.reduceBtn		= ui.pushButton_3;
	stCustProgressButton.progressBar->setMinimum(stCustProgressButton.mix);
	stCustProgressButton.progressBar->setMaximum(stCustProgressButton.max);
	m_lstCustProgressButton.append(stCustProgressButton);

	stCustProgressButton.mix			= 0;
	stCustProgressButton.max			= 5;
	stCustProgressButton.progressBar	= ui.progressBar_2;
	stCustProgressButton.addBtn			= ui.pushButton_5;
	stCustProgressButton.reduceBtn		= ui.pushButton_6;
	stCustProgressButton.progressBar->setMinimum(stCustProgressButton.mix);
	stCustProgressButton.progressBar->setMaximum(stCustProgressButton.max);
	m_lstCustProgressButton.append(stCustProgressButton);

	for (CustProgressButton & stCustProgressButton: m_lstCustProgressButton)
	{
		connect(stCustProgressButton.addBtn, &QAbstractButton::clicked, [=]() {
			stCustProgressButton.progressBar->setValue(stCustProgressButton.progressBar->value() + 1);
			}
		);
		connect(stCustProgressButton.reduceBtn, &QAbstractButton::clicked, [=]() {
			stCustProgressButton.progressBar->setValue(stCustProgressButton.progressBar->value() - 1);
			}
		);
	}

}
