#include <QEvent>
#include <QScreen>
#include <QPainter>
#include <QGuiApplication>

#include "popuptip.h"
#include "ui_popuptip.h"
#include <Tool/UiCommonTool/UiCommonTool.h>


#define SHOWTIMER_EXEPERIOD 2

#define STAYTIMER_EXEPERIOD 1000
#define STAYTIMER_MAX_EXETIMES 3

#define CLOSETIMER_EXEPERIOD 100
#define TOPOFFSET 10

PopupTip::PopupTip(const QString& strTitleInfo, const QString& strMsg, QtMsgType eMsgType, QWidget* parent)
	:QWidget(parent),
	ui(new Ui::PopupTip)
	//, m_currentHeight(QApplication::desktop()->height())
	, m_showTimer(new QTimer(this))
	, m_stayTimer(new QTimer(this))
	, m_closeTimer(new QTimer(this))
	, m_stayExeTime(0)
	, m_transparent(1.0)
	, m_firstShow(true)
	, m_enterEvent(false)
{
	ui->setupUi(this);
	init(strTitleInfo, strMsg, eMsgType);
	connect(m_showTimer, SIGNAL(timeout()), this, SLOT(slotMsgMove()));
	connect(m_stayTimer, SIGNAL(timeout()), this, SLOT(slotMsgStay()));
	connect(m_closeTimer, SIGNAL(timeout()), this, SLOT(slotMsgClose()));
}


PopupTip::~PopupTip()
{
	deleteTimer(m_showTimer);
	deleteTimer(m_stayTimer);
	deleteTimer(m_closeTimer);
	delete ui;
}

void PopupTip::init(const QString& strTitleInfo, const QString& strMsg, QtMsgType eMsgType)
{
	setWindowFlag(Qt::FramelessWindowHint, true);
	ui->labContnt->setText(strMsg);
	ui->labLevel->setText(strTitleInfo);

	int iWidth = 0;
	//加上 布局左右间隙值
	int left, top, right, bottom;
	ui->horizontalLayout_2->getContentsMargins(&left, &top, &right, &bottom);
	iWidth += left;
	iWidth += right;

	QFont font;
	QRect label_rect;
	//内容
	font = ui->labContnt->font();
	QFontMetrics fontContentWidth(font);
	label_rect = fontContentWidth.boundingRect(strMsg);
	iWidth += ui->horizontalLayout_2->spacing();
	iWidth += label_rect.width();

	//标题
	font = ui->labLevel->font();
	QFontMetrics fontTitleWidth(font);
	label_rect = fontTitleWidth.boundingRect(strTitleInfo);
	iWidth += ui->horizontalLayout_2->spacing();
	iWidth += label_rect.width();

	//关闭按钮
	iWidth += ui->horizontalLayout_2->spacing();
	iWidth += ui->btnClose->width();

	//图标
	iWidth += ui->horizontalLayout_2->spacing();
	iWidth += ui->labIcon->width();

	setFixedWidth(iWidth);
	if (eMsgType == QtMsgType::QtDebugMsg)
	{
		m_pixIcon = QPixmap(":/image/homeview/btn_icon_about@2x.png");
	}
	switch (eMsgType)
	{
	case QtMsgType::QtDebugMsg:
		m_pixIcon = QPixmap(":/image/homeview/btn_icon_about@2x.png");
		setStyleSheet("background-color: #F4F4F4;border: 1px solid #E5E5E5;border-radius: 10px;");
		//UICommonTool::changComponentProperty(ui->frame, "Style_Widget", "Style_Tip_Debug_Widget");
		break;
	case QtMsgType::QtCriticalMsg:
		m_pixIcon = QPixmap(":/image/homeview/btn_icon_about@2x.png");
		setStyleSheet("background-color: #DFF6DD;border: 1px solid #E5E5E5;border-radius: 10px;");
		//UICommonTool::changComponentProperty(ui->frame, "Style_Widget", "Style_Tip_Critical_Widget");
		break;
	case QtMsgType::QtFatalMsg:
		m_pixIcon = QPixmap(":/image/homeview/btn_icon_about@2x.png");
		setStyleSheet("background-color: #FDE7E9;border: 1px solid #E5E5E5;border-radius: 10px;");
		//UICommonTool::changComponentProperty(ui->frame, "Style_Widget", "Style_Tip_Fatal_Widget");
		break;
	case QtMsgType::QtInfoMsg:
		m_pixIcon = QPixmap(":/image/homeview/btn_icon_about@2x.png");
		setStyleSheet("background-color: #F4F4F4;border: 1px solid #E5E5E5;border-radius: 10px;");
		//UICommonTool::changComponentProperty(ui->frame, "Style_Widget", "Style_Tip_Info_Widget");
		break;
	case QtMsgType::QtWarningMsg:
		m_pixIcon = QPixmap(":/image/homeview/btn_icon_about@2x.png");
		setStyleSheet("background-color: #FFF4CE;border: 1px solid #E5E5E5;border-radius: 10px;");
		//UICommonTool::changComponentProperty(ui->frame, "Style_Widget", "Style_Tip_Warning_Widget");
		break;
	default:
		m_pixIcon = QPixmap(":/image/homeview/btn_icon_about@2x.png");
		setStyleSheet("background-color: #F4F4F4;border: 1px solid #E5E5E5;border-radius: 10px;");
		//UICommonTool::changComponentProperty(ui->frame, "Style_Widget", "Style_Tip_Debug_Widget");
		break;
	}

	ui->labIcon->installEventFilter(this);
}

