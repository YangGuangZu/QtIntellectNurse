#include <QStyle>
#include <QVariant>
#include <QStyleOption>
#include <QApplication>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include "BackgroundMask.h"
#include "EmptyChildView.h"
#include "tool/uicommontool/uicommontool.h"
#include "manager/appguimanager/appguimanager.h"

BackGroundMask::BackGroundMask(QWidget* parent)
	: QFrame(parent)
{
	init();
}

BackGroundMask::~BackGroundMask()
{
}

void BackGroundMask::init()
{
	UICommonTool::changComponentProperty(this, "Style_Widget", "Style_Base_Mask");
	m_pHorizontalLayout = new QHBoxLayout(this);
	m_pHorizontalLayout->setSpacing(0);
	m_pHorizontalLayout->setContentsMargins(50, 50, 50, 50);
}

void BackGroundMask::mousePressEvent(QMouseEvent* event)
{
	if (isClickedClose && nullptr != m_pChildWidget)
	{
		QRect childGeometry = m_pChildWidget->geometry();
		if (!childGeometry.contains(event->pos()))
		{
			emit signals_closeSelf();
		}
	}
	QFrame::mousePressEvent(event);
}

bool BackGroundMask::eventFilter(QObject* watched, QEvent* event)
{
	if(watched == parentWidget())
	{
		if (event->type() == QEvent::Resize)
		{
			setGeometry(parentWidget()->rect());
		}
	}
	return QFrame::eventFilter(watched, event);
}

void BackGroundMask::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0, 0, 0, 180));
	painter.drawRect(rect());
	__super::paintEvent(event);
}

void BackGroundMask::addContentPtr(QWidget* pBasicWidget, const QString& strTitle)
{
	EmptyChildView *pEmptyChildView = new EmptyChildView(this);
	m_pChildWidget = pEmptyChildView;
	pEmptyChildView->addContentPtr(pBasicWidget, strTitle);
	m_pHorizontalLayout->addWidget(pEmptyChildView);

	m_pChildWidget->installEventFilter(this);
	connect(pEmptyChildView, &EmptyChildView::singalExitEmptyChildView, [=]() {
		pBasicWidget->setParent(nullptr);
		pBasicWidget->hide();
		deleteLater();
		}
	);
}

BackGroundMask* BackGroundMask::getBackGroundMaskWithShadow(QWidget* parent)
{
	if (parent == nullptr)
	{
		parent = AppGUIManager::Instance().getAppTopLevelWidget();

	}

	if (parent)
	{
		BackGroundMask* mask = new BackGroundMask(parent);
		mask->setGeometry(parent->rect());
		mask->show();
		return mask;
	}
	return nullptr;
}

BackGroundMask* BackGroundMask::getBackGroundMask(QWidget* parent)
{
	if (parent == nullptr)
	{
		parent = AppGUIManager::Instance().getAppTopLevelWidget();

	}
	if (parent)
	{
		BackGroundMask* mask = new BackGroundMask(parent);
		parent->installEventFilter(mask);
		mask->setGeometry(parent->rect());
		mask->show();
		return mask;
	}
	return nullptr;
}

BackGroundMask* BackGroundMask::getClickedBackGroundMask(QWidget* parent)
{
	BackGroundMask* backgroundMask = getBackGroundMask(parent);
	if (backgroundMask != nullptr)
	{
		backgroundMask->isClickedClose = true;
	}
	return backgroundMask;
}
