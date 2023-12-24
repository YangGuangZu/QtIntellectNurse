#include <QEvent>
#include "storagewidget.h"
#include "tool/uicommontool/uicommontool.h"

StorageWidget::StorageWidget(QWidget* parent)
	:QWidget(parent),
	m_pParent(parent)
{
	initView();
}

StorageWidget::~StorageWidget()
{
	if (nullptr != m_pAniStorage)
	{
		m_pAniStorage->deleteLater();
		m_pAniStorage = nullptr;
	}
}

void StorageWidget::initView()
{
	setProperty("isStorage", false);
	//动画
	m_pAniStorage = new QVariantAnimation(this);
	connect(m_pAniStorage, &QVariantAnimation::valueChanged, [=](QVariant offset) {
		qDebug() << " m_pAniStorage :" << offset;
		switch (m_eStorageDirection)
		{
		case StorageWidget::StorageTop:
			move(0, offset.toInt());
			break;
		case StorageWidget::StorageBottom:
			qDebug() << " m_pAniStorage :" << m_pParent->height() - offset.toInt();
			move(0, m_pParent->height() + offset.toInt());
			qDebug() << pos();
			break;
		case StorageWidget::StorageLeft:
			move(offset.toInt(), 0);
			break;
		case StorageWidget::StorageRight:
			move(m_pParent->width() - offset.toInt(), 0);
			break;
		case StorageWidget::StorageDefault:
			break;
		default:
			break;
		}
		}
	);
	m_pAniStorage->setEasingCurve(QEasingCurve::OutQuad);
	m_pAniStorage->setDuration(m_uiStorageTime);

	m_pParent->installEventFilter(this);
}

void StorageWidget::updateWidgetPos()
{
	switch (m_eStorageDirection)
	{
	case StorageWidget::StorageTop:
		setGeometry(0, getIsStorage() ? 0 : -m_uiStorageOffset, m_pParent->width(), m_uiStorageOffset);
		break;
	case StorageWidget::StorageBottom:
		setGeometry(0, getIsStorage() ? m_pParent->height() - m_uiStorageOffset : m_pParent->height(), m_pParent->width(), m_uiStorageOffset);
		break;
	case StorageWidget::StorageLeft:
		setGeometry(getIsStorage() ? 0 : -m_uiStorageOffset, 0, m_uiStorageOffset, m_pParent->height());
		break;
	case StorageWidget::StorageRight:
		setGeometry(getIsStorage() ? m_pParent->width() - m_uiStorageOffset : m_pParent->width(), 0, m_uiStorageOffset, m_pParent->height());
		break;
	case StorageWidget::StorageDefault:
		break;
	default:
		break;
	}
}

void StorageWidget::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	UICommonTool::paintDirectLineWidget(this, event);
	QPainter p(this);
	p.setBrush(QColor(255, 0, 0));
	p.drawRect(rect());
}

bool StorageWidget::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::Resize)
	{
		if (m_pParent == watched)
		{
			updateWidgetPos();
		}
	}
	return __super::eventFilter(watched, event);
}

StorageWidget::StorageDirection StorageWidget::getStorageDirection()
{
	return m_eStorageDirection;
}

void StorageWidget::setStorageDirection(const StorageDirection& eStorageDirection)
{
	if (eStorageDirection == m_eStorageDirection)
	{
		return;
	}
	m_eStorageDirection = eStorageDirection;
	updateWidgetPos();
}

uint StorageWidget::getStorageTime()
{
	return m_uiStorageTime;
}

void StorageWidget::setStorageTime(const uint& uiTime)
{
	m_uiStorageTime = uiTime;
	m_pAniStorage->setDuration(m_uiStorageTime);
}

bool StorageWidget::getIsStorage()
{
	return property("isStorage").toBool();
}

void StorageWidget::setIsStorage(const bool& bIsStorage)
{
	//判断动画状态
	if (m_pAniStorage->state() == QVariantAnimation::Running)
	{
		return;
	}

	//判断当前导航栏状态
	if (property("isStorage").toBool() == bIsStorage)
	{
		return;
	}
	setProperty("isStorage", bIsStorage);	
	if (!bIsStorage)
	{
		m_pAniStorage->setStartValue(0);
		m_pAniStorage->setEndValue(-((int)m_uiStorageOffset));
	}
	else
	{
		m_pAniStorage->setStartValue(-((int)m_uiStorageOffset));
		m_pAniStorage->setEndValue(0);
	}

	m_pAniStorage->start();
}

uint StorageWidget::getStorageOffset()
{
	return m_uiStorageOffset;
}

void StorageWidget::setStorageOffset(const uint& uiTime)
{
	m_uiStorageOffset = uiTime;
}

