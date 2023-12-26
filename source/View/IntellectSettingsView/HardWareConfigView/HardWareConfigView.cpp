#include "HardWareConfigView.h"

HardWareConfigView::HardWareConfigView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

HardWareConfigView::~HardWareConfigView()
{}

void HardWareConfigView::init()
{
	initForm();
}

void HardWareConfigView::initForm()
{
	ui.listWidget->clear();

	m_pMachineConfigView = new MachineConfigView(ui.stackedWidget);
	m_pCommunicateConfigView = new CommunicateConfigView(ui.stackedWidget);

	HardWareChildView stHardWareChildView;
	stHardWareChildView.title = QStringLiteral("通讯配置");
	stHardWareChildView.pWidget = m_pCommunicateConfigView;
	m_lstHardWareChildViews.append(stHardWareChildView);

	stHardWareChildView.title = QStringLiteral("机械配置");
	stHardWareChildView.pWidget = m_pMachineConfigView;
	m_lstHardWareChildViews.append(stHardWareChildView);

	for (const HardWareChildView & stTempHardWareChildView : m_lstHardWareChildViews)
	{
		ui.listWidget->addItem(stTempHardWareChildView.title);
		ui.stackedWidget->addWidget(stTempHardWareChildView.pWidget);
	}

	connect(ui.listWidget, &QListWidget::currentTextChanged, [=](const QString& currentText) {
		for (const HardWareChildView& stTempHardWareChildView : m_lstHardWareChildViews)
		{
			if (currentText == stTempHardWareChildView.title)
			{
				ui.stackedWidget->setCurrentWidget(stTempHardWareChildView.pWidget);
			}
		}
		}
	);
}
