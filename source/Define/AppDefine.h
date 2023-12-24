#ifndef APPDEFINE_H
#define APPDEFINE_H
#include <QMap>
#include <QStringList>
#include <QAbstractButton>
#include <QProgressBar>
#include "Communication/CommunicationDefine.h"

struct StatusButtonNormalType
{
	QAbstractButton* pBtn;
	//开始
	CommunicationDefine::CommunicationIdType start;
	//暂停
	CommunicationDefine::CommunicationIdType pause;
	//复位
	CommunicationDefine::CommunicationIdType reset;
};

struct StatusButtonDirectionType
{
	QAbstractButton* pBtn;
	//正转
	CommunicationDefine::CommunicationIdType foreward;
	//反转
	CommunicationDefine::CommunicationIdType reversal;
	//暂停
	CommunicationDefine::CommunicationIdType pause;
	//复位
	CommunicationDefine::CommunicationIdType reset;
};

struct CustProgressButton
{
	uint mix = 0;
	uint max = 5;
	uint value = 1;
	QProgressBar* progressBar = nullptr;
	QAbstractButton* addBtn = nullptr;
	QAbstractButton* reduceBtn = nullptr;
};

//程序控制类型
enum class AppControlType
{
	//首页
	TypeIntellectHome,

	//智能床体
	TypeIntellectBed,

	//智能马桶
	TypeIntellectToilet,

	//智能手臂
	TypeIntellectArm,

	//体征监测
	TypeIntellectSign,

	//娱乐视频
	TypeIntellectVideo,

	//系统设置
	TypeIntellectSettings,

	//默认值
	TypeIntellectDefault,
};

//程序功能类型
enum class AppFunctionType
{
	//助便
	FuncHelpStool,
	//体位
	FuncPosition,
	//大便
	FuncStool,
	//小便
	FuncUrinate,
	//背部升降
	FuncBackLifting,
	//腿部升降
	FuncLegsLifting,
	//整床升降
	FuncBedLifting,
	//特氏位
	FuncTertiaryLifting,
	//反特氏位
	FuncBackTertiaryLifting,
	//CPR位
	FuncCPRLifting,
	//半卧位
	FuncSemirecumbentLifting,
	//左翻位
	FuncLeftLifting,
	//右翻位
	FuncRightLifting,
	//心脏位
	FuncHeartLifting,
	//床体前升降
	FuncBedFrontLifring,
	//床体后升降
	FuncBedBackLifring,
	//背部升降
	FuncBackLifring,
	//腿部升降
	FuncLegsLifring,
	//马桶升降
	FuncClosestoolLifring,
	//床单左后升降
	FuncSheetLeftBackLifring,
	//床单右后升降
	FuncSheetRightBackLifring,
	//床单左前升降
	FuncSheetLeftFrontLifring,
	//床单右前升降
	FuncSheetRightFrontLifring,
	//马桶盖伸缩
	FuncClosestoolTelescoping,
	//默认值
	FuncDefault,
};

enum class ModbusMachineType
{
	//锐特modbus
	MachineRtelligent,
};

struct ModbusRegister
{
	//复制对象大小 -32768 ~ 32767 short
	//寄存器地址
	uint uiRegisterAddress = UINT64_MAX;
	//操作类型
	QString strOperationType;
	//数据类型
	QString strDataType;
	//功能说明
	QString strDetails;
};

using ModbusRegisters = QList<ModbusRegister>;
#endif //APPDEFINE_H