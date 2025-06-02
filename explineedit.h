#ifndef EXPLINEEDIT_H
#define EXPLINEEDIT_H

#include <QLineEdit>
#include <QString>
#include <QWidget>

class ExpLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit ExpLineEdit(QWidget *parent = nullptr);
    explicit ExpLineEdit(const QString &contents, QWidget *parent = nullptr);
    void focusOutEvent(QFocusEvent *) override;
};

#endif // EXPLINEEDIT_H
