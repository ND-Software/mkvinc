#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    QCoreApplication::addLibraryPath("C:/Qt/5.7/msvc2015_64/plugins/platforms/qwindows.dll");
    Login w;
    w.show();

    return a.exec();
}
