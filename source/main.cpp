#include <QtWidgets/QApplication>
#include "view/QtIntellectNurse/QtIntellectNurse.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtIntellectNurse w;
    w.show();
    return a.exec();
}
