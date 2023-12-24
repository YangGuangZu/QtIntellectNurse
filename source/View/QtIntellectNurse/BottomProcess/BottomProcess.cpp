#include <QPainter>
#include "BottomProcess.h"
#include "Tool/UiCommonTool/UiCommonTool.h"
#include "Manager/AppStatusManager/AppStatusManager.h"

BottomProcess::BottomProcess(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

BottomProcess::~BottomProcess()
{}

void BottomProcess::init()
{
	initForm();
	connect(&AppStatusManager::Instance(), &AppStatusManager::sigCurrAppControlTypeChanged, this, &BottomProcess::slotSetCurrAppControlType);
}

void BottomProcess::initForm()
{
	QMap<AppControlType, QStringList>*  map = AppStatusManager::Instance().getMapFuncProcess();
	for (QMap<AppControlType, QStringList>::iterator it = (*map).begin(); it != (*map).end(); ++it)
	{
		CustDrawProcessWidget* pCustDrawProcessWidget = new CustDrawProcessWidget(this);
		pCustDrawProcessWidget->setProcessList(it.value());
		m_mapCustDrawProcessWidget.insert(it.key(), pCustDrawProcessWidget);
		ui.horizontalLayout->addWidget(pCustDrawProcessWidget);
		pCustDrawProcessWidget->hide();
	}
}

void BottomProcess::slotSetCurrAppControlType(const AppControlType& eAppControlType)
{
	for (QMap<AppControlType, CustDrawProcessWidget*>::iterator it = m_mapCustDrawProcessWidget.begin(); it != m_mapCustDrawProcessWidget.end(); ++it)
	{
		it.value()->setVisible(eAppControlType == it.key());
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

CustDrawProcessWidget::CustDrawProcessWidget(QWidget* parent /*= nullptr*/)
	: QWidget(parent)
{

}

CustDrawProcessWidget::~CustDrawProcessWidget()
{

}

void CustDrawProcessWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	uint rectWidth = 120;
	uint rectHeight = height() - 24;
	//for (const QString & strName : m_lststrProcess)
	for (int irectCurrCount = m_lststrProcess.size() - 1; irectCurrCount >= 0; --irectCurrCount)
	//for (uint irectCurrCount = 0; irectCurrCount < m_lststrProcess.size(); irectCurrCount++)
	{
		painter.setPen(Qt::NoPen);
		painter.setBrush(m_lststrProcess.at(irectCurrCount) != m_strCurrProcess ? QColor(214, 220, 225) : QColor(89, 166, 242));
		QRect rectContent((irectCurrCount * (rectWidth - 20)) + 12, 12, rectWidth, rectHeight);
		painter.drawRoundedRect(rectContent, 5, 5);
		if (irectCurrCount != m_lststrProcess.size() - 1)
		{
			QPolygon triangle;
			triangle.append(rectContent.topRight());
			triangle.append(QPoint(rectContent.right() + 15, rectContent.top() + rectContent.height() / 2));
			triangle.append(rectContent.bottomRight());
			painter.drawPolygon(triangle);    //画三角形
		}
		//painter.drawText(rectContent.topLeft(), strName);
		painter.setPen(QColor(245, 249, 254));
		QFont labelFont("Microsoft Yahei", 14, 1000);
		UICommonTool::drawAlignCenterText(&painter, rectContent, labelFont, m_lststrProcess.at(irectCurrCount));
	}

	return QWidget::paintEvent(event);
}

void CustDrawProcessWidget::setProcessList(const QStringList& lststrProcess)
{
	m_lststrProcess = lststrProcess;
	if (!m_lststrProcess.isEmpty())
	{
		m_strCurrProcess = m_lststrProcess.first();
	}
}

QStringList CustDrawProcessWidget::getProcessList()
{
	return m_lststrProcess;
}

void CustDrawProcessWidget::setCurrProcess(const QString& strCurr)
{
	if (strCurr == m_strCurrProcess)
	{
		return;
	}
	m_strCurrProcess = strCurr;
}

QString CustDrawProcessWidget::getCurrProcess()
{
	return m_strCurrProcess;
}
