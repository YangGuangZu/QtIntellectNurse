#pragma once

#include <QWidget>
#include <QPoint>
#include <QTimer>
namespace Ui {
    class PopupTip;
} // namespace Ui
class PopupTip : public QWidget
{
	Q_OBJECT
public:
    PopupTip(const QString& strTitleInfo, const QString& strMsg, QtMsgType eMsgType, QWidget* parent = nullptr);
    ~PopupTip();
private:
    Ui::PopupTip* ui;
    QPoint m_pEnd_showPoint;
    int m_CurrentHeight;
    
    QPixmap m_pixIcon;

    QTimer* m_showTimer;
    QTimer* m_stayTimer;
    QTimer* m_closeTimer;

    int m_stayExeTime;
    double m_transparent;

    bool m_firstShow;
    bool m_enterEvent;

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event) override;
public:
    void updatePosition();

private:
    void init(const QString& strTitleInfo, const QString& strMsg, QtMsgType eMsgType);
    void showPopupTip();
    inline void deleteTimer(QTimer* timer);
signals:
    void sigClose(PopupTip*);
private slots:
    void slotMsgMove();
    void slotMsgStay();
    void slotMsgClose();
};
