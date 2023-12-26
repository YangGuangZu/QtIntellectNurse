#pragma once
#include <QWidget>
#include <QMetaEnum>

/*----------------------------------------------------------------
* 类 名 称 ：AppGUIManager
* 类 描 述 ：用于APP层常用功能
* 作    者 ：
* 创建时间 ：
* 更新时间 ：
* 版 本 号 ：v1.0.0.0
*******************************************************************/

class AppEnumManager
{
private:
	AppEnumManager();
	~AppEnumManager() {};
public:
	static AppEnumManager& Instance() {
		static AppEnumManager Instance;
		return Instance;
	}
private:
	//枚举名与枚举映射
	QMap<QString, QMetaEnum> m_qmapEnumName2Enum;
	// 枚举项中英文映射
	QMap<QString, QString> m_qmapEnum2Translation;
private:
	//初始化
	void init();
public:
	//注册枚举项翻译映射
	void installEnum2Translation(const QMap<QString, QMetaEnum>& qmapStr2Enum, const QMap<QString, QString>& qmapStr2Translation);
	//获取翻译队列
	QStringList getItemsByEnumName(QString strName, const QStringList& strlstValue);
	//获取翻译映射字符
	QString getOriStringByEnumNameAndKey(const QString & strName,const QString & strKey);
};
