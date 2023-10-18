#include <QPainter>
#include "pixmapwidget.h"
#include "../../Tool/UiCommonTool/UiCommonTool.h"

PixmapWidget::PixmapWidget(QWidget* parent)
    : QWidget(parent)
{
}

PixmapWidget::PixmapWidget(const QPixmap& icon, QWidget* parent)
    : PixmapWidget(parent)
{
    setPixmap(icon);
}

PixmapWidget::PixmapWidget(const QString& icon, QWidget* parent)
    : PixmapWidget(parent)
{
    setPixmap(QPixmap(icon));
}

void PixmapWidget::setPixmap(const QPixmap& icon) 
{
    m_pixmap = icon;
    update();
}

void PixmapWidget::setDrawSize(const QSize& size)
{
    m_sizeDraw = size;
    update();
}

void PixmapWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event);
	UICommonTool::paintDirectLineWidget(this, event);
    QPainter painter(this);
    QRect objRect = rect();
    QRect drawRect = QRect(QPoint(0, 0), m_sizeDraw);

    if (drawRect.isValid())
    {
		drawRect.moveCenter(objRect.center());
		UICommonTool::drawAlignCenterPixmap(&painter, drawRect, m_pixmap);
    }
    else
    {
        UICommonTool::drawAlignCenterPixmap(&painter, objRect, m_pixmap);
    }

}