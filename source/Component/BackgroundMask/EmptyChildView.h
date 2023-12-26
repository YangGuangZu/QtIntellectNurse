#pragma once

#include <QDialog>
#include <QFrame>
#include <QPropertyAnimation>
#include "ui_emptychildview.h"
class EmptyChildView : public QWidget
{
	Q_OBJECT

public:
	//构造函数
	EmptyChildView(QWidget* parent = Q_NULLPTR);
	//析构函数
	~EmptyChildView();
private:
	Ui::EmptyChildView ui;
	QWidget* m_pBasicWidget = nullptr;
private:
	//初始界面
	void initInterface();
public:
	void addContentPtr(QWidget* pBasicWidget,const QString & strTitle);
signals:
	void singalExitEmptyChildView();
public slots:
	void on_btnExit_clicked();
};
