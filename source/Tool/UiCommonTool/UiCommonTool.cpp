#include <QStyle>
#include <QStyleOption>
#include <QTransform>
#include <QRegularExpressionValidator>
#include "UICommonTool.h"

void UICommonTool::changComponentProperty(QWidget * w, const char * name, const QVariant & value)
{
	w->setProperty(name, value);
	w->style()->unpolish(w);
	w->style()->polish(w);
}

void UICommonTool::getScaleRectByOtherRect(const QRectF& rectA, const QRectF& rectB, QRectF& scaledRect, qreal & dScale)
{
	if (0 == rectB.width() || 0 == rectB.height() || 0 == rectA.width() || 0 == rectA.height())
	{
		dScale = 1.0;
		return;
	}

	// 计算矩形 B 的长宽比
	double aspectRatio = rectB.width() / rectB.height();

	// 确定应该使用哪个尺寸（宽度或高度）来适应矩形 A
	if (rectA.width() / aspectRatio <= rectA.height()) {
		// 使用宽度来适应矩形 A
		double scaledWidth = rectA.width();
		double scaledHeight = scaledWidth / aspectRatio;
		scaledRect = QRectF(rectA.x(), rectA.y(), scaledWidth, scaledHeight);
		dScale = scaledRect.width() / rectB.width();
		// 此时缩放后的矩形 B 的尺寸为 scaledRect，缩放系数为 scaleRatio
	}
	else {
		// 使用高度来适应矩形 A
		double scaledHeight = rectA.height();
		double scaledWidth = scaledHeight * aspectRatio;
		scaledRect = QRectF(rectA.x(), rectA.y(), scaledWidth, scaledHeight);
		dScale = scaledRect.height() / rectB.height();
		// 此时缩放后的矩形 B 的尺寸为 scaledRect，缩放系数为 scaleRatio
	}
}

void UICommonTool::centerRectInRect(const QRect& rectA, const QRect& rectB, int& xOffset, int& yOffset) {
	QPoint centerA = rectA.center();
	int leftB = centerA.x() - rectB.width() / 2;
	int topB = centerA.y() - rectB.height() / 2;
	xOffset = leftB - rectA.left();
	yOffset = topB - rectA.top();
}

void UICommonTool::getRotatePixmap(const QPixmap& oriPix, QPixmap& tarPix, int iAngle)
{
	QTransform transform;
	transform.rotate(iAngle);
	tarPix = oriPix.transformed(transform);
}

void UICommonTool::SetLabelColor(QLabel* label, QColor color, QPalette::ColorRole colorrole)
{
	if (label != nullptr)
	{
		QPalette pa;

		pa.setColor(colorrole, color);

		label->setPalette(pa);
	}
}

void UICommonTool::SetLabelFont(QLabel* label, int fontsize, QString& family, bool bold)
{
	if (label != nullptr)
	{
		QFont m_font(family, fontsize);

		m_font.setBold(bold);

		label->setFont(m_font);
	}
}

void UICommonTool::setRetainSizeWhenHidden(QWidget* w, bool isRetain)
{
	QSizePolicy sp_retain = w->sizePolicy();
	sp_retain.setRetainSizeWhenHidden(true);
	w->setSizePolicy(sp_retain);
}

QString UICommonTool::fontMetricsElidedText(const QFont & font, const QString & oriString, int width, Qt::TextElideMode mode /* = Qt::ElideRight */)
{
	QFontMetrics fontWidth(font);//得到字符的宽度
	QString Str = fontWidth.elidedText(oriString, mode, width);//最大宽度60像素
	return Str;
}

void UICommonTool::paintDirectLineWidget(QWidget* w, QPaintEvent* event)
{
	QStyleOption opt;
	opt.initFrom(w);
	QPainter p(w);
	w->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, w);
}

void UICommonTool::setLineEditInputType(QLineEdit* pLineEdit, LineEditInputType eType) 
{
	QString strType;
	switch (eType)
	{
	case UICommonTool::LineEditInputType::Int:
		strType = "[0-9]+$";
		break;
	case UICommonTool::LineEditInputType::Chinese:
		strType = "[\u4e00-\u9fa5]+$";
		break;
	case UICommonTool::LineEditInputType::English:
		strType = "^[A-Za-z]+$";
		break;
	case UICommonTool::LineEditInputType::UpEnglish:
		strType = "^[A-Z]+$";
		break;
	case UICommonTool::LineEditInputType::SmallEnglish:
		strType = "^[a-z]+$";
		break;
	case UICommonTool::LineEditInputType::NumberAndEnglish:
		strType = "[a-zA-Z0-9]+$";
		break;
	case UICommonTool::LineEditInputType::TimeDate:
		strType = "^(d{2}|d{4})-((0([1-9]{1}))|(1[1|2]))-(([0-2]([1-9]{1}))|(3[0|1]))$";
		break;
	case UICommonTool::LineEditInputType::TimeDate2:
		strType = "^((0([1-9]{1}))|(1[1|2]))/(([0-2]([1-9]{1}))|(3[0|1]))/(d{2}|d{4})$";
		break;
	case UICommonTool::LineEditInputType::TimeDate3:
		strType = "0000-00-00";
		break;
	case UICommonTool::LineEditInputType::IPConfig:
		strType = "000.000.000.000;_";
		break;
	case UICommonTool::LineEditInputType::MacConfig:
		strType = "HH:HH:HH:HH:HH:HH;_";
		break;
	case UICommonTool::LineEditInputType::License:
		strType = ">AAAAA-AAAAA-AAAAA-AAAAA-AAAAA;#";
		break;
	case UICommonTool::LineEditInputType::NumberAndEnglishAndUnderline:
		strType = "^[0-9a-zA-Z_]+$";
		break;
	default:
		break;
	}

	QRegularExpression regExp(strType);
	QValidator* validator = new QRegularExpressionValidator(regExp, pLineEdit);
	pLineEdit->setValidator(validator);
}

QRect UICommonTool::drawAlignCenterPixmap(QPainter * painter, QRect & objRect, const QPixmap & oriPixmap)
{
	if (!oriPixmap.isNull()) 
	{
		//if (oriPixmap.height() > objRect.height() || oriPixmap.width() > objRect.width())
		//{
			painter->save();
			//绘制
			QPixmap pix = oriPixmap.scaled(objRect.width(), objRect.height(), Qt::KeepAspectRatio, Qt::FastTransformation);
			QRect pix_rect = pix.rect();
			QRect draw_rect = objRect;
			draw_rect.moveTop(objRect.top());
			pix_rect.moveCenter(draw_rect.center());
			painter->drawPixmap(pix_rect.topLeft(), pix);
			painter->restore();
			return pix_rect;
		//}
		//else
		//{
		//	painter->save();
		//	QRect pix_rect = oriPixmap.rect();
		//	QRect draw_rect = objRect;
		//	draw_rect.moveTop(objRect.top());
		//	pix_rect.moveCenter(draw_rect.center());
		//	painter->drawPixmap(pix_rect.topLeft(), oriPixmap);
		//	painter->restore();
		//	return pix_rect;
		//}
	}
	return QRect();
}

QRect UICommonTool::drawAlignCenterText(QPainter * painter, QRect & objRect,const QFont & font ,const QString & oriString)
{
	painter->save();
	painter->setFont(font);
	QString displayStr = fontMetricsElidedText(font, oriString, objRect.width());
	QFontMetrics fontWidth(font);

	QRect draw_rect = objRect;
	QRect label_rect = fontWidth.boundingRect(displayStr);
	painter->drawText(objRect, Qt::AlignCenter , displayStr);

	painter->restore();

	return objRect;
}
