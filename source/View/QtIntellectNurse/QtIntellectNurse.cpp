#include <QFile>
#include "QtIntellectNurse.h"
#include "Component/PixmapWidget/PixmapWidget.h"

QtIntellectNurse::QtIntellectNurse(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	init();
}

QtIntellectNurse::~QtIntellectNurse()
{}

void QtIntellectNurse::init()
{
	initStyleSheet();
	initForm();
}

void QtIntellectNurse::initStyleSheet()
{
	//以stylesheet组件模式存在
	//程序内部 字体设置统一
	qApp->setFont(QFont("Microsoft Yahei"));
	//加载样式表
	QString qss;
	QFile file(":/qss/qss.css");
	if (file.open(QFile::ReadOnly)) {
		QStringList list;
		QTextStream in(&file);
		while (!in.atEnd()) {
			QString line;
			in >> line;
			list << line;
		}
		qss = list.join("\n");
		QString paletteColor = qss.mid(23, 7);
		qApp->setPalette(QPalette(paletteColor));
		file.close();
	}
	qApp->setStyleSheet("file:///:/qss/qss.css");
}

void QtIntellectNurse::initForm()
{
	showFullScreen();
	setWindowFlags(Qt::FramelessWindowHint);

	ui.soundIcon->setPixmap(QPixmap(":/image/home/volume.png"));
	ui.networkIcon->setPixmap(QPixmap(":/image/home/wifi.png"));
	ui.temperatureIcon->setPixmap(QPixmap(":/image/home/droplet.png"));
	ui.humidityIcon->setPixmap(QPixmap(":/image/home/thermometer.png"));
	ui.homeIcon->setPixmap(QPixmap(":/image/home/home.png"));
	ui.huHeader->setPixmap(QPixmap(":/image/home/common.png"));
	ui.userHeader->setPixmap(QPixmap(":/image/home/common.png"));

	ui.soundIcon->setDrawSize(QSize(18, 28));
	ui.networkIcon->setDrawSize(QSize(18, 28));
	ui.humidityIcon->setDrawSize(QSize(18, 28));
	ui.temperatureIcon->setDrawSize(QSize(18, 28));
}
