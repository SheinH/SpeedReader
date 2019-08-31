#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QClipboard>
#include <QSpinBox>
#include <memory>
#include "AppController.hpp"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    AppController controller(w);

    w.show();
    return a.exec();
}
