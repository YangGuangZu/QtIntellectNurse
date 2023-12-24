#pragma once
#include <QString>
#include <QWidget>
#include "popuptip.h"

class PopupManager :public QObject
{
	Q_OBJECT
private:
	PopupManager();
	~PopupManager();
public:
	static PopupManager& Instance() {
		static PopupManager Instance;
		return Instance;
	}
private:
	QList<PopupTip*> m_popupList;
public:
	void clearMessageShow(); 
	void addPopupTip(const QString& strTitleInfo, const QString& strMsg, QtMsgType eMsgType, QWidget* parent = nullptr);
private slots:
	void addMessage(PopupTip* popup);
	void deleteMessage(PopupTip* popup);
	void notifyMessage();
};
