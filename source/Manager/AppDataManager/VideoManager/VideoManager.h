#pragma once
#include <QObject>
#include "Manager/AppDataManager/BasicSqlData/BasicSqlData.h"
class VideoManager :public BasicSqlData
{
	Q_OBJECT
private:
	VideoManager();
	~VideoManager() {};

public:
	static VideoManager& Instance() {
		static VideoManager Instance;
		return Instance;
	}
public:
	struct VideoInfoParams {
		QString currTime;
		QString currFile;
		QString currFolder;
		QStringList playlist;
		QStringList folderList;
	};
private:
	VideoInfoParams m_videoInfoParams;
public:
	//初始化
	void init();
	//设置信息
	void setCurrTime(const QString& currTime);
	void setCurrFile(const QString& currFile);
	void setCurrFolder(const QString& currFolder);
	void setPlaylist(const QStringList& playlist);
	void setFolderList(const QStringList& folderList);

	//新增视频文件夹
	void addVideoFolder(const QString& strVideoFolder, OperaDetails& stOperaDetails);
	//使用视频文件夹
	void useVideoFolder(const QString& strVideoFolder, OperaDetails& stOperaDetails);
	//shanchu视频文件夹
	void deleteVideoFolder(const QString& strVideoFolder, OperaDetails& stOperaDetails);
	//获取信息
	QString getCurrTime() const;
	QString getCurrFile() const;
	QString getCurrFolder() const;
	QStringList getFolderList() const;

	QStringList getCurrPlaylist(OperaDetails& stOperaDetails);
	QStringList getPlaylist(const QString& strVideoFolder, OperaDetails& stOperaDetails) const;
	//信息存取
	void readConfig();
	void saveConfig();
signals:
	void signals_videoStatusChanged(VideoInfoParams params);
	void signals_videoPlayListChanged(QStringList playList);
};
