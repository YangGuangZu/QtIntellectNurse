#pragma once

#include <QWidget>
#include "ui_BottomProcess.h"
#include "Define/AppDefine.h"

class CustDrawProcessWidget : public QWidget 
{
	Q_OBJECT
public:
	CustDrawProcessWidget(QWidget* parent = nullptr);
	~CustDrawProcessWidget();
private:
	QString m_strCurrProcess;
	QStringList m_lststrProcess;
private:
	void paintEvent(QPaintEvent* event) override;
public:
	void setProcessList(const QStringList& lststrProcess);
	QStringList getProcessList();

	void setCurrProcess(const QString& strCurr);
	QString getCurrProcess();
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

class BottomProcess : public QWidget
{
	Q_OBJECT

public:
	BottomProcess(QWidget *parent = nullptr);
	~BottomProcess();

private:
	Ui::BottomProcessClass ui;
	//不同类型的映射
	QMap<AppControlType, CustDrawProcessWidget*> m_mapCustDrawProcessWidget;
private:
    //初始化
    void init();
    //初始化页面
    void initForm();
public:
public slots:
	void slotSetCurrAppControlType(const AppControlType& eAppControlType);
};
