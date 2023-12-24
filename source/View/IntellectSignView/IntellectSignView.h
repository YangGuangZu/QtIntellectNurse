#pragma once

#include <QChart>
#include <QTimer>
#include <QWidget>
#include <QAreaSeries>
#include <QSplineSeries>
#include "ui_IntellectSignView.h"

class IntellectSignView : public QWidget
{
	Q_OBJECT

public:
	IntellectSignView(QWidget *parent = nullptr);
	~IntellectSignView();

private:
	Ui::IntellectSignViewClass ui;
    QTimer* m_pTimeRun;
    int m_splineMaxSize;
    //大便趋势
    QChart* m_pChartStoolSpline;
    QSplineSeries* m_pSeriesStoolSpline;
    //小便便趋势
    QChart* m_pChartUrinateSpline;
    QSplineSeries* m_pSeriesUrinateSpline;
private:
    //初始化
    void init();
    //初始化页面
    void initForm();
    void initStoolView();
    void initUrinateView();
    //模拟
private slots:
    void rollChart();
};
