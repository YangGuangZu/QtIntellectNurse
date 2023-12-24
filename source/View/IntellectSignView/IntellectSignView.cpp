#include <QRandomGenerator>
#include "IntellectSignView.h"

IntellectSignView::IntellectSignView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

IntellectSignView::~IntellectSignView()
{}

void IntellectSignView::init()
{
	initForm();
}

void IntellectSignView::initForm()
{
    m_splineMaxSize = 40;//设置曲线的X坐标的个数
    initStoolView();
    initUrinateView();

    m_pTimeRun = new QTimer(this);
    connect(m_pTimeRun, &QTimer::timeout, this, &IntellectSignView::rollChart);
    m_pTimeRun->start(500);
    m_pTimeRun->start();
}

void IntellectSignView::initStoolView()
{
    m_pSeriesStoolSpline = new QSplineSeries();                         // 创建一个样条曲线对象
    m_pSeriesStoolSpline->setPen(QPen(QColor(0, 255, 0), 2));
    m_pChartStoolSpline = ui.graphicsStoolView->chart();             // 获取一个chart用于管理不同类型的series和其他图表相关对象
    m_pChartStoolSpline->setAnimationOptions(QChart::SeriesAnimations);
    m_pChartStoolSpline->setAnimationDuration(500);
    m_pChartStoolSpline->legend()->hide();                              // 隐藏图例
    m_pChartStoolSpline->addSeries(m_pSeriesStoolSpline);                      // 添加创建好的曲线图对象
    m_pChartStoolSpline->createDefaultAxes();                           // 基于已添加到图表中的series为图表创建轴。以前添加到图表中的任何轴都将被删除。
    m_pChartStoolSpline->axes(Qt::Horizontal).first()->setRange(0, 190);// 设置Y轴的范围
    m_pChartStoolSpline->axes(Qt::Vertical).first()->setRange(0, 20);   // 设置Y轴的范围


    //批量添加数据
    QList<QPointF> points;
    for (int i = 0; i < m_splineMaxSize; i++)
    {
        points.append(QPointF(i * 10, QRandomGenerator::global()->generate() % 15));
    }
    m_pSeriesStoolSpline->replace(points);

    ui.graphicsStoolView->setRenderHint(QPainter::Antialiasing);  // 设置抗锯齿

}

void IntellectSignView::initUrinateView()
{
    m_pSeriesUrinateSpline = new QSplineSeries();                         // 创建一个样条曲线对象
    m_pSeriesUrinateSpline->setPen(QPen(QColor(0, 255, 0), 2));
    m_pChartUrinateSpline = ui.graphicsUrinateView->chart();             // 获取一个chart用于管理不同类型的series和其他图表相关对象
    m_pChartUrinateSpline->setAnimationOptions(QChart::SeriesAnimations);
    m_pChartUrinateSpline->setAnimationDuration(500);
    m_pChartUrinateSpline->legend()->hide();                              // 隐藏图例
    m_pChartUrinateSpline->addSeries(m_pSeriesUrinateSpline);                      // 添加创建好的曲线图对象
    m_pChartUrinateSpline->createDefaultAxes();                           // 基于已添加到图表中的series为图表创建轴。以前添加到图表中的任何轴都将被删除。
    m_pChartUrinateSpline->axes(Qt::Horizontal).first()->setRange(0, 190);// 设置Y轴的范围
    m_pChartUrinateSpline->axes(Qt::Vertical).first()->setRange(0, 20);   // 设置Y轴的范围

    //批量添加数据
    QList<QPointF> points;
    for (int i = 0; i < m_splineMaxSize; i++)
    {
        points.append(QPointF(i * 10, QRandomGenerator::global()->generate() % 15));
    }
    m_pSeriesUrinateSpline->replace(points);

    ui.graphicsUrinateView->setRenderHint(QPainter::Antialiasing);  // 设置抗锯齿
}

void IntellectSignView::rollChart()
{
    m_pSeriesStoolSpline->setPen(QPen(QColor(0, 255, 0), 2));
    m_pSeriesUrinateSpline->setPen(QPen(QColor(0, 255, 0), 2));
    m_pSeriesStoolSpline->setBrush(QColor(0, 255, 0, 150));
    m_pSeriesUrinateSpline->setBrush(QColor(0, 255, 0, 150));
    for (int i = 0; i < m_splineMaxSize; i++)
    {
        m_pSeriesStoolSpline->replace(i * 10, m_pSeriesStoolSpline->at(i).y(), i * 10, 3 + QRandomGenerator::global()->generate() % 15);
    }
    for (int i = 0; i < m_splineMaxSize; i++)
    {
        m_pSeriesUrinateSpline->replace(i * 10, m_pSeriesUrinateSpline->at(i).y(), i * 10, 3 + QRandomGenerator::global()->generate() % 15);
    }
}
