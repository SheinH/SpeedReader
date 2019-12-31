#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "textdisplaywidget.h"
#include <QGridLayout>
#include <QKeyEvent>
#include <QSpinBox>
#include <QtGlobal>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        clipboard(QGuiApplication::clipboard()) {
    ui->setupUi(this);
    textSpeedBox = findChild<QSpinBox *>("spinBox");
    textSizeBox = findChild<QSpinBox *>("textSizeBox");
    statusBar = findChild<QStatusBar *>("statusBar");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    auto grid = this->findChild<QGridLayout *>("gridLayout");
    grid->addWidget(&display, 0, 0);
    setTabOrder(&display, textSpeedBox);
    setTabOrder(textSpeedBox, textSizeBox);
    this->setFixedSize(QSize(550, 400));

}

MainWindow::~MainWindow() {
    delete ui;
}

TextDisplayWidget &MainWindow::getDisplay() {
    return display;
}

