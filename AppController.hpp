//
// Created by Shein Htike on 8/30/19.
//

#ifndef SPEEDREADER_APPCONTROLLER_HPP
#define SPEEDREADER_APPCONTROLLER_HPP


#include "mainwindow.h"
#include <QThread>
#include <QMutex>
#include <QStateMachine>
#include <QWaitCondition>

class AppData {
public:
    QStringList text;
    QStringList::iterator iterator;
    QMutex mutex;
    volatile bool is_paused = true;
    QWaitCondition pauseCond;
    double base_time = 200000;
};

class AppController;

class WorkerThread : public QThread {
    Q_OBJECT
    void next_word();
public:
    AppController *controller;

    AppData &data;

    WorkerThread(AppController *parent);

    void run() override;

    void update_word();

signals:

    void new_word(const QString &result);

};

class AppController : public QObject {
    Q_OBJECT
    TextDisplayWidget &display;
    unsigned int wpm;
    bool currently_running;
public:
    MainWindow &mainWindow;
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
