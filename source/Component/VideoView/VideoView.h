#pragma once

#include <QWidget>
#include <QVector>
#include <QTimer>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QHBoxLayout>
#include "Component/StorageWidget/StorageWidget.h"
#include "VideoStorageView/VideoStorageView.h"
#include "ui_VideoView.h"

class VideoView : public QWidget
{
	Q_OBJECT

public:
	VideoView(QWidget* parent = nullptr);
	~VideoView();

private:
	Ui::VideoViewClass ui;
	//视频详情节点
	QWidget*				m_pStorageDetails			= nullptr;
	QHBoxLayout*			m_pHBoxLayout				= nullptr;
	QMediaPlayer*			mediaPlayer					= nullptr;
	QVideoWidget*			videoWidget					= nullptr;
	QAudioOutput*			audioOutput					= nullptr;
	StorageWidget*			m_pStorageWidget			= nullptr;
	VideoStorageView*		m_pVideoStorageView			= nullptr;
	QTimer *				m_pStorageTimer				= nullptr;
private:
	void resizeEvent(QResizeEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
private:
	void init();
public:
	void setCurrSource(const QString& fileName);
public slots:
	void videoStorageStatusChange();
	void changePlayStatus();
	void play();
	void pause();
	void stop();
};
