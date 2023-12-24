#pragma once

/*!
 * \file storagewidget.h
 * \date 2023/11/13 16:54
 *
 * \author Ygz
 * Contact: user@company.com
 *
 * \brief
 *
 * \note
 * Illustrate:
 * Nodes can be stored, and the storage type is StorageWidget::StorageDirection,
 * You can set the storage time and the distance offset corresponding to the storage direction
 * 
 * Usage method:
 * 	StorageWidget * pStorageWidget = new StorageWidget(...);
 *	pStorageWidget->setStorageTime(150);
 *	pStorageWidget->setStorageDirection(StorageWidget::StorageTop);
 *	pStorageWidget->setStorageOffset(150);
*/

#include <QWidget>
#include <QVariantAnimation>
class StorageWidget : public QWidget {
    Q_OBJECT

public:
    explicit StorageWidget(QWidget* parent);
    ~StorageWidget();
public:
    enum StorageDirection
    {
        //上
        StorageTop,
        //下
        StorageBottom,
        //左
        StorageLeft,
        //右
        StorageRight,
        //默认
        StorageDefault
    };
private:
    //收纳方向
    StorageDirection m_eStorageDirection    = StorageDefault;
    //收纳时间
    uint m_uiStorageTime                    = 100;
	//收纳偏移
	uint m_uiStorageOffset                  = 100;
    //收纳动画对象
    QVariantAnimation* m_pAniStorage        = nullptr;
    //父节点
    QWidget* m_pParent                      = nullptr;
private:
    //初始化页面
	void initView();
    //刷新节点位置
    void updateWidgetPos();
    //绘制事件
	void paintEvent(QPaintEvent* event) override;
	//事件过滤器
	bool eventFilter(QObject* watched, QEvent* event) override;
public:
    // 设置收纳方向
    StorageDirection getStorageDirection();
    void setStorageDirection(const StorageDirection & eStorageDirection);

    // 设置收纳时间
    uint getStorageTime();
    void setStorageTime(const uint & uiTime);

    // 是否已收纳
    bool getIsStorage();
    void setIsStorage(const bool& bIsStorage);

    // 设置与收纳方向相对的高度或者宽度
	uint getStorageOffset();
	void setStorageOffset(const uint& uiTime);
};