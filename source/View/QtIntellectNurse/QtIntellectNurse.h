#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtIntellectNurse.h"
#include "View/HomeView/HomeView.h"
#include "View/IntellectArmView/IntellectArmView.h"
#include "View/IntellectBedView/IntellectBedView.h"
#include "View/IntellectSettingsView/IntellectSettingsView.h"
#include "View/IntellectSignView/IntellectSignView.h"
#include "View/IntellectToiletView/IntellectToiletView.h"
#include "View/IntellectVideoView/IntellectVideoView.h"
#include "BottomProcess/BottomProcess.h"
#include "Communication/CommunicationRtu.h"

class QtIntellectNurse : public QMainWindow
{
    Q_OBJECT

public:
    QtIntellectNurse(QWidget *parent = nullptr);
    ~QtIntellectNurse();

private:
    Ui::QtIntellectNurseClass ui;
    //主页
    HomeView*               m_pHomeView                 = nullptr;
    //智能床位
    IntellectBedView*       m_pIntellectBedView         = nullptr;
    //智能马桶
    IntellectToiletView*    m_pIntellectToiletView      = nullptr;
    //智能手臂
    IntellectArmView*       m_pIntellectArmView         = nullptr;
    //体征监测
    IntellectSignView*      m_pIntellectSignView        = nullptr;
    //娱乐视频
    IntellectVideoView*     m_pIntellectVideoView       = nullptr;
    //系统设置
    IntellectSettingsView*  m_pIntellectSettingsView    = nullptr;
    //流程栏
    BottomProcess*          m_pBottomProcess            = nullptr;
    //主界面按钮映射列表
    QMap<QAbstractButton*, QWidget*> m_mapButtonForWidget;
private:
    //初始化
    void init();
    //初始化样式表
    void initStyleSheet();
    //初始化页面
    void initForm();
    //初始化按钮
    void initButton();
public slots:
    //智能床位
    void on_IntellectHomeBtn_clicked();
    //智能床位
    void on_IntellectBedBtn_clicked();
    //智能马桶
    void on_IntellectToiletBtn_clicked();
    //智能手臂
    void on_IntellectArmBtn_clicked();
    //体征监测
    void on_IntellectSignBtn_clicked();
    //娱乐视频
    void on_IntellectVideoBtn_clicked();
    //系统设置
    void on_IntellectSettingsBtn_clicked();
};
