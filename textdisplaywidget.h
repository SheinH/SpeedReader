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
    void change_font_size(int newSize);
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
};

