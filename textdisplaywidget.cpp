
#include "textdisplaywidget.h"
#include <Qt>
#include <QKeyEvent>
#include <QTextStream>


TextDisplayWidget::TextDisplayWidget()
{
    this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    this->setFocus();
    font.setPixelSize(30);
    setFont(font);
    setAlignment(Qt::AlignCenter);
}

void TextDisplayWidget::keyPressEvent(QKeyEvent *event) {
    emit keyPressed(event->key());
}

void TextDisplayWidget::change_word(const QString &word) {
    setText(word);
}
