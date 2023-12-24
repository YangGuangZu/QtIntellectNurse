#pragma once

#include <QProgressBar>


/// <summary>
/// 图标展示区
/// </summary>
class CustProgressBar : public QProgressBar {
    Q_OBJECT
public:
    /// <summary>
    /// 构造图标展示区域 
    /// </summary>
    explicit CustProgressBar(QWidget* parent = nullptr);
private:
protected:
    /// <summary>
    /// 绘制接口
    /// </summary>
    /// <param name="event"></param>
	void paintEvent(QPaintEvent* event);
};