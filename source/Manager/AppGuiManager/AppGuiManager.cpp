#include <QIcon>
#include <QApplication>
#include "appguimanager.h"

AppGUIManager::AppGUIManager() 
	:QObject()
{
	init();
}

void AppGUIManager::init()
{
}

void AppGUIManager::setAppTopLevelWidget(QWidget* w)
{
	m_widgetTopLevel = w;
}

QWidget* AppGUIManager::getAppTopLevelWidget()
{
	QWidget* widgetTopLevel = m_widgetTopLevel;
	if (widgetTopLevel == nullptr)
	{
		widgetTopLevel = QApplication::activeWindow();
	}
	return widgetTopLevel;
}

void AppGUIManager::activateTopLevelWindow()
{
	if (m_widgetTopLevel) {
		m_widgetTopLevel->show();
		m_widgetTopLevel->raise();
		m_widgetTopLevel->activateWindow(); // 激活窗口
	}
}