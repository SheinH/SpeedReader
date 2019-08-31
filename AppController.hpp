//
// Created by Shein Htike on 8/30/19.
//

#ifndef SPEEDREADER_APPCONTROLLER_HPP
#define SPEEDREADER_APPCONTROLLER_HPP


#include "mainwindow.h"
#include <QThread>

struct AppData {
    std::vector<QString> words;
    std::vector<QString>::iterator current_word;

    AppData();
};

class AppController : public QObject {
Q_OBJECT
    AppData data;
    MainWindow &mainWindow;
    TextDisplayWidget &display;
    unsigned int wpm;
    bool currently_running;
public:
    virtual ~AppController();

    void threadEventLoop();
private:

public:
    AppController(MainWindow &mainWindow);

signals:

    void change_word(const QString &newWord);
};


#endif //SPEEDREADER_APPCONTROLLER_HPP
