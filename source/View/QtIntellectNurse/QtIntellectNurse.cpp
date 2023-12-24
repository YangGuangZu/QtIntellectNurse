#include <QFile>
#include "QtIntellectNurse.h"
#include "Component/PixmapWidget/PixmapWidget.h"
#include "Manager/AppStatusManager/AppStatusManager.h"
#include "Manager/AppGuiManager/AppGuiManager.h"
#include "Manager/MachineManager/MachineManager.h"
#include "Tool/UICommonTool/UICommonTool.h"

QtIntellectNurse::QtIntellectNurse(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	init();
}

QtIntellectNurse::~QtIntellectNurse()
{}

void QtIntellectNurse::init()
{
	MachineManager::Instance().init();
	CommunicationRtu::Instance().start();
	initStyleSheet();
	initForm();
}

void QtIntellectNurse::initStyleSheet()
{
	//以stylesheet组件模式存在
	//程序内部 字体设置统一
	qApp->setFont(QFont("Microsoft Yahei"));
	//加载样式表
	QString qss;
	QFile file(":/qss/qss.css");
	if (file.open(QFile::ReadOnly)) {
		QStringList list;
		QTextStream in(&file);
		while (!in.atEnd()) {
			QString line;
			in >> line;
			list << line;
		}
		qss = list.join("\n");
		QString paletteColor = qss.mid(23, 7);
		qApp->setPalette(QPalette(paletteColor));
		file.close();
	}
	qApp->setStyleSheet("file:///:/qss/qss.css");
}

void QtIntellectNurse::initForm()
{
	AppGUIManager::Instance().setAppTopLevelWidget(this);
	initButton();
	//showFullScreen();
	setFixedSize(QSize(1920, 1080));
	setWindowFlags(Qt::FramelessWindowHint);

	//图标设置
	ui.soundIcon->setPixmap(QPixmap(":/image/home/volume.png"));
	ui.networkIcon->setPixmap(QPixmap(":/image/home/wifi.png"));
	ui.temperatureIcon->setPixmap(QPixmap(":/image/common/温度.png"));
	ui.humidityIcon->setPixmap(QPixmap(":/image/common/湿度.png"));
	//ui.homeIcon->setPixmap(QPixmap(":/image/common/图层 15.png"));
	ui.huHeader->setPixmap(QPixmap(":/image/home/common.png"));
	ui.userHeader->setPixmap(QPixmap(":/image/home/common.png"));

	ui.soundIcon->setDrawSize(QSize(18, 28));
	ui.networkIcon->setDrawSize(QSize(18, 28));
	ui.humidityIcon->setDrawSize(QSize(18, 28));
	ui.temperatureIcon->setDrawSize(QSize(18, 28));

	//流程栏
	m_pBottomProcess			= new BottomProcess(ui.widget_5);
	ui.horizontalLayout_7->addWidget(m_pBottomProcess);

	//主要功能页面
	m_pHomeView					= new HomeView(ui.stackedWidget);
	m_pIntellectBedView			= new IntellectBedView(ui.stackedWidget);
	m_pIntellectToiletView		= new IntellectToiletView(ui.stackedWidget);
	m_pIntellectArmView			= new IntellectArmView(ui.stackedWidget);
	m_pIntellectSignView		= new IntellectSignView(ui.stackedWidget);
	m_pIntellectVideoView		= new IntellectVideoView(ui.stackedWidget);
	m_pIntellectSettingsView	= new IntellectSettingsView(ui.stackedWidget);

	ui.stackedWidget->addWidget(m_pHomeView);
	ui.stackedWidget->addWidget(m_pIntellectBedView);
	ui.stackedWidget->addWidget(m_pIntellectToiletView);
	ui.stackedWidget->addWidget(m_pIntellectArmView);
	ui.stackedWidget->addWidget(m_pIntellectSignView);
	ui.stackedWidget->addWidget(m_pIntellectVideoView);
	ui.stackedWidget->addWidget(m_pIntellectSettingsView);

	ui.stackedWidget->setCurrentWidget(m_pHomeView);
	AppStatusManager::Instance().slotSetCurrAppControlType(AppControlType::TypeIntellectHome);
}

void QtIntellectNurse::initButton()
{
	m_mapButtonForWidget.insert(ui.IntellectBedBtn,			ui.widget_10);
	m_mapButtonForWidget.insert(ui.IntellectToiletBtn,		ui.widget_11);
	m_mapButtonForWidget.insert(ui.IntellectArmBtn,			ui.widget_12);
	m_mapButtonForWidget.insert(ui.IntellectSignBtn,		ui.widget_13);
	m_mapButtonForWidget.insert(ui.IntellectSettingsBtn,	ui.widget_8);
	m_mapButtonForWidget.insert(ui.IntellectVideoBtn,		ui.widget_9);

	connect(ui.buttonGroup, &QButtonGroup::buttonClicked, [=](QAbstractButton* btn) {
		for (QMap<QAbstractButton*, QWidget*>::iterator it = m_mapButtonForWidget.begin(); it != m_mapButtonForWidget.end(); ++it)
		{
			UICommonTool::changComponentProperty(it.value(), "MainButtonChecked", it.key() == btn);
		}
		update();
		}
	);
}

void QtIntellectNurse::on_IntellectHomeBtn_clicked()
{
	AppStatusManager::Instance().slotSetCurrAppControlType(AppControlType::TypeIntellectHome);
	ui.stackedWidget->setCurrentWidget(m_pHomeView);
}


void QtIntellectNurse::on_IntellectBedBtn_clicked()
{
	AppStatusManager::Instance().slotSetCurrAppControlType(AppControlType::TypeIntellectBed);
	ui.stackedWidget->setCurrentWidget(m_pIntellectBedView);
}

void QtIntellectNurse::on_IntellectToiletBtn_clicked()
{
	AppStatusManager::Instance().slotSetCurrAppControlType(AppControlType::TypeIntellectToilet);
	ui.stackedWidget->setCurrentWidget(m_pIntellectToiletView);
}

void QtIntellectNurse::on_IntellectArmBtn_clicked()
{
	AppStatusManager::Instance().slotSetCurrAppControlType(AppControlType::TypeIntellectArm);
	ui.stackedWidget->setCurrentWidget(m_pIntellectArmView);
}

void QtIntellectNurse::on_IntellectSignBtn_clicked()
{
	AppStatusManager::Instance().slotSetCurrAppControlType(AppControlType::TypeIntellectSign);
	ui.stackedWidget->setCurrentWidget(m_pIntellectSignView);
}

void QtIntellectNurse::on_IntellectVideoBtn_clicked()
{
	AppStatusManager::Instance().slotSetCurrAppControlType(AppControlType::TypeIntellectVideo);
	ui.stackedWidget->setCurrentWidget(m_pIntellectVideoView);
}

void QtIntellectNurse::on_IntellectSettingsBtn_clicked()
{
	AppStatusManager::Instance().slotSetCurrAppControlType(AppControlType::TypeIntellectSettings);
	ui.stackedWidget->setCurrentWidget(m_pIntellectSettingsView);
}
