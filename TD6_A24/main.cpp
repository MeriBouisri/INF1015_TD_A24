#include "CashRegisterView.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CashRegisterView w;
    w.show();
    return a.exec();
}
