#pragma once

#include <QWidget>
#include "ui_IntellectVideoView.h"
#include "Manager/AppDataManager/VideoManager/VideoManager.h"
#include "Component/VideoView/VideoView.h"

class IntellectVideoView : public QWidget
{
	Q_OBJECT

public:
	IntellectVideoView(QWidget *parent = nullptr);
	~IntellectVideoView();

private:
	Ui::IntellectVideoViewClass ui;
private:
    //初始化
    void init();
    //初始化页面
    void initForm();
	//刷新列表
	void updateVideoList(const QStringList & lststrFolderList, const QString& strCurrFolder);
	//刷新列表
	void updateVideoPlayerList(const QStringList & lststrFolderList);
private slots:
	void upSource();
	void downSource();
	void slots_setCurrVideoPath(QListWidgetItem* item);
	void slots_useVideoFolderChanged(const QString& currentText);
	void slots_updateVideoInfo(const VideoManager::VideoInfoParams & params);
	void on_btnOpen_clicked();
	void on_btnDelete_clicked();
};
