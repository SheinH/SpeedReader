#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <thread>
#include "textdisplaywidget.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QClipboard* clipboard;
    TextDisplayWidget display;
public:
    TextDisplayWidget &getDisplay();
    QSpinBox* textSpeedBox;
    QSpinBox* textSizeBox;
    QStatusBar* statusBar;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
