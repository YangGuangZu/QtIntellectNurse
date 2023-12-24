#include <QPainter>
#include "CustProgressBar.h"
#include "Tool/UiCommonTool/UiCommonTool.h"

CustProgressBar::CustProgressBar(QWidget* parent)
    : QProgressBar(parent)
{
    connect(this, &QProgressBar::valueChanged, [=](int value) {
        if (value < maximum()) 
        {
            setStyleSheet("QProgressBar {\
            background: #EEF2FB;\
            border-radius: 15px;\
            text-align: center;\
            border: 0px solid #C0D3EB;\
            }\
            \
            QProgressBar:chunk {\
                border-bottom-left-radius: 14px;\
                border-bottom-right-radius: 14px;\
                background-color: #1593F4;\
            }");
        }
        else if (value == maximum())
        {
            setStyleSheet("QProgressBar {\
            background: #EEF2FB;\
            border-radius: 15px;\
            text-align: center;\
            border: 0px solid #C0D3EB;\
            }\
            \
            QProgressBar:chunk {\
                border-radius: 14px;\
                background-color: #1593F4;\
            }");
        }
        }
    );
}

void CustProgressBar::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event);
    QProgressBar::paintEvent(event);
    QPainter painter(this);

}