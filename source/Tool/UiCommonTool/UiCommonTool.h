#pragma once
#include <QWidget>
#include <QPainter>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>

class UICommonTool
{
public:
#pragma region 基础工具
	/// <summary>
	/// 过长字符使用...代替
	/// </summary>
	/// <param name="font">针对对象字体</param>
	/// <param name="oriString">原文文本</param>
	/// <param name="width">宽度阈值,过长即截断</param>
	/// <param name="mode">
	/// 截取方式
	/// ElideLeft 左侧替代
	/// ElideRight 右侧替代
	/// ElideMiddle 中间截取
	/// ElideNone 不截取
	/// </param>
	/// <returns>裁剪过后文字文本</returns>
	static QString fontMetricsElidedText(const QFont& font, const QString& oriString, int width, Qt::TextElideMode mode = Qt::ElideRight);

	/// <summary>
	/// 使用Qt弱属性变更节点样式
	/// </summary>
	/// <param name="w">节点对象</param>
	/// <param name="name">属性名</param>
	/// <param name="value">变更值</param>
	static void paintDirectLineWidget(QWidget* w, QPaintEvent* event);

	/// <summary>
	/// 使用Qt弱属性变更节点样式
	/// </summary>
	/// <param name="w">节点对象</param>
	/// <param name="name">属性名</param>
	/// <param name="value">变更值</param>
	static void changComponentProperty(QWidget* w, const char* name, const QVariant& value);
	
	/// <summary>
	/// 一个矩形在另一个矩形中保持宽高缩放比
	/// </summary>
	/// <param name="rectA">转换缩放的对象的目标</param>
	/// <param name="rectB">转换缩放的对象</param>
	/// <param name="rectRes">rectB 转换后 保持宽高比的对象</param>
	/// <param name="dScale">缩放系数</param>
	static void getScaleRectByOtherRect(const QRectF& rectA, const QRectF& rectB, QRectF& scaledRect, qreal & dScale);

	/// <summary>
	/// 获取B基于A的中心偏移量
	/// </summary>
	/// <param name="rectA">矩形A</param>
	/// <param name="rectB">矩形B</param>
	/// <param name="xOffset">X偏移值</param>
	/// <param name="yOffset">X偏移值</param>
	static void centerRectInRect(const QRect& rectA, const QRect& rectB, int& xOffset, int& yOffset);

	/// <summary>
	/// 获取基于原图的旋转图像
	/// </summary>
	/// <param name="oriPix">原图</param>
	/// <param name="tarPix">结果图</param>
	/// <param name="iAngle">旋转角度</param>
	static void getRotatePixmap(const QPixmap& oriPix, QPixmap& tarPix, int iAngle);

	/// <summary>
	/// 设置文字控件颜色
	/// </summary>
	/// <param name="label">设置对象</param>
	/// <param name="color">颜色</param>
	/// <param name="colorrole"></param>
	static void SetLabelColor(QLabel* label, QColor color, QPalette::ColorRole colorrole = QPalette::NColorRoles);

	/// <summary>
	/// 设置文字控件字体
	/// </summary>
	/// <param name="label"></param>
	/// <param name="fontsize"></param>
	/// <param name="family"></param>
	/// <param name="bold"></param>
	static void SetLabelFont(QLabel* label, int fontsize, QString& family, bool bold = false);

	/// <summary>
	/// 设置占位属性
	/// </summary>
	/// <param name="w"></param>
	/// <param name="isRetain"></param>
	static void setRetainSizeWhenHidden(QWidget * w,bool isRetain);
#pragma endregion

#pragma region QLineEdit 相关
	enum class LineEditInputType
	{
		//只能输入整数
		Int,
		//只能输入中文
		Chinese,
		//只许输入字母
		English,
		//只许输入大写字母
		UpEnglish,
		//只许输入小写字母
		SmallEnglish,
		//只许输入字母和数字
		NumberAndEnglish,
		//输入时间格式（年月日格式）
		TimeDate,
		//输入时间格式（月-日-年）
		TimeDate2,
		//输入时间格式
		TimeDate3,
		//输入IP格式
		IPConfig,
		//输入MAC地址格式
		MacConfig,
		//输入License号格式
		License,
		//只许输入字母, 数字和下划线
		NumberAndEnglishAndUnderline,
	};
	static void setLineEditInputType(QLineEdit* pLineEdit, LineEditInputType eType);
#pragma endregion

#pragma region QPainter 绘制
	/// <summary>
	/// 绘制居中图像
	/// </summary>
	/// <param name="painter">绘制句柄</param>
	/// <param name="objRect">绘制区域</param>
	/// <param name="oriPixmap">绘制图像</param>
	static QRect drawAlignCenterPixmap(QPainter * painter, QRect & objRect,const QPixmap & oriPixmap);

	/// <summary>
	/// 绘制居中文字
	/// </summary>
	/// <param name="painter">绘制句柄</param>
	/// <param name="objRect">绘制区域</param>
	/// <param name="font">对象字体</param>
	/// <param name="oriString">原有文本</param>
	static QRect drawAlignCenterText(QPainter * painter, QRect & objRect,const QFont & font ,const QString & oriString);
#pragma endregion
};