#pragma once

#include <QFrame>
#include <QHBoxLayout>
#include <QToolButton>

class BackGroundMask : public QFrame
{
	Q_OBJECT
public:
	BackGroundMask(QWidget *parent = Q_NULLPTR);
	~BackGroundMask();
private:
	QHBoxLayout* m_pHorizontalLayout;
	QWidget* m_pChildWidget = nullptr;
	bool isClickedClose = false;
private:
	/// <summary>
	/// 初始化
	/// </summary>
	void init();

	void mousePressEvent(QMouseEvent* event);
	bool eventFilter(QObject* watched, QEvent* event);
	void paintEvent(QPaintEvent* event) override;
public:
	/// <summary>
	/// 添加子节点
	/// </summary>
	/// <param name="child">子节点对象</param>
	void addContentPtr(QWidget* pBasicWidget, const QString& strTitle = QStringLiteral("暂无介绍"));
public:
	/// <summary>
	/// 带有边框阴影的背景遮罩 QDialog使用
	/// </summary>
	/// <param name="parent"></param>
	static BackGroundMask* getBackGroundMaskWithShadow(QWidget* parent = Q_NULLPTR);

	/// <summary>
	/// 基础背景遮罩
	/// </summary>
	/// <param name="parent"></param>
	static BackGroundMask* getBackGroundMask(QWidget* parent = Q_NULLPTR);

	/// <summary>
	/// 点击背景关闭的背景遮罩
	/// </summary>
	/// <param name="parent"></param>
	/// <returns></returns>
	static BackGroundMask* getClickedBackGroundMask(QWidget* parent = Q_NULLPTR);
signals:
	void signals_closeSelf();
};