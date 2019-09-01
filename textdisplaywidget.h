#pragma once

#include <QLabel>
#include <QClipboard>
#include <QThread>
#include <QObject>
#include <QApplication>
#include <QRegularExpression>
#include <cmath>


class TextDisplayWidget : public QLabel {
Q_OBJECT
    QFont font;
public:
    TextDisplayWidget();

signals:

    void keyPressed(int);
public slots:
    void change_word(const QString &word);
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

