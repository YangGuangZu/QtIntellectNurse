#pragma once

#include <QWidget>
#include "ui_IntellectToiletView.h"
#include "Define/AppDefine.h"	
#include "Component/PixmapWidget/PixmapWidget.h"

class IntellectToiletView : public QWidget
{
	Q_OBJECT

public:
	IntellectToiletView(QWidget *parent = nullptr);
	~IntellectToiletView();

private:
	struct ToiletPixmapWidget
	{
		double x = 0.0;
		double y = 0.0;
		PixmapWidget* w = nullptr;
	};
private:
	Ui::IntellectToiletViewClass ui;
	QList<ToiletPixmapWidget> m_lststToiletPixmapWidget;
	QList<CustProgressButton> m_lstCustProgressButton;
private:
    //初始化
    void init();
    //初始化页面
    void initForm();
	//事件重载
	bool eventFilter(QObject* watched, QEvent* event) override;
};
