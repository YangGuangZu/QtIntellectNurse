#pragma once

#include <QDialog>
#include <QVector>
#include "ui_BasicPopupView.h"

struct PopupInfoParam
{
	QString title;
	QString content;
};
using PopupParams = QList<PopupInfoParam>;

class BasicPopupView : public QDialog
{
	Q_OBJECT

public:
	BasicPopupView(PopupParams& stPopupParams, const QString& title, QWidget* parent = nullptr);
	~BasicPopupView();

private:
	Ui::BasicPopupViewClass ui;
	PopupParams & m_stPopupParams;
	PopupParams m_stTempPopupParams;
private:
	void init();
	void createRowInfo(PopupInfoParam & stPopupInfoParam);
private slots:
	void on_btnOk_clicked();
	void on_btnChannel_clicked();
};
