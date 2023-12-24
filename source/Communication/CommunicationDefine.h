#ifndef COMMUNICATIONDEFINE_H
#define COMMUNICATIONDEFINE_H
#include <QObject>
class CommunicationDefine : public QObject
{
	Q_OBJECT
public:
	CommunicationDefine() {};
	~CommunicationDefine() {};
public:
	enum class CommunicationIdType
	{
		//助便启动
		HelpStoolStart,
		//助便暂停
		HelpStoolPause,

		//体位启动
		PositionStart,
		//体位暂停
		PositionPause,
		//体位复位
		PositionReset,

		//大便启动
		BigStoolStart,
		//便中
		BigStoolRunning,
		//去污
		BigStoolDecontaminate,
		//清洁
		BigStoolClear,
		//烘干
		BigStoolDry,
		//大便暂停
		BigStoolPause,
		//大便复位
		BigStoolReset,

		//小便启动
		SmallStoolStart,
		//便中
		SmallStoolRunning,
		//去污
		SmallStoolDecontaminate,
		//清洁
		SmallStoolClear,
		//烘干
		SmallStoolDry,
		//小便暂停
		SmallStoolPause,
		//小便复位
		SmallStoolReset,

		//背部升降护理
		//体位启动
		BackNurseStart,
		//体位暂停
		BackNursePause,
		//体位复位
		BackNurseReset,

		//腿部升降护理
		//体位启动
		LegsNurseStart,
		//体位暂停
		LegsNursePause,
		//体位复位
		LegsNurseReset,

		//整床升降护理
		//体位启动
		BedNurseStart,
		//体位暂停
		BedNursePause,
		//体位复位
		BedNurseReset,

		//特氏位护理
		//体位启动
		TertiaryNurseStart,
		//体位暂停
		TertiaryNursePause,
		//体位复位
		TertiaryNurseReset,

		//反特氏位护理
		//体位启动
		BackTertiaryNurseStart,
		//体位暂停
		BackTertiaryNursePause,
		//体位复位
		BackTertiaryNurseReset,

		//CPR位护理
		//体位启动
		CPRNurseStart,
		//体位暂停
		CPRNursePause,
		//体位复位
		CPRNurseReset,

		//半卧位护理
		//体位启动
		SemiNurseStart,
		//体位暂停
		SemiNursePause,
		//体位复位
		SemiNurseReset,

		//左翻位护理
		//体位启动
		LeftFlipNurseStart,
		//体位暂停
		LeftFlipNursePause,
		//体位复位
		LeftFlipNurseReset,

		//右翻位护理
		//体位启动
		RightFlipNurseStart,
		//体位暂停
		RightFlipNursePause,
		//体位复位
		RightFlipNurseReset,

		//心脏位护理
		//体位启动
		HeartNurseStart,
		//体位暂停
		HeartNursePause,
		//体位复位
		HeartNurseReset,

		//背部升降
		//启动
		//复位

		//腿部升降
		//启动
		//复位

		//整床升降
		//启动
		//复位

		//特氏位
		//启动
		//复位

		//反特氏位
		//启动
		//复位

		//CPR位
		//启动
		//复位

		//半卧位
		//启动
		//复位

		//左翻位
		//启动
		//复位

		//右翻位
		//启动
		//复位

		//心脏位
		//启动
		//复位

	};
	Q_ENUM(CommunicationIdType);

private:

};

#endif //COMMUNICATIONDEFINE_H