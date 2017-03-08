#ifndef MEDIADIRECTORIES_H
#define MEDIADIRECTORIES_H

#include <QObject>
#include <QFileDialog>
//#include <QString>
class MediaDirectories : public QObject
{
    Q_OBJECT
public:
    QStringList directoriesPaths;

    explicit MediaDirectories(QObject *parent = 0);
    void add();
    void remove(QString seekPath);
    void removeAll();
    void edit(int index);
    QStringList getList();
    //reading from QDataStream:
    friend QDataStream & operator>>(QDataStream & dStream, MediaDirectories &mediaDirectories);
    //saving to QDataStream:
    friend QDataStream & operator<<(QDataStream & dStream,const MediaDirectories &mediaDirectories);
    static QString getDirectoryPath();
private:
    void clearDirectoryPaths();

signals:

public slots:
};

#endif // MEDIADIRECTORIES_H
