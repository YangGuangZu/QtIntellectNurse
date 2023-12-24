#include "UserManager.h"
#include "Component/PopupTips/PopupManager.h"

UserManager::UserManager()
{
	m_strAppFuncName = "UserManager";
}

void UserManager::init()
{
	m_tableName = "Users";
	APPSqlData::CreateTableStruct loginTable;
	loginTable.tableName = m_tableName;

	// 添加账号
	APPSqlData::CreateTableParam accountParam;
	accountParam.name = "Account";
	accountParam.type = APPSqlData::CreateType::TEXT;
	accountParam.bIsCanNull = false;  // 不允许为空
	accountParam.bIsUnique = true;  // 确保唯一
	loginTable.content.append(accountParam);

	// 添加用户名列
	APPSqlData::CreateTableParam usernameParam;
	usernameParam.name = "Username";
	usernameParam.type = APPSqlData::CreateType::TEXT;
	usernameParam.bIsCanNull = false;  // 不允许为空
	loginTable.content.append(usernameParam);

	// 添加密码列
	APPSqlData::CreateTableParam passwordParam;
	passwordParam.name = "Password";
	passwordParam.type = APPSqlData::CreateType::TEXT;
	passwordParam.bIsCanNull = false;  // 不允许为空
	loginTable.content.append(passwordParam);

	// 添加年龄列
	APPSqlData::CreateTableParam ageParam;
	ageParam.name = "Age";
	ageParam.type = APPSqlData::CreateType::INTEGER; // 假设年龄为整数类型
	ageParam.bIsCanNull = true; // 可以为空，根据实际情况设置
	loginTable.content.append(ageParam);

	// 添加护理区域列
	APPSqlData::CreateTableParam nursingAreaParam;
	nursingAreaParam.name = "NursingArea";
	nursingAreaParam.type = APPSqlData::CreateType::TEXT; // 可能是文本类型，根据需求设置
	nursingAreaParam.bIsCanNull = true; // 可以为空，根据实际情况设置
	loginTable.content.append(nursingAreaParam);

	// 添加床位号列
	APPSqlData::CreateTableParam bedNumberParam;
	bedNumberParam.name = "BedNumber";
	bedNumberParam.type = APPSqlData::CreateType::INTEGER; // 假设床位号为整数类型
	bedNumberParam.bIsCanNull = true; // 可以为空，根据实际情况设置
	loginTable.content.append(bedNumberParam);

	// 添加入院时间列
	APPSqlData::CreateTableParam admissionTimeParam;
	admissionTimeParam.name = "AdmissionTime";
	admissionTimeParam.type = APPSqlData::CreateType::INTEGER; // 可能是日期时间类型，根据需求设置
	admissionTimeParam.bIsCanNull = true; // 可以为空，根据实际情况设置
	loginTable.content.append(admissionTimeParam);

	// 添加护理人列
	APPSqlData::CreateTableParam caregiverParam;
	caregiverParam.name = "Caregiver";
	caregiverParam.type = APPSqlData::CreateType::TEXT; // 可能是文本类型，根据需求设置
	caregiverParam.bIsCanNull = true; // 可以为空，根据实际情况设置
	loginTable.content.append(caregiverParam);

	// 调用函数生成创建表的SQL语句
	APPSqlData::SqlOperaDetails stSqlOperaDetails;
	QString createTableSQL = APPSqlData::Instance().getCreateTableParamsString(loginTable, stSqlOperaDetails);
	readConfig();
}

bool UserManager::insertUser(const UserInfoParam& stUserSqlStruct)
{
	QString queryString = QString("INSERT INTO %1 (Account, Password, UserName, Age, NursingArea, BedNumber, AdmissionTime, Caregiver) VALUES ('%2', '%3', '%4', %5, '%6', %7, '%8', '%9');")
		.arg(m_tableName)
		.arg(stUserSqlStruct.strAccount)
		.arg(stUserSqlStruct.strPassword)
		.arg(stUserSqlStruct.strUserName)
		.arg(stUserSqlStruct.uiAge)
		.arg(stUserSqlStruct.strNursingArea)
		.arg(stUserSqlStruct.uiBedNumber)
		.arg(stUserSqlStruct.strAdmissionTime)
		.arg(stUserSqlStruct.Caregiver);

	APPSqlData::SqlOperaDetails stSqlOperaDetails;
	APPSqlData::Instance().execInsertFunc(queryString, stSqlOperaDetails);
	return stSqlOperaDetails.isOk;
}

bool UserManager::checkLogin(const QString& account, const QString& password, APPSqlData::SqlOperaDetails & stSqlOperaDetails)
{
	m_bIsLogin = false;
	QString queryString = QString("SELECT * FROM %1 WHERE Account='%2';").arg(m_tableName).arg(account);

	QSqlQuery query = APPSqlData::Instance().execQueryFunc(queryString, stSqlOperaDetails);
	if (query.next())
	{
		QString storedHashedPassword = query.value("Password").toString();

		// 这里简化为直接比较密码，实际应用中不推荐
		if (password == storedHashedPassword)
		{
			m_bIsLogin = true;
			m_currUser.strAccount			= query.value("Account").toString();
			m_currUser.strPassword			= query.value("Password").toString();
			m_currUser.strUserName			= query.value("UserName").toString();
			m_currUser.uiAge				= query.value("Age").toInt();
			m_currUser.strNursingArea		= query.value("NursingArea").toString();
			m_currUser.uiBedNumber			= query.value("BedNumber").toInt();
			m_currUser.strAdmissionTime		= query.value("AdmissionTime").toString();
			m_currUser.Caregiver			= query.value("Caregiver").toString();
			PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("登录成功"), QtMsgType::QtDebugMsg);

			emit signals_userLoginStatusChanged(m_bIsLogin, &m_currUser);
			return true;
		}
		else
		{
			PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("密码错误"), QtMsgType::QtFatalMsg);
			return false;
		}
	}
	else
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("没有找到账户"), QtMsgType::QtFatalMsg);
		return false;
	}
	return false;
}

void UserManager::loginUser(const QString& account, const QString& password)
{
	APPSqlData::SqlOperaDetails stSqlOperaDetails;
	m_bIsLogin = checkLogin(account, password, stSqlOperaDetails);
	if (m_bIsLogin)
	{
		return;
	}
}

void UserManager::exitLoginUser()
{
	m_bIsLogin = false;
	emit signals_userLoginStatusChanged(m_bIsLogin);
}

void UserManager::readConfig()
{
	QJsonObject jsonObject = readJsonObjectFromSql();

	// Read from JSON object and set values
	bool isLogin = false;
	QString strAccount, strPassword;
	if (jsonObject.contains("Account")) {
		QJsonValue value = jsonObject.value("Account");
		strAccount = value.toString();
	}
	if (jsonObject.contains("Password")) {
		QJsonValue value = jsonObject.value("Password");
		strPassword = value.toString();
	}
	if (jsonObject.contains("IsLogin")) {
		QJsonValue value = jsonObject.value("IsLogin");
		isLogin = value.toBool();
	}

	if (isLogin)
	{
		loginUser(strAccount, strPassword);
	}
}

void UserManager::saveConfig()
{
	QJsonObject jsonObject;

	// Insert values into JSON object
	jsonObject.insert("Account", m_currUser.strAccount);
	jsonObject.insert("Password", m_currUser.strPassword);
	jsonObject.insert("IsLogin", m_bIsLogin);

	// Save JSON object to file or perform necessary operations
	saveJsonObjectFromSql(jsonObject);
}
