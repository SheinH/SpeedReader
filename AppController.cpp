//
// Created by Shein Htike on 8/30/19.
//

#include "AppController.hpp"
#include <chrono>

AppController::AppController(MainWindow &mainWindow) :
        mainWindow(mainWindow),
        display(mainWindow.getDisplay()),
        currently_running(false),
        wpm(300) {
    connect(this, &AppController::change_word, &display, &TextDisplayWidget::change_word);
    data.current_word = data.words.begin();
    currently_running = true;
}

AppData::AppData() : current_word(words.begin()) {
}

void AppController::threadEventLoop() {
    if (data.current_word == data.words.end())
        data.current_word = data.words.begin();
    emit change_word(*data.current_word);
    data.current_word++;
}

AppController::~AppController() {
    currently_running = false;
}
