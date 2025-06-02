#include "explineedit.h"

ExpLineEdit::ExpLineEdit(QWidget *parent)
    : QLineEdit{parent}
{}

ExpLineEdit::ExpLineEdit(const QString &contents, QWidget *parent) : QLineEdit(contents, parent)
{}

void ExpLineEdit::focusOutEvent(QFocusEvent *)
{
    emit editingFinished();
}
