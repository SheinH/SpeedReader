#include "mainwindow.h"
#include <QApplication>
#include "AppController.hpp"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    AppController controller(w);
    w.show();


    return QApplication::exec();
}
