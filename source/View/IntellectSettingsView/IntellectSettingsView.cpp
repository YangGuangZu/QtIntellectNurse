#include "IntellectSettingsView.h"
#include "Manager/AppDataManager/UserManager/UserManager.h"
#include "Manager/AppDataManager/CaregiverManager/CaregiverManager.h"
#include "Manager/AppDataManager/NetworkManager/NetworkManager.h"
#include "Manager/AppDataManager/CommunicateManager/CommunicateManager.h"
#include "Manager/AppDataManager/BasicConfigManager/BasicConfigManager.h"
#include "Manager/AppDataManager/VideoManager/VideoManager.h"
#include "Manager/AppDataManager/ScreenManager/ScreenManager.h"
#include "Component/BasicPopupView/BasicPopupView.h"
#include "Component/PopupTips/PopupManager.h"

IntellectSettingsView::IntellectSettingsView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

IntellectSettingsView::~IntellectSettingsView()
{}

void IntellectSettingsView::init()
{
	initForm();
}

void IntellectSettingsView::initForm()
{
	ui.widget->setPixmap(QPixmap(":/image/common/用户管理.png"));
	ui.widget_4->setPixmap(QPixmap(":/image/common/用户登录.png"));
	ui.widget_6->setPixmap(QPixmap(":/image/common/屏幕.png"));
	ui.widget_10->setPixmap(QPixmap(":/image/common/网络.png"));
	ui.widget_12->setPixmap(QPixmap(":/image/common/通讯设定.png"));
	connect(&UserManager::Instance(),&UserManager::signals_userLoginStatusChanged,this,[=](const bool & bIsLogin,const  UserManager::UserInfoParam* stUserInfoParam)
		{
			if (bIsLogin)
			{
				ui.labelUserName->setText(QStringLiteral("康复人: ") + stUserInfoParam->strUserName);
				ui.labelAge->setText(QStringLiteral("年龄: ") + QString::number(stUserInfoParam->uiAge));
				ui.labelNursingArea->setText(QStringLiteral("护理区: ") + stUserInfoParam->strNursingArea);
				ui.labelBedNumber->setText(QStringLiteral("床位号: ") + QString::number(stUserInfoParam->uiBedNumber));
				ui.labelAdmissionTime->setText(QStringLiteral("入住时间: ") + stUserInfoParam->strAdmissionTime);
				ui.labelCaregiv->setText(QStringLiteral("护理人: ") + stUserInfoParam->Caregiver);
			}
			else
			{
				ui.labelUserName->setText(QStringLiteral("康复人: 暂无"));
				ui.labelAge->setText(QStringLiteral("年龄: 暂无"));
				ui.labelNursingArea->setText(QStringLiteral("护理区: 暂无"));
				ui.labelBedNumber->setText(QStringLiteral("床位号: 暂无"));
				ui.labelAdmissionTime->setText(QStringLiteral("入住时间: 暂无"));
				ui.labelCaregiv->setText(QStringLiteral("护理人: 暂无"));
			}
		}
	);

	connect(&CaregiverManager::Instance(), &CaregiverManager::signals_caregiverStatusChanged, this, [=](const QString & strCaregiver, const QString & strEngineer,const QString & strMaintainer)
		{
			ui.labelCaregiver->setText(QStringLiteral("护理人: ") + strCaregiver);
			ui.labelEngineer->setText(QStringLiteral("工程师: ") + strEngineer);
			ui.labelMaintainer->setText(QStringLiteral("维护人: ") + strMaintainer);
		}
	);

	connect(&NetworkManager::Instance(), &NetworkManager::signals_networkStatusChanged, this, [=](const NetworkManager::NetworkInfoParam& stNetworkInfoParam)
		{
			ui.labelWifiName->setText(QStringLiteral("WIFI: ") + stNetworkInfoParam.wifiName);
			ui.labelWifiPassword->setText(QStringLiteral("WIFI密码: ") + stNetworkInfoParam.wifiPassword);
		}
	);

	connect(&ScreenManager::Instance(), &ScreenManager::signals_screenStatusChanged, this, [=](const ScreenManager::ScreenInfoParam& stScreenInfoParam)
		{
			ui.labelScreenBrightness->setText(QStringLiteral("屏幕亮度: ") + QString::number(stScreenInfoParam.screenBrightness));
			ui.labelScreenOffTime->setText(QStringLiteral("屏幕关闭: ") + stScreenInfoParam.screenOffTime);
		}
	);

	connect(&CommunicateManager::Instance(), &CommunicateManager::signals_communicateStatusChanged, this, [=](const CommunicateManager::CommunicateInfo& info)
		{
			ui.labelCanPort->setText(QStringLiteral("CAN端口: ") + info.canPort);
			ui.labelBaudRate->setText(QStringLiteral("波特率: ") + info.baudRate);
			ui.labelPort485A->setText(QStringLiteral("485-A端口: ") + info.port485A);
			ui.labelBaudRate485A->setText(QStringLiteral("波特率: ") + info.baudRate485A);
			ui.labelPort485B->setText(QStringLiteral("485-B端口: ") + info.port485B);
			ui.labelBaudRate485B->setText(QStringLiteral("波特率: ") + info.baudRate485B);
		}
	);
}

void IntellectSettingsView::on_btnUserLogin_clicked()
{
	PopupParams stPopupParams;
	PopupInfoParam stPopupInfoParam;
	stPopupInfoParam.title = QStringLiteral("账号:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("密码:");
	stPopupParams.append(stPopupInfoParam);

	BasicPopupView PopupView(stPopupParams, QStringLiteral("康复人登录"));
	int res = PopupView.exec();
	if (res == 1000)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("取消修改"), QtMsgType::QtFatalMsg);
		return;
	}

	UserManager::Instance().loginUser(stPopupParams.at(0).content, stPopupParams.at(1).content);
}

