#include "wham.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    wham w;
    w.show();

    return a.exec();
}
