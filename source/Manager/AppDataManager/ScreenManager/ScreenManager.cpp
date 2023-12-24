#include <QJsonObject>
#include "ScreenManager.h"
#include "Component/PopupTips/PopupManager.h"

ScreenManager::ScreenManager()
{
	m_strAppFuncName = "ScreenManager";
}

void ScreenManager::init()
{
	readConfig();
}

void ScreenManager::setBrightness(int brightness) {
	if (brightness >= 0 && brightness <= 100) {
		m_stScreenInfoParam.screenBrightness = brightness;
	}
	else {
		// Handle error: brightness value out of range
	}
	emit signals_screenStatusChanged(m_stScreenInfoParam);
}

void ScreenManager::setScreenOffTime(const QString& time) {
	m_stScreenInfoParam.screenOffTime = time;
	emit signals_screenStatusChanged(m_stScreenInfoParam);
}

int ScreenManager::getBrightness() const {
	return m_stScreenInfoParam.screenBrightness;
}

QString ScreenManager::getScreenOffTime() const {
	return m_stScreenInfoParam.screenOffTime;
}

void ScreenManager::readConfig() {
	QJsonObject jsonObject = readJsonObjectFromSql();

	// Read from JSON object and set values
	if (jsonObject.contains("Brightness")) {
		QJsonValue value = jsonObject.value("Brightness");
		m_stScreenInfoParam.screenBrightness = value.toInt();
	}

	if (jsonObject.contains("ScreenOffTime")) {
		QJsonValue value = jsonObject.value("ScreenOffTime");
		m_stScreenInfoParam.screenOffTime = value.toString();
	}
	emit signals_screenStatusChanged(m_stScreenInfoParam);
}

void ScreenManager::saveConfig() {
	QJsonObject jsonObject;

	// Insert values into JSON object
	jsonObject.insert("Brightness", m_stScreenInfoParam.screenBrightness);
	jsonObject.insert("ScreenOffTime", m_stScreenInfoParam.screenOffTime);

	// Save JSON object to file or perform necessary operations
	saveJsonObjectFromSql(jsonObject);
}