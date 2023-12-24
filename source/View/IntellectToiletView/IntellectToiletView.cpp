#include "IntellectToiletView.h"

IntellectToiletView::IntellectToiletView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

IntellectToiletView::~IntellectToiletView()
{}

void IntellectToiletView::init()
{
	initForm();
}

void IntellectToiletView::initForm()
{
	ui.widget->setPixmap(QPixmap(":/image/common/智能坐垫.png"));
	//ui.widget->setDrawSize(QSize(538, 629));


	ui.widget_29->setPixmap(QPixmap(":/image/common/正转.png"));
	ui.widget_29->setDrawSize(QSize(130, 130));

	ui.widget_27->setPixmap(QPixmap(":/image/common/反转.png"));
	ui.widget_27->setDrawSize(QSize(130, 130));

	ui.widget_30->setPixmap(QPixmap(":/image/common/暂停.png"));
	ui.widget_30->setDrawSize(QSize(130, 130));

	ui.widget_31->setPixmap(QPixmap(":/image/common/复位.png"));
	ui.widget_31->setDrawSize(QSize(130, 130));
	

	ui.widget_2->setPixmap(QPixmap(":/image/common/箭头.png"));

	CustProgressButton stCustProgressButton;
	stCustProgressButton.mix = 0;
	stCustProgressButton.max = 5;
	stCustProgressButton.progressBar = ui.progressBar;
	stCustProgressButton.addBtn = ui.pushButton;
	stCustProgressButton.reduceBtn = ui.pushButton_3;
	stCustProgressButton.progressBar->setMinimum(stCustProgressButton.mix);
	stCustProgressButton.progressBar->setMaximum(stCustProgressButton.max);
	m_lstCustProgressButton.append(stCustProgressButton);

	stCustProgressButton.mix = 0;
	stCustProgressButton.max = 5;
	stCustProgressButton.progressBar = ui.progressBar_2;
	stCustProgressButton.addBtn = ui.pushButton_5;
	stCustProgressButton.reduceBtn = ui.pushButton_6;
	stCustProgressButton.progressBar->setMinimum(stCustProgressButton.mix);
	stCustProgressButton.progressBar->setMaximum(stCustProgressButton.max);
	m_lstCustProgressButton.append(stCustProgressButton);

	stCustProgressButton.mix = 0;
	stCustProgressButton.max = 5;
	stCustProgressButton.progressBar = ui.progressBar_3;
	stCustProgressButton.addBtn = ui.pushButton_2;
	stCustProgressButton.reduceBtn = ui.pushButton_7;
	stCustProgressButton.progressBar->setMinimum(stCustProgressButton.mix);
	stCustProgressButton.progressBar->setMaximum(stCustProgressButton.max);
	m_lstCustProgressButton.append(stCustProgressButton);

	stCustProgressButton.mix = 0;
	stCustProgressButton.max = 5;
	stCustProgressButton.progressBar = ui.progressBar_4;
	stCustProgressButton.addBtn = ui.pushButton_8;
	stCustProgressButton.reduceBtn = ui.pushButton_4;
	stCustProgressButton.progressBar->setMinimum(stCustProgressButton.mix);
	stCustProgressButton.progressBar->setMaximum(stCustProgressButton.max);
	m_lstCustProgressButton.append(stCustProgressButton);

	for (CustProgressButton& stCustProgressButton : m_lstCustProgressButton)
	{
		connect(stCustProgressButton.addBtn, &QAbstractButton::clicked, [=]() {
			stCustProgressButton.progressBar->setValue(stCustProgressButton.progressBar->value() + 1);
			}
		);
		connect(stCustProgressButton.reduceBtn, &QAbstractButton::clicked, [=]() {
			stCustProgressButton.progressBar->setValue(stCustProgressButton.progressBar->value() - 1);
			}
		);
	}

	ToiletPixmapWidget stToiletPixmapWidget;
	stToiletPixmapWidget.x = 11.5;
	stToiletPixmapWidget.y = 18.5;
	stToiletPixmapWidget.w = new PixmapWidget(ui.widget_2);
	stToiletPixmapWidget.w->setPixmap(QPixmap(":/image/common/水泵.png"));
	stToiletPixmapWidget.w->setFixedSize(QSize(70, 70));
	m_lststToiletPixmapWidget.append(stToiletPixmapWidget);

	stToiletPixmapWidget.x = 11.2;
	stToiletPixmapWidget.y = 36.7;
	stToiletPixmapWidget.w = new PixmapWidget(ui.widget_2);
	stToiletPixmapWidget.w->setPixmap(QPixmap(":/image/common/水泵.png"));
	stToiletPixmapWidget.w->setFixedSize(QSize(70, 70));
	m_lststToiletPixmapWidget.append(stToiletPixmapWidget);

	stToiletPixmapWidget.x = 11.0;
	stToiletPixmapWidget.y = 57.5;
	stToiletPixmapWidget.w = new PixmapWidget(ui.widget_2);
	stToiletPixmapWidget.w->setPixmap(QPixmap(":/image/common/水泵.png"));
	stToiletPixmapWidget.w->setFixedSize(QSize(70, 70));	
	m_lststToiletPixmapWidget.append(stToiletPixmapWidget);

	/*stToiletPixmapWidget.x = 27.0;
	stToiletPixmapWidget.y = 16.5;
	stToiletPixmapWidget.w = new PixmapWidget(ui.widget_2);
	stToiletPixmapWidget.w->setPixmap(QPixmap(":/image/common/转换阀.png"));
	stToiletPixmapWidget.w->setFixedSize(QSize(100, 100));
	m_lststToiletPixmapWidget.append(stToiletPixmapWidget);

	stToiletPixmapWidget.x = 61.9;
	stToiletPixmapWidget.y = 16.5;
	stToiletPixmapWidget.w = new PixmapWidget(ui.widget_2);
	stToiletPixmapWidget.w->setPixmap(QPixmap(":/image/common/转换阀.png"));
	stToiletPixmapWidget.w->setFixedSize(QSize(100, 100));
	m_lststToiletPixmapWidget.append(stToiletPixmapWidget);

	stToiletPixmapWidget.x = 61.7;
	stToiletPixmapWidget.y = 57.1;
	stToiletPixmapWidget.w = new PixmapWidget(ui.widget_2);
	stToiletPixmapWidget.w->setPixmap(QPixmap(":/image/common/转换阀.png"));
	stToiletPixmapWidget.w->setFixedSize(QSize(100, 100));
	m_lststToiletPixmapWidget.append(stToiletPixmapWidget);
	

	stToiletPixmapWidget.x = 13.5;
	stToiletPixmapWidget.y = 13.5;
	stToiletPixmapWidget.w = new PixmapWidget(ui.widget_2);
	stToiletPixmapWidget.w->setPixmap(QPixmap(":/image/common/调节阀.png"));
	stToiletPixmapWidget.w->setFixedSize(QSize(70, 70));
	m_lststToiletPixmapWidget.append(stToiletPixmapWidget);

	stToiletPixmapWidget.x = 13.5;
	stToiletPixmapWidget.y = 13.5;
	stToiletPixmapWidget.w = new PixmapWidget(ui.widget_2);
	stToiletPixmapWidget.w->setPixmap(QPixmap(":/image/common/调节阀.png"));
	stToiletPixmapWidget.w->setFixedSize(QSize(70, 70));
	m_lststToiletPixmapWidget.append(stToiletPixmapWidget);

	stToiletPixmapWidget.x = 13.5;
	stToiletPixmapWidget.y = 13.5;
	stToiletPixmapWidget.w = new PixmapWidget(ui.widget_2);
	stToiletPixmapWidget.w->setPixmap(QPixmap(":/image/common/调节阀.png"));
	stToiletPixmapWidget.w->setFixedSize(QSize(70, 70));
	m_lststToiletPixmapWidget.append(stToiletPixmapWidget);

	stToiletPixmapWidget.x = 13.5;
	stToiletPixmapWidget.y = 13.5;
	stToiletPixmapWidget.w = new PixmapWidget(ui.widget_2);
	stToiletPixmapWidget.w->setPixmap(QPixmap(":/image/common/调节阀.png"));
	stToiletPixmapWidget.w->setFixedSize(QSize(70, 70));
	m_lststToiletPixmapWidget.append(stToiletPixmapWidget);*/

	ui.widget_2->installEventFilter(this);
}

bool IntellectToiletView::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == ui.widget_2 && event->type() == QEvent::Resize)
	{
		QRect widRect = ui.widget_2->rect();
		double width = 1134.0 / (widRect.width() * 1.0);
		double height = 720 / (widRect.height() * 1.0);
		for (ToiletPixmapWidget & stToiletPixmapWidget : m_lststToiletPixmapWidget)
		{
			stToiletPixmapWidget.w->setFixedSize(QSize(stToiletPixmapWidget.w->width() * width, stToiletPixmapWidget.w->width() * height));
			stToiletPixmapWidget.w->move((int)((widRect.width() * 1.0) * (stToiletPixmapWidget.x / 100.0)), (int)((widRect.height() * 1.0) * (stToiletPixmapWidget.y / 100.0)));
		}
	}
	return QWidget::eventFilter(watched, event);
}
