//
// Created by Shein Htike on 8/30/19.
//

#include "AppController.hpp"
#include "textdisplaywidget.h"
#include <QSpinBox>
#include <QtGlobal>
#include <QMutexLocker>

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
            thread.start();
        }

void AppController::keyInput(int key) {
    if (key == Qt::Key_P && data->is_paused) {
        QMutexLocker locker(&data->mutex);
        data->text = QApplication::clipboard()->text().split(QRegularExpression("[ .,—]+"));
        data->iterator = data->text.begin();
        data->is_paused = false;
    } else if (key == Qt::Key_Space) {
        data->is_paused = !data->is_paused;
    } else if (key == Qt::Key_Left && data->is_paused) {
        QMutexLocker locker(&data->mutex);
        if (data->iterator != data->text.begin()) {
            data->iterator--;
        }
        thread.update_word();
    } else if (key == Qt::Key_Right && data->is_paused) {
        QMutexLocker locker(&data->mutex);
        if (data->iterator != data->text.end()) {
            data->iterator++;
        }
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
    while (true) {
        while (data.is_paused) {
        }

        if (data.iterator != data.text.end()) {
            data.mutex.lock();
            const auto &word = *data.iterator++;
            auto len = word.size();
            emit(new_word(word));
            data.mutex.unlock();
            double time = base_time;
            if (len > 7) {
                time *= 1.5;
            } else if (len < 4) {
                time /= 2;
            }
            QThread::msleep(llround(time));
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


void WorkerThread::speed_change(int new_speed) {
    base_time = 60000.0 / new_speed;
}

void WorkerThread::update_word() {
    const auto &word = *data.iterator;
    emit new_word(word);
}

#pragma clang diagnostic pop
