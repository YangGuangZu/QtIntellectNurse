#include <QFileDialog>
#include "IntellectVideoView.h"
#include "Component/PopupTips/PopupManager.h"

IntellectVideoView::IntellectVideoView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

IntellectVideoView::~IntellectVideoView()
{}

void IntellectVideoView::init()
{
	initForm();
	connect(ui.btnStatusChange,			&PixmapWidget::clicked,							ui.widget,		&VideoView::changePlayStatus);
	connect(ui.btnStop,					&PixmapWidget::clicked,							ui.widget,		&VideoView::stop);
	connect(ui.btnUp,					&PixmapWidget::clicked,							this,			&IntellectVideoView::upSource);
	connect(ui.btnDown,					&PixmapWidget::clicked,							this,			&IntellectVideoView::downSource);

	connect(ui.listWidgetPlayer,		&QListWidget::itemDoubleClicked,				this,			&IntellectVideoView::slots_setCurrVideoPath);

	connect(ui.listWidget,				&QListWidget::currentTextChanged,				this,			&IntellectVideoView::slots_useVideoFolderChanged);

	connect(&VideoManager::Instance(),	&VideoManager::signals_videoStatusChanged,		this,			&IntellectVideoView::slots_updateVideoInfo);
	connect(&VideoManager::Instance(),	&VideoManager::signals_videoPlayListChanged,	this,			&IntellectVideoView::updateVideoPlayerList);
}

void IntellectVideoView::initForm()
{
	ui.btnVideoCall->setPixmap(QPixmap(":/image/common/视频.png"));
	ui.btnVideoCall->setDrawSize(QSize(130, 130));

	ui.btnAudioCall->setPixmap(QPixmap(":/image/common/语音.png"));
	ui.btnAudioCall->setDrawSize(QSize(130, 130));

	ui.btnCallOver->setPixmap(QPixmap(":/image/common/挂断.png"));
	ui.btnCallOver->setDrawSize(QSize(130, 130));

	ui.btnUp->setPixmap(QPixmap(":/image/common/上一首.png"));
	ui.btnUp->setDrawSize(QSize(130, 130));

	ui.btnStatusChange->setPixmap(QPixmap(":/image/common/暂停播放.png"));
	ui.btnStatusChange->setDrawSize(QSize(130, 130));

	ui.btnStop->setPixmap(QPixmap(":/image/common/停止.png"));
	ui.btnStop->setDrawSize(QSize(130, 130));

	ui.btnDown->setPixmap(QPixmap(":/image/common/下一首.png"));
	ui.btnDown->setDrawSize(QSize(130, 130));

	ui.btnAuto->setPixmap(QPixmap(":/image/common/循环.png"));
	ui.btnAuto->setDrawSize(QSize(130, 130));

}

void IntellectVideoView::updateVideoList(const QStringList & lststrFolderList, const QString& strCurrFolder)
{
	ui.listWidget->clear();
	ui.listWidget->addItems(lststrFolderList);
	if (lststrFolderList.contains(strCurrFolder))
	{
		int index = lststrFolderList.indexOf(strCurrFolder);
		QListWidgetItem* item = ui.listWidget->item(index);
		ui.listWidget->setCurrentItem(item);
	}
}

void IntellectVideoView::updateVideoPlayerList(const QStringList& lststrFolderList)
{
	ui.listWidgetPlayer->clear();
	ui.listWidgetPlayer->addItems(lststrFolderList);
}

void IntellectVideoView::upSource()
{
	QListWidgetItem* item = ui.listWidgetPlayer->currentItem();
	if (nullptr == item)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("警告"), QStringLiteral("没有选中任何项目"), QtMsgType::QtFatalMsg);
		return;
	}

	int res = ui.listWidgetPlayer->row(item);

	if (res > 0)
	{
		QListWidgetItem* pitem = ui.listWidgetPlayer->item(res - 1);
		ui.listWidgetPlayer->setCurrentItem(pitem);
		emit ui.listWidgetPlayer->itemDoubleClicked(pitem);
	}
	else
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("已是第一部"), QtMsgType::QtFatalMsg);
		return;
	}
}

void IntellectVideoView::downSource()
{
	QListWidgetItem* item = ui.listWidgetPlayer->currentItem();
	if (nullptr == item)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("警告"), QStringLiteral("没有选中任何项目"), QtMsgType::QtFatalMsg);
		return;
	}

	int res = ui.listWidgetPlayer->row(item);

	if (res < ui.listWidgetPlayer->count() - 1)
	{
		QListWidgetItem* pitem = ui.listWidgetPlayer->item(res + 1);
		ui.listWidgetPlayer->setCurrentItem(pitem);
		emit ui.listWidgetPlayer->itemDoubleClicked(pitem);
	}
	else
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("提示"), QStringLiteral("已是第最后一部"), QtMsgType::QtFatalMsg);
		return;
	}
}

void IntellectVideoView::slots_setCurrVideoPath(QListWidgetItem* item)
{
	if (nullptr == item)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("警告"), QStringLiteral("没有选中任何项目"), QtMsgType::QtFatalMsg);
		return;
	}
	QString currentText = ui.listWidget->currentItem()->text();

	QString strCurrFolder = VideoManager::Instance().getCurrFolder();
	ui.widget->setCurrSource(strCurrFolder+ "/" + item->text());
	ui.widget->play();
}

void IntellectVideoView::slots_useVideoFolderChanged(const QString& currentText)
{
	OperaDetails stOperaDetails;
	VideoManager::Instance().useVideoFolder(currentText, stOperaDetails);
	if (false == stOperaDetails.isOk)
	{
		PopupManager::Instance().addPopupTip(stOperaDetails.strOpera, stOperaDetails.strDetails, QtMsgType::QtFatalMsg);
		return;
	}
	VideoManager::Instance().saveConfig();
}

void IntellectVideoView::slots_updateVideoInfo(const VideoManager::VideoInfoParams& params)
{
	updateVideoList(params.folderList, params.currFolder);
}

void IntellectVideoView::on_btnOpen_clicked()
{
	// 打开文件对话框以选择路径
	QString folderPath = QFileDialog::getExistingDirectory(nullptr, "选择文件夹", "", QFileDialog::ShowDirsOnly);

	// 检查用户是否取消了选择
	if (folderPath.isEmpty()) {
		return;
	}
	OperaDetails stOperaDetails;
	VideoManager::Instance().addVideoFolder(folderPath, stOperaDetails);
	if (false == stOperaDetails.isOk)
	{
		PopupManager::Instance().addPopupTip(stOperaDetails.strOpera, stOperaDetails.strDetails, QtMsgType::QtFatalMsg);
		return;
	}
	VideoManager::Instance().saveConfig();
}

void IntellectVideoView::on_btnDelete_clicked()
{
	QListWidgetItem * item = ui.listWidget->currentItem();
	if (nullptr == item)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("警告"), QStringLiteral("没有选中任何项目"), QtMsgType::QtFatalMsg);
		return;
	}
	QString currentText = ui.listWidget->currentItem()->text();

	OperaDetails stOperaDetails;
	VideoManager::Instance().deleteVideoFolder(currentText, stOperaDetails);
	if (false == stOperaDetails.isOk)
	{
		PopupManager::Instance().addPopupTip(stOperaDetails.strOpera, stOperaDetails.strDetails, QtMsgType::QtFatalMsg);
	}
	VideoManager::Instance().saveConfig();
}
