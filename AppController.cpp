//
// Created by Shein Htike on 8/30/19.
//

#include "AppController.hpp"
#include "textdisplaywidget.h"
#include <QSpinBox>
#include <QtGlobal>
#include <iostream>

AppController::AppController(MainWindow &mainWindow) :
        mainWindow(mainWindow),
        display(mainWindow.getDisplay()),
        currently_running(false),
        wpm(300),
        thread(*(new WorkerThread(this))),
        data(new AppData()) {
    connect(this, &AppController::change_word, &display, &TextDisplayWidget::change_word);
    data->iterator = data->text.begin();
    connect(&thread, &WorkerThread::finished, &thread, &QObject::deleteLater);
    connect(&thread, &WorkerThread::new_word, &display, &TextDisplayWidget::change_word);
    connect(&display, &TextDisplayWidget::keyPressed, this, &AppController::keyInput);
    connect(mainWindow.textSpeedBox,QOverload<int>::of(&QSpinBox::valueChanged),[this](int n){
        constexpr double minute = 6e7;
        this->data->base_time = minute / n;
    });
    connect(mainWindow.textSizeBox,QOverload<int>::of(&QSpinBox::valueChanged),&display,&TextDisplayWidget::change_font_size);
    thread.start();
}

void AppController::keyInput(int key) {
    std::cout<< "KEY PRESSED: " << key << "\n";
    std::cout << "CLIPBOARD: \n" << QApplication::clipboard()->text().toStdString() << "\n";
    if (key == Qt::Key_P && data->is_paused) {
        QMutexLocker locker(&data->mutex);
        data->text = QApplication::clipboard()->text().split(QRegularExpression("[ .,—\n]+"));
        data->iterator = data->text.begin();
        data->is_paused = false;
    } else if (key == Qt::Key_Space) {
        data->is_paused = !data->is_paused;
        std::cout << "UNPAUSED\n";
        std::cout << "PAUSE STATE: " << data->is_paused << "\n";
    } else if ((key == Qt::Key_Left || key == Qt::Key_H )&& data->is_paused) {
        QMutexLocker locker(&data->mutex);
        if (data->iterator != data->text.begin()) {
            data->iterator--;
        }
        thread.update_word();
    } else if ((key == Qt::Key_Right || key== Qt::Key_L) && data->is_paused) {
        QMutexLocker locker(&data->mutex);
        if (data->iterator != data->text.end()) {
            data->iterator++;
        }
        thread.update_word();
    }
    else if (key == Qt::Key_R){
        QMutexLocker locker(&data->mutex);
        data->iterator = data->text.begin();
        thread.update_word();
    }

}

AppController::~AppController() {
}

WorkerThread::WorkerThread(AppController *parent) : controller(parent), data(*parent->data) {
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void WorkerThread::run() {
    std::cout << "THREAD STARTED \n";
    bool writeonce = true;
    while (true) {
        if(writeonce){
            writeonce =false;
            std::cout << "INNER LOOP REACHED\n";
        }
        while (data.is_paused) {
        }
        std::cout << "UNPAUSED\n";
        if (data.iterator != data.text.end()) {
            data.mutex.lock();
            const auto &word = *data.iterator++;
            auto len = word.size();
            emit(new_word(word));
            std::cout << "NEW WORD EMITTED \n";
            double time = data.base_time;
            data.mutex.unlock();
            if (len > 5) {
                time *= len / 5.0;
            } else if (len < 4) {
                time /= 2;
            }
            QThread::usleep(lround(time));
        } else
            data.is_paused = true;

        while (data.is_paused) {
        }
    }
    /*
    while (true) {
        if (is_running) {
            is_paused = false;
            while (iterator == text.end()) {}
            while (is_paused) {}
            const auto &str = *iterator;
            double time = base_time;
            emit new_word(str);
            if (str.size() > 7) {
                time *= 1.5;
            } else if (str.size() < 4) {
                time /= 2;
            }
            QThread::msleep(llround(time));
        }
        is_running = false;
    }
     */
}



void WorkerThread::update_word() {
    if(data.iterator == data.text.end())
        return;
    const auto &word = *data.iterator;
    emit new_word(word);
}

#pragma clang diagnostic pop
