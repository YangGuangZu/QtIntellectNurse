#pragma once

#include <QWidget>


/// <summary>
/// 图标展示区
/// </summary>
class PixmapWidget : public QWidget {
    Q_OBJECT

public:
    /// <summary>
    /// 构造图标展示区域 
    /// </summary>
    explicit PixmapWidget(QWidget* parent = nullptr);
    explicit PixmapWidget(const QPixmap& icon, QWidget* parent = nullptr);
    explicit PixmapWidget(const QString& icon, QWidget* parent = nullptr);

private:
    //图标
    QPixmap m_pixmap;
    //居中绘制区域
    QSize m_sizeDraw;
protected:
    /// <summary>
    /// 绘制接口
    /// </summary>
    /// <param name="event"></param>
    void paintEvent(QPaintEvent* event);
public:
    /// <summary>
    /// 设置图标
    /// </summary>
    /// <param name="icon"></param>
    void setPixmap(const QPixmap& icon);

    /// <summary>
    /// 设置绘制居中区域
    /// </summary>
    /// <param name="size"></param>
    void setDrawSize(const QSize& size);
};