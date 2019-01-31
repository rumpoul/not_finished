#include "copyfiles.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    copyfiles w;
    w.show();

    return a.exec();
}
