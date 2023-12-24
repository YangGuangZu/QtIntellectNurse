#include "PopupManager.h"
#include <QApplication>
#include <Manager/AppGuiManager/AppGuiManager.h>
PopupManager::PopupManager()
{
}

PopupManager::~PopupManager()
{
}

void PopupManager::clearMessageShow()
{
	qDeleteAll(m_popupList);
	m_popupList.clear();
}

void PopupManager::addPopupTip(const QString& strTitleInfo, const QString& strMsg, QtMsgType eMsgType, QWidget* parent)
{
	qDebug() << strMsg;
	if (parent == nullptr)
	{
		parent = AppGUIManager::Instance().getAppTopLevelWidget();

	}
	PopupTip* popup = new PopupTip(strTitleInfo, strMsg, eMsgType, parent);
	connect(popup, &PopupTip::sigClose, this, &PopupManager::deleteMessage);
	addMessage(popup);
}

void PopupManager::addMessage(PopupTip* popup)
{
	connect(popup, &PopupTip::sigClose, this, &PopupManager::deleteMessage);
	m_popupList.append(popup);
	notifyMessage();
}

void PopupManager::deleteMessage(PopupTip* popup)
{
	disconnect(popup, &PopupTip::sigClose, this, &PopupManager::deleteMessage);
	m_popupList.removeOne(popup);
	delete popup;
	popup = nullptr;
}

void PopupManager::notifyMessage()
{
	for (int i = 0; i < m_popupList.length(); i++) {
		m_popupList.at(i)->updatePosition();
	}
}
