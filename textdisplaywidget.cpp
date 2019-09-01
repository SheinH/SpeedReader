
#include "textdisplaywidget.h"
#include <Qt>
#include <QKeyEvent>
#include <QTextStream>
#include <QApplication>


TextDisplayWidget::TextDisplayWidget() {
    this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    this->setFocus();
    font.setPixelSize(30);
    setFont(font);
    setAlignment(Qt::AlignCenter);
    setText("Press P to read\n from clipboard");
}

void TextDisplayWidget::keyPressEvent(QKeyEvent *event) {
    emit keyPressed(event->key());
}

void TextDisplayWidget::change_word(const QString &word) {
    setText(word);
}

void TextDisplayWidget::change_font_size(int newSize) {
    font.setPixelSize(newSize);
    setFont(font);
}

void TextDisplayWidget::focusOutEvent(QFocusEvent *event) {
    setStyleSheet("QLabel {  color : gray; }");
}

void TextDisplayWidget::focusInEvent(QFocusEvent *event) {
    setStyleSheet("QLabel {  color : black; }");
}
