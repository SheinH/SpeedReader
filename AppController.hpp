//
// Created by Shein Htike on 8/30/19.
//

#ifndef SPEEDREADER_APPCONTROLLER_HPP
#define SPEEDREADER_APPCONTROLLER_HPP


#include "mainwindow.h"
#include <QThread>
#include <QMutex>

struct AppData {
    QStringList text;
    QStringList::iterator iterator;
    QMutex mutex;
    bool is_paused;

};

class AppController;

class WorkerThread : public QThread {
Q_OBJECT

public:
    bool is_running = false;
    bool is_paused = false;
    double base_time = 200;
    AppController *controller;

    AppData &data;

    WorkerThread(AppController *parent);

    void run() override;

    void update_word();

public slots:

    void speed_change(int new_speed);

signals:

    void new_word(const QString &result);
};

class AppController : public QObject {
Q_OBJECT
    MainWindow &mainWindow;
    TextDisplayWidget &display;
    unsigned int wpm;
    bool currently_running;
public:
    virtual ~AppController();

    AppData *data;

public slots:

    void keyInput(int key);
private:
    WorkerThread &thread;
public:
    AppController(MainWindow &mainWindow);

signals:
    void change_word(const QString &newWord);
};


#endif //SPEEDREADER_APPCONTROLLER_HPP
