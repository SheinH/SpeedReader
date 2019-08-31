#pragma once

#include <QLabel>
#include <QClipboard>
#include <QThread>
#include <QObject>
#include <QApplication>
#include <QRegularExpression>
#include <cmath>

class WorkerThread : public QThread {
Q_OBJECT

public:
    bool is_running = false;
    bool is_paused = false;
    double base_time = 200;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    void run() override {
        while(true) {
            if(is_running) {
                is_paused = false;
                auto text = QApplication::clipboard()->text();
                auto arr = text.split(QRegularExpression("[\n .]"));
                text.clear();
                for (const auto &str : arr) {
                    double time = base_time;
                    while(is_paused){

                    }
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
        }
    }
#pragma clang diagnostic pop
public slots:
    void speed_change(int new_speed){
        base_time = 60000.0 / new_speed;
    }

signals:

    void new_word(const QString &result);
};

class TextDisplayWidget : public QLabel {
Q_OBJECT
    QFont font;
public:
    WorkerThread *workerThread;
    TextDisplayWidget();

public slots:

    void change_word(const QString &word);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

