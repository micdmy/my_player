#ifndef ERRGUI_H
#define ERRGUI_H

#include <QObject>
#include <QString>
#include <QErrorMessage>
#include <QFile>
#include <QMessageBox>
class ErrGui : public QObject
{
    Q_OBJECT
public:
    static void error(QString message);
    static void error(QFile & file);
    static bool ask(QString);
signals:

public slots:
};

#endif // ERRGUI_H