void IntellectSettingsView::on_btnUserRegister_clicked()
{
	PopupParams stPopupParams;
	PopupInfoParam stPopupInfoParam;
	stPopupInfoParam.title = QStringLiteral("账号:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("密码:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("康复人:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("年龄:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("护理区:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("床号:");
	stPopupParams.append(stPopupInfoParam);

	BasicPopupView PopupView(stPopupParams, QStringLiteral("康复人注册"));
	int res = PopupView.exec();
	if (res == 1000)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("取消修改"), QtMsgType::QtFatalMsg);
		return;
	}
	UserManager::UserInfoParam stUserSqlStruct;
	stUserSqlStruct.strAccount		= stPopupParams.at(0).content;
	stUserSqlStruct.strPassword		= stPopupParams.at(1).content;
	stUserSqlStruct.strUserName		= stPopupParams.at(2).content;
	stUserSqlStruct.uiAge			= stPopupParams.at(3).content.toInt();
	stUserSqlStruct.strNursingArea	= stPopupParams.at(4).content;
	stUserSqlStruct.uiBedNumber		= stPopupParams.at(5).content.toInt();

	bool isOk = UserManager::Instance().insertUser(stUserSqlStruct);
	if (isOk)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("康复人注册成功"), QtMsgType::QtFatalMsg);
	}
}

void IntellectSettingsView::on_btnUserEdit_clicked()
{

}

void IntellectSettingsView::on_btnUserExit_clicked()
{
	UserManager::Instance().exitLoginUser();
	PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("退出登录成功"), QtMsgType::QtFatalMsg);
}

void IntellectSettingsView::on_btnCaregiverEdit_clicked()
{
	PopupParams stPopupParams;
	PopupInfoParam stPopupInfoParam;
	stPopupInfoParam.title = QStringLiteral("护理人:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("工程师:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("维护人:");
	stPopupParams.append(stPopupInfoParam);

	BasicPopupView PopupView(stPopupParams, QStringLiteral("护理信息修改"));
	int res = PopupView.exec();
	if (res == 1000)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("取消修改"), QtMsgType::QtFatalMsg);
		return;
	}
	CaregiverManager::Instance().setCaregiver(stPopupParams.at(0).content);
	CaregiverManager::Instance().setEngineer(stPopupParams.at(1).content);
	CaregiverManager::Instance().setMaintainer(stPopupParams.at(2).content);
	CaregiverManager::Instance().saveConfig();
}

void IntellectSettingsView::on_btnScreenEdit_clicked()
{
	PopupParams stPopupParams;
	PopupInfoParam stPopupInfoParam;
	stPopupInfoParam.title = QStringLiteral("屏幕亮度:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("屏幕关闭:");
	stPopupParams.append(stPopupInfoParam);

	BasicPopupView PopupView(stPopupParams, QStringLiteral("屏幕信息修改"));
	int res = PopupView.exec();
	if (res == 1000)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("取消修改"), QtMsgType::QtFatalMsg);
		return;
	}

	ScreenManager::Instance().setBrightness(stPopupParams.at(0).content.toInt());
	ScreenManager::Instance().setScreenOffTime(stPopupParams.at(1).content);
	ScreenManager::Instance().saveConfig();
}

void IntellectSettingsView::on_btnWifiEdit_clicked()
{
	PopupParams stPopupParams;
	PopupInfoParam stPopupInfoParam;
	stPopupInfoParam.title = QStringLiteral("Wifi名称:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("Wifi密码:");
	stPopupParams.append(stPopupInfoParam);

	BasicPopupView PopupView(stPopupParams, QStringLiteral("Wifi信息修改"));
	int res = PopupView.exec();
	if (res == 1000)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("取消修改"), QtMsgType::QtFatalMsg);
		return;
	}

	NetworkManager::Instance().setWifiName(stPopupParams.at(0).content);
	NetworkManager::Instance().setWifiPassword(stPopupParams.at(1).content);
	NetworkManager::Instance().saveConfig();
}

void IntellectSettingsView::on_btnNetEdit_clicked()
{
	PopupParams stPopupParams;
	PopupInfoParam stPopupInfoParam;
	stPopupInfoParam.title = QStringLiteral("CAN端口:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("波特率:");
	stPopupParams.append(stPopupInfoParam);
	
	stPopupInfoParam.title = QStringLiteral("485A端口:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("485A波特率:");
	stPopupParams.append(stPopupInfoParam);
	
	stPopupInfoParam.title = QStringLiteral("485B端口:");
	stPopupParams.append(stPopupInfoParam);

	stPopupInfoParam.title = QStringLiteral("485B波特率:");
	stPopupParams.append(stPopupInfoParam);

	BasicPopupView PopupView(stPopupParams, QStringLiteral("通信信息修改"));
	int res = PopupView.exec();
	if (res == 1000)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("取消修改"), QtMsgType::QtFatalMsg);
		return;
	}

	CommunicateManager::Instance().setCanPort(stPopupParams.at(0).content);
	CommunicateManager::Instance().setBaudRate(stPopupParams.at(1).content);
	CommunicateManager::Instance().setPort485A(stPopupParams.at(2).content);
	CommunicateManager::Instance().setPort485B(stPopupParams.at(3).content);
	CommunicateManager::Instance().setBaudRate485A(stPopupParams.at(4).content);
	CommunicateManager::Instance().setBaudRate485B(stPopupParams.at(5).content);
	CommunicateManager::Instance().saveConfig();
}
