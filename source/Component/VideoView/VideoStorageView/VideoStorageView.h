#pragma once

#include <QWidget>
#include "Component/StorageWidget/StorageWidget.h"
#include "ui_VideoStorageView.h"

class VideoStorageView : public QWidget
{
	Q_OBJECT

public:
	VideoStorageView(QWidget* parent = nullptr);
	~VideoStorageView();

private:
	Ui::VideoStorageViewClass ui;
private:
	void init();
};
