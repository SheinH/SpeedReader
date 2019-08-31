
#include "textdisplaywidget.h"
#include <Qt>
#include <QKeyEvent>
#include <QTextStream>
#include <QApplication>



TextDisplayWidget::TextDisplayWidget() :
workerThread(new WorkerThread())
{
    this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    this->setFocus();
    font.setPixelSize(30);
    setFont(font);
    setAlignment(Qt::AlignCenter);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    connect(workerThread, &WorkerThread::new_word, this, &TextDisplayWidget::change_word);
    workerThread->start();
}

void TextDisplayWidget::keyPressEvent(QKeyEvent *event) {
    const auto key = event->key();
    if (key == Qt::Key_P) {
        if(!workerThread->is_running){
            workerThread->is_running = true;
        }
    }
    else if(key == Qt::Key_Space){
        workerThread->is_paused = ! workerThread->is_paused;
    }
}

void TextDisplayWidget::change_word(const QString &word) {
    setText(word);
}
