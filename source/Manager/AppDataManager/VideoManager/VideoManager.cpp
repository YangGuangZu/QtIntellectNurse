#include <QDir>
#include <QJsonValue>
#include <QJsonObject>
#include "VideoManager.h"

VideoManager::VideoManager()
{
	m_strAppFuncName = "VideoManager";
}

void VideoManager::init()
{
	readConfig();
}

void VideoManager::setCurrTime(const QString& currTime)
{
	m_videoInfoParams.currTime = currTime;
	emit signals_videoStatusChanged(m_videoInfoParams);
}

void VideoManager::setCurrFile(const QString& currFile)
{
	m_videoInfoParams.currFile = currFile;
	emit signals_videoStatusChanged(m_videoInfoParams);
}

void VideoManager::setCurrFolder(const QString& currFolder)
{
	m_videoInfoParams.currFolder = currFolder;
	emit signals_videoStatusChanged(m_videoInfoParams);
}


void VideoManager::setPlaylist(const QStringList& playlist)
{
	m_videoInfoParams.playlist = playlist;
	emit signals_videoStatusChanged(m_videoInfoParams);
}

void VideoManager::setFolderList(const QStringList& folderList)
{
	m_videoInfoParams.folderList = folderList;
	emit signals_videoStatusChanged(m_videoInfoParams);
}

void VideoManager::addVideoFolder(const QString& strVideoFolder, OperaDetails& stOperaDetails)
{
	QStringList lststrFolderList = m_videoInfoParams.folderList;
	if (lststrFolderList.contains(strVideoFolder))
	{
		stOperaDetails.isOk = false;
		stOperaDetails.strOpera = QStringLiteral("新增文件夹");
		stOperaDetails.strDetails = QStringLiteral("当前视频文件夹对了已有相同路径!");
	}
	else
	{
		lststrFolderList.append(strVideoFolder);
		m_videoInfoParams.folderList = lststrFolderList;
		emit signals_videoStatusChanged(m_videoInfoParams);
	}
}

void VideoManager::useVideoFolder(const QString& strVideoFolder, OperaDetails& stOperaDetails)
{
	QString currFolder = m_videoInfoParams.currFolder;
	if (strVideoFolder == currFolder)
	{
		stOperaDetails.isOk = false;
		stOperaDetails.strOpera = QStringLiteral("切换文件路径");
		stOperaDetails.strDetails = QStringLiteral("已被选中!");
	}
	else
	{
		m_videoInfoParams.currFolder = strVideoFolder;
		//emit signals_videoStatusChanged(m_videoInfoParams);
		emit signals_videoPlayListChanged(getCurrPlaylist(stOperaDetails));
	}
}

void VideoManager::deleteVideoFolder(const QString& strVideoFolder, OperaDetails& stOperaDetails)
{
	QStringList lststrFolderList = m_videoInfoParams.folderList;
	if (!lststrFolderList.contains(strVideoFolder))
	{
		stOperaDetails.isOk = false;
		stOperaDetails.strOpera = QStringLiteral("删除文件夹");
		stOperaDetails.strDetails = QStringLiteral("当前视频文件夹并不存在!");
	}
	else
	{
		lststrFolderList.removeOne(strVideoFolder);
		m_videoInfoParams.folderList = lststrFolderList;
		emit signals_videoStatusChanged(m_videoInfoParams);
	}
}

QString VideoManager::getCurrTime() const
{
	return m_videoInfoParams.currTime;
}

QString VideoManager::getCurrFile() const
{
	return m_videoInfoParams.currFile;
}

QString VideoManager::getCurrFolder() const
{
	return m_videoInfoParams.currFolder;
}

QStringList VideoManager::getCurrPlaylist(OperaDetails& stOperaDetails)
{
	QStringList videoList;
	QString currFolder = m_videoInfoParams.currFolder;
	if (isPathExists(currFolder)) {
		// 创建 QDir 对象，并设置路径
		QDir dir(currFolder);

		// 设置过滤器以仅显示视频文件
		QStringList nameFilters;
		nameFilters << "*.mp4" << "*.avi" << "*.mkv";  // 添加你希望支持的视频文件类型

		dir.setNameFilters(nameFilters);

		// 获取过滤后的文件列表
		videoList = dir.entryList();
		if (videoList.isEmpty())
		{
			stOperaDetails.isOk = false;
			stOperaDetails.strOpera = QStringLiteral("查找视频列表");
			stOperaDetails.strDetails = QStringLiteral("找不到当前支持的视频类型(mp4,avi,mkv),请检查后再试!");
		}
	}
	else {
		stOperaDetails.isOk = false;
		stOperaDetails.strOpera = QStringLiteral("查找视频列表");
		stOperaDetails.strDetails = QStringLiteral("找不到当前选中文件夹,所对应的路径,请检查后再试!");
	}
	return videoList;
}

QStringList VideoManager::getPlaylist(const QString& strVideoFolder, OperaDetails& stOperaDetails) const
{
	if (strVideoFolder.isEmpty())
	{
		stOperaDetails.isOk = false;
		stOperaDetails.strOpera = QStringLiteral("新增文件夹");
		stOperaDetails.strDetails = QStringLiteral("当前视频文件夹对了已有相同路径!");

	}
	return m_videoInfoParams.playlist;
}

QStringList VideoManager::getFolderList() const
{
	return m_videoInfoParams.folderList;
}

void VideoManager::readConfig()
{
	QJsonObject jsonObject = readJsonObjectFromSql();

	// Read from JSON object and set values
	if (jsonObject.contains("CurrTime"))
	{
		QJsonValue value = jsonObject.value("CurrTime");
		m_videoInfoParams.currTime = value.toString();
	}

	if (jsonObject.contains("CurrFile"))
	{
		QJsonValue value = jsonObject.value("CurrFile");
		m_videoInfoParams.currFile = value.toString();
	}

	// Read from JSON object and set values
	if (jsonObject.contains("Playlist")) {
		QJsonValue value = jsonObject.value("Playlist");
		m_videoInfoParams.playlist = value.toString().split(",");
	}

	if (jsonObject.contains("FolderList")) {
		QJsonValue value = jsonObject.value("FolderList");
		m_videoInfoParams.folderList = value.toString().split(",");
	}

	emit signals_videoStatusChanged(m_videoInfoParams);
}

void VideoManager::saveConfig()
{
	QJsonObject jsonObject;

	// Insert values into JSON object
	jsonObject.insert("CurrTime", m_videoInfoParams.currTime);
	jsonObject.insert("CurrFile", m_videoInfoParams.currFile);
	jsonObject.insert("Playlist", m_videoInfoParams.playlist.join(","));
	jsonObject.insert("FolderList", m_videoInfoParams.folderList.join(","));

	// Save JSON object to file or perform necessary operations
	saveJsonObjectFromSql(jsonObject);
}
