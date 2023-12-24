#include <QLineEdit>
#include "VideoView.h"

VideoView::VideoView(QWidget* parent /*= nullptr*/)
	: QWidget(parent),
	mediaPlayer(new QMediaPlayer),
	videoWidget(new QVideoWidget(this)),
	audioOutput(new QAudioOutput)
{
	ui.setupUi(this);
	init();
}

VideoView::~VideoView()
{
}

void VideoView::init()
{
	mediaPlayer->setVideoOutput(videoWidget);
	mediaPlayer->setAudioOutput(audioOutput);
	ui.verticalLayout->addWidget(videoWidget);


	m_pStorageDetails = new QWidget(this);
	m_pStorageWidget = new StorageWidget(m_pStorageDetails);
	m_pStorageWidget->setStorageTime(150);
	m_pStorageWidget->setStorageDirection(StorageWidget::StorageBottom);
	m_pStorageWidget->setStorageOffset(150);

	m_pHBoxLayout = new QHBoxLayout(m_pStorageWidget);
	m_pStorageWidget->setLayout(m_pHBoxLayout);

	m_pVideoStorageView = new VideoStorageView(m_pStorageWidget);
	m_pHBoxLayout->addWidget(m_pVideoStorageView);

	m_pStorageTimer = new QTimer();
	m_pStorageTimer->setInterval(5000);
	m_pStorageTimer->setSingleShot(true);

	connect(m_pStorageTimer, &QTimer::timeout, this, &VideoView::videoStorageStatusChange);
}

void VideoView::resizeEvent(QResizeEvent* event)
{
	QRect Vrect = rect();
	m_pStorageDetails->setGeometry(Vrect);
	__super::resizeEvent(event);
}

void VideoView::mousePressEvent(QMouseEvent* event)
{
	videoStorageStatusChange();
	__super::mousePressEvent(event);
}

void VideoView::mouseReleaseEvent(QMouseEvent* event)
{
	__super::mouseReleaseEvent(event);
}

void VideoView::setCurrSource(const QString& fileName)
{
	mediaPlayer->setSource(QUrl::fromLocalFile(fileName));
}

void VideoView::videoStorageStatusChange()
{
	bool isStorage = m_pStorageWidget->getIsStorage();
	m_pStorageWidget->setIsStorage(!isStorage);
	if (true == !isStorage)
	{
		m_pStorageTimer->start();
	}
}

void VideoView::changePlayStatus()
{
	QMediaPlayer::PlaybackState ePlaybackState = mediaPlayer->playbackState();
	switch (ePlaybackState)
	{
	case QMediaPlayer::StoppedState:

		break;
	case QMediaPlayer::PlayingState:
		pause();
		break;
	case QMediaPlayer::PausedState:
		play();
		break;
	default:
		break;
	}
}

void VideoView::play()
{
	mediaPlayer->play();
}

void VideoView::pause()
{
	mediaPlayer->pause();
}

void VideoView::stop()
{
	mediaPlayer->stop();
}