void PopupTip::enterEvent(QEnterEvent* event)
{
	m_enterEvent = true;
	m_stayTimer->stop();
	m_transparent = 1.0;
	setWindowOpacity(1.0);
	m_closeTimer->stop();
}

void PopupTip::leaveEvent(QEvent* event)
{
	m_enterEvent = false;

	m_stayExeTime = STAYTIMER_MAX_EXETIMES / 2;
	m_stayTimer->start(STAYTIMER_EXEPERIOD);
}

bool PopupTip::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == ui->labIcon)
	{
		if (event->type() == QEvent::Paint)
		{
			QPainter painter(ui->labIcon);
			painter.setRenderHint(QPainter::Antialiasing, true);
			painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
			QRect rectPixArea = ui->labIcon->rect();
			UICommonTool::drawAlignCenterPixmap(&painter, rectPixArea, m_pixIcon);
		}
	}
	return QWidget::eventFilter(watched, event);
}

void PopupTip::updatePosition()
{
	if (m_firstShow) {
		showPopupTip();
		m_firstShow = false;
	}
	else {
		m_pEnd_showPoint.setY(m_pEnd_showPoint.y() + height() + 2);
		m_CurrentHeight = m_CurrentHeight + height() + 2;
		move(m_pEnd_showPoint.x(), m_CurrentHeight);
	}
}

void PopupTip::showPopupTip()
{
	m_showTimer->stop();
	m_stayTimer->stop();
	m_closeTimer->stop();
	if (parentWidget() == nullptr)
	{
		emit sigClose(this);
		return;
	}
	setWindowOpacity(1);

	// 计算最后呈现的位置
	m_pEnd_showPoint.setX(parentWidget()->width() / 2 - rect().width() / 2);
	m_pEnd_showPoint.setY(0 + TOPOFFSET);

	// 先将弹窗移动到桌面外
	m_CurrentHeight = -rect().height();
	move(
		parentWidget()->width() / 2 - rect().width() / 2, 
		- rect().height()
	);

	show();
	m_showTimer->start(SHOWTIMER_EXEPERIOD);
}

inline void PopupTip::deleteTimer(QTimer* timer)
{
	if (timer->isActive())
		timer->stop();

	delete timer;
	timer = NULL;
}

void PopupTip::slotMsgMove()
{
	m_CurrentHeight++;
	move(m_pEnd_showPoint.x(), m_CurrentHeight);
	if (m_CurrentHeight >= m_pEnd_showPoint.y())
	{
		m_showTimer->stop();
		if (!m_enterEvent)
			m_stayTimer->start(STAYTIMER_EXEPERIOD);
	}
}

void PopupTip::slotMsgStay()
{
	m_stayExeTime++;
	if (m_stayExeTime >= STAYTIMER_MAX_EXETIMES)
	{
		m_stayTimer->stop();
		m_closeTimer->start(CLOSETIMER_EXEPERIOD);
	}
}

void PopupTip::slotMsgClose()
{
	m_transparent -= 0.2;
	if (m_transparent <= 0.0)
	{
		m_closeTimer->stop();
		emit sigClose(this);
	}
	else
	{
		setWindowOpacity(m_transparent);
	}
}
